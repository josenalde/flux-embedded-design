#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

QueueHandle_t temperature_queue = NULL;
float average_temperature;

void temperature_reading(void *params) {
    float temperature;
    while(true) {
        //reading temp sensor
        temperature = 20.0 * ((float) rand() / (float)(RAND_MAX/10));
        long result = xQueueSend(&temperature_queue, &temperature, pdMS_TO_TICKS(1000));
        if (result) {
            ESP_LOGI("Reading", "Reading: OK");
        } else {
            ESP_LOGE("Reading", "Reading: FAIL");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void calculate_average_temperature(void *params) {
    float temperature = 0.0;
    float previous_temperature = 0.0;
    while(true) {
        if (xQueueReceive(temperature_queue, &temperature, pdMS_TO_TICKS(5000))) { 
            average_temperature = (previous_temperature + temperature) / 2.0;
            previous_temperature = temperature;
            printf("Average temperature %.1f\n", average_temperature);
        }
    }
}

void app_main() {
    temperature_queue = xQueueCreate(5, sizeof(float));
    xTaskCreatePinnedToCore(&temperature_reading, "temperature_reading", 4096, NULL, 1, NULL, 0);
    //xTaskCreatePinnedToCore(&calculate_average_temperature, "calculate_average_temperature", 4096, NULL, 2, NULL, 0);
}
