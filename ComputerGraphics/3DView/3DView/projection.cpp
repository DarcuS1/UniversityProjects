//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"
#include "vec2.h"
#include "include/SDL.h"
namespace egc {
    //define the viewport transformation matrix
    //see section 3 from the laboratory work
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
        mat4 VTMatrix, S, M, T;
        for (int i = 0; i < 4; i++) {
            S.at(i, i) = 1;
            M.at(i, i) = 1;
            T.at(i, i) = 1;
        }
        S.at(0, 0) = width / 2;
        S.at(1, 1) = height / 2;
        M.at(1, 1) = -1;
        T.at(0, 3) = 1;
        T.at(1, 3) = -1;

        mat4 trans;
        trans.at(0, 3) = startX;
        trans.at(1, 3) = startY;
        VTMatrix = trans * S * M * T;
        return VTMatrix;
    }

    //define the camera transformation matrix
    //see section 4 from the laboratory work
    mat4 defineCameraMatrix(Camera mc)
    {
        mat4 CMatrix;
        vec3 U, V, W, G, E, T;
        E = mc.cameraPosition;
        G = mc.cameraTarget - mc.cameraPosition;
        T = mc.cameraUp;
        W = -G.normalize();
        U = crossProduct(T, W).normalize();
        V = crossProduct(W, U);

        CMatrix.at(0, 0) = U.x;
        CMatrix.at(0, 1) = U.y;
        CMatrix.at(0, 2) = U.z;

        CMatrix.at(1, 0) = V.x;
        CMatrix.at(1, 1) = V.y;
        CMatrix.at(1, 2) = V.z;

        CMatrix.at(2, 0) = W.x;
        CMatrix.at(2, 1) = W.y;
        CMatrix.at(2, 2) = W.z;
        mat4 trans;
        trans.at(0, 3) = -E.x;
        trans.at(1, 3) = -E.y;
        trans.at(2, 3) = -E.z;
        CMatrix = CMatrix * trans;
        return CMatrix;
    }

    //define the projection transformation matrix
    //see section 5 from the laboratory work
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 PPMatrix;
        PPMatrix.at(0, 0) = -1 / (aspect * tan(fov / 2));
        PPMatrix.at(1, 1) = -1 / (tan(fov / 2));
        PPMatrix.at(2, 2) = (zFar + zNear) / (zNear - zFar);
        PPMatrix.at(2, 3) = (2 * zFar * zNear) / (zFar - zNear);
        PPMatrix.at(3, 3) = 0;
        PPMatrix.at(3, 2) = 1;
        return PPMatrix;
    }

    //define the perspective divide operation
    //see section 5 from the laboratory work
    void perspectiveDivide(vec4& iv)
    {
        float getInversW = 1.0f / iv.w;
        iv.x *= getInversW;
        iv.y *= getInversW;
        iv.z *= getInversW;
        iv.w = 1;
    }

    //check if a point should be clipped
    //see section 9 from the laboratory work
    bool clipPointInHomogeneousCoordinate(const egc::vec4& vertex)
    {
        return false;
    }

    //check if a triangle should be clipped
    //clip only those triangles for which all vertices are outside the viewing volume
    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4>& triangle)
    {
        return false;
    }

    //compute the normal vector to a triangle
    //see section 7 from the laboratory work
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4>& triangle)
    {
        egc::vec3 n;

        return n;
    }

    //compute the coordinates of the triangle's center
    //(we will use this point to display the normal vector)
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4>& triangle)
    {
        egc::vec4 triangleCenter;

        return triangleCenter;
    }

    //check if the triangle is visible (front facing)
    //see section 8 from the laboratory work
    bool isTriangleVisible(const std::vector<egc::vec4>& triangle, const egc::vec3& normalVector)
    {
        return true;
    }

    //display the normal vector of a triangle
    //see section 7 from the laboratory work
    //use the SDL_RenderDrawLine to draw the normal vector
    void displayNormalVectors(egc::vec3& normalVector, egc::vec4& triangleCenter, SDL_Renderer* renderer, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix)
    {

    }
}



    ////check if a point should be clipped
    ////see section 9 from the laboratory work
    //bool clipPointInHomogeneousCoordinate(const egc::vec4& vertex)
    //{
    //   /* vec4 const& P = vertex;
    //    if (-P.w <= P.x && P.x <= P.w ||
    //        -P.w <= P.y && P.y <= P.w ||
    //        -P.w <= P.z && P.z <= P.w)
    //    {
    //        return true;
    //    }*/
    //    return false;
    //}

    ////check if a triangle should be clipped
    ////clip only those triangles for which all vertices are outside the viewing volume
    //bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4>& triangle)
    //{
    //    /*bool ok = true;*/
    //  //  for (auto const& p : triangle)
    //    //    ok &= clipPointInHomogeneousCoordinate(p);

    //    return false;
    //}

    ////compute the normal vector to a triangle
    ////see section 7 from the laboratory work
    //egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4>& triangle)
    //{
    //   // egc::vec3 n = crossProduct(triangle[1] - triangle[0], triangle[2] - triangle[0]);
    //    vec3 at;
    //    return at;
    //}

    ////compute the coordinates of the triangle's center
    ////(we will use this point to display the normal vector)
    //egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4>& triangle)
    //{
    //   // egc::vec4 triangleCenter(triangle[0] + triangle[1] + triangle[2]);
    //    //return triangleCenter * (1.0f / 3.0f);
    //    return triangle[0];
    //}

    ////check if the triangle is visible (front facing)
    ////see section 8 from the laboratory work
    //bool isTriangleVisible(const std::vector<egc::vec4>& triangle, const egc::vec3& normalVector)
    //{
    //    //egc::vec3 const& v0 = egc::vec3(triangle[0]);
    //    //egc::vec3 const& v1 = egc::vec3(triangle[1]);
    //    //egc::vec3 const& v2 = egc::vec3(triangle[2]);
    //    //egc::vec3 triangleNormal = crossProduct(v1 - v0, v2 - v0);

    //    //// Check if the triangle is front-facing
    //   // return dotProduct(triangleNormal, normalVector) > 0.0f;
    //    return false;
    //}



    //void displayNormalVectors(egc::vec3& normalVector, egc::vec4& triangleCenter, SDL_Renderer* renderer, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix)
    //{
    //    //// Transform the triangle center to the camera space
    //    //egc::vec4 cameraSpaceCenter = viewTransformMatrix * triangleCenter;

    //    //// Compute the endpoint of the normal vector
    //    //egc::vec4 normalEndpoint = cameraSpaceCenter + egc::vec4(normalVector.x, normalVector.y, normalVector.z, 0.0f);

    //    //// Apply the perspective projection
    //    //egc::vec4 projectedCenter = perspectiveMatrix * cameraSpaceCenter;
    //    //egc::vec4 projectedNormalEndpoint = perspectiveMatrix * normalEndpoint;

    //    //// Normalize the projected coordinates
    //    //projectedCenter = projectedCenter * (1.0f / projectedCenter.w);
    //    //projectedNormalEndpoint = projectedNormalEndpoint * (1.0f / projectedNormalEndpoint.w);

    //    //// Scale and translate the projected coordinates to the screen space
    //    //int screenWidth, screenHeight;
    //    //SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
    //    //float x1 = (projectedCenter.x + 1.0f) * 0.5f * screenWidth;
    //    //float y1 = (1.0f - projectedCenter.y) * 0.5f * screenHeight;
    //    //float x2 = (projectedNormalEndpoint.x + 1.0f) * 0.5f * screenWidth;
    //    //float y2 = (1.0f - projectedNormalEndpoint.y) * 0.5f * screenHeight;

    //    //// Draw the line using SDL_RenderDrawLine
    //    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //    //SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    //}

