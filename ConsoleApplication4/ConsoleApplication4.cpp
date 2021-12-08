#include <iostream>
#include <sstream>
#include <string>
#include <istream>
#include <stdlib.h>


enum switches {
	POWER = 1,
	MAIN_OUTLETS = 2,
	LIGHT_INSIDE_HOME = 4,
	LIGHT_OUTSIDE = 8,
	TEMP_INSIDE = 16,
	TEMP_WATER_PIPES = 32,
	AIR_COND = 64,
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
//state &= ~LIGHT;
//
//if (state & LIGHT) {
//	std::cout << " Light on";
//}

int main()
{	
	int status = 0;
	std::stringstream buffer;
	std::string temp, movement = "no", lights = "off";
	int tempInside = 25, tempOutside = 15;
	int hour = 0;
	std::cout << "Smart house..." << std::endl;


	
	while (true) {
		hour++;
		std::cout << std::endl;
		std::cout << "Enter sensor readings(temp outside '15', temp inside '25', movement 'No', lights 'No')" << std::endl;
		std::getline(std::cin, temp);

		buffer << temp;
		buffer >> tempOutside >> tempInside >> movement >> lights;
		std::cout << buffer.str() << std::endl;


		std::cout << "Current temperature outside: " << tempOutside << std::endl;
		std::cout << "Current temperature inside: " << tempInside << std::endl;
		std::cout << "There is movement otside: " << movement << std::endl;
		std::cout << "Light in the house: " << lights << std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////
		// вкл/выкл датчики

		// проверка на температуру вне дома и включении подогрева труб
		if (tempOutside < 0) {
			status |= TEMP_WATER_PIPES;
		}
		else if (tempOutside > 5) {
			status &= ~TEMP_WATER_PIPES;
		}

		// с 16:00 до 5:00 - свет вкл, если есть движение
		if ((hour >= 16 || hour <= 5) && movement == "yes") {
			status |= LIGHT_OUTSIDE;
		}
		else status &= ~LIGHT_OUTSIDE;

		//темпреаптруа в доме ниже 22 отопление вкл, темпреатруа выше 24 отопление выкл
		if (tempInside < 22) {
			status |= TEMP_INSIDE;
		}
		else if (tempInside > 24) {
			status &= ~TEMP_INSIDE;
		}

		// enable air cond
		if (tempInside > 30) {
			status |= AIR_COND;
		}
		else if (tempInside < 26) {
			status &= ~AIR_COND;
		}

////////////////////////////////////////////////////////////////////////////////////////////////////////

		// выводим
		if (status & TEMP_WATER_PIPES) {
			std::cout << "Pipes - on" << std::endl;
		}
		else std::cout << "Pipes - off" << std::endl;

		if (status & LIGHT_OUTSIDE) {
			std::cout << "LIGHT_OUTSIDE - on" << std::endl;
		}
		else std::cout << "LIGHT_OUTSIDE - off" << std::endl;

		if (status & TEMP_INSIDE) {
			std::cout << "TEMP_INSIDE - on" << std::endl;
		}
		else std::cout << "TEMP_INSIDE - off" << std::endl;
		if (status & AIR_COND) {
			std::cout << "AIR_COND - on" << std::endl;
		}
		else std::cout << "AIR_COND - off" << std::endl;

		 
		buffer.str("");
		buffer.clear();
	}
	system("cls");
}
