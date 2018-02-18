﻿#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class WeatherData : public AbstractObservable<WeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void SetMeasurements(double temperature, double humidity, double pressure)
	{
		m_temperature = temperature;
		m_humidity = humidity;
		m_pressure = pressure;
		NotifyObservers();
	}

protected:
	WeatherInfo GetChangedData()const override
	{
		return { m_temperature, m_humidity, m_pressure };
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class InOutSensorDisplay : public IObserver<WeatherInfo>
{
public:
	InOutSensorDisplay(WeatherData& in, WeatherData& out)
		: m_inSensor(in)
		, m_outSensor(out)
	{
		m_inSensor.RegisterObserver(*this);
		m_outSensor.RegisterObserver(*this);
	}

	virtual ~InOutSensorDisplay()
	{
		m_inSensor.RemoveObserver(*this);
		m_outSensor.RemoveObserver(*this);
	}

protected:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo> & sensor)override
	{
		if (std::addressof(sensor) == std::addressof(m_inSensor))
		{
			// signal from inside sensor
		}
		else if (std::addressof(sensor) == std::addressof(m_outSensor))
		{
			// signal from outside sensor
		}
		else
		{
			// signal from unknown sensor
		}
	}

	WeatherData & m_inSensor;
	WeatherData & m_outSensor;
};

class SimpleDisplay : public InOutSensorDisplay
{
public:
	SimpleDisplay(WeatherData& in, WeatherData& out)
		: InOutSensorDisplay(in, out)
	{
	}

protected:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override
	{
		std::cout << "Current Temperature " << data.temperature << std::endl;
		std::cout << "Current Humidity " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class StatisticsDisplay : public InOutSensorDisplay
{
public:
	StatisticsDisplay(WeatherData& in, WeatherData& out)
		: InOutSensorDisplay(in, out)
	{
	}

protected:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override
	{
		if (m_minTemperature > data.temperature)
		{
			m_minTemperature = data.temperature;
		}
		if (m_maxTemperature < data.temperature)
		{
			m_maxTemperature = data.temperature;
		}
		m_accumulatedTemperature += data.temperature;
		++m_accumulationsCount;

		std::cout << "Max Temperature: " << m_maxTemperature << std::endl;
		std::cout << "Min Temperature: " << m_minTemperature << std::endl;
		std::cout << "Average Temperature " << (m_accumulatedTemperature / m_accumulationsCount) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accumulatedTemperature = 0;
	unsigned m_accumulationsCount = 0;
};
