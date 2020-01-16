
#include "start.h"

#ifdef AWCU359
#define BOOT_MODE_BTN   WICED_GPIO_6
#elif AWCU427
#define BOOT_MODE_BTN   WICED_GPIO_6
#else
#define BOOT_MODE_BTN   WICED_GPIO_1
#endif

void factory_start(void)
{
    uint8_t mode = boot_mode_read_dct();
    WPRINT_APP_INFO( ( "\r\nBoot mode : %d\r\n", mode ) );

    wiced_gpio_init( BOOT_MODE_BTN, INPUT_PULL_UP );
    if ( wiced_gpio_input_get( BOOT_MODE_BTN ) == WICED_FALSE ){
        mode++;
        if( mode >= boot_num ){
            mode = boot_normal;
        }
        boot_mode_write_dct( mode );
        WPRINT_APP_INFO( ( "Waiting for release button, then reboot entry factory mode.\r\n" ) );
        while( wiced_gpio_input_get( BOOT_MODE_BTN ) == WICED_FALSE ){;}
        reboot_now();
    }

    switch( mode )
    {
        case boot_normal:
            return;
        case boot_ota:
            boot_mode_write_dct(boot_normal);
            ota_start();
            break;
        default:
            boot_mode_write_dct(boot_normal);
            reboot_now();
            break;
    }
}

uint8_t boot_mode_read_dct(void)
{
    dct_app_boot* app_dct = NULL;
    uint8_t result;

    wiced_dct_read_lock( (void**) &app_dct, WICED_FALSE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    result = app_dct->dct_next_boot_mode;

    wiced_dct_read_unlock( app_dct, WICED_FALSE );

    return result;
}


void boot_mode_write_dct(uint8_t mode)
{
    dct_app_boot* app_dct = NULL;
    uint32_t time_before_writing;
    uint32_t time_after_writing;
    uint8_t before_mode;

    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    before_mode = app_dct->dct_next_boot_mode;
    app_dct->dct_next_boot_mode = mode;
    wiced_time_get_time(&time_before_writing);
    wiced_dct_write( (const void*) &(app_dct->dct_next_boot_mode), DCT_APP_SECTION, OFFSETOF(dct_app_boot, dct_next_boot_mode), sizeof(uint8_t) );
    wiced_time_get_time(&time_after_writing);

    wiced_dct_read_unlock( app_dct, WICED_TRUE );

    WPRINT_APP_INFO( ( "Change next boot mode %d -> %d (time=%ldms)\r\n", before_mode, mode, time_after_writing - time_before_writing) );
}

void reboot_now(void)
{
    WPRINT_APP_INFO(( "Rebooting...\n" ));
    wiced_rtos_delay_milliseconds( 1000 );
    wiced_framework_reboot();
}
