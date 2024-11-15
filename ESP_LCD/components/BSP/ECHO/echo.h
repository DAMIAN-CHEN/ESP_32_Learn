/*
 * exit.h
 *
 *  Created on: 2024年11月14日
 *      Author: Administrator
 */

#ifndef COMPONENTS_BSP_ECHO_ECHO_H_
#define COMPONENTS_BSP_ECHO_ECHO_H_

#include "esp_err.h"
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "esp_system.h" 
#include "esp_log.h"
#include "sdkconfig.h"
#include "led.h"
#include "esp_timer.h"

/* 引脚定义 */
#define ECHO_INT_GPIO_PIN   GPIO_NUM_5
#define TRIG_GPIO_PIN       GPIO_NUM_6

/* 函数声明 */
void exit_init(void);   /* 外部中断初始化程序 */

void trig_gpio_init(void);

/* 函数声明 */
void echo_dev_tim_init(); /* 初始化初始化高分辨率定时器 */

void echo_tim_callback(void *arg); /* 定时器回调函数 */

void trig_tim_callback(void *arg);

void distance_detect(void);

#endif /* COMPONENTS_BSP_ECHO_ECHO_H_ */
