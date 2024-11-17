#include "PlayerCollisionSystem.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/AABB.h"
#include "PlayerController.h"
#include "ECS/Components/Collider_Static.h"
#include "Logger.h"

#include <glm/glm.hpp>

#include <limits>

void PlayerCollisionSystem::Update(float delta) {
	auto playerAABB = _registry->view<Transform, AABB, PlayerController>();
	auto staticAABBs = _registry->view<Transform, AABB, Collider_Static>();

	float minDist;
	float overlaps[4];
	int projVecIndex;

	for (auto [pEntity, pTrans, pAabb, pContr] : playerAABB.each()) {
			pContr.isTouchingRight = false;
			pContr.isGrounded = false;
			pContr.isTouchingLeft = false;

		for (auto [sEntity, sTrans, sAabb] : staticAABBs.each()) {

			// COLLISION DETECTION
			// Measure overlaps and early return if there is an edge with no overlap
			if ((overlaps[0] = pTrans.position.x + pAabb.extents.x - (sTrans.position.x - sAabb.extents.x)) < 0) { continue; }
			if ((overlaps[1] = sTrans.position.x + sAabb.extents.x - (pTrans.position.x - pAabb.extents.x)) < 0) { continue; }
			if ((overlaps[2] = pTrans.position.y + pAabb.extents.y - (sTrans.position.y - sAabb.extents.y)) < 0) { continue; }
			if ((overlaps[3] = sTrans.position.y + sAabb.extents.y - (pTrans.position.y - pAabb.extents.y)) < 0) { continue; }

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
				pTrans.position.x -= minDist;
				pContr.isTouchingRight = true;
				break;
			case 1:
				pTrans.position.x += minDist;
				pContr.isTouchingLeft = true;
				break;
			case 2:
				pTrans.position.y -= minDist;
				break;
			case 3:
				pTrans.position.y += minDist;
				pContr.isGrounded = true;
			}
		}
	}
}