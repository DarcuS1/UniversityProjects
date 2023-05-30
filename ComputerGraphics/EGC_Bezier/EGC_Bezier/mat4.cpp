#include "mat4.h"
namespace egc {
    mat4& mat4::operator =(const mat4& srcMatrix) {
        if (this != &srcMatrix) {
            for (int i = 0; i < 16; i++) {
                matrixData[i] = srcMatrix.matrixData[i];
            }
        }
        return *this;
    }
    mat4 mat4::operator *(float scalarValue) const {
        mat4 result;
        for (int i = 0; i < 16; i++) {
            result.matrixData[i] = matrixData[i] * scalarValue;
        }
        return result;
    }
    mat4 mat4::operator *(const mat4& srcMatrix) const {
        mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0;
                for (int k = 0; k < 4; k++) {
                    sum += matrixData[k * 4 + i] * srcMatrix.matrixData[j * 4 + k];
                }
                result.matrixData[j * 4 + i] = sum;
            }
        }
        return result;
    }
    vec4 mat4::operator *(const vec4& srcVector) const {
        vec4  result;
        result.x = matrixData[0] * srcVector.x + matrixData[4] * srcVector.y + matrixData[8] * srcVector.z + matrixData[12] * srcVector.w;
        result.y = matrixData[1] * srcVector.x + matrixData[5] * srcVector.y + matrixData[9] * srcVector.z + matrixData[13] * srcVector.w;
        result.z = matrixData[2] * srcVector.x + matrixData[6] * srcVector.y + matrixData[10] * srcVector.z + matrixData[14] * srcVector.w;
        result.w = matrixData[3] * srcVector.x + matrixData[7] * srcVector.y + matrixData[11] * srcVector.z + matrixData[15] * srcVector.w;
        return result;
    }
    mat4 mat4::operator +(const mat4& srcMatrix) const {
        mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
            }
        }
        return result;
    }
    //get element by (row, column)
    float& mat4::at(int i, int j) {
        return matrixData[j * 4 + i];
    }
    const float& mat4::at(int i, int j) const {
        return matrixData[j * 4 + i];
    }
    float mat4::determinant() const {
        float det = 0.0f;
        det += matrixData[0] * ( matrixData[5] * (matrixData[10] * matrixData[15] - matrixData[11] * matrixData[14])
            - matrixData[6] * (matrixData[9] * matrixData[15] - matrixData[11] * matrixData[13])
            + matrixData[7] * (matrixData[9] * matrixData[14] - matrixData[10] * matrixData[13]));
        det -= matrixData[1] * ( matrixData[4] * (matrixData[10] * matrixData[15] - matrixData[11] * matrixData[14])
            - matrixData[6] * (matrixData[8] * matrixData[15] - matrixData[11] * matrixData[12])
            + matrixData[7] * (matrixData[8] * matrixData[14] - matrixData[10] * matrixData[12]));
        det += matrixData[2] * ( matrixData[4] * (matrixData[9] * matrixData[15] - matrixData[11] * matrixData[13])
            - matrixData[5] * (matrixData[8] * matrixData[15] - matrixData[11] * matrixData[12])
            + matrixData[7] * (matrixData[8] * matrixData[13] - matrixData[9] * matrixData[12]));
        det -= matrixData[3] * (matrixData[4] * (matrixData[9] * matrixData[14] - matrixData[10] * matrixData[13])
            - matrixData[5] * (matrixData[8] * matrixData[14] - matrixData[10] * matrixData[12])
            + matrixData[6] * (matrixData[8] * matrixData[13] - matrixData[9] * matrixData[12]));
        return det;
    }

    mat4 mat4::inverse() const {
        mat4 result;
        float invdet = 1 / determinant();
        result.matrixData[0] = matrixData[5] * matrixData[10] * matrixData[15] - matrixData[5] * matrixData[11] * matrixData[14] - matrixData[9] * matrixData[6] * matrixData[15] + matrixData[9] * matrixData[7] * matrixData[14] + matrixData[13] * matrixData[6] * matrixData[11] - matrixData[13] * matrixData[7] * matrixData[10];
        result.matrixData[4] = -matrixData[4] * matrixData[10] * matrixData[15] + matrixData[4] * matrixData[11] * matrixData[14] + matrixData[8] * matrixData[6] * matrixData[15] - matrixData[8] * matrixData[7] * matrixData[14] - matrixData[12] * matrixData[6] * matrixData[11] + matrixData[12] * matrixData[7] * matrixData[10];
        result.matrixData[8] = matrixData[4] * matrixData[9] * matrixData[15] - matrixData[4] * matrixData[11] * matrixData[13] - matrixData[8] * matrixData[5] * matrixData[15] + matrixData[8] * matrixData[7] * matrixData[13] + matrixData[12] * matrixData[5] * matrixData[11] - matrixData[12] * matrixData[7] * matrixData[9];
        result.matrixData[12] = -matrixData[4] * matrixData[9] * matrixData[14] + matrixData[4] * matrixData[10] * matrixData[13] + matrixData[8] * matrixData[5] * matrixData[14] - matrixData[8] * matrixData[6] * matrixData[13] - matrixData[12] * matrixData[5] * matrixData[10] + matrixData[12] * matrixData[6] * matrixData[9];
        result.matrixData[1] = -matrixData[1] * matrixData[10] * matrixData[15] + matrixData[1] * matrixData[11] * matrixData[14] + matrixData[9] * matrixData[2] * matrixData[15] - matrixData[9] * matrixData[3] * matrixData[14] - matrixData[13] * matrixData[2] * matrixData[11] + matrixData[13] * matrixData[3] * matrixData[10];
        result.matrixData[5] = matrixData[0] * matrixData[10] * matrixData[15] - matrixData[0] * matrixData[11] * matrixData[14] - matrixData[8] * matrixData[2] * matrixData[15] + matrixData[8] * matrixData[3] * matrixData[14] + matrixData[12] * matrixData[2] * matrixData[11] - matrixData[12] * matrixData[3] * matrixData[10];
        result.matrixData[9] = -matrixData[0] * matrixData[9] * matrixData[15] + matrixData[0] * matrixData[11] * matrixData[13] + matrixData[8] * matrixData[1] * matrixData[15] - matrixData[8] * matrixData[3] * matrixData[13] - matrixData[12] * matrixData[1] * matrixData[11] + matrixData[12] * matrixData[3] * matrixData[9];
        result.matrixData[13] = matrixData[0] * matrixData[9] * matrixData[14] - matrixData[0] * matrixData[10] * matrixData[13] - matrixData[8] * matrixData[1] * matrixData[14] + matrixData[8] * matrixData[2] * matrixData[13] + matrixData[12] * matrixData[1] * matrixData[10] - matrixData[12] * matrixData[2] * matrixData[9];
        result.matrixData[2] = matrixData[1] * matrixData[6] * matrixData[15] - matrixData[1] * matrixData[7] * matrixData[14] - matrixData[5] * matrixData[2] * matrixData[15] + matrixData[5] * matrixData[3] * matrixData[14] + matrixData[13] * matrixData[2] * matrixData[7] - matrixData[13] * matrixData[3] * matrixData[6];
        result.matrixData[6] = -matrixData[0] * matrixData[6] * matrixData[15] + matrixData[0] * matrixData[7] * matrixData[14] + matrixData[4] * matrixData[2] * matrixData[15] - matrixData[4] * matrixData[3] * matrixData[14] - matrixData[12] * matrixData[2] * matrixData[7] + matrixData[12] * matrixData[3] * matrixData[6];
        result.matrixData[10] = matrixData[0] * matrixData[5] * matrixData[15] - matrixData[0] * matrixData[7] * matrixData[13] - matrixData[4] * matrixData[1] * matrixData[15] + matrixData[4] * matrixData[3] * matrixData[13] + matrixData[12] * matrixData[1] * matrixData[7] - matrixData[12] * matrixData[3] * matrixData[5];
        result.matrixData[14] = -matrixData[0] * matrixData[5] * matrixData[14] + matrixData[0] * matrixData[6] * matrixData[13] + matrixData[4] * matrixData[1] * matrixData[14] - matrixData[4] * matrixData[2] * matrixData[13] - matrixData[12] * matrixData[1] * matrixData[6] + matrixData[12] * matrixData[2] * matrixData[5];
        result.matrixData[3] = -matrixData[1] * matrixData[6] * matrixData[11] + matrixData[1] * matrixData[7] * matrixData[10] + matrixData[5] * matrixData[2] * matrixData[11] - matrixData[5] * matrixData[3] * matrixData[10] - matrixData[9] * matrixData[2] * matrixData[7] + matrixData[9] * matrixData[3] * matrixData[6];
        result.matrixData[7] = matrixData[0] * matrixData[6] * matrixData[11] - matrixData[0] * matrixData[7] * matrixData[10] - matrixData[4] * matrixData[2] * matrixData[11] + matrixData[4] * matrixData[3] * matrixData[10] + matrixData[8] * matrixData[2] * matrixData[7] - matrixData[8] * matrixData[3] * matrixData[6];
        result.matrixData[11] = -matrixData[0] * matrixData[5] * matrixData[11] + matrixData[0] * matrixData[7] * matrixData[9] + matrixData[4] * matrixData[1] * matrixData[11] - matrixData[4] * matrixData[3] * matrixData[9] - matrixData[8] * matrixData[1] * matrixData[7] + matrixData[8] * matrixData[3] * matrixData[5];
        result.matrixData[15] = matrixData[0] * matrixData[5] * matrixData[10] - matrixData[0] * matrixData[6] * matrixData[9] - matrixData[4] * matrixData[1] * matrixData[10] + matrixData[4] * matrixData[2] * matrixData[9] + matrixData[8] * matrixData[1] * matrixData[6] - matrixData[8] * matrixData[2] * matrixData[5];
        return result * invdet;
    }
    mat4 mat4::transpose() const {
        mat4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.at(j, i) = at(i, j);
            }
        }

        return result;
    }
}