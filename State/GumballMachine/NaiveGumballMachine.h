#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class GumballMachine
{
	enum class State
	{
		NoCoin,
		HasCoin,
		Sold,
		SoldOut
	};

public:
	GumballMachine(std::ostream& output, unsigned count = 0)
		: m_gumballs(count)
		, m_state(count > 0 ? State::NoCoin : State::SoldOut)
		, m_coins(0)
		, m_output(output)
	{
	}

	void InsertQuarter()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoCoin:
			std::cout << "You inserted a quarter\n";
			m_state = State::HasCoin;
			break;
		case State::HasCoin:
			std::cout << "You can't insert another quarter\n";
			break;
		case State::Sold:
			std::cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			break;
		case State::NoCoin:
			std::cout << "You haven't inserted a quarter\n";
			break;
		case State::HasCoin:
			std::cout << "Quarter returned\n";
			m_state = State::NoCoin;
			break;
		case State::Sold:
			std::cout << "Sorry you already turned the crank\n";
			break;
		}
	}

	void TurnCrank()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You turned but there's no gumballs\n";
			break;
		case State::NoCoin:
			std::cout << "You turned but there's no quarter\n";
			break;
		case State::HasCoin:
			std::cout << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			std::cout << "Turning twice doesn't give you another gumball\n";
			break;
		}
	}

	void Refill(unsigned count)
	{
		m_gumballs = count;
		m_state = count > 0 ? State::NoCoin : State::NoCoin;
	}

	std::string ToString() const
	{
		std::string state =
			(m_state == State::SoldOut)		? "sold out" :
			(m_state == State::NoCoin)		? "waiting for quarter" :
			(m_state == State::HasCoin)		? "waiting for turn of crank"
											: "delivering a gumball";

		auto fmt = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");

		return (fmt % m_gumballs % (m_gumballs != 1 ? "s" : "") % state).str();
	}

private:
	void Dispense()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "This is impossible\n";
			break;
		case State::NoCoin:
			std::cout << "You need to pay first\n";
			break;
		case State::HasCoin:
			std::cout << "This is impossible\n";
			break;
		case State::Sold:
			std::cout << "A gumball comes rolling out the slot\n";
			--m_gumballs;
			if (m_gumballs == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_state = State::NoCoin;
			}
			break;
		}
	}

private:
	unsigned m_gumballs;
	unsigned m_coins;
	State m_state;
	std::ostream& m_output;
};
}
