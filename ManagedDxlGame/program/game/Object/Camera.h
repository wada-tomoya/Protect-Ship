#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class Camera : public dxe::Camera {
private:
	//�^�[�Q�b�g�ƃJ�����̋���
	tnl::Vector3 camera_pos{ 0,300,-500 };
	
public:
	Camera();
	//�J�����̃A�b�v�f�[�g�̏���
	//�����i�Ǐ]����^�[�Q�b�g���W�j
	void Update(tnl::Vector3 target_pos = {0,0,0});
};