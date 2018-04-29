#include "stdafx.h"
#include "ShapeCollection.h"
#include "ShapeComposite.h"
#include "Slide.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	Slide slide(100, 100);
	auto rectangle = std::make_shared<Rectangle>(Point2D{ 0, 0 }, 10.f, 10.f);
	auto triangle = std::make_shared<Triangle>(Point2D{ 1, 1 }, Point2D{ 2, 3 }, Point2D{ 4, 0 });
	auto ellipse = std::make_shared<Ellipse>(Point2D{ 100, 100 }, 50.f, 50.f);

	auto composite = std::make_shared<ShapeComposite>();
	composite->InsertShape(rectangle);
	composite->InsertShape(triangle);
	composite->InsertShape(ellipse);

	slide.GetShapes().InsertShape(composite);
	return 0;
}
