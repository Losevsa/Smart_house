#include <iostream>
#include <sstream>
#include <string>
#include <istream>

enum switches {
	POWER,
	MAIN_OUTLETS,
	LIGHT_INSIDE_HOME,
	LIGHT_OUTSIDE,
	TEMP_INDIDE,
	TEMP_WATER_PIPES,
	AIR_COND,
};



//enum switches {
//	OUTLETS = 1,
//	BOILER = 2,
//	OUTLETS_2 = 4,
//	LIGHT = 8,
//	LIGHT_2 = 16,
//};
//int state = 0;
//state |= OUTLETS;
//state |= LIGHT;
//
//if (state & LIGHT) {
//	std::cout << " Light on";
//}

int main()
{	
	int status = 0;
	std::stringstream buffer;
	std::string temp, movement = "No", lights = "No", time = "00:00";
	int tempInside = 25, tempOutside = 15;
	
	std::cout << "Smart house..." << std::endl;
	std::cout << "Current temperature inside: " << tempInside << std::endl;
	std::cout << "Current temperature outside: " << tempOutside << std::endl;
	std::cout << "There is movement otside: " << movement << std::endl;
	std::cout << "Light in the house: " << lights << std::endl;

	status &= ~TEMP_WATER_PIPES;
	
	if (status & TEMP_WATER_PIPES) {
		std::cout << "On";
	}

	while (true) {

		std::cout << "Enter sensor readings(temp outside '15', temp inside '25', movement 'No', lights 'No')" << std::endl;
		std::getline(std::cin, temp);
		buffer << temp;
		buffer >> tempOutside >> tempInside >> movement >> lights;

		std::cout << "Current temperature inside: " << tempInside << std::endl;
		std::cout << "Current temperature outside: " << tempOutside << std::endl;
		std::cout << "There is movement otside: " << movement << std::endl;
		std::cout << "Light in the house: " << lights << std::endl;


	}
}