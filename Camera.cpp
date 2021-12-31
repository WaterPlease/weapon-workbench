#include "Camera.h"

inline void Camera::GetPerspectiveMat(glm::mat4x4& mat)
{
	mat = glm::perspective(fovy,aspect,zNear,zFar);
}

inline void Camera::GetViewMat(glm::mat4x4& mat)
{
	mat = glm::lookAt(pos,pos+lookFront,lookUp);
}

inline void Camera::GetPVMat(glm::mat4x4& mat)
{
	glm::mat4x4 matPerspective, matView;
	GetPerspectiveMat(matPerspective);
	GetViewMat(matView);
	mat = matPerspective * matView;
}
