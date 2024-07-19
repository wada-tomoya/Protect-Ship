#include "EnemyBase.h"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"
#include "math.h"

EnemyBase::EnemyBase(){

	//プレイヤーの攻撃がヒットした時のse読み込み
	hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Hit_SE");

	//死亡時のパーティクル読み込み
	death_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Enemy_Death");

}

EnemyBase::~EnemyBase(){
	MV1DeleteModel(duplication_model_);
	death_ptcl_.reset();

}

void EnemyBase::Update(float delat_time){

	//移動前座標設定
	prev_pos_ = MV1GetPosition(duplication_model_);
}

void EnemyBase::Draw(std::shared_ptr<Camera> camera){
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
		return (atan(aaa) + tnl::PI );
	}
	else {
		return atan(aaa);
	}
}

float EnemyBase::Distance_target() {
	return distance_target_ = static_cast<float>(sqrt(pow(MV1GetPosition(duplication_model_).x - target_pos_.x, 2) + pow(MV1GetPosition(duplication_model_).z - target_pos_.z, 2)));
}

void EnemyBase::Movedir_update(float delta_time, float movedir_update_interval){	
	//movedir_update_intervalごとに進行方向更新
	movedir_update_count_ += delta_time;
	if (movedir_update_count_ >= movedir_update_interval) {
		movedir_update_count_ = 0.0f;

		//進行方向更新
		move_dir_ = tnl::Vector3::Normalize(target_pos_ - Getter_pos());
	}
}

void EnemyBase::PlyaerAttack_Recieve(float damage){
	//プレイヤーの攻撃が当たった時のse再生
	PlaySoundMem(hit_se_hdl_, DX_PLAYTYPE_BACK);
	//ダメージ反映
	Setter_hp(damage);
	//ダメージフラグtrue
	is_HitRecieve_ = true;
}

void EnemyBase::Anim_Change(int animtype){
	//アニメーションの種類変更
	anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype, -1, false);
	//アニメーションの再生時間設定
	anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
	//アニメーション再生時間リセット
	anim_count_ = 0.0f;
}

void EnemyBase::AnimPlay(float delta_time){
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

