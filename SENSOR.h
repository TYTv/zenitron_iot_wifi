
#define NUM_I2C_MESSAGE_RETRIES   (3)


wiced_result_t sens_init( wiced_i2c_device_t dev, char *partname );
wiced_result_t sens_chkid( wiced_i2c_device_t dev, char *partname, uint8_t id, uint8_t id_def );

void sens_w( wiced_i2c_device_t *dev, uint8_t reg, uint8_t *dat, uint8_t len );
void sens_r( wiced_i2c_device_t *dev, uint8_t reg, uint8_t *dat, uint8_t len );
void sens_wb( wiced_i2c_device_t *dev, uint8_t reg, uint8_t dat );
uint8_t sens_rb( wiced_i2c_device_t *dev, uint8_t reg );
