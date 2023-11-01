#pragma once
#include <vector>

struct Vec3d
{
	float x, y, z;
};

struct Triangle
{
	Vec3d points[3];
};

// Siatka obiektu sk³adaj¹ca siê z trójk¹tó
struct Mesh
{
	std::vector<Triangle> triangles;
};

struct Matrix4x4
{
	float elementOf[4][4] = { 0 };
};

void MultiplyMatrixVector(Vec3d& input, Vec3d& output, Matrix4x4& matrix);