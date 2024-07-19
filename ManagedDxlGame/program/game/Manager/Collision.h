#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class EnemyBase;
class AttackBase;
class Player;
class ItemBase;

class Collision {
private:

public:
	Collision();
	//�v���C���[�̍U���ƓG�̓����蔻��
	//�����i�U����list�A�G��list�j
	void Attack_Enemy_HitCheck(std::list<Shared<AttackBase>>& atk_list, std::list<Shared<EnemyBase>>& ene_list);

	//�v���C���[�ƓG�̓����蔻��
	void Player_Enemy_HitChack(std::shared_ptr<Player>& player, std::list<Shared<EnemyBase>>& ene_list);

	//�v���C���[�ƃA�C�e���̓����蔻��
	void Player_Item_HitChack(std::shared_ptr<Player>& player, std::list<std::shared_ptr<ItemBase>>& item_list);
};