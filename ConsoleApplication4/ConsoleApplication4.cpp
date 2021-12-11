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
	int k = 5000;
	std::stringstream buffer;
	std::string temp, movement = "no", lights = "off";
	int tempInside = 25, tempOutside = 15;
	int hour = 0;
	int day = 1;
	std::cout << "Smart house..." << std::endl;


	
	while (true) {
		std::cout << std::endl;
		std::cout << "Enter sensor readings(temp outside '15', temp inside '25', movement 'No', lights 'No')" << std::endl;
		std::getline(std::cin, temp);
		system("cls");
		buffer << temp;
		buffer >> tempOutside >> tempInside >> movement >> lights;
		

		std::cout << "Day: " << day << ". Time: " << hour << ":00" << std::endl;
		std::cout << "Current temperature outside: " << tempOutside << std::endl;
		std::cout << "Current temperature inside: " << tempInside << std::endl;
		std::cout << "There is movement otside: " << movement << std::endl;
		std::cout << "Light in the house: " << lights << std::endl;
		std::cout << "------------------------------------------" << std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////
		// вкл/выкл датчики

		// проверка на температуру вне дома и включении подогрева труб
		if (tempOutside < 0) {
			if (!(status & TEMP_WATER_PIPES)) {
				status |= TEMP_WATER_PIPES;
				std::cout << "Pipes - on" << std::endl;
			}
		}
		else if (tempOutside > 5) {
			if (status & TEMP_WATER_PIPES) {
				status &= ~TEMP_WATER_PIPES;
				std::cout << "Pipes - off" << std::endl;
			}
			
		}

		// с 16:00 до 5:00 - свет вкл, если есть движение
		if ((hour >= 16 || hour <= 5) && movement == "yes") {
			if (!(status & LIGHT_OUTSIDE)) {
				status |= LIGHT_OUTSIDE;
				std::cout << "LIGHT_OUTSIDE - on" << std::endl;
			}
			
		}
		else if (status & LIGHT_OUTSIDE) {
			std::cout << "LIGHT_OUTSIDE - off" << std::endl;
			status &= ~LIGHT_OUTSIDE;
		}

		//темпреаптруа в доме ниже 22 отопление вкл, темпреатруа выше 24 отопление выкл
		if (tempInside < 22) {
			if (!(status & TEMP_INSIDE)) {
				status |= TEMP_INSIDE;
				std::cout << "TEMP_INSIDE - on" << std::endl;
			}
			
		}
		else if (tempInside > 24) {
			if (status & TEMP_INSIDE) {
				status &= ~TEMP_INSIDE;
				std::cout << "TEMP_INSIDE - off" << std::endl;
			}
			
		}

		// enable air cond
		if (tempInside > 30) {
			if (!(status & AIR_COND)) {
				status |= AIR_COND;
				std::cout << "AIR_COND - on" << std::endl;
			}
			
		}
		else if (tempInside < 26) {
			if (status & AIR_COND) {
				status &= ~AIR_COND;
				std::cout << "AIR_COND - off" << std::endl;
			}
			
		}

		//5000 - 2700 
		
		if (hour == 16) k = 4540;
		else if (hour == 17) k = 4080;
		else if (hour == 18) k = 3620;
		else if (hour == 19) k = 3160;
		else if (hour == 20) k = 2700;
		else if (hour == 0) k = 5000;
		if (lights == "on" && (hour >= 16 && hour <= 20)) {
			if (!(status & LIGHT_INSIDE_HOME)) {
				status |= LIGHT_INSIDE_HOME;
				std::cout << "Light in home - on, " << k << "K" << std::endl;
			}
		}
		else if (lights == "on") {
			if (!(status & LIGHT_INSIDE_HOME)) {
				status |= LIGHT_INSIDE_HOME;
				std::cout << "Light in home - on, " << k << "K" << std::endl;
			}
		}
		else if (status & LIGHT_INSIDE_HOME) {
			status &= ~LIGHT_INSIDE_HOME;
			std::cout << "Light in home - off" << std::endl;
		}

		buffer.str("");
		buffer.clear();
	}
	
}
