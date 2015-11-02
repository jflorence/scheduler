#ifndef SIMPLETEMPERATUREMODEL_H
#define SIMPLETEMPERATUREMODEL_H



#include "temperatureModel.h"

class SimpleTemperatureModel : public TemperatureModel
{
public:
	void updateTemperature(double timeInterval, double power);
private:
	double currentTemp;
};





#endif
