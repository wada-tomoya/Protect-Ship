#include "EnemyChase.h"
#include "../Object/Camera.h"
#include "../Character/CharacterBase.h"
#include "../Manager/ResourceManager.h"

EnemyChase::EnemyChase(std::weak_ptr<CharacterBase> player, const int& duplication_mesh, const Shared<dxe::InstMesh>& shadow_mesh, 
	const float& speed, const float& hp, const float& colli_rad, const tnl::Vector3& colli_size) : 
	EnemyBase(duplication_mesh, shadow_mesh, speed, hp, colli_rad, colli_size) {
	//ターゲット
	target_ = player;
	auto target = target_.lock();
	if (!target) {
		return;
	}
	//ターゲット座標
	target_pos_ = target->GetterPos();
	//攻撃のインターバル
	attack_interval_ = 1.0f;
	//攻撃に移るターゲットとの距離
	trans_attack_distance_ = 20.0f;
	//移動方向更新インターバル
	movedir_update_interval_ = 0.2f;
	//初期移動方向計算
	move_dir_ = tnl::Vector3::Normalize(target->GetterPos() - Getter_pos());

	//攻撃のse読み込み
	attack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy2_Voice_SE");
	//死亡時のse読み込み
	death_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy2_Death");

	//再生アニメーション
	anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype_, -1, false);
	//再生するアニメーションの再生時間
	anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
}

EnemyChase::~EnemyChase(){

}

void EnemyChase::Update(const float& delta_time){
	auto target = target_.lock();
	if (!target) {return;}

	//ベースクラス記載の実行処理
	__super::Update(delta_time);

	//シーケンス実行
	tnl_sequence_.update(delta_time);

	//ターゲットの座標更新
	target_pos_ = target->GetterPos();

	//当たり判定座標更新
	colli_center_ = {Getter_pos().x, Getter_pos().y + colli_rad_, Getter_pos().z};
	//影の座標更新
	shadow_mesh_->setPosition({ Getter_pos().x, shadow_mesh_->getPosition().y, Getter_pos().z });
}

void EnemyChase::Draw(const std::shared_ptr<Camera>& camera){
	//ベースクラス記載の描画処理
	__super::Draw(camera);

	//当たり判定描画
	//DrawAABB(camera, colli_center_, colli_size_);
}

bool EnemyChase::SEQ_Move(const float delta_time){
	if (tnl_sequence_.isStart()) {
		//アニメーションをWalkに変更
		Anim_Change(Walk);

		//死亡した場合アイテムをドロップしない
		is_itemspawn_ = true;
	}

	//移動
	MV1SetPosition(duplication_model_,
		{ Getter_pos().x + (move_dir_.x * speed_), Getter_pos().y, Getter_pos().z + (move_dir_.z * speed_) });

	//進行方向更新
	Movedir_update(delta_time, movedir_update_interval_);
	if (Getter_is_movedirchange()) {
		//進行方向を向く
		MV1SetRotationXYZ(duplication_model_, { 0, Rotate_front(), 0 });
	}
	
	//シーケンス移動条件
	//体力が0以下に場合死亡シーケンスに移動
	if (hp_ <= 0) {
		tnl_sequence_.change(&EnemyChase::SEQ_Death);
	}
	//ターゲットに近づいたとき
	else if (Distance_target() <= trans_attack_distance_) {
		tnl_sequence_.change(&EnemyChase::SEQ_Attack);
	}
	//攻撃を受けた時
	else if (is_HitRecieve_) {
		tnl_sequence_.change(&EnemyChase::SEQ_HitRecieve);
	}

	TNL_SEQ_CO_END
}

bool EnemyChase::SEQ_Attack(const float delta_time){
	if (tnl_sequence_.isStart()) {
		//アニメーション変更
		Anim_Change(Danse);
	}

	//シーケンス移動条件
	//体力が0以下の場合
	if (hp_ <= 0) {
		tnl_sequence_.change(&EnemyChase::SEQ_Death);
	}
	//ターゲットと離れた時
	else if (Distance_target() >= trans_attack_distance_) {
		tnl_sequence_.change(&EnemyChase::SEQ_Move);
	}
	//プレイヤーの攻撃を受けた時
	else if (is_HitRecieve_) {
		tnl_sequence_.change(&EnemyChase::SEQ_HitRecieve);
	}

	TNL_SEQ_CO_END
}

bool EnemyChase::SEQ_HitRecieve(const float dleta_time){
	if (tnl_sequence_.isStart()) {
		//アニメーション変更
		Anim_Change(HitRecieve);
	}

	//ダメージフラグfalse
	is_HitRecieve_ = false;

	//シーケンス移動条件
	//アニメーションが終了したら一つ前のSEQに戻る
	if (is_anim_end_) {
		tnl_sequence_.undo();
	}
	//体力が0以下の場合
	else if (hp_ <= 0) {
		tnl_sequence_.change(&EnemyChase::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool EnemyChase::SEQ_Death(const float delta_time){
	if (tnl_sequence_.isStart()) {
		//死亡時se再生
		PlaySoundMem(death_se_hdl_, DX_PLAYTYPE_BACK);

		//パーティクル生成
		death_ptcl_->setPosition(Getter_pos());
		death_ptcl_->start();
	}

	//死亡時seの再生が終われば死
	int cheack = CheckSoundMem(death_se_hdl_);
	if (cheack != 0) {
		//消去
		Delete();
	}

	TNL_SEQ_CO_END
}
