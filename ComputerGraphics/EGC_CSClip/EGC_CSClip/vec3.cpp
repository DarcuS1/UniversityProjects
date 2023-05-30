#include "vec3.h"

namespace egc {
    
    vec3& vec3::operator =(const vec3& srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        return *this;
    }
    vec3 vec3::operator +(const vec3& srcVector) const {
        vec3 result;
        result.x = this->x + srcVector.x;
        result.y = this->y + srcVector.y;
        result.z = this->z + srcVector.z;
        return result;
    }
    vec3& vec3::operator +=(const vec3& srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;
        return *this;
    }
    vec3 vec3::operator *(float scalarValue) const {
        vec3 result;
        result.x = this->x * scalarValue;
        result.y = this->y * scalarValue;
        result.z = this->z * scalarValue;
        return result;
    }
    vec3 vec3::operator -(const vec3& srcVector) const {
        vec3 result;
        result.x = this->x - srcVector.x;
        result.y = this->y - srcVector.y;
        result.z = this->z - srcVector.z;
        return result;
    }
    vec3& vec3::operator -=(const vec3& srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;
        return *this;
    }
    vec3 vec3::operator -() const {
        vec3 result;
        result.x = -this->x;
        result.y = -this->y;
        result.z = -this->z;
        return result;
    }
    float vec3::length() const {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    vec3& vec3::normalize() {
        float len = this->length();
        if (len != 0) {
            this->x /= len;
            this->y /= len;
            this->z /= len;
        }
        return *this;
    }

    float dotProduct(const vec3& v1, const vec3& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
    vec3 crossProduct(const vec3& v1, const vec3& v2) {
        float x = v1.y * v2.z - v1.z * v2.y;
        float y = v1.z * v2.x - v1.x * v2.z;
        float z = v1.x * v2.y - v1.y * v2.x;
        return vec3(x, y, z);
    }
    
}