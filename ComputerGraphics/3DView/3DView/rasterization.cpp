#include "rasterization.h"

namespace egc {


    void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma)
    {
        egc::vec2 A(triangleVertices[0].x, triangleVertices[0].y);
        egc::vec2 B(triangleVertices[1].x, triangleVertices[1].y);
        egc::vec2 C(triangleVertices[2].x, triangleVertices[2].y);

        float ac = (A.y - C.y) * B.x + (C.x - A.x) * B.y + A.x * C.y - C.x * A.y;
        float bc = (B.y - C.y) * A.x + (C.x - B.x) * A.y + B.x * C.y - C.x * B.y;

        alpha = ((B.y - C.y) * pixel.x + (C.x - B.x) * pixel.y + B.x * C.y - C.x * B.y) / bc;
        beta = ((A.y - C.y) * pixel.x + (C.x - A.x) * pixel.y + A.x * C.y - C.x * A.y) / ac;
        gamma = 1 - alpha - beta;
    }

    void rasterizeTriangle(SDL_Renderer* renderer, const std::vector<egc::vec4>& triangleVertices, const std::vector<egc::vec4>& triangleColors) {
        vec2 A(triangleVertices[0].x, triangleVertices[0].y);
        vec2 B(triangleVertices[1].x, triangleVertices[1].y);
        vec2 C(triangleVertices[2].x, triangleVertices[2].y);

        int minX = std::min(std::min(A.x, B.x), C.x);
        int minY = std::min(std::min(A.y, B.y), C.y);
        int maxX = std::max(std::max(A.x, B.x), C.x);
        int maxY = std::max(std::max(A.y, B.y), C.y);


        for (int y = minY; y <= maxY; y++) {
            float alpha, beta, gamma;
            for (int x = minX; x <= maxX; x++) {

                computeAlphaBetaGamma(triangleVertices, vec2(x, y), alpha, beta, gamma);
                if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                    vec4 color = triangleColors[0] * alpha + triangleColors[1] * beta + triangleColors[2] * gamma;
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
    }

}