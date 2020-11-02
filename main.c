#include "appled.h"

Led_t led_red;
Led_t led_blue;


uint8_t aLED_OFF[]      		  		    = {1,0,LEDEND, 2};             //常关
uint8_t aLED_ON[]        		  		    = {1,1,LEDEND, 2};             //常开
uint8_t aLED_SHINE_FAST[] 		  			= {SHINE_ON_TIME,1,SHINE_FAST_OFF,0,LEDAGN, 4};           //快闪
uint8_t aLED_SHINE_SLOW[] 		  			= {SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,LEDAGN, 4};           //慢闪
uint8_t aLED_ON_THREE_SECONDS[]   			= {ON_THREE_TIME,1,1,0,LEDEND, 2};     //长亮三秒

uint8_t aLED_ON_TRIG_STATE[]      			= {SHINE_ON_TIME,1,1,0,LEDEND, 2};     //长亮三秒
uint8_t aLED_SHINE_FAST_THREE_TIMES[] 		= {SHINE_ON_TIME,1,SHINE_FAST_OFF,0,SHINE_ON_TIME,1,SHINE_FAST_OFF,0,SHINE_ON_TIME,1,SHINE_FAST_OFF,0,LEDEND, 2};           //快闪
uint8_t aLED_SHINE_SLOW_THREE_TIMES[] 		= {2,0,SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,LEDEND, 2};           //慢闪
uint8_t aLED_ON_ONE_SECOND[]   				= {ON_ONE_TIME,1,1,0,LEDEND, 2};     //长亮三秒
uint8_t aLED_SHINE_SLOW_SIX_TIMES[] 	    = {SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   SHINE_ON_TIME,1,SHINE_SLOW_OFF,0,
											   LEDEND, 2
											  };           //慢闪

event_map_t user_event_map[MAX_MODE]=
{
	{LED_NONE,NULL},
	{LED_OFF ,aLED_OFF},
	{LED_ON , aLED_ON},
	{LED_SHINE_FAST ,aLED_SHINE_FAST},
	{LED_SHINE_SLOW , aLED_SHINE_SLOW},
	{LED_ON_TRIG_STATE ,aLED_ON_TRIG_STATE},
	{LED_ON_THREE_SECONDS , aLED_ON_THREE_SECONDS},
	{LED_SHINE_FAST_THREE_TIMES , aLED_SHINE_FAST_THREE_TIMES},
	{LED_SHINE_SLOW_THREE_TIMES ,aLED_SHINE_SLOW_THREE_TIMES},
	{LED_ON_ONE_SECOND , aLED_ON_ONE_SECOND},
	{LED_SHINE_SLOW_SIX_TIMES ,aLED_SHINE_SLOW_SIX_TIMES}
};

void HalGpioSet(GPIO_Port_TypeDef port, unsigned int pin,bool level)
{
	if(level)
	  {
	    GPIO_PinOutSet(port, pin);

	  }else
	  {
	      GPIO_PinOutClear(port, pin);
	  }
}



void halSetMcuWakeupGpioLevel(bool level)
{
	HalGpioSet(BSP_LED0_PORT,BSP_LED0_PIN,level);

}

void halSetRedledGpioLevel(bool level)
{
	HalGpioSet(BSP_LED0_PORT,BSP_LED0_PIN,level);

}


void halSetBlueledGpioLevel(bool level)
{
	HalGpioSet(BSP_LED0_PORT,BSP_LED0_PIN,level);
}




//led 定时器自定义实现
EmberEventControl RedLedEventControl;
EmberEventControl BlueLedEventControl;


void redledtimer_start()
{

	emberEventControlSetDelayMS(RedLedEventControl,LED_INTERVAL);
}

void redledtimer_stop()
{

	 emberEventControlSetInactive(RedLedEventControl);
}


void blueledtimer_start()
{
	emberEventControlSetDelayMS(BlueLedEventControl,LED_INTERVAL);

}

void blueledtimer_stop()
{
	 emberEventControlSetInactive(BlueLedEventControl);

}



//按键扫描
void RedLedEventHandle()
{
	led_scan_event(&led_red);
}


void BlueLedEventHandle()
{
	led_scan_event(&led_blue);
}


//时间回调
void led_proInit(void)
{

	led_timer_t redled_timer = {

	.led_init  = NULL,
	.start_led = redledtimer_start,
	.stop_led  = redledtimer_stop,
	};

//	led_timer_t blueled_timer =
//  {
//	  .led_init  = NULL,
//	  .start_led = blueledtimer_start,
//	  .stop_led  = blueledtimer_stop,
//	};

	led_object_creat(&led_red,user_event_map,halSetRedledGpioLevel, redled_timer);
	//led_object_creat(&led_blue,user_event_map,halSetBlueledGpioLevel, blueled_timer);

	led_send(&led_red,LED_SHINE_FAST);
}


main()
{
led_proInit();






}





