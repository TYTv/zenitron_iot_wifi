#include "KX122.h"

//char kx122_data[kx122_siz];
//static wiced_timed_event_t sensor_timed_event;
uint8_t kx122_init_success = 0;

static wiced_i2c_device_t i2c_device_kx122 =
{
#ifdef AWCU359              // for AW-CU359 EVB use
    .port = WICED_I2C_2,
#elif AWCU427               // for AW-CU427 EVB use
    .port = WICED_I2C_4,
    .flags = I2C_DEVICE_NO_DMA,
#else
    .port = WICED_I2C_1,
#endif
    .address = KX122_DEVICE_ADDRESS_1E,
    .address_width = I2C_ADDRESS_WIDTH_7BIT,
    .speed_mode = I2C_STANDARD_SPEED_MODE,
};

wiced_result_t kx122_init(void)
{

//    uint8_t wbuf[8];
//    uint8_t rbuf[8];
//
//    /* Initialize I2C */
//    if ( wiced_i2c_init( &i2c_device_kx122 ) != WICED_SUCCESS )
//    {
//        WPRINT_APP_INFO( ( "I2C Initialization Failed\n" ) );
//        return WICED_ERROR;
//    }
//
//    /* Probe I2C bus for accelerometer */
//    if(  wiced_i2c_probe_device( &i2c_device_kx122, NUM_I2C_MESSAGE_RETRIES )  != WICED_TRUE )
//    {
//        WPRINT_APP_INFO( ( "Failed to connect to KX122 device; addr 0x%x\n", i2c_device_kx122.address ) );
//        return WICED_ERROR;
//    }
//
////    wbuf[0] = KX122_WHO_AM_I;
////    wiced_i2c_write( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, wbuf, 1 );
////    wiced_i2c_read( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, rbuf, 1 );
////    if( rbuf[0] != KX122_WHO_AM_I_WIA_ID )
//    if( sens_rb(&i2c_device_kx122, KX122_WHO_AM_I) != KX122_WHO_AM_I_WIA_ID )
//    {
//        WPRINT_APP_INFO( ( "Failed to read WHOAMI from KX122 device; addr 0x%x\n", i2c_device_kx122.address ) );
//        return WICED_ERROR;
//    }
//    WPRINT_APP_INFO( ( "KX122 device (0x%x) at address 0x%x\n", rbuf[0], i2c_device_kx122.address ) );

    if( sens_init( i2c_device_kx122, KX122_PartName ) != WICED_SUCCESS ){
        return WICED_ERROR;
    }

    if( sens_chkid( i2c_device_kx122, KX122_PartName, sens_rb(&i2c_device_kx122,KX122_WHO_AM_I), KX122_WHO_AM_I_WIA_ID ) != WICED_SUCCESS ){
        return WICED_ERROR;
    }



//    wbuf[0] = KX122_CNTL1;
//    wbuf[1] = KX122_CNTL1_PC1 | KX122_CNTL1_RES | KX122_CNTL1_GSEL_8G;
//    wiced_i2c_write( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, wbuf, 2 );
//    sens_w( &i2c_device_kx122, KX122_CNTL1, KX122_CNTL1_PC1 | KX122_CNTL1_RES | KX122_CNTL1_GSEL_8G, 1 );
    sens_wb( &i2c_device_kx122, KX122_CNTL1, KX122_CNTL1_PC1 | KX122_CNTL1_RES | KX122_CNTL1_GSEL_8G );

//    uint8_t chk = sens_rb(&i2c_device_kx122, KX122_CNTL1);
//    WPRINT_APP_INFO( ( "raw:%x\r\n", KX122_CNTL1,chk ) );
//
//    sens_wb(&i2c_device_kx122, KX122_CNTL1, KX122_CNTL1_RES|KX122_CNTL1_GSEL_8G);
//    chk = sens_rb(&i2c_device_kx122, KX122_CNTL1);
//    WPRINT_APP_INFO( ( "res:%x\r\n", KX122_CNTL1,chk ) );

//    switch( wbuf[1] & KX122_CNTL1_GSEL_MASK ) {

    switch( sens_rb(&i2c_device_kx122, KX122_CNTL1) & KX122_CNTL1_GSEL_MASK ) {
      case KX122_CNTL1_GSEL_2G:
//          _g_sens = 16384;
          WPRINT_APP_INFO(("GSEL: 2G\r\n"));
          break;
      case KX122_CNTL1_GSEL_4G:
//          _g_sens = 8192;
          WPRINT_APP_INFO(("GSEL: 4G\r\n"));
          break;
      case KX122_CNTL1_GSEL_8G:
//          _g_sens = 4096;
          WPRINT_APP_INFO(("GSEL: 8G\r\n"));
          break;
      default:
          break;
    }

//    wbuf[0] = KX122_ODCNTL;
//    wbuf[1] = KX122_ODCNTL_OSA_50;
//    wiced_i2c_write( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, wbuf, 2 );
    sens_wb(&i2c_device_kx122, KX122_ODCNTL, KX122_ODCNTL_OSA_50);

//    wbuf[0] = KX122_CNTL1;
//    wiced_i2c_write( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, wbuf, 1 );
//    wiced_i2c_read( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, rbuf, 1 );
//
//    wbuf[0] = KX122_CNTL1;
//    wbuf[1] = rbuf[0] | KX122_CNTL1_PC1;
//    wiced_i2c_write( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, wbuf, 2 );

//    uint8_t tmp = sens_rb(&i2c_device_kx122, KX122_CNTL1);
//    tmp |= KX122_CNTL1_PC1;
//    sens_wb(&i2c_device_kx122, KX122_CNTL1, tmp );

    // get sensor data service
//    wiced_rtos_register_timed_event( &sensor_timed_event, WICED_NETWORKING_WORKER_THREAD, &kx122_get, 100, 0 );

    kx122_init_success = 1;

    return WICED_SUCCESS;
}


