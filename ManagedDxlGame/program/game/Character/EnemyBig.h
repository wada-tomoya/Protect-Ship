#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "EnemyBase.h"
#include "../Manager/ResourceManager.h"
#include "../Object/ProtectObject.h"

//通常より大きい敵
//引数（ターゲット、複製メッシュ、影メッシュ、移動速度、体力、たまとの当たり判定用の半径、プレイヤーとの当たり判定用のサイズ）
class EnemyBig : public EnemyBase {
private:
	//ターゲット（船）
	std::weak_ptr<ProtectObject> target_;

	//シーケンス
	TNL_CO_SEQUENCE(EnemyBig, &EnemyBig::SEQ_Move)
	//移動シーケンス
	bool SEQ_Move(const float delta_time);
	//攻撃シーケンス
	bool SEQ_Attack(const float delta_time);
	//攻撃を受けた時シーケンス
	bool SEQ_HitRecieve(const float delta_time);
	//死亡シーケンス
	bool SEQ_Death(const float delta_time);

	//アニメーションの種類
	enum ANIMTYPE {
		Attack_1,
		Attack_2,
		Dance,
		Death,
		HitRecieve,
		Jump,
		No,
		Walk,
		Yes,
		Idle,
		Max
	};
	ANIMTYPE animtype_ = Idle;

public:
	EnemyBig(std::weak_ptr<ProtectObject> protectobject, int duplication_mesh, Shared <dxe::InstMesh> shadow_mesh,
		float speed, float hp, float colli_rad, tnl::Vector3 colli_size);
	~EnemyBig();

	//実行関数
	void Update(float delta_time) override;
	//描画関数
	void Draw(std::shared_ptr<Camera> camera) override;
};