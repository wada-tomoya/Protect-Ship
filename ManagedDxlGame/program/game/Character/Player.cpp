#include "Player.h"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"

Player::Player(const tnl::Vector3& map_center, const float& map_rad, std::weak_ptr<dxe::Mesh> ground, std::weak_ptr<Camera> camera){
	//�ړ����x
	speed_ = 4;
	ori_speed_ = speed_;
	//�摜�T�C�Y
	size_ = { 32,32,0 };
	//�������W
	pos_ = { -48,(size_.y / 2),0 };
	//�ړ��ł���}�b�v�̔��a
	map_rad_ = map_rad;
	//�}�b�v�̒�������̊O���܂ł̒l��2��
	map_rad_root_ = map_rad_ * map_rad_;
	//�ړ��ł���}�b�v�̒��S
	map_center_ = map_center;
	//�G�Ƃ̓��Ă蔻��p�T�C�Y�̐ݒ�
	colli_size_ = { size_.x,size_.y,colli_thickness_ };
	//�v���C���[�̃e�N�X�`�������[�h
	texture_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER");

	//�U��se�ǂݍ���
	attack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("PlayerAttack_SE");
	//���e�U��se�ǂݍ���
	bomattack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("BombAttack");
	//�G�Ɠ�����������se�ǂݍ���
	enemy_hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy_Hit");
	//�G�Ɠ����������̃p�[�e�B�N��
	enemy_hit_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Player_Enemy_Hit");

	//�e�N�X�`���̕����ʒu
	float div = 1.0f / texture_div_;
	//�e�N�X�`���̏c�����ʒu
	float high_div = 1.0f / texture_height_div_;
	//�O�����̂������ʒu�̉��[
	float flont_div_down = high_div * (float)DIRECTION::FRONT;
	//�������̂������ʒu�̉��[
	float left_div_down = high_div * (float)DIRECTION::LEFT;
	//�E�����̂������ʒu�̉��[
	float right_div_down = high_div * (float)DIRECTION::RIGHT;
	//�������̂������ʒu�̉��[
	float back_div_down = high_div * (float)DIRECTION::BACK;

	//���b�V������
	for (int i = 0; i < player_mesh_index_; ++i) {
		//�e�N�X�`���̐؂���ʒu�v�Z
		const float ltop_x = div * i;
		const float rbottom_x = div * (i + 1);
		
		if (i < player_mesh_index_) {
			//�O����
			mesh_front_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, 0, 0 }, { rbottom_x, flont_div_down, 0 });
			mesh_front_[i]->setTexture(texture_hdl_);
			mesh_front_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_front_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_front_[i]->setCullingMode(DX_CULLING_RIGHT);
			//������
			mesh_left_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, left_div_down, 0 }, { rbottom_x, right_div_down, 0 });
			mesh_left_[i]->setTexture(texture_hdl_);
			mesh_left_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_left_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_left_[i]->setCullingMode(DX_CULLING_RIGHT);
			//�E����
			mesh_right_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, flont_div_down, 0 }, { rbottom_x, left_div_down, 0 });
			mesh_right_[i]->setTexture(texture_hdl_);
			mesh_right_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_right_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_right_[i]->setCullingMode(DX_CULLING_RIGHT);
			//������
			mesh_back_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, right_div_down, 0 }, { rbottom_x, back_div_down, 0 });
			mesh_back_[i]->setTexture(texture_hdl_);
			mesh_back_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_back_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_back_[i]->setCullingMode(DX_CULLING_RIGHT);
		}
	}

