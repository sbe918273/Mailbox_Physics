#pragma once
#include "Vector.h"
#include "EntityCircle.h"
#include <vector>
#include <memory>

bool CheckColliding(const EntityCircle& circle1, const EntityCircle& circle2);
float ResolveLine(float m1, float v1, float m2, float v2, float coef);
void ResolvePostions(EntityCircle& c1, EntityCircle& c2);
void ResolveCollision(EntityCircle& c1, EntityCircle& c2, float coef);

void GroupAndResolveCollisions(std::vector<EntityCircle>& circles, unsigned int xDim, unsigned int yDim, float w, float h, float xOrigin, float yOrigin, float coef);