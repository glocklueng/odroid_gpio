#include <iostream>
#include <sstream>
#include <dirent.h>
#include <fstream>
#include "gpio.hpp"

GPIO::GPIO(int pin) {
	this->pin = pin;
	
	ostringstream oss;
	oss<<"/sys/class/gpio/gpio";
	oss<<this->pin;
	this->dir_path = oss.str(); 
}

bool GPIO::is_exported() {
			
	DIR * gpio_dir = opendir(this->dir_path.c_str());
	if(gpio_dir != NULL) {
		closedir(gpio_dir);
		return true;
	} else  {
		closedir(gpio_dir);
		return false;
	}
}

void GPIO::export_pin() {
	if (!is_exported()) {
		string gpio_export_path = "/sys/class/gpio/export";
		ofstream export_file(gpio_export_path.c_str(), ofstream::out);
		export_file << this->pin;
		export_file.close();
	}
}

void GPIO::unexport_pin() {
	if (is_exported()) {
		string gpio_export_path = "/sys/class/gpio/unexport";
		ofstream export_file(gpio_export_path.c_str(), ofstream::out);
		export_file << this->pin;
		export_file.close();
	}
}

void GPIO::set_input() {
	if (is_exported()) {
		string dir_path = this->dir_path + "/direction";
		ofstream direction_file(dir_path.c_str(), ofstream::out);
		direction_file << "in";
		direction_file.close();
	}
}

void GPIO::set_output() {
	if (is_exported()) {
		string dir_path = this->dir_path + "/direction";
		ofstream direction_file(dir_path.c_str(), ofstream::out);
		direction_file << "out";
		direction_file.close();
	} 
}

void GPIO::set_value(int value) {
	if (is_exported()) {
		string dir_path = this->dir_path + "/value";
		ofstream value_file(dir_path.c_str(), ofstream::out);
		value_file << value;
		value_file.close();
	} 
}

int GPIO::get_value() {
	
	int value = -1;

	if (is_exported()) {
		string dir_path = this->dir_path + "/value";
		ifstream value_file(dir_path.c_str(), ifstream::in);
		value_file >> value;
		value_file.close();
	} 

	return value;
}

void GPIO::print() {
	cout<<"GPIO:"<<endl;
	cout<<"\tpin:\t"<<this->pin<<endl;
	cout<<"\tdir:\t"<<this->dir_path<<endl;
	cout<<"\texists:\t"<<is_exported()<<endl;
	cout<<"\tvalue:\t"<<get_value()<<endl;
}
