#include <iostream>
#include "gpio.hpp"

using namespace std;

void print_main_menu() {
	cout << "[1] Set Pin" << endl;
	cout << "[2] Export" << endl;
	cout << "[3] Unexport" << endl;
	cout << "[4] Set Input" << endl;
	cout << "[5] Set Output" << endl;
	cout << "[6] Set" << endl;
	cout << "[7] Reset" << endl;
	cout << "[8] Print" << endl;
	cout << "[0] Exit" << endl;
}

int get_option() {
	int option;
	do {
		cin >> option;
	} while(!cin.good());
	return option;
}


int main(void) {
	int option = 1;
	int gpio_pin;
	int ret_code;
	GPIO *gpio = NULL;

	while(option != 0) {
		print_main_menu();	
		option = get_option();
		switch(option) {
			case 1:
				cout << "Enter GPIO pin: ";
				gpio_pin = get_option();
				gpio = new GPIO(gpio_pin);
				break;
			case 2:
				if(gpio)
					gpio->export_pin();
				break;
			case 3:
				if(gpio)
					gpio->unexport_pin();
				break;
			case 4:
				if(gpio)
					gpio->set_input();
				break;
			case 5:
				if(gpio)
					gpio->set_output();
				break;
			case 6:
				if(gpio)
					gpio->set_value(1);
				break;
			case 7:
				if(gpio)
					gpio->set_value(0);
				break;
			case 8:
				if(gpio)
					gpio->print();
				break;
			default:
				break;
		}
	}
	return 0;
}

