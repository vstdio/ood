#include "stdafx.h"

using namespace std;

using FlyBehavior = function<void()>;
using QuackBehavior = function<void()>;
using DanceBehavior = function<void()>;

namespace
{
// Можно было бы использовать обычные функции
const function<void()> DO_NOT_DO_ANYTHING = []() {};
const QuackBehavior QUACK_AS_USUAL = []() { cout << "Quack Quack!!!" << endl; };
const QuackBehavior SQUEEK = []() { cout << "Squeek!!!" << endl; };
const DanceBehavior DANCE_WALTZ = []() { cout << "I'm dancing waltz!" << endl; };
const DanceBehavior DANCE_MINUET = []() { cout << "I'm dancing minuet!" << endl; };
const DanceBehavior DO_NOT_DANCE = []() { cout << "Men don't dance!" << endl; };
}

class Duck
{
public:
	Duck(const FlyBehavior& flyBehavior,
		const QuackBehavior& quackBehavior,
		const DanceBehavior& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(const FlyBehavior& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck(const FlyBehavior& flyBehavior)
		: Duck(flyBehavior, QUACK_AS_USUAL, DANCE_WALTZ)
	{
	}
	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck(const FlyBehavior& flyBehavior)
		: Duck(flyBehavior, QUACK_AS_USUAL, DANCE_MINUET)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(DO_NOT_DO_ANYTHING, DO_NOT_DO_ANYTHING, DO_NOT_DANCE)
	{
	}
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(DO_NOT_DO_ANYTHING, SQUEEK, DO_NOT_DANCE)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(DO_NOT_DO_ANYTHING, QUACK_AS_USUAL, DO_NOT_DANCE)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	int mallardDuckFlyCounter = 0;
	MallardDuck mallardDuck([&mallardDuckFlyCounter]() {
		cout << "I'm flying with wings!! Flights: " << ++mallardDuckFlyCounter << endl;
	});
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior([&mallardDuckFlyCounter]() {
		cout << "I'm flying with rocket engine!! Flights: " << ++mallardDuckFlyCounter << endl;
	});
	PlayWithDuck(mallardDuck);

	int redheadDuckFlyCounter = 0;
	RedheadDuck redheadDuck([&redheadDuckFlyCounter]() {
		cout << "I'm flying with wings!! Flights: " << ++redheadDuckFlyCounter << endl;
	});
	PlayWithDuck(redheadDuck);

	// Эти утки летать не умеют, поэтому счётчик полётов им не нужен
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);

	// Модель утки - по умолчанию не летает
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	// Однако можно нацепить на неё крылья и она полетит, подсчитывая количество полётов
	int modelDuckFlyCounter = 0;
	modelDuck.SetFlyBehavior([&modelDuckFlyCounter]() {
		cout << "I'm flying with wings!! Flights: " << ++modelDuckFlyCounter << endl;
	});
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior([&modelDuckFlyCounter]() {
		cout << "I'm flying with rocket engine!! Flights: " << ++modelDuckFlyCounter << endl;
	});
	PlayWithDuck(modelDuck);
}
