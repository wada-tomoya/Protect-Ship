#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Manager/GameManager.h"
#include "SceneBace.h"
#include "../Manager/Sspawner.h"

class Camera;
class Play_Map;
class Player;
//class Spawner;
class ProtectObject;
class Collision;
class UIManager;
class TitleScene;
//enum class ENEMYTYPE;

class PlayScene : public SceneBace {
private:
	//シーケンス
	tnl::Sequence<PlayScene> play_sequence_ = tnl::Sequence<PlayScene>(this, &PlayScene::Seq_Explanation);
	//ゲーム説明シーケンス
	bool Seq_Explanation(float delat_time);
	//実行シーケンス
	bool Seq_Update(float delta_time);
	//ゲームオーバーシーケンス
	bool Seq_Gameover(float delta_time);
	//ゲームクリアシーケンス
	bool Seq_GameClear(float delta_time);
	//メニュー画面シーケンス
	bool Seq_Menu(float delta_time);

	//ステータス変更タイミング
	std::vector<float> status_change_timing_;	
	//変更するステータスの値
	float change_hp_[static_cast<int>(ENEMYTYPE::max)];
	float change_spawninterval_[static_cast<int>(ENEMYTYPE::max)];
	float change_speed_[static_cast<int>(ENEMYTYPE::max)];
	//敵の体力
	float enemy_hp_[static_cast<int>(ENEMYTYPE::max)];
	//スポンインターバル
	float enemy_spawninterval_[static_cast<int>(ENEMYTYPE::max)];
	//移動スピード
	float enemy_speed_[static_cast<int>(ENEMYTYPE::max)];
	//ステータス変更フラグ
	bool is_status_change_ = false;
	//ステータス変更回数
	int status_change_num_ = 0;
	//ステータス変更回数上限
	int status_change_max_ = 0;
	//ゲームの制限時間
	float gametime_ = 61.0f;

	//シーケンス名
	enum class NOWSEQUENCE {
		play,
		gameover,
		gameclear,
		explanation,
		menu,
	};
	NOWSEQUENCE nowsequence_ = NOWSEQUENCE::explanation;

	//オブジェクトのプレハブ
	std::shared_ptr<Camera> camera_ = nullptr;
	std::shared_ptr<Play_Map> map_ = nullptr;
	std::shared_ptr<Player> player_ = nullptr;
	std::shared_ptr<Spawner> spawner_ = nullptr;
	std::shared_ptr<ProtectObject> protectobject_ = nullptr;
	std::shared_ptr<Collision> collision_ = nullptr;
	std::shared_ptr<UIManager> ui_ = nullptr;

	//ゲームクリア時のbgm
	int gameclear_bgm_ = 0;
	//ゲームオーバー時のbgm
	int gameover_bgm_ = 0;

	//escメニュー案内座標
	const tnl::Vector2i esc_guid_pos_ = { DXE_WINDOW_WIDTH - 150, 15 };

public:
	PlayScene(ENDCLASS_NAME class_name);
	~PlayScene();
	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time) override;
};