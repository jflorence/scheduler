#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor
{
private:
	const double maxFreq{2.0};
	const double minFreq{1.0};
	double usage{0.0};
	static Processor *proc;
	/*I have no clue about what is a good alpha value.
	It depends on the UsageUpdate event period and on the governor invocation period.*/
	double alpha{0.7};
public:
	double getMinFreq();
	double getMaxFreq();
	double getUsage();
	static Processor *getInstance();
	void updateUsage(bool isBusy);
};


#endif
