#include "Player.h"

Player::Player(float up_edge, float down_edge, float right_edge, float left_edge) {	
	//移動速度
	speed_ = 5;
	//画像サイズ
	size_ = { 48,48,0 };
	//初期座標
	pos_ = { 900,570,0 };
	//プレイヤーが動ける画面の端
	up_edge_ = up_edge + size_.y;
	down_edge_ = down_edge - size_.y-76;
	right_edge_ = right_edge - size_.x;
	left_edge_ = left_edge + size_.x;
//------------------------------------------------------------------------------------------
	//右向きと左向きのテクスチャをロード
	texture_hdl_right_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER_RIGHT");
	texture_hdl_left_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER_LEFT");

	//テクスチャの分割位置
	float dir = 1 / texture_dir;

	for (int i = 0; i < mesh_index_; ++i) {
		//テクスチャの切り取る位置計算
		const float ltop_x = dir * i;
		const float rbottom_x = dir * (i + 1);
		
		if (i < mesh_index_) {
			//右向き
			mesh_right_[i] = dxe::Mesh::CreatePlaneMV({ size_.x, size_.y,0 }, 1, 1, false, { ltop_x,0,0 }, { rbottom_x,1,0 });
			mesh_right_[i]->setTexture(texture_hdl_right_);
			//mesh_right_[i]->dxe::Mesh::setBlendMode();
			//mesh_right_[i]->dxe::Mesh::setSampleFilterMode();

			//左向き
			mesh_left_[i] = dxe::Mesh::CreatePlaneMV({ size_.x, size_.y,0 }, 1, 1, false, { ltop_x,0,0 }, { rbottom_x,1,0 });
			mesh_left_[i]->setTexture(texture_hdl_left_);
			//mesh_left_[i]->dxe::Mesh::setBlendMode();
			//mesh_left_[i]->dxe::Mesh::setSampleFilterMode();
		}
	}
}

void Player::Update(float delta_time) {
	//メッシュの座標を合わせる
	for (int i = 0; i < mesh_index_; ++i) {
		mesh_right_[i]->pos_ = pos_;
		mesh_left_[i]->pos_ = pos_;
	}

	Move(delta_time, up_edge_, down_edge_, right_edge_, left_edge_);
	//Attack(delta_time);

	DrawStringEx(10, 10, -1, "%d", render_);
	DrawStringEx(10, 30, -1, "%d", chara_dir_);
}

void Player::Draw(float delta_time, std::shared_ptr<Camera> camera) {
	//プレイヤー表示
	//右向き
	if (chara_dir_ == DIRECTION::RIGHT) {
		mesh_right_[render_]->render(camera);
	}
	//左向き
	else if (chara_dir_ == DIRECTION::LEFT) {
		mesh_left_[render_]->render(camera);
	}	
	
	//弾の表示
	/*auto it = normal_attacks_.begin();
	while (it != normal_attacks_.end()) {
		(*it)->Draw(delta_time);
		it++;
	}*/
}

void Player::Move(float delta_time, float up_edge, float down_edge, float right_edge, float left_edge) {
	
	
	//移動　上
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		//移動
		pos_.y -= speed_;
		//上端以上に行かない
		if (pos_.y < up_edge) pos_.y = up_edge;
		//アニメーション再生
		anim_time_ += delta_time;
		for (; anim_time_ > anim_speed_;) {
			render_++;
			render_ %= mesh_index_;
			anim_time_ = 0;
		}
	}
	//移動　下
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		//移動
		pos_.y += speed_;
		//下端以上に行かない
		if (pos_.y > down_edge) pos_.y = down_edge;
		//アニメーション再生
		anim_time_ += delta_time;
		for (; anim_time_ > anim_speed_;) {
			render_++;
			render_ %= mesh_index_;
			anim_time_ = 0;
		}
	}
	//移動　右
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		//移動
		pos_.x += speed_; 
		//右端以上に行かない
		if (pos_.x > right_edge) pos_.x = right_edge;
		//アニメーション再生
		anim_time_ += delta_time;
		for (; anim_time_ > anim_speed_;) {
			render_++;
			render_ %= mesh_index_;
			anim_time_ = 0;
		}
		//向き変換　右
		chara_dir_ = DIRECTION::RIGHT;
	}
	//移動　左
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		//移動
		pos_.x -= speed_;
		//左端以上に行かない
		if (pos_.x < left_edge) pos_.x = left_edge;
		//アニメーション再生
		anim_time_ += delta_time;
		for (; anim_time_ > anim_speed_;) {
			render_++;
			render_ %= mesh_index_;
			anim_time_ = 0;
		}
		//向き変換　左
		chara_dir_ = DIRECTION::LEFT;
	}
}

//void Player::Attack(float delta_time) {
//	//マウスの座標
//	int mouse_pos_x = 0;
//	int mouse_pos_y = 0;
//
//	//クリックで攻撃
//	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
//		//マウスの座標を取得
//		GetMousePoint(&mouse_pos_x, &mouse_pos_y);
//		mposx = mouse_pos_x;
//		mposy = mouse_pos_y;
//		//攻撃生成
//		normal_attacks_.emplace_back(std::make_shared<NormalAttack>(pos_, mouse_pos_x,mouse_pos_y, attack_speed_));
//	}
//
//	//弾のUpdate実行、
//	auto it = normal_attacks_.begin();
//	while (it != normal_attacks_.end()) {
//		(*it)->Update(delta_time);
//		it++;
//	}
//
//	//弾を消す処理を書いてない
//}

tnl::Vector3 Player::GetterPos() {
	return pos_;
}