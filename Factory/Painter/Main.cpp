#include "stdafx.h"
#include "ShapeFactory.h"
#include "Designer.h"
#include "ConsoleCanvas.h"
#include "Painter.h"

void DrawPicture(PictureDraft& draft, ICanvas& canvas)
{
	Painter painter;
	painter.DrawPicture(draft, canvas);
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	DrawPicture(Designer(ShapeFactory()).CreateDraft(std::cin), ConsoleCanvas());

	return 0;
}
