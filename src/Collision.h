#pragma once

#include "Entity.h"

namespace Collision {

float distanceSquaredXZ(const Vec3& a, const Vec3& b);

bool circlesIntersectXZ(
    const Vec3& positionA,
    float radiusA,
    const Vec3& positionB,
    float radiusB
);

}
