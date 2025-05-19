#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

SemaphoreHandle_t syncTasks_semph;

void serverConnection(void *params) {
    while(true) {
        //...connection code (wifi-serverport)
        ESP_LOGI("Server:","Connected...: OK");
        xSemaphoreGive(syncTasks_semph);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void processData(void *params) {
    while(true) {
        xSemaphoreTake(syncTasks_semph, portMAX_DELAY);
        //processing code...
        printf("Page loaded...\n");
    }
}

/*void app_main() {
    syncTasks_semph = xSemaphoreCreateBinary();
    xTaskCreatePinnedToCore(&serverConnection, "serverConnection", 4096, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(&processData, "processData", 4096, NULL, 1, NULL, 0);
}*/
