#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"


#define ADC1_CHAN0 ADC_CHANNEL_0
#define ADC_ATTEN ADC_ATTEN_DB_12

const static char *TAG = "EXAMPLE";

static int adc_raw[2][10];
// static int voltage[2][10];


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

	//Dmax = 2^chan_config.bitwidth;
	Dmax = 4096;

	adc_oneshot_read(adc1_handle, ADC1_CHAN0, &adc_raw[0][0]);
	Dout = adc_raw[0][0];


	Vout = Dout * Vmax / Dmax;
	ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %f",ADC_UNIT_1 + 1, ADC1_CHAN0, Vout);
}
