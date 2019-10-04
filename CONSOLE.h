
#include "command_console.h"

#define MAX_LINE_LENGTH  (128)
#define MAX_HISTORY_LENGTH (20)
#define MAX_NUM_COMMAND_TABLE  (8)

#define DIAGNOSTICS_COMMANDS \
{ "json_parser",  json_parser,  0, NULL, NULL,"",  "json data parser" }, \
//{ "hts221",  hts221_get,  0, NULL, NULL,"",  "get HTS221 temperature" }, \
//{ "lis2dh12",  lis2dh12_get,  0, NULL, NULL,"",  "get LIS2DH12 accelerometer" }, \
//{ "kx122",  kx122_get,  0, NULL, NULL,"",  "get KX122 accelerometer" }, \
//{ "icm20602",  icm20602_get,  0, NULL, NULL,"",  "get ICM20602 accelerometer" }, \

void console_start(void);

