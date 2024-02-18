#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "SceneBace.h"
#include "../Object/Map/Play_Map.h"
#include "../Object/Camera.h"
#include "../Character/Player.h"
#include "../Character/Enemy.h"
#include "../Manager/Sspawner.h"
#include "../Object/ProtectObject.h"
#include "../Manager/Sspawner.h"
#include "../Object/Attack/AttackManager.h"
#include "../Manager/Collision.h"
#include "../Manager/ResourceManager.h"

class PlayScene : public SceneBace{
private:
	//オブジェクトのプレハブ
	std::shared_ptr<Play_Map> map_ = nullptr;
	std::shared_ptr<Camera> camera_ = nullptr;
	std::shared_ptr<Player> player_ = nullptr;
	std::shared_ptr<ProtectObject> protectobj_= nullptr;
	std::shared_ptr<Collision> collision_ = nullptr;

	//音楽
	int bgm_ = 0;
	
public:
	PlayScene();
	~PlayScene();
	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time) override;
};
