#include <SFML/Graphics.hpp>

#include "GraphicsRenderer.h"
#include "Math.h"

sf::RenderWindow window(sf::VideoMode(800, 800, 32u), "3D Engine");

int main()
{
	// OnCreate
	Mesh cubeMesh = 
	// inicjalizer brakets
	{
		// vector brakets
		{
			// SOUTH
			{ 0.f, 0.f, 0.f,    0.f, 1.f, 0.f,    1.f, 1.f, 0.f },
			{ 0.f, 0.f, 0.f,    1.f, 1.f, 0.f,    1.f, 0.f, 0.f },

			// EAST
			{ 1.f, 0.f, 0.f,    1.f, 1.f, 0.f,    1.f, 1.f, 1.f },
			{ 1.f, 0.f, 0.f,    1.f, 1.f, 1.f,    1.f, 0.f, 1.f },

			// NORTH
			{ 1.f, 0.f, 1.f,    1.f, 1.f, 1.f,    0.f, 1.f, 1.f },
			{ 1.f, 0.f, 1.f,    0.f, 1.f, 1.f,    0.f, 0.f, 1.f },

			// WEST
			{ 0.f, 0.f, 1.f,    0.f, 1.f, 1.f,    0.f, 1.f, 0.f },
			{ 0.f, 0.f, 1.f,    0.f, 1.f, 0.f,    0.f, 0.f, 0.f },

			// TOP
			{ 0.f, 1.f, 0.f,    0.f, 1.f, 1.f,    1.f, 1.f, 1.f },
			{ 0.f, 1.f, 0.f,    1.f, 1.f, 1.f,    1.f, 1.f, 0.f },

			// BOTTOM
			{ 1.f, 0.f, 1.f,    0.f, 0.f, 1.f,    0.f, 0.f, 0.f },
			{ 1.f, 0.f, 1.f,    0.f, 0.f, 0.f,    1.f, 0.f, 0.f },

		}	// end of vector brakets
	};	// end of inicjalizer brakets

	// Projection matrix !!!!!!!!!!!
	float fNear = 0.1;
	float fFar = 1000;
	float fFov = 90;
	float fAspectRatio = window.getSize().y / static_cast<float>(window.getSize().x);
	float fFovRad = 1.0f / tanf(fFov * 0.5 /180 * 3.14159f);

	Matrix4x4 projectionMatrix;
	projectionMatrix.elementOf[0][0] = fAspectRatio * fFovRad;
	projectionMatrix.elementOf[1][1] = fFovRad;
	projectionMatrix.elementOf[2][2] = fFar / (fFar - fNear);
	projectionMatrix.elementOf[3][2] = (-fFar * fNear) / (fFar - fNear);
	projectionMatrix.elementOf[2][3] = 1.f;
	projectionMatrix.elementOf[3][3] = 0.f;

	// Updating Frames
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::Black);

		// Spin
		Matrix4x4 matRotZ, matRotX;

		// Drawings
		for (auto triangle : cubeMesh.triangles)
		{
			Triangle projectedTriangle, translatedTriangle;

			translatedTriangle = triangle;
			translatedTriangle.points[0].z = triangle.points[0].z + 3.0f;
			translatedTriangle.points[1].z = triangle.points[1].z + 3.0f;
			translatedTriangle.points[2].z = triangle.points[2].z + 3.0f;

			MultiplyMatrixVector(translatedTriangle.points[0], projectedTriangle.points[0], projectionMatrix);
			MultiplyMatrixVector(translatedTriangle.points[1], projectedTriangle.points[1], projectionMatrix);
			MultiplyMatrixVector(translatedTriangle.points[2], projectedTriangle.points[2], projectionMatrix);

			// Scale into view
			projectedTriangle.points[0].x += 1.f;	projectedTriangle.points[0].y += 1.f;
			projectedTriangle.points[1].x += 1.f;	projectedTriangle.points[1].y += 1.f;
			projectedTriangle.points[2].x += 1.f;	projectedTriangle.points[2].y += 1.f;

			projectedTriangle.points[0].x *= 0.5 * static_cast<float>(window.getSize().x);
			projectedTriangle.points[0].y *= 0.5 * static_cast<float>(window.getSize().y);
			projectedTriangle.points[1].x *= 0.5 * static_cast<float>(window.getSize().x);
			projectedTriangle.points[1].y *= 0.5 * static_cast<float>(window.getSize().y);
			projectedTriangle.points[2].x *= 0.5 * static_cast<float>(window.getSize().x);
			projectedTriangle.points[2].y *= 0.5 * static_cast<float>(window.getSize().y);

			drawTriangle(
				projectedTriangle.points[0].x, projectedTriangle.points[0].y,
				projectedTriangle.points[1].x, projectedTriangle.points[1].y,
				projectedTriangle.points[2].x, projectedTriangle.points[2].y,
				sf::Color::White
			);
		}

		window.display();
	}

	return 0;
}