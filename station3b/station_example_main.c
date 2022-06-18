# include <freertos/FreeRTOS.h>
# include <esp_wifi.h>
# include <esp_system.h>
# include <esp_event.h>
# include <esp_event_loop.h>
# include <nvs_flash.h>
# include <esp_err.h>
# include <tcpip_adapter.h>
#include "esp_spi_flash.h"
# include <lwip/sockets.h>
# include <stdio.h>
# include "sdkconfig.h"
# include <freertos/task.h>

int app_main ( void ){
    nvs_flash_init();
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA)) ;
    wifi_config_t sta_config = {
        .sta = {
            .ssid = "SoftDrink56",
            .password = "Loc05062001",
            .bssid_set = 0
            }
    };
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA , &sta_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    printf("Connecting...!\n");
    ESP_ERROR_CHECK(esp_wifi_connect());
    printf("Connected!");
    while(1){vTaskDelay(3000/portTICK_RATE_MS);}
    return 0;
}






