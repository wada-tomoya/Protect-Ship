#include "EnemyBase.h"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"
#include "math.h"

EnemyBase::EnemyBase(const int& duplication_mesh, const Shared<dxe::InstMesh>& shadow_mesh,
	const float& speed, const float& hp, const float& colli_rad, const tnl::Vector3& colli_size){
	//プレイヤーの攻撃がヒットした時のse読み込み
	hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Hit_SE");
	//死亡時のパーティクル読み込み
	death_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Enemy_Death");

	//モデル
	duplication_model_ = duplication_mesh;
	//影のメッシュ
	shadow_mesh_ = shadow_mesh;
	//移動速度設定
	speed_ = speed;
	//弾との当たり判定用半径
	colli_rad_ = colli_rad;
	//プレイヤーとの当たり判定用ボックスサイズ
	colli_size_ = colli_size;
	//体力
	hp_ = hp;
}

EnemyBase::~EnemyBase(){
	MV1DeleteModel(duplication_model_);
	death_ptcl_.reset();

}

void EnemyBase::Update(const float& delta_time){
	//移動前座標設定
	prev_pos_ = MV1GetPosition(duplication_model_);

	//ノックバック方向にノックバックさせる
	tnl::Vector3 knockback = Getter_pos() + (knockback_dir_ * knockback_value_);
	MV1SetPosition(duplication_model_, VGet(knockback.x, 0, knockback.z));

	//ノックバック値が0より多ければ減らす
	if (knockback_value_ > 0) {
		knockback_value_ -= delta_time;
	}
	else {
		knockback_value_ = 0;
		//向きを進行方向を向くようにする
		is_movedir_ = true;
	}

	//アニメーション再生
	AnimPlay(delta_time);
}

void EnemyBase::Draw(const std::shared_ptr<Camera>& camera){
	//描画
	MV1DrawModel(duplication_model_);

	dxe::DirectXRenderBegin();

	//パーティクルの描画
	death_ptcl_->render(camera);

	dxe::DirectXRenderEnd();
}

float EnemyBase::Rotate_front() {
	//移動前座標と現座標のxとzの差（方向）
	float vec_x = Getter_pos().x - prev_pos_.x;
	float vec_z = Getter_pos().z - prev_pos_.z;

	//比を計算
	float aaa = vec_x / vec_z;

	//zの差が正の数だった場合逆向きにする
	if (vec_z >= 0) {
		return (atan(aaa) + tnl::PI);
	}
	else {
		return atan(aaa);
	}
}

float EnemyBase::Distance_target() {
	return distance_target_ = static_cast<float>(sqrt(pow(MV1GetPosition(duplication_model_).x - target_pos_.x, 2) + pow(MV1GetPosition(duplication_model_).z - target_pos_.z, 2)));
}

void EnemyBase::Movedir_update(const float& delta_time, const float& movedir_update_interval){	
	//進行方向変更フラグがtrueならば
	if (is_movedir_) {
		//movedir_update_intervalごとに進行方向更新
		movedir_update_count_ += delta_time;
		if (movedir_update_count_ >= movedir_update_interval) {
			movedir_update_count_ = 0.0f;

			//進行方向更新
			move_dir_ = tnl::Vector3::Normalize(target_pos_ - Getter_pos());
		}
	}
}

void EnemyBase::PlyaerAttack_Recieve(const float& damage, const tnl::Vector3& atkpos, const float& knockback_value){
	//プレイヤーの攻撃が当たった時のse再生
	PlaySoundMem(hit_se_hdl_, DX_PLAYTYPE_BACK);
	//ダメージ反映
	Setter_hp(damage);
	//ダメージフラグtrue
	is_HitRecieve_ = true;
	//ダメージを受けた時向きを変えない
	is_movedir_ = false;
	//ノックバック値設定
	knockback_value_ = knockback_value;
	//ノックバック方向設定
	knockback_dir_ = tnl::Vector3::Normalize(Getter_pos() - atkpos);
}

void EnemyBase::Anim_Change(const int& animtype){
	//アニメーションの種類変更
	anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype, -1, false);
	//アニメーションの再生時間設定
	anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
	//アニメーション再生時間リセット
	anim_count_ = 0.0f;
}

void EnemyBase::AnimPlay(const float& delta_time){
	//アニメーション終了フラグをfalse
	is_anim_end_ = false;
	//アニメーション再生
	if (is_anim_) {
		anim_count_ += (delta_time * anim_speed_);
		if (anim_count_ >= anim_totaltime_) {
			anim_count_ = 0.0f;
			//アニメーション終了true
			is_anim_end_ = true;
		}
		MV1SetAttachAnimTime(duplication_model_, anim_attachi_index_, anim_count_);
	}
}

