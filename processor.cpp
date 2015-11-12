#include "processor.h"
#include "process.h"
#include "simpleTemperatureModel.h"
#include <iostream>
#include <fstream>


Processor *Processor::proc = nullptr;


Processor *Processor::getInstance()
{
	if (proc == nullptr)
	{
		proc = new Processor;
		proc->setTemperatureModel(new SimpleTemperatureModel);
	}
	return proc;
}

double Processor::getMaxFreq()
{
	return maxFreq;
}

double Processor::getMinFreq()
{
	return minFreq;
}

double Processor::getUsage()
{
	return usage;
}

void Processor::updateUsage()
{/*exponential average. Is that the best average to use?*/
	usage = (1.0 - alpha)*usage + alpha*(busy?1.0:0.0);
}


bool Processor::isBusy()
{
	return busy;
}

void Processor::setBusy(bool b)
{
	busy = b;
}


bool Processor::isRunning(Process *p)
{
	return (runningTask == p);
}


void Processor::setRunning(Process *p)
{
	runningTask = p;
}




Process *Processor::getRunningTask()
{
	return runningTask;
}




void Processor::updateTemperature(double timeInterval)
{
	/*FIXME where should the powerCoeff of an idle processor be defined?*/
	double powerCoeff = (runningTask==nullptr) ? 0.0: runningTask->powerCoeff;

	temperatureModel->updateTemperature(timeInterval, &powerParams, powerCoeff, freq);

}



void Processor::setTemperatureModel(TemperatureModel *model)
{
	temperatureModel = model;
}

void Processor::setFreq(double f)
{
	freq = f;
}


double Processor::getFreq()
{
	return freq;
}



void Processor::printTemperatureReport()
{
	std::ofstream file;
        file.open("reports.txt", std::ios_base::app);
        std::vector<std::pair<double, double>> tempHist = temperatureModel->getTemperatureHistory();
        file << "temperature report:\n";
        for (unsigned int i = 0; i < tempHist.size(); i++)
        {
                file << tempHist[i].first << ": " << tempHist[i].second << "\n";
        }
        file << "\n";
        file.close();

}







