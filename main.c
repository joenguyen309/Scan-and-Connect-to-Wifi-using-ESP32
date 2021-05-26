#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "esp_event_loop.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "connect.h"
#include "scan.h"


#define TAG "main"

// Empty infinite task
void loop_task(void *pvParameter)
{
    while(1) { 
		vTaskDelay(1000 / portTICK_RATE_MS);		
    }
}

void app_main()
{
	// initialize NVS
	ESP_ERROR_CHECK(nvs_flash_init());


	ESP_LOGI(TAG, "WiFi scan");
	wifi_scan();
	
	vTaskDelay(1000 / portTICK_RATE_MS);
	// initialize NETIF
	esp_wifi_stop();
	// Start Wi-Fi connection

    ESP_LOGI(TAG, "WiFi init");
    wifi_init();

	
	// infinite loop
	xTaskCreate(&loop_task, "loop_task", 2048, NULL, 5, NULL);
}