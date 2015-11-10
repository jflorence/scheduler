#include "simpleTemperatureModel.h"
#include <cmath>
#include <iostream>
#include <utility>

double SimpleTemperatureModel::updateTemperature(double timeInterval, double power)
{
	std::cout << "temperature updated, with interval "<<timeInterval<<" and power "<<power<<"\n";
	
	/*T(t) = [T0 - (Ta + RP)]exp(-t/(RC)) + (Ta + RP)*/
	const double A = Ta + R*power;
	double T = (T0 - A)*exp(-timeInterval/(R*C)) + A;
	currentTime = currentTime + timeInterval;
	std::cout << "Current time: "<<currentTime<<", temp: "<<T<<"\n";
	history.push_back(std::pair<double, double>(currentTime, T));
	T0 = T;
	return T;

}


std::vector<std::pair<double, double>> SimpleTemperatureModel::getTemperatureHistory()
{
	
	return history;
}


