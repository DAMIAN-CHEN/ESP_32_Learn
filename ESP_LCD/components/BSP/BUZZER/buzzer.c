/*
 * buzzer.c
 *
 *  Created on: 2024年12月8日
 *      Author: Administrator
 */
#include "buzzer.h"
#include "driver/gpio.h"
/**
 * @brief       初始化BUZZER
 * @param       无
 * @retval      无
 */
void buzzer_init(void)
{
    gpio_config_t gpio_init_struct = {0};

    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;         /* 失能引脚中断 */
    gpio_init_struct.mode = GPIO_MODE_INPUT_OUTPUT;         /* 输入输出模式 */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;       /* 使能上拉 */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;  /* 失能下拉 */
    gpio_init_struct.pin_bit_mask = 1ull << BUZZER_GPIO_PIN;   /* 设置的引脚的位掩码 */
    gpio_config(&gpio_init_struct);                         /* 配置GPIO */
                                                 
}


void buzzer_on(void)
{
	gpio_set_level(BUZZER_GPIO_PIN, 0);
}


void buzzer_off(void)
{
	gpio_set_level(BUZZER_GPIO_PIN, 1);
	
}