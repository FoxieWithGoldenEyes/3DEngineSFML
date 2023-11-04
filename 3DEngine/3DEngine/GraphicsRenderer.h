#pragma once
#include <SFML/Graphics.hpp>


void drawPoint(float x, float y, sf::Color color);

void drawLine(float x1, float y1, float x2, float y2, sf::Color color);

void drawFilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::Color color);

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::Color color);

sf::Color GetColor(float lum);

extern sf::RenderWindow window;