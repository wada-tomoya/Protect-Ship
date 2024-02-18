#include "Collision.h"

void Collision::Attack_Enemy_HitCheck(std::list<Shared<AttackBase>> atk_list, std::list<Shared<EnemyBase>> ene_list) {
	for (auto atk : atk_list) {
		for (auto ene : ene_list) {
			if (tnl::IsIntersectSphere(atk->Getter_pos_(), atk->Getter_rad_(), ene->Getter_pos_(), ene->Getter_rad_())) {
				atk->Setter_is_alive(false);
				ene->Setter_is_alive(false);

				DrawStringEx(100, 10, -1, "“–‚½‚è");
			}
		}
	}

	int aaa = atk_list.size();
	DrawStringEx(10, 90, -1, "coli atk %d", aaa);
}
