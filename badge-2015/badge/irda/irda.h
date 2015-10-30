#include "asf.h"
#include "tc.h"
#include "pwm.h"

typedef struct {
	// The fields are ordered to reduce memory over caused by struct-padding
	uint8_t       rcvstate;        // State Machine state
	uint8_t       recvpin;         // Pin connected to IR data from detector
	uint8_t       rawlen;          // counter of entries in rawbuf
	unsigned int  timer;           // State timer, counts 50uS ticks.
	unsigned int  rawbuf[101];  // raw data
	uint8_t       overflow;        // Raw buffer overflow occurred
}
irparams_t;

typedef enum {
		UNKNOWN      = -1,
		UNUSED       =  0,
		RC5,
		RC6,
		NEC,
		SONY,
		PANASONIC,
		JVC,
		SAMSUNG,
		WHYNTER,
		AIWA_RC_T501,
		LG,
		SANYO,
		MITSUBISHI,
		DISH,
		SHARP,
		DENON,
		PRONTO,
}
decode_type_t;

typedef struct {
		decode_type_t          decode_type;  // UNKNOWN, NEC, SONY, RC5, ...
		unsigned int           address;      // Used by Panasonic & Sharp [16-bits]
		unsigned long          value;        // Decoded value [max 32-bits]
		int                    bits;         // Number of bits in decoded value
		volatile unsigned int  *rawbuf;      // Raw intervals in 50uS ticks
		int                    rawlen;       // Number of records in rawbuf
		int                    overflow;     // true iff IR raw code too long
}
decode_results;

#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261
#define SEND_HZ 38

// ISR State-Machine : Receiver States
#define STATE_IDLE      2
#define STATE_MARK      3
#define STATE_SPACE     4
#define STATE_STOP      5
#define STATE_OVERFLOW  6

#define SONY_BITS                   12
#define SONY_HDR_MARK             2400
#define SONY_HDR_SPACE             600
#define SONY_ONE_MARK             1200
#define SONY_ZERO_MARK             600
#define SONY_RPT_LENGTH          45000
#define SONY_DOUBLE_SPACE_USECS    500  // usually ssee 713 - not using ticks as get number wrapround
#define REPEAT 0xFFFFFFFF

#define NEC_BITS          32
#define NEC_HDR_MARK    9000
#define NEC_HDR_SPACE   4500
#define NEC_BIT_MARK     560
#define NEC_ONE_SPACE   1690
#define NEC_ZERO_SPACE   560
#define NEC_RPT_SPACE   2250

#define MARK_EXCESS    100
// microseconds per clock interrupt tick
#define USECPERTICK    50

// Upper and Lower percentage tolerances in measurements
#define TOLERANCE       25
#define LTOL            (1.0 - (TOLERANCE/100.))
#define UTOL            (1.0 + (TOLERANCE/100.))

#define TICKS_LOW(us)   ((int)(((us)*LTOL/USECPERTICK)))
#define TICKS_HIGH(us)  ((int)(((us)*UTOL/USECPERTICK + 1)))


int  MATCH       (int measured, int desired);
int  MATCH_MARK  (int measured_ticks, int desired_us);
int  MATCH_SPACE (int measured_ticks, int desired_us);

volatile irparams_t  irparams;
struct pwm_config pwm_cfg;
     
void irda_init(void);
void irda_decoder(void);
bool decode(decode_results *results);
void irda_send(uint32_t data, uint8_t nbits);

// Allow all parts of the code access to the ISR data
// NB. The data can be changed by the ISR at any time, even mid-function
// Therefore we declare it as "volatile" to stop the compiler/CPU caching it