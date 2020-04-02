#include "Volume.h"

void Volume::DrawSphere(double offX, double offY, double offZ, double r, int lats, int longs, float red, float green, float blue)
{

	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		glColor3f(red, green, blue);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);
			auto a = { x * zr0, y * zr0, z0 };
			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(offX + r * x * zr0, offY + r * y * zr0, offZ + r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(offX + r * x * zr1, offY + r * y * zr1, offZ + r * z1);
		}
		glEnd();
	}
}

Volume::Volume()
{
}

Volume::Volume(float oneLength, float oneWidth, float oneHeight)
{
	length = oneLength;
	width = oneWidth;
	height = oneHeight;

	vector<vector<vector<volCube>>> tempVol;

	for (int i = 0; i < length; i++)
	{
		vector<vector<volCube>> yzVect;
		for (int j = 0; j < height; j++)
		{

			vector<volCube> zVect;
			for (int k = 0; k < width; k++)
			{
				
				volCube oneVolCube;

				oneVolCube.x = i / 1.;
				oneVolCube.y = j / 1.;
				oneVolCube.z = k / 1.;

				oneVolCube.centerX = oneVolCube.x + .5;
				oneVolCube.centerY = oneVolCube.y + .5;
				oneVolCube.centerZ = oneVolCube.z + .5;

				zVect.push_back(oneVolCube);

			}

			yzVect.push_back(zVect);

		}

		tempVol.push_back(yzVect);

	}

	copy(tempVol.begin(), tempVol.end(), back_inserter(vol));

}

void Volume::OffsetPath()
{
	for (int i = 0; i < bestPath.xyz.size(); i++)
	{
		auto oneNotOffsetNode = bestPath.xyz[i];
		oneNotOffsetNode[0] = oneNotOffsetNode[0] + .5;
		oneNotOffsetNode[1] = oneNotOffsetNode[1] + .5;
		oneNotOffsetNode[2] = oneNotOffsetNode[2] + .5;
		bestPath.centerXYZ.push_back(oneNotOffsetNode);
	}
}

void Volume::DrawPath()
{
	auto startNode = bestPath.centerXYZ[0];
	DrawSphere(startNode[0], startNode[1], startNode[2], .25, 20, 20, 0., 0., 1.);

	auto endNode = bestPath.centerXYZ[bestPath.centerXYZ.size()-1];
	DrawSphere(endNode[0], endNode[1], endNode[2], .25, 20, 20, 0., 1., 0.);

	for (int i = 1; i < bestPath.centerXYZ.size()-1; i++)
	{
		auto oneNode = bestPath.centerXYZ[i];
		DrawSphere(oneNode[0], oneNode[1], oneNode[2], .25, 20, 20, 1., 0., 0.);
	}
	
}
