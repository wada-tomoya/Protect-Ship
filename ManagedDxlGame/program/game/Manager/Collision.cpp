#include "Collision.h"
#include "../Object/Attack/AttackBase.h"
#include "../Character/EnemyBase.h"
#include "../Character/Player.h"
#include "../Manager/ItemSpawner.h"

void Collision::Attack_Enemy_HitCheck(const std::list<Shared<AttackBase>>& atk_list, const std::list<Shared<EnemyBase>>& ene_list) {
	for (auto atk_ : atk_list) {
		for (auto ene_ : ene_list) {
			//一度当たった敵には当たらない（アドレスで判断する）
			bool continue_loop_ = true;
			for (auto hitene : atk_->Getter_hiteneaddress()) {
				if (hitene == ene_.get()) {
					continue_loop_ = false;
				}
			}
			if (continue_loop_) {
				//攻撃の当たり判定がtrueならば敵との当たり判定を計算する
				if (atk_->Getter_is_collision()) {
					//敵とプレイヤーの攻撃との当たり判定
					if (tnl::IsIntersectSphere(ene_->Getter_colli_center(), ene_->Getter_colli_rad(), atk_->Getter_pos(), atk_->Getter_bullet_rad())) {
						//弾の敵が当たった時の処理
						atk_->Enemy_Hit(ene_.get());
						//敵の弾と当たった時の処理
						ene_->PlyaerAttack_Recieve(-(atk_->Getter_attack_power()));
					}
				}
			}
		}
	}
}

void Collision::Player_Enemy_HitChack(const std::shared_ptr<Player>& player, const std::list<Shared<EnemyBase>>& ene_list){
	for (auto ene_ : ene_list) {
		//プレイヤーの当たり判定フラグがtrueの時のみ
		if (tnl::IsIntersectAABB(player->GetterPos(), player->Getter_colli_size_(), ene_->Getter_colli_center(), ene_->Getter_colli_size())
			&& player->Getter_is_colli()) {
			//プレイヤーの敵と当たった時の処理
			player->Enemy_Hit();
		}
	}
}

void Collision::Player_Item_HitChack(const std::shared_ptr<Player>& player, const std::list<std::shared_ptr<ItemBase>>& item_list){
	for (auto item_ : item_list) {
		if (tnl::IsIntersectAABB(player->GetterPos(), player->Getter_colli_size_(), item_->Getter_pos(), item_->Getter_size())) {
			//アイテムのプレイヤーと当たった時の処理
			item_->PlyarHit();
			//プレイヤーのアイテムと当たった時の処理
			player->Item_Hit(item_->Getter_itemtype());
		}
	}
}
