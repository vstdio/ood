#include "stdafx.h"
#include "GumballMachineWithState.h"
#include "NaiveGumballMachine.h"
#include "Menu.h"

void InteractWithGumballMachines()
{
	Menu menu;
	naive::GumballMachine m_naiveMachine(std::cout);
	with_state::GumballMachine m_machineWithState(std::cout);
	IGumballMachine* m_selectedMachine = &m_naiveMachine;

	menu.AddItem("Exit", "Exit from menu", [&menu](std::istream&) { menu.Exit(); });
	menu.AddItem("Help", "Show menu instructions", [&menu](std::istream&) { menu.ShowInstructions(); });
	menu.AddItem("SwitchMachine", "Switch current gumball machine", [&](std::istream&) {
		if (m_selectedMachine == &m_naiveMachine)
		{
			m_selectedMachine = &m_machineWithState;
		}
		else
		{
			m_selectedMachine = &m_naiveMachine;
		}
	});
	menu.AddItem("InsertCoin", "Insert coin into selected gumball machine", [&](std::istream&) {
		m_selectedMachine->InsertCoin();
	});
	menu.AddItem("EjectCoin", "Eject coins from selected gumball machine", [&](std::istream&) {
		m_selectedMachine->EjectCoin();
	});
	menu.AddItem("TurnCrank", "Turn crank of selected gumball machine", [&](std::istream&) {
		m_selectedMachine->TurnCrank();
	});
	menu.AddItem("Refill", "Refill machine with some gumballs", [&](std::istream& strm) {
		unsigned gumballs;
		if (strm >> gumballs)
		{
			m_selectedMachine->Refill(gumballs);
		}
		else
		{
			std::cout << "Provide gumballs count\n";
		}
	});
	menu.AddItem("ToString", "Get detailed information of selected gumball machine", [&](std::istream&) {
		std::cout << "Selected machine: " << (m_selectedMachine == &m_naiveMachine ? "naive" : "with state pattern") << "\n";
		std::cout << m_selectedMachine->ToString() << "\n";
	});

	menu.Run();
}

int main(int argc, char* argv[])
{
	InteractWithGumballMachines();
	return 0;
}
