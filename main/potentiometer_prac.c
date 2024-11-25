#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"

// CONSTANTS
#define ADC1_CHAN0 ADC_CHANNEL_0
#define ADC_ATTEN ADC_ATTEN_DB_12

const static char *TAG = "EXAMPLE";

// variable for list of raw adc readings
static int adc_raw[2][10];

//variable to hold calibrated voltage
static int voltage[2][10];

// Variables for basic voltage conversion
int Dout;
float Vmax = 3.3;
int  Dmax;
float Vout;



void app_main(void)
{
//----------------create adc unit handle----------------------|

	adc_oneshot_unit_handle_t adc1_handle;
	adc_oneshot_unit_init_cfg_t init_config1 =
			{
				.unit_id = ADC_UNIT_1,
				.ulp_mode = ADC_ULP_MODE_DISABLE,
			}; // end of init_config1

	adc_oneshot_new_unit(&init_config1, &adc1_handle);

 //-----------------------------------------------------------|


//-------------------unit configuration-----------------------|

	adc_oneshot_chan_cfg_t chan_config =
			{
				.bitwidth = ADC_BITWIDTH_DEFAULT,
				.atten = ADC_ATTEN,
			};// end of chan_config

	adc_oneshot_config_channel(adc1_handle, ADC1_CHAN0, &chan_config);

//-------------------------------------------------------------|


//---------------line fitting scheme configuration---------------|
	adc_cali_handle_t cali_handle;
	adc_cali_line_fitting_config_t cali_config =
			{
				.unit_id = ADC_UNIT_1,
				.atten = ADC_ATTEN,
				.bitwidth = ADC_BITWIDTH_DEFAULT,
			};// end of cali config

	// create handle
	adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle);
//---------------------------------------------------------------|




	//max integer for raw adc reading
	Dmax = 4096;

	//read raw adc data
	adc_oneshot_read(adc1_handle, ADC1_CHAN0, &adc_raw[0][0]);

	// turn raw reading in array to single integer
	Dout = adc_raw[0][0];

	// simple raw adc to voltage conversion
	Vout = Dout * Vmax / Dmax;


	// read line fitting cali in mV
        adc_cali_raw_to_voltage(cali_handle, adc_raw[0][0], &voltage[0][0]);


	// display voltage reading to monitor/log
	ESP_LOGI(TAG, "ADC%d Channel[%d] Voltage: %d mV",ADC_UNIT_1 + 1, ADC1_CHAN0, voltage[0][0]);

}
