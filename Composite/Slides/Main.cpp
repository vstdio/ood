#include "stdafx.h"
#include "Shape.h"
#include "Shapes.h"

class Rectangle : public Shape
{
public:
	void Draw(ICanvas& canvas)const override
	{
		(void)canvas;
	}
};

class Triangle : public Shape
{
public:
	void Draw(ICanvas& canvas)const override
	{
		(void)canvas;
	}
};

class Ellipse : public Shape
{
public:
	void Draw(ICanvas& canvas)const override
	{
		(void)canvas;
	}
};

class ISlide : public ICanvasDrawable
{
public:
	virtual ~ISlide() = default;

	virtual float GetWidth()const = 0;
	virtual float GetHeight()const = 0;

	virtual IShapes& GetShapes() = 0;
	virtual const IShapes& GetShapes()const = 0;
};

class Slide : public ISlide
{
public:
	Slide(float width, float height, uint32_t backgroundColor = std::numeric_limits<uint32_t>::max())
		: m_width(width)
		, m_height(height)
		, m_backgroundColor(backgroundColor)
	{
	}

	void Draw(ICanvas& canvas)const override
	{
		for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
		{
			m_shapes.GetShape(i)->Draw(canvas);
		}
	}

	float GetWidth()const override
	{
		return m_width;
	}

	float GetHeight()const override
	{
		return m_height;
	}

	IShapes& GetShapes() override
	{
		return m_shapes;
	}

	const IShapes& GetShapes()const override
	{
		return m_shapes;
	}

private:
	float m_width;
	float m_height;
	uint32_t m_backgroundColor;
	Shapes m_shapes;
};

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	Slide slide(100, 100);
	Rectangle rect;
	auto& style = rect.GetFillStyle();

	return 0;
}
