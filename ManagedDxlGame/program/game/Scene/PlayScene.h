#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Manager/GameManager.h"
#include "SceneBace.h"
#include "../Manager/Sspawner.h"

class Camera;
class Play_Map;
class Player;
//class Spawner;
class ProtectObject;
class Collision;
class UIManager;
class TitleScene;
//enum class ENEMYTYPE;

class PlayScene : public SceneBace {
private:
	//�V�[�P���X
	tnl::Sequence<PlayScene> play_sequence_ = tnl::Sequence<PlayScene>(this, &PlayScene::Seq_Explanation);
	//�Q�[�������V�[�P���X
	bool Seq_Explanation(float delat_time);
	//���s�V�[�P���X
	bool Seq_Update(float delta_time);
	//�Q�[���I�[�o�[�V�[�P���X
	bool Seq_Gameover(float delta_time);
	//�Q�[���N���A�V�[�P���X
	bool Seq_GameClear(float delta_time);
	//���j���[��ʃV�[�P���X
	bool Seq_Menu(float delta_time);

	//�X�e�[�^�X�ύX�^�C�~���O
	std::vector<float> status_change_timing_;	
	//�ύX����X�e�[�^�X�̒l
	float change_hp_[static_cast<int>(ENEMYTYPE::max)];
	float change_spawninterval_[static_cast<int>(ENEMYTYPE::max)];
	float change_speed_[static_cast<int>(ENEMYTYPE::max)];
	//�G�̗̑�
	float enemy_hp_[static_cast<int>(ENEMYTYPE::max)];
	//�X�|���C���^�[�o��
	float enemy_spawninterval_[static_cast<int>(ENEMYTYPE::max)];
	//�ړ��X�s�[�h
	float enemy_speed_[static_cast<int>(ENEMYTYPE::max)];
	//�X�e�[�^�X�ύX�t���O
	bool is_status_change_ = false;
	//�X�e�[�^�X�ύX��
	int status_change_num_ = 0;
	//�X�e�[�^�X�ύX�񐔏��
	int status_change_max_ = 0;
	//�Q�[���̐�������
	float gametime_ = 61.0f;

	//�V�[�P���X��
	enum class NOWSEQUENCE {
		play,
		gameover,
		gameclear,
		explanation,
		menu,
	};
	NOWSEQUENCE nowsequence_ = NOWSEQUENCE::explanation;

	//�I�u�W�F�N�g�̃v���n�u
	std::shared_ptr<Camera> camera_ = nullptr;
	std::shared_ptr<Play_Map> map_ = nullptr;
	std::shared_ptr<Player> player_ = nullptr;
	std::shared_ptr<Spawner> spawner_ = nullptr;
	std::shared_ptr<ProtectObject> protectobject_ = nullptr;
	std::shared_ptr<Collision> collision_ = nullptr;
	std::shared_ptr<UIManager> ui_ = nullptr;

	//�Q�[���N���A����bgm
	int gameclear_bgm_ = 0;
	//�Q�[���I�[�o�[����bgm
	int gameover_bgm_ = 0;

	//esc���j���[�ē����W
	const tnl::Vector2i esc_guid_pos_ = { DXE_WINDOW_WIDTH - 150, 15 };

public:
	PlayScene(ENDCLASS_NAME class_name);
	~PlayScene();
	//���s�֐�
	void Update(float delta_time) override;
	//�\���֐�
	void Draw(float delta_time) override;
};