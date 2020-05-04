#pragma once

#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

const float PI = 3.141592653;

void DrawQuad(float lw[2], float rgba[4]);

void DrawCube(float lwh[3], float rgba[4]);

void DrawCubeInv(float lwh[3], float rgba[4]);

void DrawSphere(double offX, double offY, double offZ, double r, int lats, int longs);

void DrawChecker(int numX, int numY, float length, float width, float rgbaMain[4], float rgbaOff[4], bool offset, float shininess);

void DrawCheckerGaps(int numX, int numY, float length, float width, float rgba[4], bool offset);

void SetMaterial(float rgba[4], float shininess);

void SetMaterialf(float rgba[4], float shininess);

float* Normalize(float* vec);
