#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <dirent.h>
#include <unistd.h>

const char *gpio_basepath =  "/sys/class/gpio/";

using namespace std;

void print_main_menu() {
	cout << "[1] Export" << endl;
	cout << "[2] Unexport" << endl;
	cout << "[3] Set" << endl;
	cout << "[4] Reset" << endl;
	cout << "[0] Exit" << endl;
}

int get_option() {
	int option;
	do {
		cin >> option;
	} while(!cin.good());
	return option;
}

int export_gpio(int gpio) { 
	ostringstream oss;
	oss << gpio;
	
	string gpio_path(gpio_basepath);

	gpio_path += "gpio";
	gpio_path += oss.str();
	
	//check if gpio is already exported
	DIR * gpio_dir = opendir(gpio_path.c_str());
	if(gpio_dir != NULL)
		return -1;
	closedir(gpio_dir);

	//export gpio by writing pin number to export file
	string gpio_export_path(gpio_basepath);
	gpio_export_path += "export";

	ofstream export_file(gpio_export_path.c_str(), ofstream::out);
	export_file << oss.str();
	export_file.close();

	usleep(200000);
	
	//set gpio as output
	gpio_path += "/direction";
	ofstream direction_file(gpio_path.c_str(), ofstream::out);
	direction_file << "out";
	direction_file.close();

	return 0;
}

int unexport_gpio(int gpio) {
    ostringstream oss;
    oss << gpio;

    string gpio_path(gpio_basepath);

    gpio_path += "gpio";
    gpio_path += oss.str();

    DIR * gpio_dir = opendir(gpio_path.c_str());
    if(gpio_dir == NULL)
        return -1;
    closedir(gpio_dir);

	string gpio_export_path(gpio_basepath);
	gpio_export_path += "unexport";

	ofstream file(gpio_export_path.c_str(), ofstream::out);
	file << oss.str();
	file.close();

	return 0;
}

int set_gpio_state(int gpio, int state) {
    ostringstream oss;
    oss << gpio;

    string gpio_path(gpio_basepath);

    gpio_path += "gpio";
    gpio_path += oss.str();

    DIR * gpio_dir = opendir(gpio_path.c_str());
    if(gpio_dir == NULL)
        return -1;
    closedir(gpio_dir);

	gpio_path += "/value";

	ofstream file(gpio_path.c_str(), ofstream::out);
	file << state;
	file.close();

	return 0;
}
int main(void) {
	int option = 1;
	int gpio;
	int ret_code;

	while(option != 0) {
		print_main_menu();	
		option = get_option();
		switch(option) {
			case 1:
				cout << "Enter GPIO pin: ";
				gpio = get_option();
				ret_code = export_gpio(gpio);
				if(ret_code == -1) {
					cout << "GPIO already exported!" << endl << endl;
				} else {
					cout << "GPIO successfully exported!" << endl << endl;
				}
				break;
			case 2:
				cout << "Enter GPIO pin: ";
				gpio = get_option();
				ret_code = unexport_gpio(gpio);
				if(ret_code == -1) {
					cout << "GPIO already unexported!" << endl << endl;
				} else {
					cout << "GPIO successfully unexported!" << endl << endl;
				}
				break;
			case 3:
				cout << "Enter GPIO pin: ";
				gpio = get_option();
				ret_code = set_gpio_state(gpio,1);
				if(ret_code == -1) {
					cout << "GPIO unexported!" << endl << endl;
				} else {
					cout << "GPIO set!" << endl << endl;
				}
				break;
			case 4:
				cout << "Enter GPIO pin: ";
				gpio = get_option();
				ret_code = set_gpio_state(gpio,0);
				if(ret_code == -1) {
					cout << "GPIO unexported!" << endl << endl;
				} else {
					cout << "GPIO reset!" << endl << endl;
				}
				break;
			default:
				break;
		}
	}

	return 0;
}

