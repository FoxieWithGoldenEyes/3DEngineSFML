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

// Siatka obiektu sk�adaj�ca si� z tr�jk�t�
struct Mesh
{
	std::vector<Triangle> triangles;
};

struct Matrix4x4
{
	float elementOf[4][4] = { 0 };
};

void MultiplyMatrixVector(Vec3d& i, Vec3d& o, Matrix4x4& m);