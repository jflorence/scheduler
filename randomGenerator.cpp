#include "randomGenerator.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

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


void RandomGenerator::seed(time_t seed)
{
	std::cout << "\033[1;32m" << "Using seed "<< seed << "\033[0m" << "\n"; //FIXME use the log class for color
	gen.seed(seed);
}


int RandomGenerator::drawUniformInt(int min, int max)
{
	double d;
	do
	{
		d = drawUniform((double) min, (double) max + 1.0);
	} while(d == (double) max + 1.0);
	int ret = (int) floor(d);
	return ret;
}

std::vector<double> RandomGenerator::drawDistribution(int nbOfBins)
{
	std::vector<double> vector(nbOfBins);
	double total = 0.0;
	for (int i = 0; i < nbOfBins; i++)
	{
		vector[i] = drawUniform(0.0, 1.0);
		total += vector[i];
	}
	for (int i = 0; i < nbOfBins; i++)
	{
		vector[i] /= total;
	}
	return vector;
}

