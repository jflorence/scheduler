#ifndef SIMPLETEMPERATUREMODEL_H
#define SIMPLETEMPERATUREMODEL_H

#include <utility>

#include "temperatureModel.h"

class SimpleTemperatureModel : public TemperatureModel
{
public:
	double updateTemperature(double timeInterval, double power);
	std::vector<std::pair<double, double>> getTemperatureHistory();
private:
	double T0{20.0}; /*previous temperature*/
	const double Ta{20.0}; /*ambient temperature*/
	const double R{1.0}; /*thermal resistance*/
	const double C{1.0}; /*thermal capacity*/
	double currentTime{0.0};
	std::vector<std::pair<double, double>> history;
};





#endif
