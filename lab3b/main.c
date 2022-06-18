#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_wifi.h>
#include <esp_err.h>
#include <nvs_flash.h>
#include <tcpip_adapter.h>







int app_main ( void ){
    nvs_flash_init();
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg)) ;
    // ESP_ERROR_CHECK(esp_event_loop_init(event_handler , NULL)) ;
    // ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM)) ;
    // ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA)) ;
    // wifi_config_t sta_config = {.sta = {.ssid = "Xiaohu", .password = "thaonhi04072001", .bssid_set = 0}};
//    ESP_ERROR_CHECK( esp_wifi_set_config ( WIFI_IF_STA , &sta_config)) ;
//     ESP_ERROR_CHECK( esp_wifi_start()) ;

   ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP)) ;
   wifi_config_t apConfig = {
    .ap = {
        .ssid ="Cypher",
        .ssid_len =0 ,
        .password ="270901",
        .channel =0 ,
        .authmode = WIFI_AUTH_OPEN ,
        .ssid_hidden =0 ,
        .max_connection =4 ,
        .beacon_interval =100
        }
    };
    esp_wifi_set_config(WIFI_IF_AP, &apConfig);
    ESP_ERROR_CHECK(esp_wifi_start());
    while(1){vTaskDelay(3000/portTICK_RATE_MS);}
    return 0;
}
