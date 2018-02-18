#include "stdafx.h"
#include "WeatherData.h"

int main(int, char*[])
{
	WeatherData observable;

	SimpleDisplay simpleDisplay;
	observable.RegisterObserver(simpleDisplay);

	StatisticsDisplay statisticsDisplay;
	observable.RegisterObserver(statisticsDisplay);

	observable.SetMeasurements(15, 0.5, 800);
	observable.RemoveObserver(simpleDisplay);

	observable.SetMeasurements(20, 0.6, 750);

	return 0;
}
