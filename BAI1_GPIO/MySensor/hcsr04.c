#include "hcsr04.h"
float kc;
void sr04_init(){
	dvn_gpio_output(GPIOA,PIN_0);
	
	dvn_gpio_input(GPIOA,PIN_1);
}
void sr04_handle(){
	dvn_gpio_write_pin(GPIOA,PIN_0,0);
	dvn_gpio_write_pin(GPIOA,PIN_0,1);
	dvn_timer_delay_ms(TIMER_0,1);
	dvn_gpio_write_pin(GPIOA,PIN_0,0);
	while(dvn_gpio_read_pin(GPIOA,PIN_1) == 0);
	dvn_timer_start_count();
	while(dvn_gpio_read_pin(GPIOA,PIN_1) == 1);
	kc = 0.017*dvn_timer_get_count();
	dvn_timer_stop_count();
}