#include "avr/delay.h"
//#include <avr/sfr_defs.h>
#include "stdio.h"
extern "C" {
#include "dvn_gpio.h"
#include "dvn_interrupt.h"
#include "dvn_timer.h"
#include "dvn_adc.h"
#include "hcsr04.h"
#include "dvn_i2c.h"
#include "lcd.h"
#include "dvn_spi.h"
#include "HX711.h"
}	
extern float kc;

char buffer[10];
char buffer_kc[10];


int convert05To01000(double data){
	
	if(data > 5){ return 1000; }
	if(data < 1){ return 0;}
	int result = 0 ;
	result = (int)(data*1000/5);
	return result;
};
int8_t gain = HX711_GAINCHANNELA128;

//set the offset
int32_t offset = 8389246;
//set the scale
double scale = 15797.8;
int chieucao(float n){
	int m = (int)(n - 5) ;
	if(m<=0){
		return 0;
	}
	return m;
}
int main(void)
{	
	hx711_init(gain, scale, offset);
	sr04_init();
	twi_init();
	twi_lcd_init();
	twi_lcd_cmd(0x0C);
	
	while(1){
		sr04_handle();
		twi_lcd_cmd(0x01);
		twi_lcd_cmd(0x80);
		
		sprintf(buffer_kc,"%d cm",chieucao(kc));
		twi_lcd_msg(buffer_kc);
		int32_t read = hx711_read();
	    double weight = hx711_getweight()*(-1) -24;
		int data = convert05To01000(weight);
		twi_lcd_cmd(0xC0);
		sprintf(buffer,"%d gam",data);
		twi_lcd_msg(buffer);
		
	
		 

		 _delay_ms(3000);
	}
	 return 0;
}

