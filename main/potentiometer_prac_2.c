#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_adc/adc_continuous.h"
#include "adc_esp/adc_cali.h"
#include "adc_esp/adc_cali_scheme.h"
#include "esp_log.h"


#define ADC_UNIT 		ADC_UNIT_1
#define _ADC_UNIT_STR(unit)	#unit
#define ADC_UNIT_STR(unit)	_ADC_UNIT_STR(unit)
#define ADC_CONV_MODE		ADC_CONV_SINGLE_UNIT_1
#define ADC_ATTEN		ADC_ATTEN_DB_0
#define ADC_BIT_WIDTH		SOC_ADC_DIGI_MAX_BITWIDTH


#define ADC_OUTPUT_TYPE		ADC_DIGI_OUTPUT_FORMAT_TYPE1
#define ADC_GET_CHANNEL(p_data)	((p_data)->type1.channel)
#define ADC_GET_DATA(p_data)	((p_data)->type1.data)


#define READ_LEN		256


static adc_channel_t channel[2] = {ADC_CHANNEL_0, ADC_CHANNEL_1};


static TaskHandle_t s_task_handle;

static const char *TAG = "READING";

void app_main(void)
{
	//|-----------------------------------------------|
	adc_continuous_handle_t handle = NULL;

	adc_continuous_handle_cfg_t adc_config = {
				.max_store_buf_size = 1024,
				.conv_frame_size = READ_LEN,
				};

	adc_continuous_new_handle(&adc_config, &handle);


	adc_continuous_config_t dig_cfg = {
				.sample_freq_hz = 20 * 1000,
				.conv_mode = ADC_CONV_MODE,
				.format = ADC_OUTPUT_TYPE,
				};
	//|-----------------------------------------------|
};
