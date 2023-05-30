
#include "clip.h"

#include <algorithm>

namespace egc {

    std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p)
    {
        
        float x_min = clipWindow[0].x;
        float y_min = clipWindow[0].y;
        float x_max = clipWindow[0].x;
        float y_max = clipWindow[0].y;

        for (int i = 1; i < clipWindow.size(); i++) {
            if (clipWindow[i].x < x_min) {
                x_min = clipWindow[i].x;
            }
            if (clipWindow[i].y < y_min) {
                y_min = clipWindow[i].y;
            }
            if (clipWindow[i].x > x_max) {
                x_max = clipWindow[i].x;
            }
            if (clipWindow[i].y > y_max) {
                y_max = clipWindow[i].y;
            }
        }

        std::vector<int> code(4, 0);

        if (p.x < x_min) {
            code[0] = 1;
        }
        else if (p.x > x_max) {
            code[1] = 1;
        }

        if (p.y < y_min) {
            code[2] = 1;
        }
        else if (p.y > y_max) {
            code[3] = 1;
        }

        return code;

    }

    bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2)
    {
        bool ok1 = false;
        bool ok2 = false;

        for (auto& c : cod1)
        {
            if (c == 1)
            {
                ok1 = true;
                break;
            }
        }

        for (auto& c : cod2)
        {
            if (c == 1)
            {
                ok2 = true;
                break;
            }
        }

        return ok1 && ok2;
    }

    bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2)
    {
        for (auto& c : cod1)
            if (c == 1)
                return false;

        for (auto& c : cod2)
            if (c == 1)
                return false;

        return true;
    }

    //function returns -1 if the line segment cannot be clipped
    int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2)
    {
        float x_min = clipWindow[0].x;
        float y_min = clipWindow[0].y;
        float x_max = clipWindow[0].x;
        float y_max = clipWindow[0].y;

        for (int i = 1; i < clipWindow.size(); i++) {
            if (clipWindow[i].x < x_min) {
                x_min = clipWindow[i].x;
            }
            if (clipWindow[i].y < y_min) {
                y_min = clipWindow[i].y;
            }
            if (clipWindow[i].x > x_max) {
                x_max = clipWindow[i].x;
            }
            if (clipWindow[i].y > y_max) {
                y_max = clipWindow[i].y;
            }
        }
        while (true)
        {
            auto cod1 = computeCSCode(clipWindow, p1);
            auto cod2 = computeCSCode(clipWindow, p2);

            bool reject = simpleRejection(cod1, cod2);

            if (reject)
            {
                return -1;
            }
            bool display = simpleAcceptance(cod1, cod2);
            if (display)
            {
                return 0;
            }

            if (std::find(cod1.begin(), cod1.end(), 1) == cod1.end())
            {
                vec3 tmp = p1;
                p1 = p2;
                p2 = tmp;
                std::swap(cod1, cod2);
            }

            if (cod1[3] == 1 && p2.y != p1.y)
            {
                p1.x = p1.x + (p2.x - p1.x) * (y_max - p1.y) / (p2.y - p1.y);
                p1.y = y_max;
            }
            else if (cod1[2] == 1 && p2.y != p1.y)
            {
                p1.x = p1.x + (p2.x - p1.x) * (y_min - p1.y) / (p2.y - p1.y);
                p1.y = y_min;
            }
            else if (cod1[1] == 1 && p2.x != p1.x)
            {
                p1.y = p1.y + (p2.y - p1.y) * (x_max - p1.x) / (p2.x - p1.x);
                p1.x = x_max;
            }
            else if (cod1[0] == 1 && p1.x != p2.x)
            {
                p1.y = p1.y + (p2.y - p1.y) * (x_min - p1.x) / (p2.x - p1.x);
                p1.x = x_min;
            }

        }

        return 0;
    }
}