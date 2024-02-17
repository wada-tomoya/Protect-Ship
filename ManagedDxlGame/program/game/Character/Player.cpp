#include "Player.h"

Player::Player(tnl::Vector3 upleft, tnl::Vector3 downright) {
	//移動速度
	speed_ = 10;
	//画像サイズ
	size_ = { 32,32,0 };
	//初期座標
	pos_ = { -48,0,0 };
	//プレイヤーが動ける画面の端
	up_edge_ = upleft.y + size_.y;
	down_edge_ = downright.y - size_.y;
	right_edge_ = downright.x - size_.x;
	left_edge_ = upleft.x + size_.x;

	//AttackManagerインスタンス
	attack_manager_ = std::make_shared<AttackManager>();

	//右向きと左向きのテクスチャをロード
	texture_hdl_right_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER_RIGHT");
	texture_hdl_left_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER_LEFT");

	//テクスチャの分割位置
	float dir = 1.0f / texture_dir;

	//メッシュ生成
	for (int i = 0; i < mesh_index_; ++i) {
		//テクスチャの切り取る位置計算
		const float ltop_x = dir * i;
		const float rbottom_x = dir * (i + 1);
		
		if (i < mesh_index_) {
			//右向き
			mesh_right_[i] = dxe::Mesh::CreatePlaneMV(size_, 1, 1, false, { ltop_x,0,0 }, { rbottom_x,1,0 });
			mesh_right_[i]->setTexture(texture_hdl_right_);
			mesh_right_[i]->dxe::Mesh::setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_right_[i]->dxe::Mesh::setSampleFilterMode(DX_DRAWMODE_NEAREST);

			//左向き
			mesh_left_[i] = dxe::Mesh::CreatePlaneMV(size_, 1, 1, false, { ltop_x,0,0 }, { rbottom_x,1,0 });
			mesh_left_[i]->setTexture(texture_hdl_left_);
			mesh_left_[i]->dxe::Mesh::setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_left_[i]->dxe::Mesh::setSampleFilterMode(DX_DRAWMODE_NEAREST);
		}
	}
}

void Player::Update(float delta_time) {
	Move(delta_time, up_edge_, down_edge_, right_edge_, left_edge_);
	
	//メッシュの座標を合わせる
	for (int i = 0; i < mesh_index_; ++i) {
		mesh_right_[i]->pos_ = pos_;
		mesh_left_[i]->pos_ = pos_;
	}
	
	//Normal_Attack生成
	Normal_Attack();
	//各攻撃実行
	attack_manager_->Update(delta_time);
}

void Player::Move(float delta_time, float up_edge, float down_edge, float right_edge, float left_edge) {	
	//移動　上
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		is_move_ = true;
		//移動
		pos_.y += speed_;
	}
	//移動　下
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		is_move_ = true;
		//移動
		pos_.y -= speed_;	
	}
	//移動　右
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		is_move_ = true;
		//移動
		pos_.x += speed_; 
		//向き変換　右
		chara_dir_ = DIRECTION::RIGHT;
	}
	//移動　左
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		is_move_ = true;
		//移動
		pos_.x -= speed_;
		//向き変換　左
		chara_dir_ = DIRECTION::LEFT;
	}
	//上端以上に行かない
	if (pos_.y < up_edge) pos_.y = up_edge;
	//下端以上に行かない
	if (pos_.y > down_edge) pos_.y = down_edge;
	//右端以上に行かない
	if (pos_.x > right_edge) pos_.x = right_edge;
	//左端以上に行かない
	if (pos_.x < left_edge) pos_.x = left_edge;

	//移動アニメーション再生
	Texture_Anim_Play(mesh_index_, delta_time);
	is_move_ = false;
}

void Player::Normal_Attack() {
	//マウス座標を取得、攻撃を生成	
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		mouse_pos_ = tnl::Input::GetMousePosition();
		//マウスの座標補正
		tnl::Vector3 a = { mouse_pos_.x - (DXE_WINDOW_WIDTH/2), mouse_pos_.y - (DXE_WINDOW_HEIGHT/2),0.0f };
		//攻撃生成
		attack_manager_->NormalAttack_Create(pos_, a);
	}
}

tnl::Vector3 Player::GetterPos() {
	return pos_;
}