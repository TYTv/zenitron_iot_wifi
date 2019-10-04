
#include "start.h"

#define MAX_LINE_LENGTH  (128)
#define MAX_HISTORY_LENGTH (20)
#define MAX_NUM_COMMAND_TABLE  (8)


#define DIAGNOSTICS_COMMANDS \
{ "json_parser",  json_parser,  0, NULL, NULL,"",  "json data parser" }, \
//{ "hts221",  hts221_get,  0, NULL, NULL,"",  "get HTS221 temperature" }, \
//{ "lis2dh12",  lis2dh12_get,  0, NULL, NULL,"",  "get LIS2DH12 accelerometer" }, \
//{ "kx122",  kx122_get,  0, NULL, NULL,"",  "get KX122 accelerometer" }, \
//{ "icm20602",  icm20602_get,  0, NULL, NULL,"",  "get ICM20602 accelerometer" }, \


static char line_buffer[MAX_LINE_LENGTH];
static char history_buffer_storage[MAX_LINE_LENGTH * MAX_HISTORY_LENGTH];

static const command_t init_commands[] = {
        DIAGNOSTICS_COMMANDS
        CMD_TABLE_END
};

void application_start( )
{
    /* Initialise the device */
    wiced_init();

    ping_start();


    /* enable command line interface */
    WPRINT_APP_INFO( ( "\r\nType help to know more about commands ...\r\n" ) );
    command_console_init( STDIO_UART, MAX_LINE_LENGTH, line_buffer, MAX_HISTORY_LENGTH, history_buffer_storage, " " );
    console_add_cmd_table( init_commands );

}
