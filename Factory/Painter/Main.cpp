#include "stdafx.h"
#include "ShapeFactory.h"
#include "Designer.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ShapeFactory factory;
	Designer designer(factory);
	auto draft = designer.CreateDraft(std::cin);

	return 0;
}
