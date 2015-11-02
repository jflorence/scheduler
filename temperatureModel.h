#ifndef TEMPERATUREMODEL_H
#define TEMPERATUREMODEL_H


class TemperatureModel
{

public:
	virtual void updateTemperature(double timeInterval, double power)=0;

};


#endif
