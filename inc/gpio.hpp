#ifndef GPIO_HPP
#define GPIO_HPP

#include <string>

using namespace std;

class GPIO {
	
public:

	GPIO(int pin);
	void export_pin();
	void unexport_pin();
	void set_input();
	void set_output();
	void print();
	int get_value();
	void set_value(int value);

private:
	
	int pin;
	string dir_path;	
	bool is_exported();
};

#endif

