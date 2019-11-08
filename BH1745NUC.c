
#include "start.h"

uint8_t bh1745nuc_init_success = 0;

static wiced_i2c_device_t i2c_device_bh1745nuc =
{
    .port = WICED_I2C_2,  //I2C_1
    .address = BH1745NUC_DEVICE_ADDRESS_39,
    .address_width = I2C_ADDRESS_WIDTH_7BIT,
    .speed_mode = I2C_STANDARD_SPEED_MODE,
};

wiced_result_t bh1745nuc_init(void)
{

    if( sens_init( i2c_device_bh1745nuc, BH1745NUC_PartName ) != WICED_SUCCESS ){
        return WICED_ERROR;
    }

    if( sens_chkid( i2c_device_bh1745nuc, BH1745NUC_PartName, sens_rb(&i2c_device_bh1745nuc,BH1745NUC_SYSTEM_CONTROL) & 0b00111111, BH1745NUC_Part_ID_Default ) != WICED_SUCCESS ){
        return WICED_ERROR;
    }

    sens_wb( &i2c_device_bh1745nuc, BH1745NUC_MODE_CONTROL1, 0x00 );
    sens_wb( &i2c_device_bh1745nuc, BH1745NUC_MODE_CONTROL2, 0x12 );
    sens_wb( &i2c_device_bh1745nuc, BH1745NUC_MODE_CONTROL3, 0x02 );

    bh1745nuc_init_success = 1;
    return WICED_SUCCESS;
}


int bh1745nuc_get(int argc, char *argv[])
{
    if( bh1745nuc_init_success == 0 ){
        return bh1745nuc_init_success;
    }

    uint16_t data[4] = {NULL};
    sens_r( &i2c_device_bh1745nuc, BH1745NUC_RED_DATA_LSBs, &data, sizeof(data) );

    // make json command and parser
    char par0[] = {"json_parser"};
    char par1[] = {"7"};
    char par2[rawsiz] = {NULL};
    sprintf(par2, "{\"BH1745_RED\":%d,\"BH1745_GREEN\":%d,\"BH1745_BLUE\":%d,\"BH1745_CLEAR\":%d}", data[0], data[1], data[2], data[3]);
    char *cmd[] = {par0, par1, par2};
    json_parser(3, cmd);

    // show to uart
    WPRINT_APP_INFO(( "%s %s %s\r\n", cmd[0], cmd[1], cmd[2] ));

    return 0;
}
