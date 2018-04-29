#include "stdafx.h"
#include "ShapeCollection.h"
#include "CompositeShape.h"
#include "Slide.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "ConsoleCanvas.h"
#include "IOutlineStyle.h"
#include "IFillStyle.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	Slide slide(100, 100);
	auto rectangle = std::make_shared<Rectangle>(Point2D{ 0, 0 }, 10.f, 10.f);
	auto triangle = std::make_shared<Triangle>(Point2D{ 1, 1 }, Point2D{ 2, 3 }, Point2D{ 4, 0 });
	auto ellipse = std::make_shared<Ellipse>(Point2D{ 100, 100 }, 50.f, 50.f);

	auto composite = std::make_shared<CompositeShape>();
	composite->InsertShape(rectangle);
	composite->InsertShape(triangle);
	composite->InsertShape(ellipse);

	auto& style = composite->GetOutlineStyle();
	style.SetThickness(2);
	style.Enable(true);

	composite->GetFillStyle().Enable(false);

	ConsoleCanvas canvas(std::cout);

	slide.GetShapes().InsertShape(composite);
	slide.Draw(canvas);
	return 0;
}
