/*
 * i2c_task.c
 *
 *  Created on: 2024年12月7日
 *      Author: Administrator
 */

#include "i2c_task.h"
#include "soc/gpio_num.h"
#include "buzzer.h"
#include "echo.h"
extern int64_t detect_tim_us;
/****************************************************************************/
#define DATA_LENGTH 100
uint8_t wr_buf;
i2c_master_bus_config_t i2c_mst_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = -1,     //TEST_I2C_PORT -1 auto selecting
    .scl_io_num = I2C_MASTER_SCL_IO,
    .sda_io_num = I2C_MASTER_SDA_IO,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
};
i2c_master_bus_handle_t bus_handle;


i2c_device_config_t dev_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = 0x44,
    .scl_speed_hz = 100000,
};
i2c_master_dev_handle_t dev_handle;
/****************************************************************************/
tm1637_led_t dev_tm1637={
	.m_pin_clk=GPIO_NUM_37,
	.m_pin_dta=GPIO_NUM_36, 
	.m_brightness=0x04,
};

void iic_task_init(void)
{
	xTaskCreate(i2c_task_entry, "i2c_task_entry", 4096, NULL,  1, NULL);
}



 
 void i2c_task_entry(void *arg)
 {
	 
	buzzer_init();
	//ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
	//ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle)); 
	//ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, &wr_buf, DATA_LENGTH, -1));
	//tm1637_led_t * lcd = tm1637_init(GPIO_NUM_15, GPIO_NUM_16);
	//static bool dots_state = true;
	 
		
		

	while (1) {
        
        
		//tm1637_set_segment_number(lcd, 0, 1, dots_state);
		//tm1637_set_segment_number(lcd, 1, 2, dots_state); // On my display "dot" (clock symbol ":") connected only here
		//tm1637_set_segment_number(lcd, 2, 3, dots_state);
		//tm1637_set_segment_number(lcd, 3, 4, dots_state);
        //dots_state = !dots_state;
		
		 tm1637_set_number(tm1637_init(GPIO_NUM_15,GPIO_NUM_16),(uint16_t)(detect_tim_us/58)); 
		 if((uint32_t)(detect_tim_us/58)<=5)  buzzer_on();
		      
		 if((uint32_t)(detect_tim_us/58)>=5) buzzer_off();
		      vTaskDelay(100);
	       }
	 
 }
   