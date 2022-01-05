#ifndef __MODEL__
#define __MODEL__

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "glmCommon.h"

#include "util.h"
#include "Shader.h"
#include "Camera.h"

struct Material{
    float Ka[3];
    float Kd[3];
    float Ks[3];
    float Ns;
    GLuint map_Kd=-1;
};

struct Group{
    Material* mat;
    std::vector<float> vbo_data; // represent vbo in opengl : v3 vn3 vt2
    GLuint VAO;
    GLuint VBO;
};

class Model{
    void mtlParser(const char*);
    void objParser(const char*);

    std::map<std::string,Material*> mtl;
    std::map<std::string,Group*>    groups;

    glm::vec3 pos;
    glm::vec4 rot;
    glm::vec3 scale;

    glm::mat4 matTrans;

    Shader* shader;
public:
    Model(const char* path,Shader* _shader):shader(_shader){
        objParser(path);

        //glGenVertexArrays(1);
        for(auto iter=groups.begin(); iter!=groups.end();iter++){
            Group* ptr_group = iter->second;

            glGenVertexArrays(1,&ptr_group->VAO);
            glGenBuffers(1,&ptr_group->VBO);

            glBindVertexArray(ptr_group->VAO);
            
            glBindBuffer(GL_ARRAY_BUFFER,ptr_group->VBO);
            glBufferData(GL_ARRAY_BUFFER,
                    sizeof(float)*ptr_group->vbo_data.size(),
                    ptr_group->vbo_data.data(),GL_STATIC_DRAW);
            
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2,3,GL_FLOAT,GL_TRUE,8*sizeof(float),(void*)(5*sizeof(float)));
            glEnableVertexAttribArray(2);
            // group.vbo_data will remain to ray tracing rendering..?
        }
    }
    void draw();

    ~Model(){
        for(auto iter = groups.begin(); iter != groups.end();iter++){
            glDeleteVertexArrays(1,&iter->second->VAO);
            glDeleteBuffers(1,&iter->second->VBO);
            delete iter->second;
        }
        for(auto iter = mtl.begin(); iter != mtl.end();iter++){
            delete iter->second;
        }
    }

    inline glm::vec3 getPos()  {return pos;}
    inline glm::vec4 getRot()  {return rot;}
    inline glm::vec3 getScale(){return scale;}

    inline void setPos(glm::vec3 _pos)    {pos   = _pos;}
    inline void setRot(glm::vec4 _rot)    {rot   = _rot;}
    inline void setScale(glm::vec3 _scale){scale = _scale;}

    inline void updateTrans(){
        matTrans = glm::mat4(1.0f);
        matTrans = glm::translate(matTrans,pos);
        matTrans = glm::rotate(matTrans,rot[0],glm::vec3(rot[1],rot[2],rot[3]));
        matTrans = glm::scale(matTrans,scale);
    }
};

#endif