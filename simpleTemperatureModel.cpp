#include "simpleTemperatureModel.h"
#include <cmath>
#include <iostream>
#include <utility>

double SimpleTemperatureModel::updateTemperature(double timeInterval, double power)
{
	/*T(t) = [T0 - (Ta + RP)]exp(-t/(RC)) + (Ta + RP)*/
	const double A = Ta + R*power;
	double T = (T0 - A)*exp(-timeInterval/(R*C)) + A;
	currentTime = currentTime + timeInterval;
	history.push_back(std::pair<double, double>(currentTime, T));
	return T;

}


std::vector<std::pair<double, double>> SimpleTemperatureModel::getTemperatureHistory()
{
	
	return history;
}


