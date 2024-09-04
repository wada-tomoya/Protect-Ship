#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "EnemyBase.h"

class ProtectObject;

//通常より大きい敵
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
	EnemyBig() = default;

	//引数１：ターゲット、２：複製メッシュ、３：影メッシュ、
	// ４：移動速度、５：体力、６：たまとの当たり判定用の半径、７：プレイヤーとの当たり判定用のサイズ
	EnemyBig(std::weak_ptr<ProtectObject> protectobject, const int& duplication_mesh, const Shared<dxe::InstMesh>& shadow_mesh,
		const float& speed, const float& hp, const float& colli_rad, const tnl::Vector3& colli_size);
	~EnemyBig();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time) override;
	//描画関数
	//引数１：カメラインスタンス
	void Draw(const std::shared_ptr<Camera>& camera) override;
};