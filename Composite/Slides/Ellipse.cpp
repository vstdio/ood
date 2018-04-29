#include "stdafx.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Point2D& center, float horizontalRadius, float verticalRadius)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

const Point2D& Ellipse::GetCenter()const
{
	return m_center;
}

float Ellipse::GetHorizontalRadius()const
{
	return m_horizontalRadius;
}

float Ellipse::GetVerticalRadius()const
{
	return m_verticalRadius;
}

void Ellipse::StrokeDrawImpl(ICanvas& canvas)const
{
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

void Ellipse::FillDrawImpl(ICanvas& canvas)const
{
	canvas.FillEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}
