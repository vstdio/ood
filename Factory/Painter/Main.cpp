#include "stdafx.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/Designer.h"
#include "../libpainter/Painter.h"
#include "ConsoleCanvas.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	try
	{
		auto factory = std::make_unique<ShapeFactory>();
		auto designer = std::make_unique<Designer>(*factory);
		auto painter = std::make_unique<Painter>();
		auto canvas = std::make_unique<ConsoleCanvas>();

		auto draft = designer->CreateDraft(std::cin);
		painter->DrawPicture(draft, *canvas);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
