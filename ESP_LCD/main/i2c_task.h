/*
 * 12c_task.h
 *
 *  Created on: 2024年12月7日
 *      Author: Administrator
 */

#ifndef MAIN_I2C_TASK_H_
#define MAIN_I2C_TASK_H_


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/i2c_master.h"
#include "tm1637.h"

#define I2C_MASTER_SCL_IO GPIO_NUM_42
#define I2C_MASTER_SDA_IO GPIO_NUM_41

void iic_task_init(void);
void i2c_task_entry(void *arg);


#endif /* MAIN_I2C_TASK_H_ */
