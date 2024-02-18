#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Attack/AttackBase.h"
#include "../Character/EnemyBase.h"

class Collision {
private:
	
public:
	Collision() {};
	//UŒ‚‚Æ“G‚Ì“–‚½‚è”»’è
	//ˆø”iUŒ‚‚ÌlistA“G‚Ìlistj
	void Attack_Enemy_HitCheck(std::list<Shared<AttackBase>> atk_list, std::list<Shared<EnemyBase>>ene_list);
};