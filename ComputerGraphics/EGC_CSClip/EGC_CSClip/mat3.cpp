#include "mat3.h"

namespace egc {
    mat3& mat3::operator =(const mat3& srcMatrix) {
        if (this != &srcMatrix) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    this->at(i, j) = srcMatrix.at(i, j);
                }
            }
        }
        return *this;
    }
    mat3 mat3::operator *(float scalarValue) const {
        mat3 result;
        for (int i = 0; i < 9; i++) {
            result.matrixData[i] = matrixData[i] * scalarValue;
        }
        return result;
    }
    mat3 mat3::operator *(const mat3& srcMatrix) const {
        mat3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float sum = 0;
                for (int k = 0; k < 3; k++) {
                    sum += matrixData[k*3 + i ] * srcMatrix.matrixData[j*3 + k];
                }
                result.matrixData[j*3 + i] = sum;
            }
        }
        return result;
    }
    vec3 mat3::operator *(const vec3& srcVector) const {
        vec3 result;
        result.x = matrixData[0] * srcVector.x + matrixData[3] * srcVector.y + matrixData[6] * srcVector.z;
        result.y = matrixData[1] * srcVector.x + matrixData[4] * srcVector.y + matrixData[7] * srcVector.z;
        result.z = matrixData[2] * srcVector.x + matrixData[5] * srcVector.y + matrixData[8] * srcVector.z;
        return result;
    }
    mat3 mat3::operator +(const mat3& srcMatrix) const {
        mat3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
            }
        }
        return result;
    }
    //get element by (row, column)
    float& mat3::at(int i, int j) {
        return matrixData[j*3 + i];
    }
    const float& mat3::at(int i, int j) const {
        return matrixData[j*3 + i];
    }
    float mat3::determinant() const {
        return matrixData[0] * matrixData[4] * matrixData[8] +
            matrixData[1] * matrixData[5] * matrixData[6] +
            matrixData[2] * matrixData[3] * matrixData[7] -
            matrixData[2] * matrixData[4] * matrixData[6] -
            matrixData[1] * matrixData[3] * matrixData[8] -
            matrixData[0] * matrixData[5] * matrixData[7];
    }
    mat3 mat3::inverse() const {
        mat3 result;

        float a = at(0, 0), b = at(0, 1), c = at(0, 2);
        float d = at(1, 0), e = at(1, 1), f = at(1, 2);
        float g = at(2, 0), h = at(2, 1), i = at(2, 2);

        float A = e * i - f * h;
        float B = f * g - d * i;
        float C = d * h - e * g;
        float D = c * h - b * i;
        float E = a * i - c * g;
        float F = b * g - a * h;
        float G = b * f - c * e;
        float H = c * d - a * f;
        float I = a * e - b * d;

        float det = a * A + b * B + c * C;

        if (fabs(det) < 1e-6f) {
            // The matrix is singular, return the identity matrix
            return result;
        }

        float invDet = 1.0f / det;

        result.at(0, 0) = A * invDet;
        result.at(0, 1) = D * invDet;
        result.at(0, 2) = G * invDet;
        result.at(1, 0) = B * invDet;
        result.at(1, 1) = E * invDet;
        result.at(1, 2) = H * invDet;
        result.at(2, 0) = C * invDet;
        result.at(2, 1) = F * invDet;
        result.at(2, 2) = I * invDet;

        return result;
    }

    mat3 mat3::transpose() const {
        mat3 result;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.at(j, i) = at(i, j);
            }
        }

        return result;
    }

}
