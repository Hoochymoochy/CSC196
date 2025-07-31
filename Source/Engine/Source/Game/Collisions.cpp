#pragma
#include "Collisions.h"

#include "../../Math/Transform.h"

namespace viper {
    bool Collisions::CheckCollision(const Transform& t1, float r1,
        const Transform& t2, float r2) {
        Vector2 pos1 = t1.position;
        Vector2 pos2 = t2.position;

        float distSqr = (pos2 - pos1).LengthSqr();
        float radiusSum = r1 + r2;
        return distSqr <= radiusSum * radiusSum;
    }
} 