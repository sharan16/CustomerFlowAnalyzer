#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <ugpio/ugpio.h>

int main (const int argc, const char* const argv[]) {


	int i;
	int rq;
	int rv;
	int gpio;
	int value;


	if (argc < 2){
		cout << "Usage : GPIO Read" << endl;
		cout << "Reads the input value of the specified GPIO pin once a second for 20 seconds" << endl;
		return -1;
	}

	gpio = 1;


// check to see if the GPIO is already exported

	if ((rq = gpio_is_requested(gpio)) < 0 ) {
		cerr << "gpio_is_requested" << endl;
		return 0;
	}


// export the gpio

	if (!rq) {
		cout << "exporting gpio" << endl;
		if ((rv = gpio_request(gpio, NULL)) < 0){
			cerr << "gpio_request" << endl;
		}
	}

// set the initial input direction

	cout << "setting the input" << endl;

	if ((rv = gpio_direction_input(gpio)) < 0 ) {
		cerr << "gpio_direction_input"
	}


// read the GPIO 20 times

	cout << "being reading GPIO" << gpio << endl;

	for (int i = 0; i < 20; i++) {

		// read the gpio
		value = gpio_get_value (gpio);
		cout << "Read GPIO: value of " << gpio << "is " << value << endl;

		// pause 1 second between reads
		sleep (1);
	}

// unexport the GPIO

	if (!rq) {
		cout << "unexporting GPIO" << endl;
		if (gpio_free(gpio) < 0){
			cerr << "gpio_free" << endl;
		}
	}


	return 0;
}