 /*
 *  Advanced Touch Remote emulator for Samsung Smart TVs
 *  by mad_ady - 2015
 * 
 *  Based on https://github.com/FedericoVaga/libuinput
 *
 *  Copyright © 2013 Federico Vaga <federico.vaga@gmail.com>
 *  License: GPLv2
 *
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include <linux/uinput.h>

#include <libuinput.h>

static struct uinput_user_dev uudev = {
		.name = "Advanced-Touch-Remote-Fake-Keyboard",
		.id = {
				.bustype = BUS_USB,
				.vendor = 0x1,
				.product = 0x1,
				.version = 1,
		},
};
static struct input_event events[] = {
		{{0, 0}, EV_REL, REL_MISC, 18}
};

int main(int argc, char *argv[]) {
	struct uinput_tkn *tkn;
	int err;

	tkn = uinput_open(NULL);
	if (!tkn) {
		fprintf(stderr, "Cannot open uinput device\n");
		exit(1);
	}

	/* Enable keyboard events */
	err = uinput_enable_event(tkn, EV_REL);
	/* Enable a list of keyboard events */
	err = uinput_set_valid_event(tkn, UI_SET_RELBIT, REL_MISC);
	if (err)
	  fprintf(stderr, "Cannot set event KEY_SYSRQ");


	/* Create uinput device */
	err = uinput_create_new_device(tkn, &uudev);
	printf("input%d virtual device created. Read events from %s\n\n",
		uinput_get_input_no(tkn), uinput_get_event_path(tkn));
        
        
	printf("To dump events on this device, run the command:"
	       "\nevtest \"%s\"\n\n",  uinput_get_event_path(tkn));

	printf("Send some events in 10 seconds.\n");
	sleep(10);

	/* Simulate some events */
	int number_of_events = sizeof(events)/sizeof(struct input_event);
	//fprintf(stderr, "Debug: number_of_events: %d", number_of_events); 
	// sleep 300ms to allow the keyboard to register
        
	printf("Sending ChUp\n");
	usleep(300000);
	// send the actual events
	err = uinput_send_events(tkn, events, number_of_events, 1);
	if (err) {
		fprintf(stderr, "Cannot inject event uinput device\n");
	}

	uinput_close(tkn);
	return 0;
}
