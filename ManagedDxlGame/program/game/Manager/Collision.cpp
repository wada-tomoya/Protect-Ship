#include "Collision.h"
#include "../Object/Attack/AttackBase.h"
#include "../Character/EnemyBase.h"
#include "../Character/Player.h"
#include "../Manager/ItemSpawner.h"

void Collision::Attack_Enemy_HitCheck(const std::list<Shared<AttackBase>>& atk_list, const std::list<Shared<EnemyBase>>& ene_list) {
	for (auto atk_ : atk_list) {
		for (auto ene_ : ene_list) {
			//��x���������G�ɂ͓�����Ȃ��i�A�h���X�Ŕ��f����j
			bool continue_loop_ = true;
			for (auto hitene : atk_->Getter_hiteneaddress()) {
				if (hitene == ene_.get()) {
					continue_loop_ = false;
				}
			}
			if (continue_loop_) {
				//�U���̓����蔻�肪true�Ȃ�ΓG�Ƃ̓����蔻����v�Z����
				if (atk_->Getter_is_collision()) {
					//�G�ƃv���C���[�̍U���Ƃ̓����蔻��
					if (tnl::IsIntersectSphere(ene_->Getter_colli_center(), ene_->Getter_colli_rad(), atk_->Getter_pos(), atk_->Getter_bullet_rad())) {
						//�e�̓G�������������̏���
						atk_->Enemy_Hit(ene_.get());
						//�G�̒e�Ɠ����������̏���
						ene_->PlyaerAttack_Recieve(-(atk_->Getter_attack_power()));
					}
				}
			}
		}
	}
}

void Collision::Player_Enemy_HitChack(const std::shared_ptr<Player>& player, const std::list<Shared<EnemyBase>>& ene_list){
	for (auto ene_ : ene_list) {
		//�v���C���[�̓����蔻��t���O��true�̎��̂�
		if (tnl::IsIntersectAABB(player->GetterPos(), player->Getter_colli_size_(), ene_->Getter_colli_center(), ene_->Getter_colli_size())
			&& player->Getter_is_colli()) {
			//�v���C���[�̓G�Ɠ����������̏���
			player->Enemy_Hit();
		}
	}
}

void Collision::Player_Item_HitChack(const std::shared_ptr<Player>& player, const std::list<std::shared_ptr<ItemBase>>& item_list){
	for (auto item_ : item_list) {
		if (tnl::IsIntersectAABB(player->GetterPos(), player->Getter_colli_size_(), item_->Getter_pos(), item_->Getter_size())) {
			//�A�C�e���̃v���C���[�Ɠ����������̏���
			item_->PlyarHit();
			//�v���C���[�̃A�C�e���Ɠ����������̏���
			player->Item_Hit(item_->Getter_itemtype());
		}
	}
}
