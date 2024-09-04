#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class EnemyBase;
class AttackBase;
class Player;
class ItemBase;

class Collision {
private:

public:
	Collision() = default;
	//�v���C���[�̍U���ƓG�̓����蔻��
	//�����P�F�U���̃��X�g�A�Q�F�G�̃��X�g�j
	void Attack_Enemy_HitCheck(const std::list<Shared<AttackBase>>& atk_list, const std::list<Shared<EnemyBase>>& ene_list);

	//�v���C���[�ƓG�̓����蔻��
	//�����P�F�v���C���[�C���X�^���X�A�Q�F�G���X�g
	void Player_Enemy_HitChack(const std::shared_ptr<Player>& player, const std::list<Shared<EnemyBase>>& ene_list);

	//�v���C���[�ƃA�C�e���̓����蔻��
	//�����P�F�v���C���[�C���X�^���X�A�Q�F�A�C�e�����X�g
	void Player_Item_HitChack(const std::shared_ptr<Player>& player, const std::list<std::shared_ptr<ItemBase>>& item_list);
};