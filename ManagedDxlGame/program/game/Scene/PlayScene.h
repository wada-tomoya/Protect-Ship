#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Manager/GameManager.h"
#include "TitleScene.h"
#include "SceneBace.h"

class Camera;
class Play_Map;
class Player;
class Spawner;
class ProtectObject;
class Collision;
class UIManager;

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

	//�Q�[���̐�������
	float gametime_ = 121.0f;

	//�Q�[���N���A����bgm
	int gameclear_bgm_ = 0;
	//�Q�[���I�[�o�[����bgm
	int gameover_bgm_ = 0;

public:
	PlayScene(ENDCLASS_NAME class_name);
	~PlayScene();
	//���s�֐�
	void Update(float delta_time) override;
	//�\���֐�
	void Draw(float delta_time) override;
};