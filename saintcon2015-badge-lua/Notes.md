# Programming Notes
Programming items that need tracking.

Watch module names. If they conflict with ROM names you'll get strange results.

## Timer Usage
7 timers are available in NodeMCU. The following IDs are in use in this firmware.

ID | repeat | File       | Use
-- | ------ | ---------- | -----------------------------
0  | false  | init.lua   | 5 sec boot safety delay
0  | true   | scwifi.lua | no AP found random reconnect
1  | true   | scmqtt.lua | badgeinfo autosave timer
2  | true   | scmqtt.lua | mqtt connection backoff timer
3  | false  | update.lua | Update restart wait timer
4  |        |            |
5  |        |            |
6  |        |            |

## Flash Usage

File           | Use
-------------- | ------------------------------------------------------
badgeinfo.json | Storage of basic badge information
creds.json     | Storage of alternate credentials used for mqtt client.