//�U���֌W-----------------------------------------------------------------------------------------------------------------------------------------
	attack_map_center_ = map_center_;
	attack_map_rad_ = map_rad_;

	//�U���̃e�N�X�`�������[�h
	atk_textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("NORMALATTACK_1"));
	atk_textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("BombAttack"));

	//NormalAttack�֘A
	//NormalAttack���������b�V��
	noratk_.origine_mesh_ = dxe::Mesh::CreateCubeMV(noratk_.size_, (int)10, (int)10);
	//���b�V������
	noratk_.mesh_pool_ = dxe::InstMeshPool::Create(noratk_.origine_mesh_, noratk_.instmax_, &atk_textures_);
	//���b�V���̐F�ݒ�
	noratk_.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });
	//�q�b�g���p�[�e�B�N��
	noratk_.hit_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Attack_Hit_Ptcl");
	//�ړ����̃p�[�e�B�N��
	noratk_.move_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("player_Attack_Move");

	ori_noratk_size_ = noratk_.size_;

	//BombAttack�֌W
	bomatk_.size_ = 10.0f;
	bomatk_.instmax_ = 20;
	//BombAttack���������b�V��
	bomatk_.origine_mesh_ = dxe::Mesh::CreateSphereMV(bomatk_.size_);
	//���b�V������
	bomatk_.mesh_pool_ = dxe::InstMeshPool::Create(bomatk_.origine_mesh_, bomatk_.instmax_, &atk_textures_);
	//���b�V���F�ݒ�
	bomatk_.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });
	//�q�b�g���̃p�[�e�B�N��
	bomatk_.hit_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Player_BombAttack");
	//�ړ����̃p�[�e�B�N��
	bomatk_.move_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Player_BombAttackMove");
	//�q�b�g����se�ǂݍ���
	bomatk_.hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Explosion");
//-----------------------------------------------------------------------------------------------------------------------------------------

	//�e����
	shadow_mesh_ = dxe::Mesh::CreatePlaneMV({ size_.x,size_.x,0 }, 10,10);
	//�e�̃e�N�X�`�������[�h
	shadow_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("SHADOW");
	//�e�N�X�`���Z�b�g
	shadow_mesh_->setTexture(shadow_texture_);
	shadow_mesh_->setBlendMode(DX_BLENDMODE_ALPHA);
	shadow_mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	shadow_mesh_->setCullingMode(DX_CULLING_RIGHT);
	//���W�ݒ�
	shadow_mesh_->pos_ = { pos_.x, shadow_pos_y_, pos_.z };
	//90�x��]
	shadow_mesh_->rot_ = shadow_down_;

	//�J�[�\����mesh����
	cursor_mesh_ = dxe::Mesh::CreateConeMV(10,30,10,10,360.0f);
	//�J�[�\���̃e�N�X�`���ǂݍ���
	cursor_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("ATTACK_CURSOR");
	//�e�N�X�`���Z�b�g
	cursor_mesh_->setTexture(cursor_texture_);
	//���W�ݒ�
	cursor_mesh_->pos_ = pos_;

	//AttackCursor_ptcl_�ǂݍ���
	//attackcursor_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("AttackCursor");

	//�n��
	ground_ = ground;
	//�J����
	camera_ = camera;
}

Player::~Player(){
	DeleteSoundMem(attack_se_hdl_);
	DeleteSoundMem(bomattack_se_hdl_);
	DeleteSoundMem(enemy_hit_se_hdl_);
	//attackcursor_ptcl_.reset();
	statusup_itemlist_.clear();

	noratk_.mesh_pool_.reset();
	noratk_.hit_ptcl_.reset();
	noratk_.move_ptcl_.reset();

	bomatk_.mesh_pool_.reset();
	bomatk_.hit_ptcl_.reset();
	bomatk_.move_ptcl_.reset();
	DeleteSoundMem(bomatk_.hit_se_hdl_);
}

