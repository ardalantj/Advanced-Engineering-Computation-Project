#include "Drawing_jwoodfor.h"

void DrawQuad(float lw[2], float rgba[4])
{

	float length = lw[0];
	float width = lw[1];

	float r = rgba[0];
	float g = rgba[1];
	float b = rgba[2];
	float a = rgba[3];

	GLfloat vertices[] = { 0, 0, 0,
							0 + length, 0, 0,
							0 + length, 0, 0 + width,
							0, 0, 0 + width };

	GLfloat colors[] = { r, g, b, a,
							r, g, b, a,
							r, g, b, a,
							r, g, b, a };

	GLfloat normals[] = { 0.,1.,0.,  0.,1.,0.,  0.,1.,0.,  0.,1.,0. };

	GLubyte indices[] = { 3, 2, 1, 0 };

	glColorPointer(4, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normals);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);

}

void DrawCube(float lwh[3], float rgba[4])
{

	float length = lwh[0];
	float width = lwh[1];
	float height = lwh[2];

	float r = rgba[0] / 255.;
	float g = rgba[1] / 255.;
	float b = rgba[2] / 255.;
	float a = rgba[3] / 255.;

	GLfloat verticies[] = { 0.,height,0.,			0.,height,width,		length,height,width,    length,height,0.,
							0.,0.,0.,				length,0.,0.,			length,0.,width,		0.,0.,width,
							0.,0.,0.,				0.,0.,width,			0.,height,width,		0.,height,0.,
							length,0.,0.,			length,0.,width,		length,height,width,	length,height,0.,
							length,0.,width,		0.,0.,width,			0.,height,width,		length,height,width,
							0.,0.,0.,				length,0.,0.,			length,height,0.,		0.,height,0. };

	GLfloat colors[] = { r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a };

	GLfloat normals[] = { 0.,1.,0.,  0.,1.,0.,  0.,1.,0.,  0.,1.,0.,
							0.,-1.,0.,  0.,-1.,0.,  0.,-1.,0.,  0.,-1.,0.,
							-1.,0.,0.,  -1.,0.,0.,  -1.,0.,0.,  -1.,0.,0.,
							1.,0.,0.,  1.,0.,0.,  1.,0.,0.,  1.,0.,0.,
							0.,0,1.,  0.,0,1.,  0.,0,1.,  0.,0,1.,
							0.,0.,-1.,  0.,0.,-1.,   0.,0.,-1.,   0.,0.,-1. };

	GLubyte indices[] = { 0,1,2,3,
							4,5,6,7,
							8,9,10,11,
							15,14,13,12,
							19,18,17,16,
							23,22,21,20 };


	glColorPointer(4, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verticies);
	glNormalPointer(GL_FLOAT, 0, normals);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);





}


void DrawCubeInv(float lwh[3], float rgba[4])
{

	float length = lwh[0];
	float width = lwh[1];
	float height = lwh[2];

	float r = rgba[0] / 255.;
	float g = rgba[1] / 255.;
	float b = rgba[2] / 255.;
	float a = rgba[3] / 255.;

	//GLfloat rgbaGLfloat[] = { r,g,b,a };
	//GLfloat fwhite[] = { 1.,1.,1.,1. };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, rgbaGLfloat);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, rgbaGLfloat);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, fwhite);
	//glMaterialf(GL_FRONT, GL_SHININESS, 60.);

	GLfloat verticies[] = { 0.,height,0.,			0.,height,width,		length,height,width,    length,height,0.,
							0.,0.,0.,				length,0.,0.,			length,0.,width,		0.,0.,width,
							0.,0.,0.,				0.,0.,width,			0.,height,width,		0.,height,0.,
							length,0.,0.,			length,0.,width,		length,height,width,	length,height,0.,
							length,0.,width,		0.,0.,width,			0.,height,width,		length,height,width,
							0.,0.,0.,				length,0.,0.,			length,height,0.,		0.,height,0. };

	GLfloat colors[] = { r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a,
							r,g,b,a };

	GLfloat normals[] = { 0.,-1.,0.,  0.,-1.,0.,  0.,-1.,0.,  0.,-1.,0.,
							0.,1.,0.,  0.,1.,0.,  0.,1.,0.,  0.,1.,0.,
							1.,0.,0.,  1.,0.,0.,  1.,0.,0.,  1.,0.,0.,
							-1.,0.,0.,  -1.,0.,0.,  -1.,0.,0.,  -1.,0.,0.,
							0.,0,-1.,  0.,0,-1.,  0.,0,-1.,  0.,0,-1.,
							0.,0.,1.,  0.,0.,1.,   0.,0.,1.,   0.,0.,1. };

	GLubyte indices[] = { 3,2,1,0,
							7,6,5,4,
							11,10,9,8,
							12,13,14,15,
							16,17,18,19,
							20,21,22,23 };


	glColorPointer(4, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verticies);
	glNormalPointer(GL_FLOAT, 0, normals);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);





}

void DrawSphere(double offX, double offY, double offZ, double r, int lats, int longs)
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
		//glColor3f(red, green, blue);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);
			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(offX + r * x * zr0, offY + r * y * zr0, offZ + r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(offX + r * x * zr1, offY + r * y * zr1, offZ + r * z1);
		}
		glEnd();
	}
}

