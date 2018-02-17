#include "stdafx.h"
#include "../WeatherData.h"

namespace
{
class SavingWeatherInfoObserver : public IObserver<WeatherInfo>
{
public:
	WeatherInfo GetWeatherInfo()const
	{
		return m_weatherInfo;
	}

private:
	void Update(const WeatherInfo& data) override
	{
		m_weatherInfo = data;
	}

	WeatherInfo m_weatherInfo;
};

bool IsEqual(double lhs, double rhs)
{
	return std::abs(lhs - rhs) < DBL_EPSILON;
}

bool WeatherInfoEquals(const WeatherInfo& lhs, const WeatherInfo& rhs)
{
	return IsEqual(lhs.temperature, rhs.temperature) &&
		IsEqual(lhs.pressure, rhs.pressure) &&
		IsEqual(lhs.humidity, rhs.humidity);
}

class DummyObservable : public AbstractObservable<int>
{
public:
	void SetData(int data)
	{
		m_data = data;
		NotifyObservers();
	}

private:
	virtual int GetChangedData() const override
	{
		return m_data;
	}

	int m_data;
};

class DummyObserver : public IObserver<int>
{
public:
	DummyObserver(DummyObservable& observable)
		: m_observable(observable)
	{
		m_observable.RegisterObserver(*this);
	}

	~DummyObserver()
	{
		// Не должно вызвать падение программы
		m_observable.RemoveObserver(*this);
	}

	void Update(const int& data) override
	{
		{
			// Не должно вызвать падение программы
			m_observable.RemoveObserver(*this);
		}
	}

private:
	DummyObservable & m_observable;
};
}

BOOST_AUTO_TEST_SUITE(WeatherStation)
	BOOST_AUTO_TEST_CASE(observers_of_it_notified_on_measurements_set)
	{
		WeatherData weatherData;

		SavingWeatherInfoObserver saver;
		weatherData.RegisterObserver(saver);

		WeatherInfo info = { 8, 0.6, 700 };
		weatherData.SetMeasurements(info.temperature, info.humidity, info.pressure);

		BOOST_CHECK(WeatherInfoEquals(info, saver.GetWeatherInfo()));
	}
BOOST_AUTO_TEST_SUITE_END()
