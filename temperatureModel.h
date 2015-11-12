#ifndef TEMPERATUREMODEL_H
#define TEMPERATUREMODEL_H

#include <vector>
#include <tuple>


class TemperatureModel
{

public:
	virtual double updateTemperature(double timeInterval, struct PowerParams *params, double taskPowerCoeff, double freq)=0;
	virtual std::vector<std::pair<double, double>> getTemperatureHistory()=0;
};

struct PowerParams
{
	double leakage{1.0};
	double capa{1.0};
	double power{0.0};
	double energy{0.0};
};


#endif
