#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemBlue : public ItemBase {
private:
	

public:
	ItemBlue() = default;

	//�����P�F�������f��
	ItemBlue(const int& mv1model);
	~ItemBlue();

	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time)override;
};