#include "transform.h"

namespace egc {
   

    //transformation matrices in 2D
    mat3 translate(const vec2 translateArray) {
        mat3 res;
        res.at(0, 2) = translateArray.x;
        res.at(1, 2) = translateArray.y;
        return res;
    }
    mat3 translate(float tx, float ty) {
        mat3 res;
        res.at(0, 2) = tx;
        res.at(1, 2) = ty;
        return res;
    }

    mat3 scale(const vec2 scaleArray) {
        mat3 res;
        res.at(0, 0) = scaleArray.x;
        res.at(1, 1) = scaleArray.y;
        return res;
    }
    mat3 scale(float sx, float sy) {
        mat3 res;
        res.at(0, 0) = sx;
        res.at(1, 1) = sy;
        return res;
    }

    mat3 rotate(float angle) {
        mat3 res;
        res.at(0, 0) = cos((angle*PI)/180);
        res.at(0, 1) = -sin((angle * PI) / 180);
        res.at(1, 0) = sin((angle * PI) / 180);
        res.at(1, 1) = cos((angle * PI) / 180);
        return res;
    }

    //transformation matrices in 3D
    mat4 translate(const vec3 translateArray) {
        mat4 res;
        res.at(0, 3) = translateArray.x;
        res.at(1, 3) = translateArray.y;
        res.at(2, 3) = translateArray.z;
        
        return res;
    }
    mat4 translate(float tx, float ty, float tz) {
        mat4 res;
        res.at(0, 3) = tx;
        res.at(1, 3) = ty;
        res.at(2, 3) = tz;
        
        return res;
    }

    mat4 scale(const vec3 scaleArray) {
        mat4 res;
        res.at(0, 0) = scaleArray.x;
        res.at(1, 1) = scaleArray.y;
        res.at(2, 2) = scaleArray.z;
     
        return res;
    }
    mat4 scale(float sx, float sy, float sz) {
        mat4 res;
        res.at(0, 0) = sx;
        res.at(1, 1) = sy;
        res.at(2, 2) = sz;
        
        return res;
    }

    mat4 rotateX(float angle) {
        mat4 res;
      
        res.at(1, 1) = cos((angle * PI) / 180);
        res.at(1, 2) = -sin((angle * PI) / 180);
        res.at(2, 1) = sin((angle * PI) / 180);
        res.at(2, 2) = cos((angle * PI) / 180);


        return res;
    }
    mat4 rotateY(float angle) {
        mat4 res;
   

        res.at(0, 0) = cos((angle * PI) / 180);
        res.at(0, 2) = sin((angle * PI) / 180);
        res.at(2, 0) = -sin((angle * PI) / 180);
        res.at(2, 2) = cos((angle * PI) / 180);

        return res;
    }
    mat4 rotateZ(float angle) {
        mat4 res;
       


        float angle2 = (angle * PI) / 180;
        res.at(0, 0) = cos(angle2);
        res.at(0, 1) = -sin(angle2);
        res.at(1, 0) = sin(angle2);
        res.at(1, 1) = cos(angle2);
        return res;
    }
}