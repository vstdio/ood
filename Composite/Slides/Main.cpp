#include "stdafx.h"
#include "Vector2D.h"
#include <boost/optional.hpp>

class LineStyle
{
public:
	LineStyle(boost::optional<uint32_t> color, unsigned thickness)
		: m_color(color)
		, m_thickness(thickness)
	{
	}

	boost::optional<uint32_t> GetColor()const
	{
		return m_color;
	}

	void SetColor(boost::optional<uint32_t> color)
	{
		m_color = color;
	}

	unsigned GetThickness()const
	{
		return m_thickness;
	}

	void SetThickness(unsigned thickness)
	{
		m_thickness = thickness;
	}

private:
	boost::optional<uint32_t> m_color;
	unsigned m_thickness;
};

class FillStyle
{
public:
	FillStyle(boost::optional<uint32_t> color)
		: m_color(color)
	{
	}

	boost::optional<uint32_t> GetColor()const
	{
		return m_color;
	}

	void SetColor(boost::optional<uint32_t> color)
	{
		m_color = color;
	}

private:
	boost::optional<uint32_t> m_color;
};

class Frame
{
public:
	Frame(const Point2D& leftTop, float width, float height)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	void Resize(float width, float height)
	{
		m_width = width;
		m_height = height;
	}

private:
	Point2D m_leftTop;
	float m_width;
	float m_height;
};

class ICanvas
{
public:
	virtual void DrawLine(const Point2D& from, const Point2D& to) = 0;
	virtual void FillPolygon(const std::vector<Point2D>& points) = 0;

	virtual void DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) = 0;
	virtual void FillEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) = 0;

	virtual void SetFillColor(uint32_t fillColor) = 0;
	virtual void SetOutlineColor(uint32_t outlineColor) = 0;
	virtual void SetOutlineThickness(unsigned thickness) = 0;
};

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas)const = 0;
};

class Shape : public ICanvasDrawable
{
public:
	Shape(const Frame& frame, const LineStyle& lineStyle, const FillStyle& fillStyle)
		: m_frame(frame)
		, m_lineStyle(lineStyle)
		, m_fillStyle(fillStyle)
	{
	}

	void SetLineStyle()
	{
	}

private:
	LineStyle m_lineStyle;
	FillStyle m_fillStyle;
	Frame m_frame;
};

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

class CompositeShape : public Shape
{
public:
	CompositeShape()
	{
	}

private:
	Frame m_frame;
	std::vector<std::unique_ptr<Shape>> m_components;
};

class Slide : public ICanvasDrawable
{
public:
	void Draw(ICanvas& canvas)const override
	{
		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

private:
	std::vector<std::unique_ptr<Shape>> m_shapes;
};

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	Slide slide;
	(void)slide;

	return 0;
}
