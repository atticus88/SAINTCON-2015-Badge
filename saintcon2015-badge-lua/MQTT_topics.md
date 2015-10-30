# MQTT Topic Layout
## General Topics
### global/badges/commands
Used to send commands to badge. Possible commands like upgrade or schedule update.
- **QOS:** 2
- **Retain:** false
- **Message Format:** cjson
- **Example Message:** {"cmd":"run","content":"update.lua"}

### global/badges/bcastmessage
Used to send broadcast messages to all badges to be displayed on the badge.
- **QOS:** 2
- **Retain:** false
- **Message Format:** String max length ??
- **Example Message:** Lunch is ending.

## Badge Specific Topics
### {to,from}/badge/```<Badge_ID>```/hackerscore
Used to update the badge on the current score.
- **QOS:** 1
- **Retain:** false
- **Message Format:** Single integer with score.
- **Example Message:** 15435

### {to,from}/badge/```<Badge_ID>```/location
Location of the badge provided by the MSE.
- **QOS:**
- **Retain:** false
- **Message Format:** Unknown
- **Example Message:**

### {to,from}/badge/```<Badge_ID>```/pmessage
Private message directed towards a individual badge.
- **QOS:** 1
- **Retain:** false
- **Message Format:** String max length ??
- **Example Message:** Attendee you left your coat. See reg to get it back.

### {to,from}/badge/```<Badge_ID>```/info
Used by reg to send badge attendee information such as name and handle.
- **QOS:** 1
- **Retain:** true
- **Message Format:** cjson
- **Example Message:** {"first_name":"myfirst", "last_name":"mylast","org":"coolhackers inc","handle":"coolhacker"}
