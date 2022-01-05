#include "util.h"

bool readFile(const char* path, std::string& fileStr){
    std::ifstream ifs(path);
    if(ifs.is_open()){
        fileStr = std::string(std::istreambuf_iterator<char>(ifs),
                              std::istreambuf_iterator<char>());
    }else{
        return false;
    }
    ifs.close();
    return true;
}


// Original code from 
// https://stackoverflow.com/questions/9358718/similar-function-in-c-to-pythons-strip
// by Mhadhbi issam
void strip(std::string &str)
{
    if  (str.length() != 0)
    {
        auto w = std::string(" ") ;
        auto n = std::string("\n") ;
        auto r = std::string("\t") ;
        auto t = std::string("\r") ;
        auto v = std::string(1 ,str.front()); 
        while((v == w) || (v==t) || (v==r) || (v==n))
        {
            str.erase(str.begin());
            v = std::string(1 ,str.front());
        }
        v = std::string(1 , str.back()); 
        while((v ==w) || (v==t) || (v==r) || (v==n))
        {
            str.erase(str.end() - 1 );
            v = std::string(1 , str.back());
        }
    }
}