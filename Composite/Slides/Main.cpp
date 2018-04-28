#include "stdafx.h"
#include "Vector2D.h"
#include <boost/optional.hpp>
#include <memory>
#include "CommonTypes.h"

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;

	virtual bool IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual void SetColor(uint32_t color) = 0;
	virtual uint32_t GetColor()const = 0;
};

class IOutlineStyle
{
public:
	virtual ~IOutlineStyle() = default;

	virtual bool IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual void SetColor(uint32_t color) = 0;
	virtual uint32_t GetColor()const = 0;

	virtual void SetThickness(unsigned thickness) = 0;
	virtual unsigned GetThickness()const = 0;
};

class OutlineStyle : public IOutlineStyle
{
public:
	OutlineStyle(uint32_t color = 0, unsigned thickness = 1)
		: m_color(color)
		, m_thickness(thickness)
		, m_enabled(true)
	{
	}

	bool IsEnabled()const override
	{
		return m_enabled;
	}

	void Enable(bool enable) override
	{
		m_enabled = enable;
	}

	uint32_t GetColor()const override
	{
		return m_color;
	}

	void SetColor(uint32_t color) override
	{
		m_color = color;
	}

	unsigned GetThickness()const override
	{
		return m_thickness;
	}

	void SetThickness(unsigned thickness) override
	{
		m_thickness = thickness;
	}

private:
	uint32_t m_color;
	unsigned m_thickness;
	bool m_enabled;
};

class FillStyle : public IFillStyle
{
public:
	FillStyle(uint32_t color = 0)
		: m_color(color)
	{
	}

	bool IsEnabled()const override
	{
		return m_enabled;
	}

	void Enable(bool enable) override
	{
		m_enabled = enable;
	}

	uint32_t GetColor()const override
	{
		return m_color;
	}

	void SetColor(uint32_t color) override
	{
		m_color = color;
	}

private:
	uint32_t m_color;
	bool m_enabled;
};

class ICanvas
{
public:
	virtual ~ICanvas() = default;

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
	virtual ~ICanvasDrawable() = default;
	virtual void Draw(ICanvas& canvas)const = 0;
};

class IShape
{
public:
	virtual ~IShape() = default;

	virtual Rect<float> GetFrame()const = 0;
	virtual void SetFrame(const Rect<float>& frame) = 0;

	virtual void SetFillStyle(std::unique_ptr<IFillStyle>&& fillStyle) = 0;
	virtual const IFillStyle& GetFillStyle()const = 0;
	virtual IFillStyle& GetFillStyle() = 0;

	virtual void SetOutlineStyle(std::unique_ptr<IOutlineStyle>&& outlineStyle) = 0;
	virtual const IOutlineStyle& GetOutlineStyle()const = 0;
	virtual IOutlineStyle& GetOutlineStyle() = 0;
};

class Shape : public IShape
{
public:
	virtual ~Shape() = default;

	Rect<float> GetFrame()const override
	{
		return m_frame;
	}

	void SetFrame(const Rect<float>& frame) override
	{
		m_frame = frame;
	}

	void SetFillStyle(std::unique_ptr<IFillStyle>&& fillStyle) override
	{
		m_fillStyle = std::move(fillStyle);
	}

	const IFillStyle& GetFillStyle()const override
	{
		return *m_fillStyle;
	}

	IFillStyle& GetFillStyle() override
	{
		return *m_fillStyle;
	}

	void SetOutlineStyle(std::unique_ptr<IOutlineStyle>&& outlineStyle) override
	{
		m_outlineStyle = std::move(outlineStyle);
	}

	const IOutlineStyle& GetOutlineStyle()const override
	{
		return *m_outlineStyle;
	}

	IOutlineStyle& GetOutlineStyle() override
	{
		return *m_outlineStyle;
	}

private:
	std::unique_ptr<IFillStyle> m_fillStyle;
	std::unique_ptr<IOutlineStyle> m_outlineStyle;
	Rect<float> m_frame;
};

class Rectangle : public IShape
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

	void AddShape(std::unique_ptr<IShape>&& shape, boost::optional<size_t> index = boost::none)
	{
		if (!index)
		{
			m_components.push_back(std::move(shape));
		}
		else
		{
			if (*index >= m_components.size())
			{
				throw std::invalid_argument("Index must be less than components count");
			}
			m_components.insert(m_components.begin() + *index, std::move(shape));
		}
	}

	void RemoveShape(boost::optional<size_t> index)
	{

		if (index >= m_components.size())
		{
			throw std::invalid_argument("Index must be less than components count");
		}
	}

private:
	std::vector<std::unique_ptr<IShape>> m_components;
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

	unsigned GetWidth()const
	{
		return m_width;
	}

	unsigned GetHeight()const
	{
		return m_height;
	}

private:
	unsigned m_width;
	unsigned m_height;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	Slide slide;
	(void)slide;

	return 0;
}
