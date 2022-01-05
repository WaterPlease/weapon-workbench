#ifndef __CAMERA__
#define __CAMERA__

#include "glmCommon.h"
#include "parameter.h"

class Camera
{
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 lookUp;
	float fovy;
	float aspect;
	float zNear;
	float zFar;

	glm::mat4 matPV;
public:
	Camera(){
		pos = glm::vec3(0.0f,0.0f,3.0f);
		target = glm::vec3(0.0f,0.0f,0.0f);
		lookUp = glm::normalize(glm::vec3(0.0f,1.0f,0.0f));

		fovy = CAM_INIT_FOVY;
		aspect = (float)iWidth/(float)iHeight;
		zNear = CAM_INIT_ZNEAR;
		zFar = CAM_INIT_ZFAR;
	}
	inline void GetPerspectiveMat(glm::mat4x4& mat){
		mat = glm::perspective(fovy,aspect,zNear,zFar);
	}
	inline void GetViewMat(glm::mat4x4& mat){
		mat = glm::lookAt(pos,target,lookUp);
	}
	inline void updatePVMat(void){
		glm::mat4x4 matPerspective, matView;
		GetPerspectiveMat(matPerspective);
		GetViewMat(matView);
		matPV = matPerspective * matView;
	}

	
	inline const glm::vec3& getPos()   { return pos; }
	inline const glm::vec3& getTarget(){ return target; }
	inline const glm::vec3& getLookUp(){ return lookUp; }
	inline float getFovy()      { return fovy; }
	inline float getAspect()    { return aspect; }
	inline float getZNear()     { return zNear; }
	inline float getZFar()      { return zFar; }

	inline void setPos(const glm::vec3& _pos)
	{ pos=_pos; }
	inline void setTarget(const glm::vec3& _target)
	{ target = _target; }
	inline void setLookUp(const glm::vec3& _lookUp)
	{ lookUp = _lookUp; }
	inline void setFovy(float _fovy)  
	{ fovy = _fovy; }
	inline void setAspect(float _aspect)
	{ aspect = _aspect; }
	inline void setZNear(float _zNear) 
	{ zNear= _zNear; }
	inline void setZFar(float _zFar)  
	{ zFar = _zFar; }

	inline const glm::mat4& getMatPV() {return matPV;}
};

extern Camera cam;

#endif