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
	//プレイヤーの攻撃と敵の当たり判定
	//引数１：攻撃のリスト、２：敵のリスト）
	void Attack_Enemy_HitCheck(const std::list<Shared<AttackBase>>& atk_list, const std::list<Shared<EnemyBase>>& ene_list);

	//プレイヤーと敵の当たり判定
	//引数１：プレイヤーインスタンス、２：敵リスト
	void Player_Enemy_HitChack(const std::shared_ptr<Player>& player, const std::list<Shared<EnemyBase>>& ene_list);

	//プレイヤーとアイテムの当たり判定
	//引数１：プレイヤーインスタンス、２：アイテムリスト
	void Player_Item_HitChack(const std::shared_ptr<Player>& player, const std::list<std::shared_ptr<ItemBase>>& item_list);
};