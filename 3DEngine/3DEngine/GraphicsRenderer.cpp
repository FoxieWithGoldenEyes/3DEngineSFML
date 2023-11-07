#include "GraphicsRenderer.h"

void drawPoint(float x, float y, sf::Color color)
{
	if (window.isOpen() == false) return;

	sf::Vertex vertex(sf::Vector2f(x, y), sf::Color::Black);
	window.draw(&vertex, 1, sf::Points);
}

void drawLine(float x1, float y1, float x2, float y2, sf::Color color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1), color),
		sf::Vertex(sf::Vector2f(x2, y2), color)
	};
	window.draw(line, 2, sf::Lines);
}

void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::Color color)
{
	sf::ConvexShape convexShape;
	convexShape.setFillColor(color);
	convexShape.setPointCount(3);
	convexShape.setPoint(0, sf::Vector2f(x1, y1));
	convexShape.setPoint(1, sf::Vector2f(x2, y2));
	convexShape.setPoint(2, sf::Vector2f(x3, y3));

	window.draw(convexShape);
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::Color color)
{
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x3, y3, color);
	drawLine(x3, y3, x1, y1, color);
}

/// <summary>
/// Retutns a color between white and black depends on luminescence value
/// </summary>
/// <param name="lum"> A value between 0 and 1</param>
/// <returns></returns>
sf::Color GetColor(float lum)
{
    constexpr sf::Uint8 maxValue = std::numeric_limits<sf::Uint8>::max();
    sf::Uint8 colorIntensity = static_cast<int>(maxValue * lum);
    sf::Color color(lum * colorIntensity, lum * colorIntensity, lum * colorIntensity);
	return color;
}