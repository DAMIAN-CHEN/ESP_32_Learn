/*
 * exit.c
 *
 *  Created on: 2024年11月14日
 *      Author: Administrator
 */

#include "echo.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "led.h"
#include <stdint.h>

int64_t detect_tim_us;
static int64_t detect_tim_start_us;
static int64_t detect_tim_end_us;

enum{
	COUNT_START=1,
	COUNT_END=0
};
static int echo_tim_flag=COUNT_END;


 esp_timer_handle_t echo_tim_handle; /* 定时器回调函数句柄 */
 /* 定义一个定时器结构体 */
 esp_timer_create_args_t echo_tim_arg = {
 .callback = &echo_tim_callback, /* 设置回调函数 */
 .arg = NULL, /* 不携带参数 */
 };
 
 
/**
* @brief 定时器回调函数
* @param arg: 不携带参数
* @retval 无
*/
void echo_tim_callback(void *arg)
{

}


 esp_timer_handle_t trig_tim_handle; /* 定时器回调函数句柄 */
 /* 定义一个定时器结构体 */
 esp_timer_create_args_t trig_tim_arg = {
 .callback = &trig_tim_callback, /* 设置回调函数 */
 .arg = NULL, /* 不携带参数 */
 };

void trig_tim_callback(void *arg)
{
	 gpio_set_level(TRIG_GPIO_PIN, PIN_RESET);
}


 
/**
* @brief 初始化高精度定时器（ESP_TIMER）
* @param tps: 定时器周期，以微妙为单位（μs），以一秒为定时器周期来执行一次定时器中
断，那此处 tps = 1s = 1000000μs
* @retval 无
*/
void echo_dev_tim_init()
{
 esp_timer_create(&echo_tim_arg, &echo_tim_handle); /* 创建一个事件 */
 esp_timer_create(&trig_tim_arg, &trig_tim_handle); /* 创建一个事件 */
}





/**
 * @brief       外部中断服务函数
 * @param       arg：中断引脚号
 * @note        IRAM_ATTR: 这里的IRAM_ATTR属性用于将中断处理函数存储在内部RAM中，目的在于减少延迟
 * @retval      无
 */
static void IRAM_ATTR exit_gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    if (gpio_num == ECHO_INT_GPIO_PIN)
    {
		if(echo_tim_flag==COUNT_END)
		{
			 echo_tim_flag=COUNT_START;
			 detect_tim_start_us=esp_timer_get_time();
			  
		}
		else
		{
			echo_tim_flag=COUNT_END;
			detect_tim_end_us=esp_timer_get_time();
			detect_tim_us=detect_tim_end_us-detect_tim_start_us;
		}
        LED_TOGGLE();
    }
    
}

/**
 * @brief       外部中断初始化程序
 * @param       无
 * @retval      无
 */
void exit_init(void)
{
    gpio_config_t gpio_init_struct;

    /* 配置Echo引脚和外部中断 */
    gpio_init_struct.mode = GPIO_MODE_INPUT;                    /* 选择为输入模式 */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;           /* 上拉使能 */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;      /* 下拉失能 */
    gpio_init_struct.intr_type = GPIO_INTR_ANYEDGE;             /* 双边沿触发 */
    gpio_init_struct.pin_bit_mask = 1ull << ECHO_INT_GPIO_PIN;  /* 配置ECHO输入引脚 */
    gpio_config(&gpio_init_struct);                /* 配置使能 */
    
    /* 注册中断服务 */
    gpio_install_isr_service(0);
    
    /* 设置GPIO的中断回调函数 */
    gpio_isr_handler_add(ECHO_INT_GPIO_PIN, exit_gpio_isr_handler, (void*) ECHO_INT_GPIO_PIN);
}

void trig_gpio_init(void)
{
	gpio_config_t gpio_init_struct;

	gpio_init_struct.mode=GPIO_MODE_OUTPUT;
	gpio_init_struct.pull_up_en=GPIO_PULLUP_ENABLE;
	gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;      /* 下拉失能 */
	gpio_init_struct.intr_type=GPIO_INTR_DISABLE;
	gpio_init_struct.pin_bit_mask = 1ull << TRIG_GPIO_PIN;  /* 配置ECHO输入引脚 */
    gpio_config(&gpio_init_struct);                /* 配置使能 */
    gpio_set_level(TRIG_GPIO_PIN, PIN_RESET);
}

void distance_detect(void)
{
	 gpio_set_level(TRIG_GPIO_PIN, PIN_SET);
	 esp_timer_start_once(trig_tim_handle, 15);
	
}

