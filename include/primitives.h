#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__

#include <gl/GLU.h>
#include "glmCommon.h"

class Primitive{
public:
    virtual bool hit()=0;
};

class Sphere:public Primitive{
    glm::vec3 c;
    float r;
public:
    Sphere(glm::vec3 _c, float _r):c(_c),r(_r){
        gluQ
    }
    // NOT IMPLEMENTED
    bool hit(){}

    // draw in viewer
    void draw(){

    }
};

#endif