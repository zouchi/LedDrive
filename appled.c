/*
 * app_ledlib.c
 */


#include "appled.h"

#ifndef NULL
#define NULL 0
#endif


void * libmemset(void * dest, int val, unsigned int len) {
	register unsigned char *ptr = (unsigned char*) dest;
	while (len-- > 0)
		*ptr++ = (unsigned char)val;
	return dest;
}


void led_object_creat(struct Led* handle,event_map_t led_event[] ,hal_led_level gpio_led_set,led_timer_t ledtimer)
{
	int i=0;
	libmemset(handle, 0, sizeof(struct Led));

	handle->hal_led_level_set = gpio_led_set;
	handle->indication_mode = LED_NONE;
	handle->led_timer = ledtimer;

	for(i=0;i <MAX_MODE ;i++)
	{
		handle->led_event_map[i] = led_event[i];
	}
	handle->play_command = handle->led_event_map[LED_OFF].event;

}

bool led_handler(struct Led* handle)
{
	if(handle->indication_mode)
	{
		handle->play_command = handle->led_event_map[handle->indication_mode].event;
		handle->indication_mode = LED_NONE;
		handle->ticks = 0;
	}
	if(handle->ticks == 0)
	{
	    if((*handle->play_command) ==  LEDEND)
		{
			return TRUE;
		}
		else
		{	if((*handle->play_command) ==  LEDAGN)
				handle->play_command = (handle->play_command - *(handle->play_command+1));

		    handle->ticks = *handle->play_command;
			handle->play_command++;

			emberAfDebugPrintln("handle->hal_led_level_set %d ... \n",*handle->play_command);
			handle->hal_led_level_set(*handle->play_command);
			handle->play_command++;
		}
	}
	else
	{
		handle->ticks--;
	}
	return FALSE;
}





void led_scan_event(struct Led* handle)
{
	//my_printf_uart("led_scan_event runnig ... \n");
	handle->led_timer.stop_led();

	if(led_handler(handle)== false)
	{
		handle->led_timer.start_led();
	}

}


bool get_is_led_runing(struct Led* handle)
{

	return handle->ticks ? true:false;
}



void led_send(struct Led* handle,Led_IndicationMode ledindmode)
{

	handle->indication_mode = ledindmode;

	//启动
	handle->led_timer.stop_led();
	handle->led_timer.start_led();


}



/****************************************************************************/
/***		Local Functions 											  ***/
/****************************************************************************/

