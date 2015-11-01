#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>


class RandomGenerator
{
public:
	static RandomGenerator *getRandomGenerator();
	double drawExp(double lambda);
	double drawUniform(double min, double max);
private:
	static RandomGenerator *instance;
	std::default_random_engine gen;
	std::uniform_real_distribution<double> unif;
};



#endif
