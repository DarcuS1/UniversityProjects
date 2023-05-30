#include "clip.h"

namespace egc {

	//Cyrus-Beck clipping algorithm
	//clipWindow specifies the vertices that define the clipping area in conterclockwise order
	//and can represent any convex polygon
	//function returns -1 if the line segment cannot be clipped
	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cyrus-Beck line clipping algorithm - consult the laboratory work

		float tE = 0, tL = 1, t;
		vec3 norm[4];
		vec3 edge;


		for (int i = 0; i <= 2; i++)
		{
			edge = clipWindow.at(i + 1) - clipWindow.at(i);
			norm[i].x = -edge.y;
			norm[i].y = edge.x;
			norm[i].z = 1;
		}
		edge = clipWindow.at(0) - clipWindow.at(3);
		norm[3].x = -edge.y;
		norm[3].y = edge.x;
		norm[3].z = 0;

		vec3 d = p2 - p1;

		if (p1 == p2)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i <= 3; i++)
			{
				t = dotProduct(norm[i], p1 - clipWindow.at(i)) / -dotProduct(norm[i], d);
				if (dotProduct(norm[i], d) >= 0)
				{
					if (t < tL)
						tL = t;
				}
				else
				{
					if (t > tE)
						tE = t;
				}
			}
		}
		if (tE > tL)
			return -1;
		p2 = p1 + (d)*tL;
		p1 = p1 + (d)*tE;

	}


}

