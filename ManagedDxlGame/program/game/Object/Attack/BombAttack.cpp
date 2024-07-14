#include "BombAttack.h"

BombAttack::BombAttack(const tnl::Vector3 map_center, const float map_rad, tnl::Vector3 target_pos, const tnl::Vector3& spawn_pos,
	const tnl::Quaternion dir_angle, Shared<dxe::InstMesh> inst_mesh, float bullet_rad, 
	std::shared_ptr<dxe::Particle> hit_ptcl, std::shared_ptr<dxe::Particle> move_ptcl, int hit_se){
	//複製されたメッシュ
	inst_mesh_ = inst_mesh;
	//進行方向の角度
	dir_rad_ = dir_angle;
	//プレイエリアの中心
	map_center_ = map_center;
	//プレイエリアの半径
	map_rad_ = map_rad;
	//マップの中心から外周までのベクトル
	map_vec_ = static_cast<float>(std::pow(map_rad, 2));
	//弾の速度設定
	speed_ = 15.0f;
	//弾の半径設定
	bullet_rad_ = bullet_rad;
	//初期座標設定
	inst_mesh_->setPosition(spawn_pos);
	//攻撃力設定、始めは0
	attack_power_ = 0.0f;
	//終着点の座標
	end_pos_ = target_pos;
	//初期座標から終着点の長さ
	length_ = (end_pos_ - spawn_pos).length();
	//山なり移動の最大高さ
	heiget_max_ = 150.0f;

	//爆破時のパーティクル
	hit_ptcl_ = hit_ptcl;
	//生成時間設定
	hit_ptcl_time_ = hit_ptcl_->getTimeLimit();
	//移動時のパーティクル
	move_ptcl_ = move_ptcl;
	//生成範囲設定
	move_ptcl_->setOriginRange(bullet_rad_);

	//ヒット時のse読み込み
	hit_se_hdl_ = hit_se;

	heiget_ = 100.0f;
}

BombAttack::~BombAttack(){
	DeleteSoundMem(hit_se_hdl_);
	hit_ptcl_.reset();
	move_ptcl_.reset();
}

void BombAttack::Update(float delta_time){
	//シーケンス実行
	tnl_sequence_.update(delta_time);
}

void BombAttack::Enemy_Hit(){
	//爆弾を描画しない
	inst_mesh_->setDrawEnable(false);

	//ヒット時のパーティクル生成
	is_hit_ptcl_ = true;
	hit_ptcl_->setPosition(Getter_pos());
	hit_ptcl_->start();
}

bool BombAttack::SEQ_Move(const float delta_time){
	//移動
	inst_mesh_->setPosition(inst_mesh_->getPosition() + tnl::Vector3::TransformCoord({ 0,speed_, 0 }, dir_rad_));

	//放物線の高さ計算
	traveled_ += speed_;
	heiget_ = sin((traveled_ / length_) * DX_PI) * heiget_max_;
	//放物線を描く
	inst_mesh_->setPosition({ inst_mesh_->getPosition().x,heiget_,inst_mesh_->getPosition().z });

	//パーティクルの座標セット
	move_ptcl_->setPosition(inst_mesh_->getPosition());

	//弾からプレイエリアの中心のベクトルの計算
	float vec = MapCenter_Vec();

	//シーケンス移動条件
	//ヒット時のパーティクルが生成されたとき
	if (is_hit_ptcl_) {
		//移動パーティクル停止
		move_ptcl_->stop();

		tnl_sequence_.change(&BombAttack::SEQ_Hit);
	}
	//マップ外に出た時
	else if (vec >= map_vec_) {
		move_ptcl_->stop();

		//敵に当たった時の処理
		Enemy_Hit();

		tnl_sequence_.change(&BombAttack::SEQ_Hit);
	}
	//地面より下に行けば
	else if (inst_mesh_->getPosition().y <= 0.0f) {
		move_ptcl_->stop();

		//敵に当たった時の処理
		Enemy_Hit();

		tnl_sequence_.change(&BombAttack::SEQ_Hit);
	}

	TNL_SEQ_CO_END
}

bool BombAttack::SEQ_Hit(const float delta_time){
	//当たり判定無効
	is_collision_ = false;

	//始めの1フレームだけ
	if (tnl_sequence_.isStart()) {
		//当たり判定有効
		is_collision_ = true;
		//爆破時の攻撃力セット
		attack_power_ = explosion_damage_;
		//当たり判定を爆破サイズ * explosion_size_に
		bullet_rad_ = hit_ptcl_->getOriginRange() * explosion_size_;
		//se再生
		PlaySoundMem(hit_se_hdl_, DX_PLAYTYPE_BACK);
	}

	//パーティクル生成時間
	hit_ptcl_count_ += delta_time;
	//シーケンス移動条件
	//hit_ptcl_の生成時間経過したら弾消去
	if (hit_ptcl_count_ >= hit_ptcl_time_) {
		tnl_sequence_.change(&BombAttack::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool BombAttack::SEQ_Death(const float delta_time){
	//攻撃消去
	Delete();

	TNL_SEQ_CO_END
}

