#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemRed : public ItemBase {
private:


public:
	ItemRed() = default;

	//�����P�F�������f��
	ItemRed(const int& mv1model);
	~ItemRed();

	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time)override;
};
