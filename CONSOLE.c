
#include "start.h"

static char line_buffer[MAX_LINE_LENGTH];
static char history_buffer_storage[MAX_LINE_LENGTH * MAX_HISTORY_LENGTH];

static const command_t init_commands[] = {
        DIAGNOSTICS_COMMANDS
        CMD_TABLE_END
};

void console_start(void)
{
    /* enable command line interface */
    WPRINT_APP_INFO( ( "\r\nType help to know more about commands ...\r\n" ) );
    command_console_init( STDIO_UART, MAX_LINE_LENGTH, line_buffer, MAX_HISTORY_LENGTH, history_buffer_storage, " " );
    console_add_cmd_table( init_commands );
}
