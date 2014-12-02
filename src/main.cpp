#include <iostream>
#include <vector>
#include "gpio.hpp"

using namespace std;

void print_main_menu() {
	cout << "[1] Add Pin" << endl;
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
	vector <GPIO> gpio_tab;
	vector <GPIO>::iterator it;

	while(option != 0) {
		print_main_menu();	
		option = get_option();
		switch(option) {
			case 1:
				cout << "Enter GPIO pin: ";
				gpio_pin = get_option();
				gpio_tab.push_back(GPIO(gpio_pin));
				break;
			case 2:
				cout << "Enter pin index: ";
				gpio_pin = get_option();
				if(gpio_pin >=0 && gpio_pin < gpio_tab.size())
					gpio_tab[gpio_pin].export_pin();
				break;
			case 3:
				cout << "Enter pin index: ";
				gpio_pin = get_option();
				if(gpio_pin >=0 && gpio_pin < gpio_tab.size())
					gpio_tab[gpio_pin].unexport_pin();
				break;
			case 4:
				cout << "Enter pin index: ";
				gpio_pin = get_option();
				if(gpio_pin >=0 && gpio_pin < gpio_tab.size())
					gpio_tab[gpio_pin].set_input();
				break;
			case 5:
				cout << "Enter pin index: ";
				gpio_pin = get_option();
				if(gpio_pin >=0 && gpio_pin < gpio_tab.size())
					gpio_tab[gpio_pin].set_output();
				break;
			case 6:
				cout << "Entetr pin index: ";
				gpio_pin = get_option();
				if(gpio_pin >=0 && gpio_pin < gpio_tab.size())
					gpio_tab[gpio_pin].set_value(1);
				break;
			case 7:
				cout << "Entetr pin index: ";
				gpio_pin = get_option();
				if(gpio_pin >=0 && gpio_pin < gpio_tab.size())
					gpio_tab[gpio_pin].set_value(0);
			case 8:
				it = gpio_tab.begin();
				for(int i=0; it<gpio_tab.end(); i++,it++) {
					cout<<"["<<i<<"] ";
					it->print();
				}
				break;
			default:
				break;
		}
	}
	return 0;
}

