#include "draw.h"
#include "XTime.h"

#define SORT 1

XTime timer;

int main()
{
	RS_Initialize(REZ_X, REZ_Y);

	timer.Restart();
#if SORT
	//Face 1
	original.v1.point = { -0.25,  0.5, -0.25, 1.0f };
	original.v1.color = 0xFF00FF00;
	original.v1.U = 0.0;
	original.v1.V = 0.0;

	original.v2.point = { 0.25,  0.5, -0.25, 1.0f };
	original.v2.color = 0xFF00FF00;
	original.v2.U = 1.0;
	original.v2.V = 0.0;

	original.v3.point = { -0.25,  0  , -0.25, 1.0f };
	original.v3.color = 0xFF00FF00;
	original.v3.U = 0.0;
	original.v3.V = 1.0;

	original.v4.point = { 0.25,  0  , -0.25, 1.0f };
	original.v4.color = 0xFF00FF00;
	original.v4.U = 1.0;
	original.v4.V = 1.0;


	//Face 2
	original.v5.point = { 0.25,  0.5,  -0.25, 1.0f };
	original.v5.color = 0xFF00FF00;
	original.v5.U = 0.0;
	original.v5.V = 0.0;

	original.v6.point = { 0.25,  0.5,  0.25, 1.0f };
	original.v6.color = 0xFF00FF00;
	original.v6.U = 1.0;
	original.v6.V = 0.0;

	original.v7.point = { 0.25,  0  ,  0.25, 1.0f };
	original.v7.color = 0xFF00FF00;
	original.v7.U = 1.0;
	original.v7.V = 1.0;

	original.v8.point = { 0.25,  0  ,  -0.25, 1.0f };
	original.v8.color = 0xFF00FF00;
	original.v8.U = 0.0;
	original.v8.V = 1.0;

	//Face 3
	original.v9.point = { 0.25,  0.5,  0.25, 1.0f };
	original.v9.color = 0xFF00FF00;
	original.v9.U = 0.0;
	original.v9.V = 0.0;

	original.v10.point = { -0.25,  0.5,  0.25, 1.0f };
	original.v10.color = 0xFF00FF00;
	original.v10.U = 1.0;
	original.v10.V = 0.0;

	original.v11.point = { -0.25,  0.0,  0.25, 1.0f };
	original.v11.color = 0xFF00FF00;
	original.v11.U = 1.0;
	original.v11.V = 1.0;

	original.v12.point = { 0.25,  0.0,  0.25, 1.0f };
	original.v12.color = 0xFF00FF00;
	original.v12.U = 0.0;
	original.v12.V = 1.0;

	//Face 4
	original.v13.point = { -0.25,  0.5,  0.25, 1.0f };
	original.v13.color = 0xFF00FF00;
	original.v13.U = 0.0;
	original.v13.V = 0.0;

	original.v14.point = { -0.25,  0.5,  -0.25, 1.0f };
	original.v14.color = 0xFF00FF00;
	original.v14.U = 1.0;
	original.v14.V = 0.0;

	original.v15.point = { -0.25,  0.0,  -0.25, 1.0f };
	original.v15.color = 0xFF00FF00;
	original.v15.U = 1.0;
	original.v15.V = 1.0;

	original.v16.point = { -0.25,  0.0,  0.25, 1.0f };
	original.v16.color = 0xFF00FF00;
	original.v16.U = 0.0;
	original.v16.V = 1.0;
#endif

	for (unsigned int i = 0; i < 11; ++i)
	{
		gridTop[i].point.x = i * 0.1f - 0.5f;
		gridTop[i].point.y = 0.0;
		gridTop[i].point.z = 0.5;
		gridTop[i].point.w = 1;
		gridTop[i].color = 0xFFFFFFFF;

		gridLeft[i].point.x = -0.5;
		gridLeft[i].point.y = 0.0;
		gridLeft[i].point.z = i * 0.1f - 0.5f;
		gridLeft[i].point.w = 1;
		gridLeft[i].color = 0xFFFFFFFF;


		gridBottom[i].point.x = i * 0.1f - 0.5f;
		gridBottom[i].point.y = 0;
		gridBottom[i].point.z = -0.5;
		gridBottom[i].point.w = 1;
		gridBottom[i].color = 0xFFFFFFFF;

		gridRight[i].point.x = 0.5;
		gridRight[i].point.y = 0.0;
		gridRight[i].point.z = i * 0.1f - 0.5f;
		gridRight[i].point.w = 1;
		gridRight[i].color = 0xFFFFFFFF;
	}

	matrix4 r = matrix4Xrot(-18.0f*(float)RADS);
	vec3f v = { 0, 0, -1 };
	matrix4 t = matrix4trans(v);

	matrix4 cameraMatrix = matrix4Multiply(t, r);
	
	SV_PerspectiveMatrix = perspectiveMatrix(90, (float)REZ_Y / REZ_X, 0.1f, 10.0f);

	float theta = 0;
	float delta = 0;
	float moveSpeed = 1.0f;

	while (RS_Update(colorArray, REZ_X*REZ_Y))
	{
		clearBuffer(0x00000000);

		timer.Signal();
		theta += (float)timer.Delta();
		delta = (float)timer.Delta();

		//KeyStates
		if (GetAsyncKeyState('W'))
			cameraMatrix = matrix4Multiply(matrix4trans({ 0, delta*moveSpeed, 0 }), cameraMatrix);
		if (GetAsyncKeyState('S'))
			cameraMatrix = matrix4Multiply(matrix4trans({ 0, -delta*moveSpeed, 0 }), cameraMatrix);
		if (GetAsyncKeyState('A'))
			cameraMatrix = matrix4Multiply(matrix4trans({ -delta*moveSpeed, 0, 0 }), cameraMatrix);
		if (GetAsyncKeyState('D'))
			cameraMatrix = matrix4Multiply(matrix4trans({ delta*moveSpeed, 0, 0 }), cameraMatrix);
		if (GetAsyncKeyState(VK_UP))
			cameraMatrix = matrix4Multiply(matrix4trans({ 0, 0, delta*moveSpeed }), cameraMatrix);
		if (GetAsyncKeyState(VK_DOWN))
			cameraMatrix = matrix4Multiply(matrix4trans({ 0, 0, -delta*moveSpeed }), cameraMatrix);

		SV_ViewMatrix = matrix4Inverse(cameraMatrix);
	
		VertexShader = VS_World;
		PixelShader = PS_Green;

		SV_WorldMatrix = identiyMatrix();
		for (unsigned int i = 0; i < 11; i++)
		{
			drawLine(gridTop[i], gridBottom[i]);
			drawLine(gridLeft[i], gridRight[i]);
		}

		PixelShader = PS_Yellow;
		SV_WorldMatrix = matrix4Yrot(theta);

		drawLine(original.v1, original.v2);
		drawLine(original.v2, original.v4);
		drawLine(original.v4, original.v3);
		drawLine(original.v3, original.v1);

		drawLine(original.v9, original.v10);
		drawLine(original.v10, original.v11);
		drawLine(original.v11, original.v12);
		drawLine(original.v12, original.v9);

		drawLine(original.v1, original.v10);
		drawLine(original.v2, original.v9);
		drawLine(original.v3, original.v11);
		drawLine(original.v4, original.v12);

		//filling triangles

		PixelShader = PS_Tree;

		//front face
		colorTriangle(original.v1, original.v2, original.v3);      //0xFF00FF00);
		colorTriangle(original.v4, original.v3, original.v2);      //0xFF641E16);

		//right face
		colorTriangle(original.v5, original.v6, original.v8);      //0xFF512E5F);
		colorTriangle(original.v6, original.v8, original.v7);      //0xFF154360);

		//back face
		colorTriangle(original.v9, original.v10, original.v12);      //0xFF0B5345);
		colorTriangle(original.v10, original.v12, original.v11);      //0xFF7D6608);

		//left face
		colorTriangle(original.v13, original.v14, original.v16);      //0xFF6E2C00);
		colorTriangle(original.v14, original.v16, original.v15);      //0xFF7B7D7D);

	}

	RS_Shutdown();
	return 0;
}