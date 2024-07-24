#include "AttackBase.h"
#include "../../Object/Camera.h"

AttackBase::AttackBase(const std::shared_ptr<dxe::InstMesh>& inst_mesh, const std::shared_ptr<dxe::Particle>& hit_ptcl, 
	const std::shared_ptr<dxe::Particle>& move_ptcl, const tnl::Quaternion& dir_angle, const tnl::Vector3& map_center,
	const float& map_rad, const float& bullet_rad, const tnl::Vector3& spawn_pos) {
	//複製されたメッシュ
	inst_mesh_ = inst_mesh;
	//爆破時のパーティクル
	hit_ptcl_ = hit_ptcl;
	//移動時のパーティクル
	move_ptcl_ = move_ptcl;
	
	//進行方向の角度
	dir_rad_ = dir_angle;
	//プレイエリアの中心
	map_center_ = map_center;
	//プレイエリアの半径
	map_rad_ = map_rad;
	//マップの中心から外周までのベクトル
	map_vec_ = static_cast<float>(std::pow(map_rad, 2));
	//弾の半径設定
	bullet_rad_ = bullet_rad;
	//初期座標設定
	inst_mesh_->setPosition(spawn_pos);
	//生成時間設定
	hit_ptcl_time_ = hit_ptcl_->getTimeLimit();
	//生成範囲設定
	move_ptcl_->setOriginRange(bullet_rad_);
}

AttackBase::~AttackBase() {
	hit_ptcl_.reset();
	move_ptcl_.reset();
}

void AttackBase::Draw_Ptcl(const std::shared_ptr<Camera>& camera) {
	//ヒット時のパーティクル描画
	hit_ptcl_->render(camera);

	//移動時のパーティクル描画
	move_ptcl_->render(camera);
}

float AttackBase::MapCenter_Vec(){
	float vec = static_cast<float>(std::pow((inst_mesh_->getPosition().z - map_center_.z), 2))
		+ (std::pow((inst_mesh_->getPosition().x - map_center_.x), 2));

	return vec;
}
