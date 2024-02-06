#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Block {
public:
	//ブロックのサイズ
	static constexpr float size_ = 48.0f;
	//ブロックの座標
	tnl::Vector3 pos_;
	//ブロックの画像
	int graph_;

	Block(const tnl::Vector3& pos, const int graph) : pos_(pos), graph_(graph) {};
};
