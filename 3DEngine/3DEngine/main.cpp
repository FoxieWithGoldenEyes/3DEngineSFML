#include <SFML/Graphics.hpp>
#include <chrono>

#include "GraphicsRenderer.h"
#include "Math.h"

sf::RenderWindow window(sf::VideoMode(800, 800, 32u), "3D Engine");

int main()
{
	// OnCreate
	//std::chrono::high_resolution_clock::time_point start;
	//std::chrono::high_resolution_clock::time_point end;

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

	// Elapsed seckonds of privious frame
	float fps;
	float fLastFrameElapsedTime = 0;
	float fTheta = 0.f;

	// Updating Frames
	while (window.isOpen())
	{
		sf::Clock clock;

		// Event queue
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) window.close();
		}

		// Clearing screen
		window.clear(sf::Color::Black);

		// Spining angle
		fTheta += 1.f * fLastFrameElapsedTime;

		// Matrix rotation Z
		Matrix4x4 matrixRotationZ;
		// Matrix neutral elements
		matrixRotationZ.elementOf[2][2] = 1;
		matrixRotationZ.elementOf[3][3] = 1;

		// Matrix modifiers
		matrixRotationZ.elementOf[0][0] = cosf(fTheta);
		matrixRotationZ.elementOf[0][1] = sinf(fTheta);
		matrixRotationZ.elementOf[1][0] = -sinf(fTheta);
		matrixRotationZ.elementOf[1][1] = cosf(fTheta);

		// Matrix rotation X
		Matrix4x4 matrixRotationX;
		// matrix neutral elements
		matrixRotationX.elementOf[0][0] = 1;
		matrixRotationX.elementOf[3][3] = 1;

		// matrix modifiers
		matrixRotationX.elementOf[1][1] = cosf(fTheta * 0.5f);
		matrixRotationX.elementOf[1][2] = sinf(fTheta * 0.5f);
		matrixRotationX.elementOf[2][1] = -sinf(fTheta * 0.5f);
		matrixRotationX.elementOf[2][2] = cosf(fTheta * 0.5f);

		// Drawing mash
		for (Triangle normalizedTriangle : cubeMesh.triangles)
		{
			// Znormalizowany Trójk¹t -> Rotacja -> Przesuniêcie -> Rzutowanie -> Skalowanie
			// Normalized Triangle -> Rotation -> Translation -> Projection -> Scaling
			
			// Rotation Z
			Triangle triangleRotatedZ;
			MultiplyMatrixVector(normalizedTriangle.points[0], triangleRotatedZ.points[0], matrixRotationZ);
			MultiplyMatrixVector(normalizedTriangle.points[1], triangleRotatedZ.points[1], matrixRotationZ);
			MultiplyMatrixVector(normalizedTriangle.points[2], triangleRotatedZ.points[2], matrixRotationZ);

			// Rotation X
			Triangle triangleRotatedZX;
			MultiplyMatrixVector(triangleRotatedZ.points[0], triangleRotatedZX.points[0], matrixRotationX);
			MultiplyMatrixVector(triangleRotatedZ.points[1], triangleRotatedZX.points[1], matrixRotationX);
			MultiplyMatrixVector(triangleRotatedZ.points[2], triangleRotatedZX.points[2], matrixRotationX);

			// Translation z -> z + 3
			Triangle triangleTranslated = triangleRotatedZX;
			triangleTranslated.points[0].z = triangleRotatedZX.points[0].z + 3.f;
			triangleTranslated.points[1].z = triangleRotatedZX.points[1].z + 3.f;
			triangleTranslated.points[2].z = triangleRotatedZX.points[2].z + 3.f;

			// Projection
			Triangle triangleProjected;
			MultiplyMatrixVector(triangleTranslated.points[0], triangleProjected.points[0], projectionMatrix);
			MultiplyMatrixVector(triangleTranslated.points[1], triangleProjected.points[1], projectionMatrix);
			MultiplyMatrixVector(triangleTranslated.points[2], triangleProjected.points[2], projectionMatrix);

			//// Scaling
			Triangle scaledTriangle = triangleProjected;
			
			// Offset point from negative -1 to 0 and from 0 to 1, anf from 1 to 2 on x, y axis
			// So thre are vertexies from <-1,1> to <0, 2> on x, y axis from now
			// Translation?...
			scaledTriangle.points[0].x += 1.f;	scaledTriangle.points[0].y += 1.f;
			scaledTriangle.points[1].x += 1.f;	scaledTriangle.points[1].y += 1.f;
			scaledTriangle.points[2].x += 1.f;	scaledTriangle.points[2].y += 1.f;

			// Divide all point par 2, to have values between <0, 1>
			// And then multiplay it by screen size
			scaledTriangle.points[0].x *= 0.5 * static_cast<float>(window.getSize().x);
			scaledTriangle.points[0].y *= 0.5 * static_cast<float>(window.getSize().y);

			scaledTriangle.points[1].x *= 0.5 * static_cast<float>(window.getSize().x);
			scaledTriangle.points[1].y *= 0.5 * static_cast<float>(window.getSize().y);
			
			scaledTriangle.points[2].x *= 0.5 * static_cast<float>(window.getSize().x);
			scaledTriangle.points[2].y *= 0.5 * static_cast<float>(window.getSize().y);

			// Drawing
			drawTriangle(
				scaledTriangle.points[0].x, scaledTriangle.points[0].y,
				scaledTriangle.points[1].x, scaledTriangle.points[1].y,
				scaledTriangle.points[2].x, scaledTriangle.points[2].y,
				sf::Color::White
			);
		}

		window.display();
		
		// FPS calculation and elapsed time
		fLastFrameElapsedTime = clock.getElapsedTime().asSeconds();
		float fps = 1.f / fLastFrameElapsedTime;
		window.setTitle("3D Engine\tFPS - " + std::to_string(fps));
	}

	return 0;
}