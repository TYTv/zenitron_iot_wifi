//#include "wiced.h"
//#include "WEB.h"
//#include "http_server.h"
//#include "gedday.h"
//#include "wiced_resource.h"
//#include "resources.h"
//#include "ping_webserver_dct.h"

#include "start.h"

void ota_start(void)
{

    wiced_config_soft_ap_t* soft_ap;
    wiced_result_t          result;

    wiced_init();

    result = wiced_network_up( WICED_AP_INTERFACE, WICED_USE_INTERNAL_DHCP_SERVER, &device_init_ip_settings );
    if ( result != WICED_SUCCESS ){
        WPRINT_APP_INFO(("Network up error!\r\n"));
        return;
    }

    result = wiced_dct_read_lock( (void**) &soft_ap, WICED_TRUE, DCT_WIFI_CONFIG_SECTION, OFFSETOF(platform_dct_wifi_config_t, soft_ap_settings), sizeof(wiced_config_soft_ap_t) );
    if ( result != WICED_SUCCESS ){
        WPRINT_APP_INFO(("DCT read lock error!\r\n"));
        return;
    }

    wiced_ota_server_start( WICED_AP_INTERFACE );
    WPRINT_APP_INFO(("====== Entry OTA Mode ======\r\n"));

    char ssid_name[65] = { 0 };
    memcpy(ssid_name, soft_ap->SSID.value, soft_ap->SSID.length);
    WPRINT_APP_INFO( ( "SoftAP start, AP name: %s\r\n", ssid_name));
    memset(ssid_name, 0x00, sizeof(ssid_name));
    memcpy(ssid_name, soft_ap->security_key, soft_ap->security_key_length);
    WPRINT_APP_INFO( ( "           passphrase: %s\r\n\r\n", ssid_name));
    wiced_dct_read_unlock( soft_ap, WICED_FALSE );

    while(1){;}
}
