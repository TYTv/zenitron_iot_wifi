
#include "start.h"

wiced_result_t sens_init( wiced_i2c_device_t dev, char *partname )
{
    /* Initialize I2C */
    if ( wiced_i2c_init( &dev ) != WICED_SUCCESS ){
        WPRINT_APP_INFO( ( "I2C Initialization Failed\n" ) );
        return WICED_ERROR;
    }

    /* Probe I2C bus */
    if(  wiced_i2c_probe_device( &dev, NUM_I2C_MESSAGE_RETRIES )  != WICED_TRUE ){
        WPRINT_APP_INFO( ( "Failed to connect to %s device; addr 0x%x\n", partname, dev.address ) );
        return WICED_ERROR;
    }
    return WICED_SUCCESS;
}

wiced_result_t sens_chkid( wiced_i2c_device_t dev, char *partname, uint8_t id, uint8_t id_def )
{
    if( id != id_def ){
        WPRINT_APP_INFO( ( "Failed to read ID from %s device(0x%x); addr 0x%x\n", partname, id, dev.address ) );
        return WICED_ERROR;
    }
    WPRINT_APP_INFO( ( "%s device(0x%x) at address 0x%x\n", partname, id, dev.address ) );
    return WICED_SUCCESS;
}


void sens_w( wiced_i2c_device_t *dev, uint8_t reg, uint8_t *dat, uint8_t len )
{
    uint8_t tmp[1+len];
    tmp[0] = reg;
    memcpy( &tmp[1], &dat, len );
    wiced_i2c_write( dev, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, tmp, 1+len );
}

void sens_r( wiced_i2c_device_t *dev, uint8_t reg, uint8_t *dat, uint8_t len )
{
    wiced_i2c_write( dev, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, &reg, 1 );
    wiced_i2c_read( dev, WICED_I2C_START_FLAG | WICED_I2C_STOP_FLAG, dat, len );
}

void sens_wb( wiced_i2c_device_t *dev, uint8_t reg, uint8_t dat )
{
    sens_w(dev,reg,dat,1);
}

uint8_t sens_rb( wiced_i2c_device_t *dev, uint8_t reg )
{
    uint8_t result = 0x00;
    sens_r(dev,reg,&result,1);
    return result;
}

