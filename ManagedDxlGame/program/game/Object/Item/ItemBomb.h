#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemBomb : public ItemBase {
private:


public:
	ItemBomb() = default;

	//�����P�F�������f��
	ItemBomb(const int& mv1model);
	~ItemBomb();

	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time)override;
};