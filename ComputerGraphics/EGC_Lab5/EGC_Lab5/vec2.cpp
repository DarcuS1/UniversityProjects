#include "vec2.h"

namespace egc {
    //vec2 a,b
    //a=b
    //a= this
    //b= srcVector
    //return this
	vec2& vec2::operator =(const vec2& srcVector) {
        this->x = srcVector.x;
        y = srcVector.y;
        (*this).y = srcVector.y;
        return *this;
	}

    //vec2 v1 v2 v3
    //v1=v2+v3
    //v1=this
    //v2=src
    //v3=result

	vec2 vec2::operator +(const vec2& srcVector) const {
        vec2 result;
        result.x = this->x + srcVector.x;
        result.y = this->y + srcVector.y;
        return result;
	}

    vec2& vec2::operator +=(const vec2& srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        return *this;
    }
    vec2 vec2::operator *(float scalarValue) const {
        vec2 result;
        result.x = this->x * scalarValue;
        result.y = this->y * scalarValue;
        return result;
    }
    vec2 vec2::operator -(const vec2& srcVector) const {
        vec2 result;
        result.x = this->x - srcVector.x;
        result.y = this->y - srcVector.y;
        return result;
    }
    vec2& vec2::operator -=(const vec2& srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        return *this;
    }
    vec2 vec2::operator -() const {
        vec2 result;
        result.x = -this->x;
        result.y = -this->y;
        return result;
    }
    float vec2::length() const {
        return sqrt(this->x * this->x + this->y * this->y);
    }
    vec2& vec2::normalize() {
        float len = this->length();
        if (len != 0) {
            this->x /= len;
            this->y /= len;
        }
        return *this;
    }

    float dotProduct(const vec2& v1, const vec2& v2) {
        return v1.x* v2.x + v1.y * v2.y;
    }

}


