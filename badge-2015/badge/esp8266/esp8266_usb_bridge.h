#define  USART               USARTE0
#define  USART_RX_Vect       USARTE0_RXC_vect
#define  USART_DRE_Vect      USARTE0_DRE_vect
#define  USART_SYSCLK        SYSCLK_USART0
#define  USART_PORT          PORTE
#define  USART_PORT_PIN_TX   0x08  // PC3 (TXC0)
#define  USART_PORT_PIN_RX   0x04  // PC2 (RXC0)
#define  USART_PORT_SYSCLK   SYSCLK_PORT_E

void uart_config(uint8_t port, usb_cdc_line_coding_t * cfg);
void uart_open(uint8_t port);
void uart_close(uint8_t port);
void uart_rx_notify(uint8_t port);
bool main_cdc_enable(uint8_t port);
void main_cdc_disable(uint8_t port);
