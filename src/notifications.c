#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
//#include "esp_mac.h"

static TaskHandle_t receiverHandle = NULL;


void emitter(void *params) {
    while(true) {
        int qtd = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Notifications received: %d\n", qtd);
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void receiver(void *params) {
    while(true) {
        xTaskNotifyGive(receiverHandle);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main() {
    xTaskCreatePinnedToCore(&receiver, "receiver", 4096, NULL, 2, &receiverHandle, 0);
    xTaskCreatePinnedToCore(&emitter, "emitter1", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(&emitter, "emitter2", 4096, NULL, 2, NULL, 0);
}
