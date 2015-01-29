/*
 * main.c
 *
 *  Created on: 25.01.2014
 *      Author: Michail Kurochkin
 */

#include <stdio.h>
#include "init_hw.h"
#include "machine.h"
#include "modes.h"
#include "config.h"



int main(void)
{
	int rc;

	init_hw();
	printf("Init - ok\r\n");

	Machine.edit_mode = NONE;
	Machine.state = STOPED;
	Machine.power_interval = 0;
	Machine.waiting_interval = 0;
	Machine.power_interval_sec = 0;
	Machine.waiting_interval_sec = 0;
	Machine.power_time = 0;
	Machine.waiting_time = 0;

	rc = restore_state();
	if (rc)
		machine_stop();

	for(;;)
	{
		scan_buttons();
		scan_code_button();

		switch (Machine.state)
		{
			case STOPED:
				do_mode_stoped();
				break;

			case POWER:
				do_mode_power();
				break;

			case WAITING:
				do_mode_waiting();
				break;
		}

		if (Machine.state == POWER || Machine.state == WAITING)
			do_mode_power_waiting();

		clear_unused_key_code();
	}
}