int kx122_get(int argc, char *argv[])
{
    if( kx122_init_success == 0 ){
        return kx122_init_success;
    }

    uint8_t wbuf[1];
    uint8_t rbuf[6];
    int16_t acc[3];
    uint16_t _g_sens = 0;
    float data[3];

    // i2c read setting
//    wbuf[0] = KX122_CNTL1;
//    wiced_i2c_write( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, wbuf, 1 );
//    wiced_i2c_read( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, rbuf, 1 );

//    switch( rbuf[0] & KX122_CNTL1_GSEL_MASK ) {
    switch( sens_rb(&i2c_device_kx122, KX122_CNTL1) & KX122_CNTL1_GSEL_MASK ) {
      case KX122_CNTL1_GSEL_2G:
          _g_sens = 16384;
//          WPRINT_APP_INFO(("GSEL: 2G\r\n"));
          break;
      case KX122_CNTL1_GSEL_4G:
          _g_sens = 8192;
//          WPRINT_APP_INFO(("GSEL: 4G\r\n"));
          break;
      case KX122_CNTL1_GSEL_8G:
          _g_sens = 4096;
//          WPRINT_APP_INFO(("GSEL: 8G\r\n"));
          break;
      default:
          break;
    }

    // i2c read x y z data
//    wbuf[0] = KX122_XOUT_L;
//    wiced_i2c_write( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, wbuf, 1 );
//    wiced_i2c_read( &i2c_device_kx122, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, rbuf, 6 );
    sens_r(&i2c_device_kx122, KX122_XOUT_L, &rbuf, 6);

    acc[0] = ((int16_t)rbuf[1] << 8) | (rbuf[0]);
    acc[1] = ((int16_t)rbuf[3] << 8) | (rbuf[2]);
    acc[2] = ((int16_t)rbuf[5] << 8) | (rbuf[4]);

    // Convert LSB to g
    data[0] = (float)acc[0] / _g_sens;
    data[1] = (float)acc[1] / _g_sens;
    data[2] = (float)acc[2] / _g_sens;

    // make json command and parser
    char par0[] = {"json_parser"};
    char par1[] = {"3"};
    char par2[rawsiz] = {NULL};
    sprintf(par2, "{\"KX122_X(mG)\":%f,\"KX122_Y(mG)\":%f,\"KX122_Z(mG)\":%f}", data[0]*1000, data[1]*1000, data[2]*1000);
    char *cmd[] = {par0, par1, par2};
    json_parser(3, cmd);

    // show to uart
    WPRINT_APP_INFO(( "%s %s %s\r\n", cmd[0], cmd[1], cmd[2] ));

}
