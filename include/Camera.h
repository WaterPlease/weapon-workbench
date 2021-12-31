#ifndef __CAMERA__
#define __CAMERA__

#include "glmCommon.h"
#include "parameter.h"

class Camera
{
	glm::vec3 pos;
	glm::vec3 lookFront;
	glm::vec3 lookUp;
	float fovy;
	float aspect;
	float zNear;
	float zFar;
public:
	Camera(){
		pos = glm::vec3(0.0f,0.0f,-5.0f);
		lookFront = glm::vec3(0.0f,0.0f,1.0f);
		lookUp = glm::vec3(0.0f,1.0f,0.0f);

		fovy = CAM_INIT_FOVY;
		aspect = (float)iWidth/(float)iHeight;
		zNear = CAM_INIT_ZNEAR;
		zFar = CAM_INIT_ZFAR;
	}
	inline void GetPerspectiveMat(glm::mat4x4&);
	inline void GetViewMat(glm::mat4x4&);
	inline void GetPVMat(glm::mat4x4&);
};

#endif