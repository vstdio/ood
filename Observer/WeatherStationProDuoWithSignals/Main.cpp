#include "stdafx.h"
#include "WeatherData.h"
#include "StatisticsDisplay.h"

int main()
{
	WeatherData inner;
	WeatherData outer;
	{
		StatisticsDisplay display(inner, outer);
		inner.SetMeasurements({ 10, 0.9, 800 });
		outer.SetMeasurements({ 15, 0.3, 900, 30, 10 });
		outer.SetMeasurements({ 10, 0.4, 700, 20, 100 });
	}

	// Оповещения не произойдёт, так как scoped_connection разорвёт соединение
	//  с сигналом, рассылаемым наблюдаемым объектом
	inner.SetMeasurements({ 15, 0.6, 700 });
	return 0;
}
