#include "zbuffer.h"

namespace egc {

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma) {
		
			egc::vec2 A(triangleVertices[0].x, triangleVertices[0].y);
			egc::vec2 B(triangleVertices[1].x, triangleVertices[1].y);
			egc::vec2 C(triangleVertices[2].x, triangleVertices[2].y);

			float ac = (A.y - C.y) * B.x + (C.x - A.x) * B.y + A.x * C.y - C.x * A.y;
			float bc = (B.y - C.y) * A.x + (C.x - B.x) * A.y + B.x * C.y - C.x * B.y;

			alpha = ((B.y - C.y) * pixel.x + (C.x - B.x) * pixel.y + B.x * C.y - C.x * B.y) / bc;
			beta = ((A.y - C.y) * pixel.x + (C.x - A.x) * pixel.y + A.x * C.y - C.x * A.y) / ac;
			gamma = 1 - alpha - beta;
		
	}


	void drawTriangleInZBuffer(std::vector<egc::vec4> triangle, float depthBuffer[WINDOW_HEIGHT][WINDOW_WIDTH], float& zmin, float& zmax) {

		//TO DO  -  implement the "drawing" of the triangle inside the depth buffer
		//The buffer has the same dimension as the screen - use it to fill in not the pixel color of each pixel in the triangel - but the pixel depth (Z component)
		//So you are going to fill in the Z of each pixel inside the triangle - use the algorithm from last week to access the inside of the triangle

		//While you compute the z for each pixel, you can also determine the zmin and zmax values ===> from all the points of the rabbit 
		//zmin and zmax are the minimum and maximum Z values FROM ALL THE VERICES OF THE RABBIT

		zmin = std::numeric_limits<float>::max();
		zmax = std::numeric_limits<float>::lowest();

		vec3 A(triangle[0].x, triangle[0].y, triangle[0].z);
		vec3 B(triangle[1].x, triangle[1].y, triangle[1].z);
		vec3 C(triangle[2].x, triangle[2].y, triangle[2].z);

		int minX = std::min(std::min(A.x, B.x), C.x);
		int minY = std::min(std::min(A.y, B.y), C.y);
		int maxX = std::max(std::max(A.x, B.x), C.x);
		int maxY = std::max(std::max(A.y, B.y), C.y);

		float minZ = std::min(std::min(A.z, B.z), C.z);
		float maxZ = std::max(std::max(A.z, B.z), C.z);
		for (int y = minY; y <= maxY; y++) {

			float alpha, beta, gamma;
			for (int x = minX; x <= maxX; x++) {
				vec2 pixel(static_cast<float>(x), static_cast<float>(y));
				computeAlphaBetaGamma(triangle, vec2(x, y), alpha, beta, gamma);
				if (alpha >= 0 && beta >= 0 && gamma >= 0) {
					//float z = 255 * (1 - (A.z - minZ) / (maxZ - minZ));
					//float z2 = 255 * (1 - (B.z - minZ) / (maxZ - minZ));
					//float z3 = 255 * (1 - (C.z - minZ) / (maxZ - minZ));
					float z = alpha * A.z + beta * B.z + gamma * C.z;
					depthBuffer[x][y] = z;
					//zmin = std::min(minZ, z);
					//zmax = std::max(maxZ, z);
					zmin = minZ;
					zmax = maxZ;
				}
			}
		}

	}


	

}
