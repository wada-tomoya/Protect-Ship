#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneBace.h"
#include "../Manager/GameManager.h"

class UIManager;

class TitleScene : public SceneBace {
private:
	//ui�C���X�^���X
	std::shared_ptr<UIManager> ui_ = nullptr;

	//�摜�n���h��
	int background_hdl = 0;
	//�N���b�N���Ă���V�[���J�ڂɂ����鎞��
	float scenechange_time_ = 1.0f;

	int click_se_ = 0;

	//�^�C�g��
	const std::string title_name_ = "Protect-Ship";
	const int fontsize_title_ = 100;
	tnl::Vector2i title_pos_{ 0,80 };

	//���������p
	int str_len_ = 0, str_wid_ = 0;

public:
	TitleScene(ENDCLASS_NAME classname);
	~TitleScene();

	//���s�֐�
	void Update(float delta_time) override;
	//�\���֐�
	void Draw(float delta_time) override;

	//���������֐�
	//�����i�\�����镶���A�����̂����W�j
	void Centered(std::string str, int& x_pos);
};