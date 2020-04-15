#include "Volume.h"

vector<vector<vector<int>>> Volume::GetVolumeStates()
{

	vector<vector<vector<int>>> volStates;

	for (int i = 0; i < length; i++)
	{
		vector<vector<int>> yzVect;
		for (int j = 0; j < height; j++)
		{

			vector<int> zVect;
			for (int k = 0; k < width; k++)
			{

				zVect.push_back(vol[i][j][k].blocked);

			}

			yzVect.push_back(zVect);

		}

		volStates.push_back(yzVect);

	}

	return volStates;

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
	float rgbaStart[4] = { 0.,0.,255.,255. };
	float shininessStart = 60.;
	SetMaterial(rgbaStart, shininessStart);
	DrawSphere(startNode[0], startNode[1], startNode[2], .25, 20, 20);

	auto endNode = bestPath.centerXYZ[bestPath.centerXYZ.size()-1];
	float rgbaEnd[4] = { 0.,255.,0.,255. };
	float shininessEnd = 60.;
	SetMaterial(rgbaEnd, shininessEnd);
	DrawSphere(endNode[0], endNode[1], endNode[2], .25, 20, 20);

	float rgbaMid[4] = { 255.,0.,0.,255. };
	float shininessMid = 60.;
	SetMaterial(rgbaMid, shininessMid);
	for (int i = 1; i < bestPath.centerXYZ.size()-1; i++)
	{
		auto oneNode = bestPath.centerXYZ[i];
		DrawSphere(oneNode[0], oneNode[1], oneNode[2], .25, 20, 20);
	}
	
}