void Player::Update(const float& delta_time) {
	//���G��Ԃ̃J�E���g�_�E��
	if (invincible_ > 0.0f) {
		invincible_ -= delta_time;

		//invincible_��0��葽����Γ����蔻�薳��
		is_colli_ = false;
		//�v���C���[�_��
		Flashing(delta_time, flash_interval_);
	}
	else {
		//invincible_��0�ȉ��Ȃ瓖���蔻��L��
		is_colli_ = true;
		//�v���C���[���邭�\��
		//PlayerLighting(true);

		is_flash_ = true;

	}
	
	//�ړ�
	Move(delta_time);
	
	//�v���C���[���b�V���̍��W�����킹��
	for (int i = 0; i < player_mesh_index_; ++i) {
		mesh_front_[i]->pos_ = pos_;
		mesh_left_[i]->pos_ = pos_;
		mesh_right_[i]->pos_ = pos_;
		mesh_back_[i]->pos_ = pos_;
	}
	//�e�̍��W�����킹��
	shadow_mesh_->pos_ = { pos_.x, shadow_pos_y_, pos_.z };

	try {
		//�J�[�\���̈ړ��A��]
		cursor_mesh_->pos_ = pos_ + tnl::Vector3::TransformCoord({ 0,distance_cursor_player_,0 }, cursor_mesh_->rot_);
		cursor_mesh_->rot_ = cursor_down_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(Angle_Center_Mouse()));
	}
	catch (int error) {
		assert(error );
	}
	
	//�U���s�\���I���܂ł̃J�E���g
	//can_attack_��0��葽����΍U���ł��Ȃ�
	if (can_attack_ > 0.0f) {
		can_attack_ -= delta_time;
	}
	else {
		can_attack_ = 0.0f;

		//�U������
		Attack_Create(delta_time);
	}

	//�e�U���̎��s�֐�
	Attack_Update(delta_time, attacks_);
}

void Player::Draw(const float& delta_time, const std::shared_ptr<Camera>& camera) {
	//�e�`��
	shadow_mesh_->render(camera);
	//�J�[�\���`��
	cursor_mesh_->render(camera);
	
	if (is_flash_) {
		//�v���C���[�̌���
		switch (chara_dir_) {
			//�O����
		case DIRECTION::FRONT:
			mesh_front_[render_]->render(camera);
			break;
			//������
		case DIRECTION::LEFT:
			mesh_left_[render_]->render(camera);
			break;
			//�E����
		case DIRECTION::RIGHT:
			mesh_right_[render_]->render(camera);
			break;
			//������
		case DIRECTION::BACK:
			mesh_back_[render_]->render(camera);
			break;
		}
	}

	dxe::DirectXRenderBegin();

	//�p�[�e�B�N���`��
	//�G�ƐڐG������
	enemy_hit_ptcl_->render(camera);
	//�}�E�X�J�[�\�����W�̃p�[�e�B�N��
	//attackcursor_ptcl_->render(camera);

	dxe::DirectXRenderEnd();
}

void Player::AttackDraw(const std::shared_ptr<Camera>& camera) {
	//�e�U���̕`��
	Attack_Draw(camera, attacks_, noratk_);
}

void Player::Flashing(const float& delta_tim, const float& flash_interval){
	flash_count_ += delta_tim;
	if (flash_count_ <= flash_interval) {
		//�v���C���[���Â�����
		//PlayerLighting(false);

		is_flash_ = false;
	}
	else if (flash_count_ <= (flash_interval * 2)) {
		//�v���C���[���邭�\��
		//PlayerLighting(true);
		is_flash_ = true;
	}
	else {
		flash_count_ = 0.0f;
	}
}

void Player::PlayerLighting(const bool& lighting){
	for (auto& player : mesh_front_) {
		player->setDefaultLightEnable(lighting);
	}
	for (auto& player : mesh_back_) {
		player->setDefaultLightEnable(lighting);
	}
	for (auto& player : mesh_left_) {
		player->setDefaultLightEnable(lighting);
	}
	for (auto& player : mesh_right_) {
		player->setDefaultLightEnable(lighting);
	}
	//���邳�̏��
	//is_flash_ = lighting;
}

