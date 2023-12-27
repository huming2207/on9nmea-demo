#include <stdio.h>
#include <esp_log.h>
#include <on9nmea.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// static const char RMC_TEST[] = "$GNRMC,102052.00,A,3740.86716,S,14451.93670,E,0.114,,241223,,,A,V*0D\r\n";
static const char GGA_TEST[] = "$GNGGA,102052.00,3740.86716,S,14451.93670,E,1,39,0.48,124.9,M,,M,,*4D\r\n";

#define LOG_TAG "app_main"

void app_main(void)
{
    on9_nmea_ctx_t nmea_ctx = {};

    for (size_t idx = 0; idx < sizeof(GGA_TEST); idx += 1) {
        on9_nmea_state_t state = on9_nmea_feed_char(&nmea_ctx, GGA_TEST[idx]);
        ESP_LOGI(LOG_TAG, "State: 0x%x", state);
    }

    ESP_LOGI(LOG_TAG, "Lat %ld.%lu; Lon %ld.%lu; Time %u:%u:%u:%u %u/%u/%u, valid %s",
             nmea_ctx.next_result.latitude.major, nmea_ctx.next_result.latitude.minor,
             nmea_ctx.next_result.longitude.major, nmea_ctx.next_result.longitude.minor,
             nmea_ctx.next_result.time.hour, nmea_ctx.next_result.time.minute, nmea_ctx.next_result.time.second,
             nmea_ctx.next_result.time.sub_secs, nmea_ctx.next_result.date.year, nmea_ctx.next_result.date.month,
             nmea_ctx.next_result.date.day, nmea_ctx.next_result.valid ? "yea" : "nah");
    vTaskDelay(portMAX_DELAY);
}
