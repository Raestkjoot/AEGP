#include "CollisionSystem.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/AABB.h"
#include "ECS/Components/Collider_Dynamic.h"
#include "ECS/Components/Collider_Static.h"
#include "Logger.h"

#include <glm/glm.hpp>

#include <limits>

void CollisionSystem::Update(float delta) {
	auto dynamicAABBs = _registry->view<Transform, AABB, Collider_Dynamic>();
	auto staticAABBs = _registry->view<Transform, AABB, Collider_Static>();

	float minDist;
	float overlaps[4];
	int projVecIndex;

	for (auto [dEntity, dTrans, dAabb] : dynamicAABBs.each()) {
		for (auto [sEntity, sTrans, sAabb] : staticAABBs.each()) {
			// COLLISION DETECTION
			// Measure overlaps and early return if there is an edge with no overlap
			if ((overlaps[0] = dTrans.position.x + dAabb.extents.x - (sTrans.position.x - sAabb.extents.x)) < 0) { continue; }
			if ((overlaps[1] = sTrans.position.x + sAabb.extents.x - (dTrans.position.x - dAabb.extents.x)) < 0) { continue; }
			if ((overlaps[2] = dTrans.position.y + dAabb.extents.y - (sTrans.position.y - sAabb.extents.y)) < 0) { continue; }
			if ((overlaps[3] = sTrans.position.y + sAabb.extents.y - (dTrans.position.y - dAabb.extents.y)) < 0) { continue; }

			// COLLISION RESPONSE
			// If we get to this point, all edges have overlap and we know the AABBs overlap.
			// Find edge with smallest overlap and move the dynamic object back on that edge so there is no more overlap.
			minDist = std::numeric_limits<float>::max();

			for (int i = 0; i < 4; ++i) {
				if (minDist > overlaps[i]) {
					minDist = overlaps[i];
					projVecIndex = i;
				}
			}

			switch (projVecIndex)
			{
			case 0:
				dTrans.position.x -= minDist;
				break;
			case 1:
				dTrans.position.x += minDist;
				break;
			case 2:
				dTrans.position.y -= minDist;
				break;
			case 3:
				dTrans.position.y += minDist;
			}
		}
	}
}