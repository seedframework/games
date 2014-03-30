#include "camera_manager.h"

CameraManager::CameraManager()
	: pCamera(NULL)
	, cOffset(-400.0f, -300.0f, 0.0f)
	, cArea(-400.0f, -300.0f, 800.0f, 600.0f)
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::SetCamera(Camera *cam)
{
	pCamera = cam;
}

void CameraManager::SetArea(const Rect4f &area)
{
	cArea = area;
}

void CameraManager::LookAt(const vec3 &pos)
{
	/*
	Texel/Raster bug - arrendodar a posicao da camera para pixel-perfect.
	*/
	auto p = pos + cOffset;
	auto x = s32(p.x);
	auto y = s32(p.y);
	auto z = p.z;

	auto halfScreenWidth = s32(pScreen->GetWidth() / 2);
	auto halfScreenHeight = s32(pScreen->GetHeight() / 2);

	if (x < cArea.x1 - 16)
		x = cArea.x1 - 16;

	if (y < cArea.y1 - 16)
		y = cArea.y1 - 16;

	if (y > cArea.y2 - 16 - halfScreenHeight * 2)
		y = cArea.y2 - 16 - halfScreenHeight * 2;

	if (x > (cArea.x2 - 16 - halfScreenWidth * 2))
		x = cArea.x2 - 16 - halfScreenWidth * 2;

	vec3 np(f32(x), f32(y), z);
	pCamera->SetPosition(np);
}
