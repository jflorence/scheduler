#ifndef TEMPERATUREMODEL_H
#define TEMPERATUREMODEL_H

#include <vector>
#include <tuple>


class TemperatureModel
{

public:
	virtual double updateTemperature(double timeInterval, double power)=0;
	virtual std::vector<std::pair<double, double>> getTemperatureHistory()=0;
};



#endif
