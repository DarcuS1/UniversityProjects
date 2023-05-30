#include "vec4.h"

namespace egc {
    
    vec4& vec4::operator =(const vec4& srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        this->w = srcVector.w;
        return *this;
    }
    vec4 vec4::operator +(const vec4& srcVector) const {
        vec4 result;
        result.x = this->x + srcVector.x;
        result.y = this->y + srcVector.y;
        result.z = this->z + srcVector.z;
        result.w = this->w + srcVector.w;
        return result;
    }
    vec4& vec4::operator +=(const vec4& srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;
        this->w += srcVector.w;
        return *this;
    }
    vec4 vec4::operator *(float scalarValue) const {
        vec4 result;
        result.x = this->x * scalarValue;
        result.y = this->y * scalarValue;
        result.z = this->z * scalarValue;
        result.w = this->w * scalarValue;
        return result;
    }
    vec4 vec4::operator -(const vec4& srcVector) const {
        vec4 result;
        result.x = this->x - srcVector.x;
        result.y = this->y - srcVector.y;
        result.z = this->z - srcVector.z;
        result.w = this->w - srcVector.w;
        return result;
    }
    vec4& vec4::operator -=(const vec4& srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;
        this->w -= srcVector.w;
        return *this;
    }
    vec4 vec4::operator -() const {
        vec4 result;
        result.x = -this->x;
        result.y = -this->y;
        result.z = -this->z;
        result.w = -this->w;
        return result;
    }
    float vec4::length() const {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w*this->w);
    }
    vec4& vec4::normalize() {
        float len = this->length();
        if (len != 0) {
            this->x /= len;
            this->y /= len;
            this->z /= len;
            this->w /= len;
        }
        return *this;
    }
    
}