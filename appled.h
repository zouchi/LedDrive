/*
 * app_ledlib.h
 */

#ifndef LEDLIB_H_
#define LEDLIB_H_

//平台头文件
#include <stdbool.h>
#include "../include/af.h"



//库自定义
typedef unsigned char libu8 ;
typedef unsigned short int libu16;
typedef unsigned int libu32;
#ifndef FALSE
#define FALSE 	0
#endif
#ifndef TRUE
#define TRUE 	(!FALSE)
#endif



#define LED_INTERVAL    50    


#define  LEDEND   0xfe					//
#define  LEDAGN   0xff					//

#define SHINE_ON_TIME	100/LED_INTERVAL				    //100ms
#define SHINE_SLOW_OFF  800/LED_INTERVAL				//800ms
#define SHINE_FAST_OFF  200/LED_INTERVAL				//400ms
#define ON_TRIG_TIME	200/LED_INTERVAL				//500ms
#define ON_THREE_TIME	3000/LED_INTERVAL
#define ON_ONE_TIME		1000/LED_INTERVAL


//#define USER_LED_ON(pin_num)   led_onoff_gpio(pin_num,1)
//
//#define USER_LED_OFF(pin_num)  led_onoff_gpio(pin_num,0)

#define USER_LED_ON(pin_num)

#define USER_LED_OFF(pin_num)

//鑷畾涔塴ed浜嬩欢
typedef enum {
	LED_NONE = 0,     
	LED_OFF,			
	LED_ON,                   
	LED_SHINE_FAST,      
	LED_SHINE_SLOW,     
	LED_ON_TRIG_STATE,
	LED_ON_THREE_SECONDS,
	LED_SHINE_FAST_THREE_TIMES,
	LED_SHINE_SLOW_THREE_TIMES,
	LED_ON_ONE_SECOND,      
	LED_SHINE_SLOW_SIX_TIMES,
	MAX_MODE
}Led_IndicationMode;





typedef struct event_map
{
	Led_IndicationMode command_index;
	libu8 *event;

}event_map_t;


typedef void  (*hal_led_level)(bool led_level);
typedef void  (*start_led_timer)();
typedef void  (*stop_led_timer)();
typedef void  (*led_timer_init)();


typedef struct
{
	led_timer_init    led_init;
	start_led_timer   start_led;
	start_led_timer   stop_led;
}led_timer_t;



typedef struct Led {

	Led_IndicationMode  indication_mode;
	libu8  *play_command;

	event_map_t led_event_map[MAX_MODE];

	hal_led_level  hal_led_level_set;

	libu16  ticks;
	led_timer_t led_timer;
	struct Led* next;
}Led_t;


void led_object_creat(struct Led* handle,event_map_t led_event[] ,hal_led_level gpio_led_set,led_timer_t ledtimer);
void led_send(struct Led* handle,Led_IndicationMode ledindmode);

void led_scan_event(struct Led* handle);

#endif