void Player::Move(const float& delta_time) {
	//�ړ��O���W��ݒ�
	prev_pos_ = pos_;

	//�v���C���[�̈ړ�
	//�ړ��@��
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		is_move_ = true;
		//�ړ�
		pos_.z += speed_;
		//������ϊ��@�O
		chara_dir_ = DIRECTION::FRONT;
	}
	//�ړ��@��
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		is_move_ = true;
		//�ړ�
		pos_.x -= speed_;
		//�����ϊ��@��
		chara_dir_ = DIRECTION::LEFT;
	}
	//�ړ��@�E
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		is_move_ = true;
		//�ړ�
		pos_.x += speed_;
		//�����ϊ��@�E
		chara_dir_ = DIRECTION::RIGHT;
	}
	//�ړ��@��
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		is_move_ = true;
		//�ړ�
		pos_.z -= speed_;
		//������ϊ��@���
		chara_dir_ = DIRECTION::BACK;
	}
	//���S����̌����W�܂ł̒��� �x�N�g��
	float center_pos_vec = ((float)std::pow((pos_.x - map_center_.x),2) + (float)std::pow((pos_.z - map_center_.z),2));
	//�ړ��G���A���O�ɂ͍s���Ȃ�
	if (center_pos_vec >= map_rad_root_) {
		pos_ = prev_pos_;
	}

	//�ړ��A�j���[�V�����Đ�
	Texture_Anim_Play(player_mesh_index_, delta_time);
	is_move_ = false;
}

tnl::Vector3 Player::Cursor_Move_Norm_() {
	//���K�������l
	tnl::Vector3 norm_;
	//�}�E�X�̍��W
	tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();
	//��ʂ̒��S
	tnl::Vector3 center_screen = tnl::Vector3{ DXE_WINDOW_WIDTH / 2,DXE_WINDOW_HEIGHT / 2,0.0f };
	//�v�Z�i���K���j
	norm_ = tnl::Vector3::Normalize(mouse_pos - center_screen);

	return norm_;
}

float Player::Angle_Center_Mouse() {
	auto ground = ground_.lock();
	if (ground == nullptr) { throw - 1; }
	auto camera = camera_.lock();
	if (camera == nullptr) { throw - 1; }

	//�p�x
	float rad_;
	float angle_;

	//�}�E�X���W
	tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();
	//�}�E�X�J�[�\���̃��C
	tnl::Vector3 ray_nml = tnl::Vector3::CreateScreenRay(static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y),
														DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, camera->view_, camera->proj_);
	//�}�E�X�̃��C�ƒn�ʂ̓����������W���擾
	tnl::IsIntersectRayAABB(camera->pos_, ray_nml, tnl::ToMaxAABB(ground->pos_, ground->scl_), tnl::ToMinAABB(ground->pos_, ground->scl_), &ground_hit_pos_);
	//���W�A���Ŋp�x�v�Z
	rad_ = atan2((ground_hit_pos_.x - pos_.x), (ground_hit_pos_.z - pos_.z));

	//�x���@�ɒ���
	angle_ = rad_ * (180.0f / (float)DX_PI);

	return angle_;
}

void Player::Attack_Create(const float& delta_time) {
	//�ʏ�U���@���N���b�N
	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
		if (is_normalattack_) {
			is_normalattack_ = false;
			//se�Đ�
			PlaySoundMem(attack_se_hdl_, DX_PLAYTYPE_BACK);

			//�U������
			NormalAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_, itemupstatus_.speed_attack_,itemupstatus_.power_,itemupstatus_.Penetration_,
				attacks_, noratk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::normalattack), itemupstatus_.size_scale_);
			//attack_addnum_�̐��l�ɉ����Ēǉ��ŏo��U������
			for (int i = 0; i < attack_addnum_; i++) {
				NormalAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(addattack_rad_[i])),
					itemupstatus_.speed_attack_, itemupstatus_.power_, itemupstatus_.Penetration_,
					attacks_, noratk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::normalattack), itemupstatus_.size_scale_);

				NormalAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(-(addattack_rad_[i]))),
					itemupstatus_.speed_attack_, itemupstatus_.power_, itemupstatus_.Penetration_,
					attacks_, noratk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::normalattack), itemupstatus_.size_scale_);
			}
		}	
	}
	if (!is_normalattack_) {
		//�U���C���^�[�o���J�E���g
		attack_count_ += delta_time;
		if (attack_count_ >= attack_interval_) {
			//�U���\�ɂ���
			is_normalattack_ = true;
			//�U���J�E���g���Z�b�g
			attack_count_ = 0.0f;
		}
	}
	
	//���j�U���@�E�N���b�N
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT)) {
		if (bombstock_ > 0) {
			//���j�U������
			BombAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_, ground_hit_pos_,
				attacks_, bomatk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::bombattack));
			//se�Đ�
			PlaySoundMem(bomattack_se_hdl_, DX_PLAYTYPE_BACK);

			//���e�X�g�b�N�f�N�������g
			bombstock_--;
		}
	}
}

