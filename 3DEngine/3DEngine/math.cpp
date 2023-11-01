#include "Math.h"

void MultiplyMatrixVector(Vec3d& i, Vec3d& o, Matrix4x4& m)
{
	o.x = i.x * m.elementOf[0][0] + i.y * m.elementOf[1][0] + i.z * m.elementOf[2][0] + m.elementOf[3][0];
	o.y = i.x * m.elementOf[0][1] + i.y * m.elementOf[1][1] + i.z * m.elementOf[2][1] + m.elementOf[3][1];
	o.z = i.x * m.elementOf[0][2] + i.y * m.elementOf[1][2] + i.z * m.elementOf[2][2] + m.elementOf[3][2];
	float w = i.x * m.elementOf[0][3] + i.y * m.elementOf[1][3] + i.z * m.elementOf[2][3] + m.elementOf[3][3];

	if (w != 0.f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
}