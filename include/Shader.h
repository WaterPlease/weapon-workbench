#ifndef __SHADER__
#define __SHADER__

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glmCommon.h"

// This code is modified.
// Original Shader class code is from
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h

struct mat{
    float ambient[3];
    float diffuse[3];
    float specular[3];
    float shininess;
    std::string map_KA; // 나중에 이미지로 바꾸기
    std::string map_KD;
    std::string map_KS;
};

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const float value[3]) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
};

extern const std::string strTrans;
extern const std::string strPV;

extern const std::string strAMBI;
extern const std::string strDIFF;
extern const std::string strSPEC;
extern const std::string strSHINE;

extern const std::string strLdir;
extern const std::string strLcol;

extern const std::string strViewPos;

#endif