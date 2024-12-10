#include "PlayerCollisionSystem.h"

#include "PlayerController.h"
#include "Components/Transform.h"
#include "Components/AABB.h"
#include "Components/Collider_Static.h"
#include "Components/Collider_Trigger.h"
#include "Utils/Logger.h"

#include <glm/glm.hpp>

#include <limits>

void PlayerCollisionSystem::Update(float delta) {
	auto playerAABB = _registry->view<Transform, AABB, PlayerController>();
	auto staticAABBs = _registry->view<Transform, AABB, Collider_Static>();
	auto triggerAABBs = _registry->view<Transform, AABB, Collider_Trigger>();

	float minDist;
	float overlaps[4];
	int projVecIndex;

	for (auto [pEntity, pTrans, pAabb, pContr] : playerAABB.each()) {
		pContr.isTouchingRight = false;
		pContr.isGrounded = false;
		pContr.isTouchingLeft = false;
		pContr.isTouchingTop = false;
		// TODO: Add is touching top and use to set vel.y = 0
		glm::vec2 pPos = pTrans.position + pContr.offset;

		for (auto [sEntity, sTrans, sAabb] : staticAABBs.each()) {

			// COLLISION DETECTION
			// Measure overlaps and early return if there is an edge with no overlap
			if ((overlaps[0] = pPos.x + pAabb.extents.x - (sTrans.position.x - sAabb.extents.x)) < 0) { continue; }
			if ((overlaps[1] = sTrans.position.x + sAabb.extents.x - (pPos.x - pAabb.extents.x)) < 0) { continue; }
			if ((overlaps[2] = pPos.y + pAabb.extents.y - (sTrans.position.y - sAabb.extents.y)) < 0) { continue; }
			if ((overlaps[3] = sTrans.position.y + sAabb.extents.y - (pPos.y - pAabb.extents.y)) < 0) { continue; }

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
				pContr.isTouchingTop = true;
				break;
			case 3:
				pTrans.position.y += minDist;
				pContr.isGrounded = true;
			}
		}

		for (auto [tEntity, tTrans, tAabb] : triggerAABBs.each()) {

			// COLLISION DETECTION
			// Measure overlaps and early return if there is an edge with no overlap
			if ((pTrans.position.x + pAabb.extents.x - (tTrans.position.x - tAabb.extents.x)) < 0) {
				continue;
			}
			if ((tTrans.position.x + tAabb.extents.x - (pTrans.position.x - pAabb.extents.x)) < 0) {
				continue;
			}
			if ((pTrans.position.y + pAabb.extents.y - (tTrans.position.y - tAabb.extents.y)) < 0) {
				continue;
			}
			if ((tTrans.position.y + tAabb.extents.y - (pTrans.position.y - pAabb.extents.y)) < 0) {
				continue;
			}

			// Collision Detected
			_registry->destroy(tEntity);
		}
	}
}