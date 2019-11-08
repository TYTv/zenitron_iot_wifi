#
# Copyright 2019, Cypress Semiconductor Corporation or a subsidiary of 
 # Cypress Semiconductor Corporation. All Rights Reserved.
 # This software, including source code, documentation and related
 # materials ("Software"), is owned by Cypress Semiconductor Corporation
 # or one of its subsidiaries ("Cypress") and is protected by and subject to
 # worldwide patent protection (United States and foreign),
 # United States copyright laws and international treaty provisions.
 # Therefore, you may use this Software only as provided in the license
 # agreement accompanying the software package from which you
 # obtained this Software ("EULA").
 # If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 # non-transferable license to copy, modify, and compile the Software
 # source code solely for use in connection with Cypress's
 # integrated circuit products. Any reproduction, modification, translation,
 # compilation, or representation of this Software except as specified
 # above is prohibited without the express written permission of Cypress.
 #
 # Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 # EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 # WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 # reserves the right to make changes to the Software without notice. Cypress
 # does not assume any liability arising out of the application or use of the
 # Software or any product or circuit described in the Software. Cypress does
 # not authorize its products for use in any products where a malfunction or
 # failure of the Cypress product may reasonably be expected to result in
 # significant property damage, injury or death ("High Risk Product"). By
 # including Cypress's product in a High Risk Product, the manufacturer
 # of such system or application assumes all risk of such use and in doing
 # so agrees to indemnify Cypress against all liability.
#

NAME := zenitron_iot_wifi

$(NAME)_SOURCES    += start.c \
                      WEB.c \
                      JSON_CMD.c \
                      frozen.c \
                      CONSOLE.c \
                      SENSOR.c \

#------ add snesor ------
$(NAME)_SOURCES    += HTS221.c \
                      LIS2DH12.c \
                      KX122.c \
                      ICM20602.c \
                      BH1745NUC.c \

$(NAME)_COMPONENTS += daemons/HTTP_server \
                      daemons/Gedday \
				      protocols/SNTP

$(NAME)_COMPONENTS += utilities/command_console \
                      utilities/command_console/ping

#$(NAME)_COMPONENTS += protocols/Xively

$(NAME)_RESOURCES  += ../apps/work/zenitron_iot_wifi/res/index.html \
                      ../apps/work/zenitron_iot_wifi/res/table.html \
                      ../apps/work/zenitron_iot_wifi/res/cypress.jpg \
                      ../apps/work/zenitron_iot_wifi/res/line.png \
                      ../apps/work/zenitron_iot_wifi/res/favicon.ico \
                      ../apps/work/zenitron_iot_wifi/res/azurewave.png \
                      ../apps/work/zenitron_iot_wifi/res/microchip.png \
                      ../apps/work/zenitron_iot_wifi/res/rohm.jpg \
                      ../apps/work/zenitron_iot_wifi/res/wifi.png \
                      ../apps/work/zenitron_iot_wifi/res/zenitron.gif \
                      ../apps/work/zenitron_iot_wifi/res/jquery.flot.min.js \
					  ../apps/work/zenitron_iot_wifi/res/jquery-1.12.4.min.js \
					  ../apps/work/zenitron_iot_wifi/res/highcharts.js

#$(NAME)_RESOURCES  += apps/res/index.html \
                      apps/res/table.html \
                      apps/res/cypress.jpg \
                      apps/res/line.png \
                      apps/res/favicon.ico \
                      scripts/wpad.dat \
                      apps/res/azurewave.png \
                      apps/res/microchip.png \
                      apps/res/rohm.jpg \
                      apps/res/wifi.png \
                      apps/res/zenitron.gif \
                      apps/res/jquery.flot.min.js \
                      scripts/general_ajax_script.js \
					  apps/res/jquery-1.12.4.min.js \
					  ../apps/work/zenitron_iot_wifi/res/highcharts.js

APPLICATION_DCT    += ping_webserver_dct.c

WIFI_CONFIG_DCT_H  += wifi_config_dct.h

ifeq ($(PLATFORM),$(filter $(PLATFORM), CYW9MCU7X9N364))
GLOBAL_DEFINES += APPLICATION_STACK_SIZE=14*1024
GLOBAL_DEFINES += WICED_DISABLE_TLS
endif
