#include "Collision.h"

namespace Collision {

float distanceSquaredXZ(const Vec3& a, const Vec3& b) {
    const float dx = a.x - b.x;
    const float dz = a.z - b.z;
    return dx * dx + dz * dz;
}

bool circlesIntersectXZ(
    const Vec3& positionA,
    float radiusA,
    const Vec3& positionB,
    float radiusB
) {
    const float radiusSum = radiusA + radiusB;
    return distanceSquaredXZ(positionA, positionB) <= radiusSum * radiusSum;
}

}
