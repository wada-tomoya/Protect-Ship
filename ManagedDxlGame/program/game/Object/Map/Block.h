#pragma once
#include "../dxlib_ext/dxlib_ext.h"s

class Block {
public:
	//ブロックのサイズ
	static constexpr float size_ = 48.0f;
	//ブロックの座標
	tnl::Vector3 pos_;

	Block(const tnl::Vector3& pos) : pos_(pos) {};
};
