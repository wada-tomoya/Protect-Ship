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
	//コンストラクタ
	EnemyChase(std::weak_ptr<CharacterBase> player, int duplication_mesh, Shared<dxe::InstMesh> shadow_mesh, float speed, float hp, float colli_rad, tnl::Vector3 colli_size);
	~EnemyChase();

	//実行関数
	void Update(float delta_time) override;
	//描画関数
	void Draw(std::shared_ptr<Camera> camera) override;
};
