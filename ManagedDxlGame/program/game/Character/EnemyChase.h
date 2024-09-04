#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "EnemyBase.h"

class Camera;
class CharacterBase;

//プレイヤーを追いかける敵
//引数（ターゲット、複製メッシュ、移動速度、体力、たまとの当たり判定用の半径、プレイヤーとの当たり判定用のサイズ）
class EnemyChase : public EnemyBase {
private:
	//ターゲット（プレイヤー）
	std::weak_ptr<CharacterBase> target_;

	//シーケンス
	TNL_CO_SEQUENCE(EnemyChase, &EnemyChase::SEQ_Move)
	//移動シーケンス
	bool SEQ_Move(const float delta_time);
	//攻撃シーケンス
	bool SEQ_Attack(const float delta_time);
	//攻撃を受けた時シーケンス
	bool SEQ_HitRecieve(const float dleta_time);
	//死亡シーケンス
	bool SEQ_Death(const float delta_time);

	//アニメーションの種類
	enum ANIMTYPE {
		Attack_1,
		Attack_2,
		Danse,
		Death,
		HitRecieve, 
		Idle,
		Jump,
		No,
		Walk,
		Yes,
		Max
	};
	ANIMTYPE animtype_ = Idle;

public:
	EnemyChase() = default;

	//引数１：ターゲット、２：複製メッシュ、３：影メッシュ、
	// ４：移動速度、５：体力、６：たまとの当たり判定用の半径、７：プレイヤーとの当たり判定用のサイズ
	EnemyChase(std::weak_ptr<CharacterBase> player, const int& duplication_mesh, const Shared<dxe::InstMesh>& shadow_mesh,
		const float& speed, const float& hp, const float& colli_rad, const tnl::Vector3& colli_size);
	~EnemyChase();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time) override;
	//描画関数
	//引数１：カメラインスタンス
	void Draw(const std::shared_ptr<Camera>& camera) override;
};
