#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "SceneBace.h"
//#include "../Object/Block.h"
#include "../Object/Camera.h"
#include "../Character/Player.h"
#include "../Manager/ResourceManager.h"
#include "../Character/Enemy.h"
#include "../Manager/Sspawner.h"
#include "../Object/ProtectObject.h"

class PlayScene : public SceneBace{
private:
	
	//背景表示座標,左上の座標と右下の座標
	tnl::Vector3 bg_pos_{ 0,-100,0 }, map_endpos_{1968,724,0};
	//オブジェクトのプレハブ
	//std::shared_ptr<Block> block_ = nullptr;
	std::shared_ptr<Camera> camera_ = nullptr;
	std::shared_ptr<Player> player_ = nullptr;
	//std::shared_ptr<ProtectObject> protectobj_= nullptr;
	//std::shared_ptr<Enemy> enemy_ = nullptr;
	//表示するブロックのリスト
	//std::list<std::shared_ptr<Block>> blocks_;

	//仮敵スポン位置
	tnl::Vector3 enemy_spon_pos{ 1000,0,0 };

public:
	PlayScene();

	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time) override;
};