void DrawChecker(int numX, int numY, float length, float width, float rgbaMain[4], float rgbaOff[4], bool offset, float shininess)
{
	float rMain = rgbaMain[0] / 255.;
	float gMain = rgbaMain[1] / 255.;
	float bMain = rgbaMain[2] / 255.;
	float aMain = rgbaMain[3] / 255.;

	float rOff = rgbaOff[0] / 255.;
	float gOff = rgbaOff[1] / 255.;
	float bOff = rgbaOff[2] / 255.;
	float aOff = rgbaOff[3] / 255.;

	float rgbaChecker[4] = { 0.,0.,0.,0. };

	bool currTile = offset;
	for (int i = 0; i < numX; i += 1)
	{
		currTile = !currTile;

		for (int j = 0; j < numY; j += 1)
		{

			if (currTile)
			{
				rgbaChecker[0] = rMain;
				rgbaChecker[1] = gMain;
				rgbaChecker[2] = bMain;
				rgbaChecker[3] = aMain;
			}
			else
			{
				rgbaChecker[0] = rOff;
				rgbaChecker[1] = gOff;
				rgbaChecker[2] = bOff;
				rgbaChecker[3] = aOff;
			}

			glPushMatrix();
			float lw[2] = { length, width };
			glTranslatef(i * length, 0., j * width);
			SetMaterialf(rgbaChecker, shininess);
			DrawQuad(lw, rgbaChecker);
			glPopMatrix();

			currTile = !currTile;

		}
	}

	//for (int i = 1; i < numX; i += 2)
	//{
	//	currTile = !offset;

	//	for (int j = 1-offset; j < numY; j += 1)
	//	{

	//		if (currTile)
	//		{
	//			rgbaChecker[0] = rMain;
	//			rgbaChecker[1] = gMain;
	//			rgbaChecker[2] = bMain;
	//			rgbaChecker[3] = aMain;
	//		}
	//		else
	//		{
	//			rgbaChecker[0] = rOff;
	//			rgbaChecker[1] = gOff;
	//			rgbaChecker[2] = bOff;
	//			rgbaChecker[3] = aOff;
	//		}

	//		glPushMatrix();
	//		float lw[2] = { length, width };
	//		glTranslatef(i * length, 0., j * width);
	//		SetMaterialf(rgbaChecker, shininess);
	//		DrawQuad(lw, rgbaChecker);
	//		glPopMatrix();

	//		currTile = !currTile;

	//	}
	//}

	//for (int i = 1; i < numX; i += 2)
	//{
	//	for (int j = 1 - offset; j < numY; j += 2)
	//	{

	//		glPushMatrix();

	//		float lw[2] = { length, width };

	//		glTranslatef(i * length, 0., j * width);

	//		DrawQuad(lw, rgbaCheckerMain);

	//		glPopMatrix();

	//	}
	//}

}

void DrawCheckerGaps(int numX, int numY, float length, float width, float rgba[4], bool offset)
{

	float r = rgba[0] / 255.;
	float g = rgba[1] / 255.;
	float b = rgba[2] / 255.;
	float a = rgba[3] / 255.;

	float rgbaChecker[4] = { r,g,b,a };

	for (int i = 0; i < numX; i += 2)
	{
		for (int j = offset; j < numY; j += 2)
		{

			glPushMatrix();

			float lw[2] = { length, width };

			glTranslatef(i * length, 0., j * width);

			DrawQuad(lw, rgbaChecker);

			glPopMatrix();

		}
	}

	for (int i = 1; i < numX; i += 2)
	{
		for (int j = 1-offset; j < numY; j += 2)
		{

			glPushMatrix();

			float lw[2] = { length, width };

			glTranslatef(i * length, 0., j * width);

			DrawQuad(lw, rgbaChecker);

			glPopMatrix();

		}
	}

}



void SetMaterial(float rgba[4], float shininess)
{
	float r = rgba[0] / 255.;
	float g = rgba[1] / 255.;
	float b = rgba[2] / 255.;
	float a = rgba[3] / 255.;

	GLfloat rgbaGLfloat[] = { r,g,b,a };
	GLfloat fwhite[] = { 1.,1.,1.,1. };
	glMaterialfv(GL_FRONT, GL_AMBIENT, rgbaGLfloat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rgbaGLfloat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, fwhite);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void SetMaterialf(float rgba[4], float shininess)
{
	float r = rgba[0];
	float g = rgba[1];
	float b = rgba[2];
	float a = rgba[3];

	GLfloat rgbaGLfloat[] = { r,g,b,a };
	GLfloat fwhite[] = { 1.,1.,1.,1. };
	glMaterialfv(GL_FRONT, GL_AMBIENT, rgbaGLfloat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, rgbaGLfloat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, fwhite);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

float* Normalize(float* vec)
{
	float vx = vec[0];
	float vy = vec[1];
	float vz = vec[2];

	float normDiv = sqrt(pow(vx, 2.) + pow(vy, 2.) + pow(vz, 2.));

	vx /= normDiv;
	vy /= normDiv;
	vz /= normDiv;

	float normVec[3] = { vx,vy,vz };

	return normVec;
}
