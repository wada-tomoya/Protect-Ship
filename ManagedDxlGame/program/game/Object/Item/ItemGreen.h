#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemGreen : public ItemBase {
private:
	

public:
	ItemGreen() = default;

	//�����P�F�������f��
	ItemGreen(const int& mv1model);
	~ItemGreen();

	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time)override;
};
