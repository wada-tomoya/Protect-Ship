#pragma once
#include "../../library/tnl_sequence.h"
#include "../Scene/SceneBace.h"

class GameManager {
private:
	//���s���̃V�[��
	SceneBace* nowscene_ = nullptr;
	//���̃V�[��
	SceneBace* nextscene_ = nullptr;
	//�t�F�[�h�p�̉摜
	int trans_garph_hdl_ = 0;
	//�t�F�[�h�̎���
	float trans_time_ = 0.5f;
	//�V�[�P���X
	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqTransIn);
	//�t�F�[�h�C��
	bool seqTransIn(const float delta_time);
	//�t�F�[�h�A�E�g
	bool seqTransOut(const float delta_time);
	//�������Ȃ�
	bool seqRunScene(const float delta_time);

	GameManager() = default;
	GameManager(SceneBace* startscene);

	//���l�̃}�b�N�X
	const float alpha_max_ = 255.0f;

public:
	//static�N���X�ɃA�N�Z�X����֐�
	//�����P�F�����V�[��
	static GameManager* GetInstance_GameManager(SceneBace* startscene = nullptr);
	//�e�V�[����Update��Draw���s
	//�����P�F����
	void Update(const float& delta_time);
	//static�N���X����
	static void Destroy();
	//�V�[���؂�ւ�
	//�����P�F���̃V�[���A�����Q�F�g�����f�B�V�����̎���
	void ChangeScene(SceneBace* nextscene, float delta_time = 0.5f);
};
