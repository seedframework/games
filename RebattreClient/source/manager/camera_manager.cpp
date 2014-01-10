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

void CameraManager::LookAt(const Vector3f &pos)
{
	/*
	Texel/Raster bug - arrendodar a posicao da camera para pixel-perfect.
	*/
	Vector3f p = pos + cOffset;
	s32 x = static_cast<s32>(p.getX());
	s32 y = static_cast<s32>(p.getY());
	f32 z = p.getZ();

	s32 halfScreenWidth = pScreen->GetWidth() / 2;
	s32 halfScreenHeight = pScreen->GetHeight() / 2;

	if (x < cArea.x1 - 16)
		x = cArea.x1 - 16;

	if (y < cArea.y1 - 16)
		y = cArea.y1 - 16;

	if (y > cArea.y2 - 16 - halfScreenHeight * 2)
		y = cArea.y2 - 16 - halfScreenHeight * 2;

	if (x > (cArea.x2 - 16 - halfScreenWidth * 2))
		x = cArea.x2 - 16 - halfScreenWidth * 2;

	Vector3f np(static_cast<f32>(x), static_cast<f32>(y), z);
	pCamera->SetPosition(np);
}
