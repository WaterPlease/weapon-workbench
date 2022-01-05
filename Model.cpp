#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

const char* mtl_newmtl ="newmtl";
const char* mtl_Ka = "Ka";
const char* mtl_Kd = "Kd";
const char* mtl_Ks = "Ks";
const char* mtl_Ns = "Ns";
// not implemented feature
const char* mtl_d = "d";
const char* mtl_Tr = "Tr";
const char* mtl_map_Ka = "map_Ka";
const char* mtl_map_Kd = "map_Kd";
const char* mtl_map_Ks = "map_Ks";
const char* mtl_map_bump = "map_bump"; // same with bump
const char* mtl_bump = "bump";         // same with map_bump
const char* mtl_disp = "disp";

const char* obj_mtllib = "mtllib";
const char* obj_usemtl = "usemtl";
const char* obj_group = "g";
const char* obj_vertex = "v";
const char* obj_texcoord = "vt";
const char* obj_normal = "vn";
const char* obj_face = "f";

void Model::mtlParser(const char* path){
    std::string mtlStr;
    std::string lineStr;
    std::string token[4];

    int i;

    if(!readFile(path, mtlStr)){
        std::cerr<<"ERROR : "<<__PRETTY_FUNCTION__<<std::endl
                 <<"    - Failed to open .obj file"<<std::endl;
    }

    std::istringstream ss(mtlStr);
    Material* ptr_mat;
    while(std::getline(ss,lineStr)){
        strip(lineStr);
        std::istringstream tokenizer(lineStr);
        i=0;
        while(tokenizer >> token[i]) i++;
        if(token[0].compare(mtl_newmtl)==0){
            ptr_mat = new Material();
            mtl[token[1]] = ptr_mat;
        }else if(token[0].compare(mtl_Ka)==0){
            ptr_mat->Ka[0] = std::stof(token[1]);
            ptr_mat->Ka[1] = std::stof(token[2]);
            ptr_mat->Ka[2] = std::stof(token[3]);
        }else if(token[0].compare(mtl_Kd)==0){
            ptr_mat->Kd[0] = std::stof(token[1]);
            ptr_mat->Kd[1] = std::stof(token[2]);
            ptr_mat->Kd[2] = std::stof(token[3]);
        }else if(token[0].compare(mtl_Ks)==0){
            ptr_mat->Ks[0] = std::stof(token[1]);
            ptr_mat->Ks[1] = std::stof(token[2]);
            ptr_mat->Ks[2] = std::stof(token[3]);
        }else if(token[0].compare(mtl_Ns)==0){
            ptr_mat->Ns    = std::stof(token[1]);
        }else if(token[0].compare(mtl_map_Kd)==0){
            glGenTextures(1,&ptr_mat->map_Kd);
            glBindTexture(GL_TEXTURE_2D, ptr_mat->map_Kd);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int imgWidth, imgHeight, imgCh;
            // find img path
            auto pStr = std::string(path);
            auto iter = pStr.begin() + (pStr.find_last_of("/")+1);
            pStr.erase(iter,pStr.end());
            pStr = pStr+token[1];
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(pStr.c_str(), &imgWidth, &imgHeight, &imgCh, 0);
            if (data){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else{
                std::cerr<<"ERROR : "<<__PRETTY_FUNCTION__<<std::endl
                         <<"    - Failed to load texture image"<<std::endl
                         <<"    - path : "<<pStr<<std::endl;
            }
            stbi_image_free(data);
        }else{
            // Not implemented feature
        }
    }
}

void Model::objParser(const char* path){    
    std::string objStr;
    //std::string lineStr;
    std::string token[4];

    std::vector<float> vertecies;
    std::vector<float> texcoords;
    std::vector<float> verNormal;

    int i;
    //std::cout<<"READ OBJ FILE : "<<path<<std::endl;
    if(!readFile(path, objStr)){
        std::cerr<<"ERROR : "<<__PRETTY_FUNCTION__<<std::endl
                 <<"    - Failed to open .obj file"<<std::endl;
    }
    int k = 1;
    ////std::cout<<"====="<<std::endl<<objStr<<std::endl<<"====="<<std::endl;
    std::istringstream ss(objStr);
    Group* ptr_group;
    for(std::string lineStr;std::getline(ss,lineStr);){
        strip(lineStr);
        //std::cout<<"PROCESSING : "<<lineStr<<std::endl;
        if(lineStr[0]=='#') continue;
        std::istringstream tokenizer(lineStr);
        i=0;
        while(getline(tokenizer,token[i],' ')) i++;
        if(token[0].compare(obj_mtllib)==0){
            auto pStr = std::string(path);
            auto iter = pStr.begin() + (pStr.find_last_of("/")+1);
            pStr.erase(iter,pStr.end());
            pStr = pStr+token[1];
            mtlParser(pStr.c_str());
        }else if(token[0].compare(obj_group)==0){
            ptr_group = new Group();
            groups[token[1]] = ptr_group;
        }else if(token[0].compare(obj_usemtl)==0){
            ptr_group->mat = mtl[token[1]];
        }else if(token[0].compare(obj_vertex)==0){
            //std::cout<<"v : "<<std::stof(token[1])<<", "<<std::stof(token[2])<<", "<<std::stof(token[3])<<std::endl;
            vertecies.push_back(std::stof(token[1]));
            vertecies.push_back(std::stof(token[2]));
            vertecies.push_back(std::stof(token[3]));
        }else if(token[0].compare(obj_texcoord)==0){
            //std::cout<<"vt : "<<std::stof(token[1])<<", "<<std::stof(token[2])<<std::endl;
            texcoords.push_back(std::stof(token[1]));
            texcoords.push_back(std::stof(token[2]));
        }else if(token[0].compare(obj_normal)==0){
            //std::cout<<"vn : "<<std::stof(token[1])<<", "<<std::stof(token[2])<<", "<<std::stof(token[3])<<std::endl;
            verNormal.push_back(std::stof(token[1]));
            verNormal.push_back(std::stof(token[2]));
            verNormal.push_back(std::stof(token[3]));
        }else if(token[0].compare(obj_face)==0){
            //std::cout<<k<<"-th triangle : "<<std::endl;
            k++;
            for(int d=1;d<4;d++){
                //std::cout<<"\t"<<d<<"-th vertex"<<std::endl;
                std::istringstream idxSS(token[d]);
                std::string tmpStr;
                int idx;

                // vertex index
                std::getline(idxSS,tmpStr,'/');
                idx = std::stoi(tmpStr)-1;
                //std::cout<<"\t\t"<<idx<<"-th vertex pos"<<std::endl;
                //std::cout<<"\t\t\t"<<vertecies[idx*3]<<", "<<vertecies[idx*3+1]<<", "<<vertecies[idx*3+2]<<std::endl;
                ptr_group->vbo_data.push_back(vertecies[idx*3]);
                ptr_group->vbo_data.push_back(vertecies[idx*3+1]);
                ptr_group->vbo_data.push_back(vertecies[idx*3+2]);

                // texcoord index
                std::getline(idxSS,tmpStr,'/');
                idx = std::stoi(tmpStr)-1;
                //std::cout<<"\t\t"<<idx<<"-th texcoord"<<std::endl;
                //std::cout<<"\t\t\t"<<texcoords[idx*2]<<", "<<texcoords[idx*2+1]<<std::endl;
                ptr_group->vbo_data.push_back(texcoords[idx*2]);
                ptr_group->vbo_data.push_back(texcoords[idx*2+1]);

                // normal index
                std::getline(idxSS,tmpStr,'/');
                idx = std::stoi(tmpStr)-1;
                //std::cout<<"\t\t"<<idx<<"-th normal vec"<<std::endl;
                //std::cout<<"\t\t\t"<<verNormal[idx*3]<<", "<<verNormal[idx*3+1]<<", "<<verNormal[idx*3+2]<<std::endl;
                ptr_group->vbo_data.push_back(verNormal[idx*3]);
                ptr_group->vbo_data.push_back(verNormal[idx*3+1]);
                ptr_group->vbo_data.push_back(verNormal[idx*3+2]);
            }
        }else{
            //std::cout<<"Ignored"<<std::endl;
        }
    }
    for(auto iter=groups.begin(); iter!=groups.end();iter++){
        Group* ptr_group = iter->second;
        auto gIterEnd = ptr_group->vbo_data.end();
        int idx = 0;
        //std::cout<<"Group "<<iter->first<<"'s vbo"<<std::endl;
        //std::cout<<"{";
        int numFloat = ptr_group->vbo_data.size();
        for(auto gIter = ptr_group->vbo_data.begin();gIter != gIterEnd; gIter++){
            idx++;
            if(idx%8==0)
            if(idx==numFloat){
                break;
            }
        }
    }
}

void Model::draw(){
    shader->use();
    shader->setMat4(strTrans,matTrans);
    shader->setMat4(strPV,cam.getMatPV());
    shader->setInt("texture1",0);

    for(auto iter=groups.begin(); iter!=groups.end();iter++){
        Group* ptr_group = iter->second;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,ptr_group->mat->map_Kd);

        glBindVertexArray(ptr_group->VAO);
        glDrawArrays(GL_TRIANGLES,0,ptr_group->vbo_data.size()/8);
    }
}