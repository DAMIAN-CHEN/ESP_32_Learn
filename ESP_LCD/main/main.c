/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-26
 * @brief       SPILCD实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 最小系统板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "led.h"
#include "lcd.h"
#include "echo.h"
#include "i2c_task.h"


extern int64_t detect_tim_us;

/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    uint8_t x = 0;
    esp_err_t ret;
    
 
    ret = nvs_flash_init();             /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    led_init();                         /* 初始化LED */
    trig_gpio_init();
    exit_init();
    spi2_init();                        /* 初始化SPI2 */
    lcd_init();                         /* 初始化LCD */
    iic_task_init();                    /* 初始化I2C */
    echo_dev_tim_init();
    vTaskDelay(500);
    
    while (1)
    {
        distance_detect();
        
        
        lcd_show_string(0, 0, 240, 20, 16, "HainanU_20223004393", BLACK);
        lcd_show_string(0, 21, 240, 24, 24, "Length_cm:", MAGENTA);
        //lcd_show_string(0, 60, 240, 16, 16, "ATOM@ALIENTEK", RED);
        lcd_show_num(0 ,50, (uint32_t)(detect_tim_us/58),3,24 , BLUE);
        lcd_show_string(40, 50, 30, 24, 24, "CM", BROWN);
        //lcd_clear(WHITE);
       
        x++;
        
        if (x == 12)
        {
            x = 0;
        }

        //LED_TOGGLE();
        vTaskDelay(100);
    }
}
