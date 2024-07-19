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
	//プレイヤーの攻撃と敵の当たり判定
	//引数（攻撃のlist、敵のlist）
	void Attack_Enemy_HitCheck(std::list<Shared<AttackBase>>& atk_list, std::list<Shared<EnemyBase>>& ene_list);

	//プレイヤーと敵の当たり判定
	void Player_Enemy_HitChack(std::shared_ptr<Player>& player, std::list<Shared<EnemyBase>>& ene_list);

	//プレイヤーとアイテムの当たり判定
	void Player_Item_HitChack(std::shared_ptr<Player>& player, std::list<std::shared_ptr<ItemBase>>& item_list);
};