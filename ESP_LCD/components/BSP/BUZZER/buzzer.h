/*
 * buzzer.h
 *
 *  Created on: 2024年12月8日
 *      Author: Administrator
 */

#ifndef COMPONENTS_BSP_BUZZER_BUZZER_H_
#define COMPONENTS_BSP_BUZZER_BUZZER_H_


#include "driver/gpio.h"


/* 引脚定义 */
#define BUZZER_GPIO_PIN    GPIO_NUM_7  /* LED连接的GPIO端口 */


/* 函数声明*/
void buzzer_init(void);    /* 初始化LED */

void buzzer_on(void);

void buzzer_off(void);
#endif /* COMPONENTS_BSP_BUZZER_BUZZER_H_ */
