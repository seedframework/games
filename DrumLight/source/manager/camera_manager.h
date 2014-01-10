#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "../defines.h"

class CameraManager
{
	public:
		CameraManager();
		~CameraManager();

		void SetCamera(Camera *cam);
		void SetArea(const Rect4f &area);
		void LookAt(const Vector3f &pos);

	protected:
		Camera		*pCamera;
		Vector3f	cOffset;
		Rect4f		cArea;
};

#endif // CAMERA_MANAGER_H
