#include "simpleTemperatureModel.h"
#include <cmath>
#include <iostream>
#include <utility>

double SimpleTemperatureModel::updateTemperature(double timeInterval, struct PowerParams *params, double taskPowerCoeff, double freq)
{
	
	/*T(t) = [T0 - (Ta + RP)]exp(-t/(RC)) + (Ta + RP)*/
	params->power = freq*freq*freq*params->capa*taskPowerCoeff + params->leakage;
	params->energy += params->power*timeInterval;
	
	const double A = Ta + R*params->power;
	double T = (T0 - A)*exp(-timeInterval/(R*C)) + A;
	currentTime = currentTime + timeInterval;
	history.push_back(std::pair<double, double>(currentTime, T));
	T0 = T;
	return T;

}


std::vector<std::pair<double, double>> SimpleTemperatureModel::getTemperatureHistory()
{
	
	return history;
}


