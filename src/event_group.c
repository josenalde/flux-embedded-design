#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

EventGroupHandle_t eventGroupConn;
const int WiFiflag = BIT0;
const int MQTTflag = BIT1;

SemaphoreHandle_t triggerConn_semphr;
float average_temperature;

void WiFi_conn(void *params) {
    while(true) {
        ESP_LOGI("WifI", "Connection: OK");
        xEventGroupSetBits(eventGroupConn, WiFiflag);
        xSemaphoreGive(triggerConn_semphr);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void MQTT_conn(void *params) {
    while(true) {
        xSemaphoreTake(triggerConn_semphr);
        ESP_LOGI("MQTT", "Connection: OK");
        xEventGroupSetBits(eventGroupConn, MQTTflag);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void process_data(void *params) {
    while(true) {
        xEventGroupWaitBits(eventGroupConn, WiFiflag | MQTTflag, true, true, portMAX_DELAY);
        printf("Processing data...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_LOGI("TASK", "Disconnect from internet");
    }
}

void app_main() {
    eventGroupConn = xEventGroupCreate();
    triggerConn_semphr = xSemaphoreCreateBinary();

    xTaskCreatePinnedToCore(&WiFi_conn, "WiFi_conn", 4096, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(&MQTT_conn, "MQTT_conn", 4096, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(&process_data, "process_data", 4096, NULL, 1, NULL, 0);
}
