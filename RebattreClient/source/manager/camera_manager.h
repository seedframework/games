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
		void LookAt(const vec3 &pos);

	protected:
		Camera	*pCamera;
		vec3	cOffset;
		Rect4f	cArea;
};

#endif // CAMERA_MANAGER_H
