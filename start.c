
#include "start.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Static Function Declarations
 ******************************************************/

/******************************************************
 *               Variable Definitions
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

#include "stdint.h"
#include "string.h"
#include "platform_peripheral.h"
#include "platform_isr.h"
#include "platform_isr_interface.h"
#include "wwd_rtos.h"
#include "wwd_assert.h"

/******************************Application start/main function.**********************************/
void application_start( )
{
    /* Initialise the device */
    wiced_init();

    wiced_gpio_init( WICED_GPIO_6, INPUT_PULL_UP );
    if ( wiced_gpio_input_get( WICED_GPIO_6 ) == WICED_FALSE ){
        ota_start();
        while(1){;}
    }else{
        web_start();
    }

    hts221_init();      /* temperature device */
    lis2dh12_init();    /* accelerometer device */
    kx122_init();       /* accelerometer device */
    icm20602_init();    /* accelerometer device */
    bh1745nuc_init();   /* color device */

    console_start();

}
