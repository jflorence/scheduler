#include "randomGenerator.h"
#include <iostream>
#include <chrono>
#include <ctime>
RandomGenerator *RandomGenerator::instance = nullptr;


RandomGenerator *RandomGenerator::getRandomGenerator()
{
	if (instance == nullptr)
	{
		instance = new RandomGenerator();
		instance->gen.seed(time(NULL));
	}
	return instance;
}


double RandomGenerator::drawUniform(double min, double max)
{
	double ret = unif(gen);
	ret *= (max-min);
	ret += min;
	return ret;
}

double RandomGenerator::drawExp(double lambda)
{
	if (lambda <= 0)
	{
		return 0;
	}
	double uni = unif(gen);
	return -log(uni)/lambda;
}









