#include "Bezier.h"
#include "math.h"
#include "vec2.h"
#include <vector>

template <typename T>
T max(T a, T b) {
	return a > b ? a : b;
}


//Return the value of P(t), where t is in [0,1]
vec2 getParametricPoint(float t, vec2 p0, vec2 p1) {
	//P(t) = (1 - t)*P0 + t*P1
	vec2 point= p0*(1 - t) +  p1*t;

	return point;
}

//Paint the pixels that are on the line P0P1
void drawParametricLinePoints(vec2 p0, vec2 p1, SDL_Renderer* renderer) {
	//Hint: To paint a single pixel, you can use the function: SDL_RenderDrawPoint(renderer, x, y)
	float step = 1.0 / max(abs(p1.x - p0.x), abs(p1.y - p0.y));
	// Calculate the step between two points
	vec2 delta = (p1 - p0) * step;

	// Calculate the initial point on the line
	vec2 point = p0;

	// Iterate over each point on the line and paint it
	for (float i = 0; i <= 1.0; i += step) {
		SDL_RenderDrawPoint(renderer, point.x, point.y);
		point += delta;
	}
	
}

////Return the value of B(t), where t is in [0,1]. The value of B(t) is computed by taking into account all the 
////controll points contained within the input vecto
//vec2 getBezierPoint(std::vector<vec2> controlPoints, float t) {
//	vec2 point;
//
//	return point;
//}

vec2 getBezierPoint(std::vector<vec2> controlPoints, float t) {
	int n = controlPoints.size() - 1; // Degree of the curve
	std::vector<vec2> points(n + 1);

	// Initialize the first level of control points
	for (int i = 0; i <= n; ++i) {
		points[i] = controlPoints[i];
	}

	// Recursively compute intermediate control points
	for (int r = 1; r <= n; ++r) {
		for (int i = 0; i <= n - r; ++i) {
			points[i] = points[i]*(1.0f - t)  +  points[i + 1]* t;
		}
	}

	return points[0];
}


////Paint the pixels that are on the Bezier curve defined by the given control points
//void drawBezierPoints(std::vector<vec2> controlPoints, SDL_Renderer* renderer) {
//
//}

void drawBezierPoints(std::vector<vec2> controlPoints, SDL_Renderer* renderer) {
	const int STEPS = 100; // Number of steps to use when drawing the curve

	for (int i = 0; i < STEPS; ++i) {
		float t1 = static_cast<float>(i) / STEPS;
		float t2 = static_cast<float>(i + 1) / STEPS;

		vec2 p1 = getBezierPoint(controlPoints, t1);
		vec2 p2 = getBezierPoint(controlPoints, t2);

		drawParametricLinePoints(p1, p2, renderer);
	}
}