void Player::Enemy_Hit(){
	//���G���Ԏ��Ԑݒ�
	invincible_ = invincible_time_;
	//�U���s�\���Ԑݒ�
	can_attack_ = cooldown_time_;
	//�p�e�B�N������
	enemy_hit_ptcl_->setPosition(pos_);
	enemy_hit_ptcl_->start();

	PlaySoundMem(enemy_hit_se_hdl_, DX_PLAYTYPE_BACK);
}

void Player::AttackStatus_Set(){
	//list���̂��ꂼ��̃A�C�e���̐�
	int redcount = 0,bluecount = 0, greencount = 0;
	//���ꂼ��̃A�C�e���̐��J�E���g
	for (int i = 0; i < statusup_itemlist_.size(); i++) {
		if (statusup_itemlist_[i] == ITEMTYPE::Red) {
			redcount++;
		}
		else if (statusup_itemlist_[i] == ITEMTYPE::Blue) {
			bluecount++;
		}
		else if (statusup_itemlist_[i] == ITEMTYPE::Green) {
			greencount++;
		}
	}

	//�U���X�e�[�^�X�ݒ�
	//�U���͐ݒ�
	itemupstatus_.power_ = (itemupstatus_.power_up_ * redcount) - (itemupstatus_.power_down_ * greencount);
	//�U���X�s�[�h�ݒ�
	itemupstatus_.speed_attack_ = (itemupstatus_.speed_attack_up_ * redcount);
	//�U���C���^�[�o���ݒ�
	itemupstatus_.interval_ = ori_attack_interval_ - (itemupstatus_.interval_down_ * redcount);
	attack_interval_ = itemupstatus_.interval_;
	//�ђʗ͐ݒ�
	itemupstatus_.Penetration_ = ori_attack_penetration_ + (itemupstatus_.penetration_up_ * redcount);

	//�U���T�C�Y�ݒ�
	itemupstatus_.size_scale_ = 1.0f + (itemupstatus_.size_scale_up_ * redcount);
	noratk_.size_ = ori_noratk_size_ * itemupstatus_.size_scale_;

	//�v���C���[�ړ����x
	itemupstatus_.speed_player_ = ori_speed_ + (itemupstatus_.speed_player_up_ * bluecount);
	speed_ = itemupstatus_.speed_player_;

	//�ǉ��U���̌��ݒ�
	attack_addnum_ = greencount;
}

void Player::Setter_Item(const ITEMTYPE& itemtype){
	//�v�f��ǉ�
	statusup_itemlist_.emplace_back(itemtype);

	//list�̗v�f��itemmax�ȏ�Ȃ�ΐ擪�̗v�f������
	if (statusup_itemlist_.size() > itemmax_) {
		statusup_itemlist_.erase(statusup_itemlist_.begin());
	}
}

void Player::Item_Hit(const ITEMTYPE& itemtype) {
	if (itemtype == ITEMTYPE::Bomb) {
		//���e�ǉ�
		bombstock_++;
	}
	else if (itemtype == ITEMTYPE::Red || itemtype == ITEMTYPE::Blue || itemtype == ITEMTYPE::Green) {
		//list�ɃZ�b�g
		Setter_Item(itemtype);
	}
	else {
		return;
	}

	//�����A�C�e���ł̍U���X�e�[�^�Xup
	AttackStatus_Set();
}
