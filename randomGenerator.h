#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>
#include <vector>

class RandomGenerator
{
public:
	static RandomGenerator *getRandomGenerator();
	double drawExp(double lambda);
	double drawUniform(double min, double max);
	int drawUniformInt(int min, int max);
	/*This function returns a vector of nbOfBins components,
	containing elements so that the total of them is 1.
	This is generating a random discrete distribution*/
	std::vector<double> drawDistribution(int nbOfBins);
	void seed(time_t seed);
private:
	static RandomGenerator *instance;
	std::default_random_engine gen;
	std::uniform_real_distribution<double> unif;
};



#endif
