#include "Sspawner.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyChase.h"
#include "../Character/EnemyBig.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Camera.h"
#include "../Character/EnemyBase.h"
#include "../Object/ProtectObject.h"
#include "../Character/Player.h"

Spawner::Spawner(tnl::Vector3 map_center, float map_rad, std::shared_ptr<ProtectObject>& target_protectobj, std::shared_ptr<Player>& target_player) {
	//ターゲット情報
	target_player_ = target_player;
	target_protectobj_ = target_protectobj;
	
	//マップ情報挿入
	map_center_ = map_center;
	map_rad_ = map_rad;

	//ランダム値の種を時間で設定
	srand(time(0));

	//影生成
	shadow_mesh_ = dxe::Mesh::CreateDiskMV(1, 10, 10, 360);
	//影のテクスチャをロード
	shadow_textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("SHADOW_2"));
	//影複製
	shadow_mesh_pool_ = dxe::InstMeshPool::Create(shadow_mesh_, duplicate_max_, &shadow_textures_);

	//複製元 normal_enemy_のmv1モデル読み込み
	normal_enemy_.model_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("NORMAL_ENEMY_");
	normal_enemy_.colli_rad_ = normal_enemy_.size_.x * normal_enemy_.scale_.x;

	//複製元 enemy_chase_のmv1モデル読み込み
	enemy_chase_.model_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ENEMY_CHASE");
	//enemy_chase_ステータス設定
	enemy_chase_.colli_rad_ = enemy_chase_.size_.x * enemy_chase_.scale_.x;

	//複製元 big_enemy_のモデル読み込み
	big_enemy_.model_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("BIG_ENEMY");
	//big_enemy_ステータス設定
	big_enemy_.scale_ = { 0.6f,0.6f,0.6f };
	big_enemy_.spawn_interval_low_ = 1.0f;
	big_enemy_.colli_size_ = (big_enemy_.colli_size_ / big_enemy_.scale_.x);
	big_enemy_.colli_rad_ = big_enemy_.size_.x * big_enemy_.scale_.x;
}

Spawner::~Spawner() {
	shadow_mesh_pool_.reset();
	MV1DeleteModel(normal_enemy_.model_hdl_);
	MV1DeleteModel(enemy_chase_.model_hdl_);
}

void Spawner::Update(float delta_time) {
	auto protectobj = target_protectobj_.lock();
	if (protectobj == nullptr) { return; }
	auto player = target_player_.lock();
	if (player == nullptr) { return; }

	//敵生成
	Enemy_Spawn(protectobj, player, delta_time);

	//敵の実行と消去
	auto it = enemys_.begin();
	while (it != enemys_.end()){
		//実行
		(*it)->Update(delta_time);

		//is_alive_がfalseならば消去（敵死亡）
		if (!(*it)->Getter_is_alive()) {
			//アイテム生成
			CreateItem(Item_Lottery(itemprob_[0],itemprob_[1], itemprob_[2], itemprob_[3], itemprob_[4]), (*it)->Getter_pos());

			it = enemys_.erase(it);
			duplicate_count_--;
			continue;
		}
		it++;
	}

	//アイテムの実行
	ItemUpdate(delta_time);
}

void Spawner::Draw(std::shared_ptr<Camera> camera) {
	dxe::DirectXRenderBegin();

	//影描画
	shadow_mesh_pool_->render(camera);

	dxe::DirectXRenderEnd();

	//敵描画
	auto it = enemys_.begin();
	while (it != enemys_.end()) {
		//敵描画
		(*it)->Draw(camera);
		it++;
	}

	//アイテム描画
	ItemDraw(camera);
}

void Spawner::Enemy_Spawn(std::weak_ptr<ProtectObject> protectobject, std::weak_ptr<Player> player, float delta_time) {
	//normal_enemy_スポン
	normal_enemy_.spawn_count_ += delta_time;
	if (normal_enemy_.spawn_count_ > normal_enemy_.spawn_interval_) {
		//敵複製
		int duplication = EnemyDupe(normal_enemy_.model_hdl_, normal_enemy_.scale_);
		//影複製
		auto shadow = ShadowDupe(duplication);

		//listに挿入
		enemys_.emplace_back(std::make_shared<Enemy>(protectobject, duplication, shadow, normal_enemy_.speed_, normal_enemy_.hp_, normal_enemy_.colli_rad_, normal_enemy_.colli_size_));
		duplicate_count_++;

		//カウントリセット
		normal_enemy_.spawn_count_ = 0.0f;
	}

	//enemy_chase_スポン
	enemy_chase_.spawn_count_ += delta_time;
	if (enemy_chase_.spawn_count_ > enemy_chase_.spawn_interval_) {
		//敵複製
		int duplication = EnemyDupe(enemy_chase_.model_hdl_, enemy_chase_.scale_);
		//影複製
		auto shadow = ShadowDupe(duplication);

		//listに挿入
		enemys_.emplace_back(std::make_shared<EnemyChase>(player, duplication, shadow, enemy_chase_.speed_, enemy_chase_.hp_, enemy_chase_.colli_rad_, enemy_chase_.colli_size_));
		duplicate_count_++;

		//カウントリセット
		enemy_chase_.spawn_count_ = 0.0f;
	}

	//big_enemy_スポン
	big_enemy_.spawn_count_ += delta_time;
	if (big_enemy_.spawn_count_ > big_enemy_.spawn_interval_) {
		//敵複製
		int duplication = EnemyDupe(big_enemy_.model_hdl_, big_enemy_.scale_);
		//影複製
		auto shadow = ShadowDupe(duplication);

		//listに挿入
		enemys_.emplace_back(std::make_shared<EnemyBig>(protectobject, duplication, shadow, big_enemy_.speed_, big_enemy_.hp_, big_enemy_.colli_rad_, big_enemy_.colli_size_));
		duplicate_count_++;

		//カウントリセット
		big_enemy_.spawn_count_ = 0.0f;
	}
}

void Spawner::Enemy_SpawnStatusChange(ENEMYTYPE enemytype, float sub_spawn_interval, float add_hp, float add_speed) {
	switch (enemytype){
	case ENEMYTYPE::normal:
		//スポンインターバル減算
		normal_enemy_.spawn_interval_ -= sub_spawn_interval;
		//最低スポンインターバル未満にしない
		if (normal_enemy_.spawn_interval_ <= normal_enemy_.spawn_interval_low_) {
			normal_enemy_.spawn_interval_ = normal_enemy_.spawn_interval_low_;
		}
		//hp加算
		normal_enemy_.hp_ += add_hp;
		//speed加算
		normal_enemy_.speed_ += add_speed;
		break;
	case ENEMYTYPE::chase:
		//スポンインターバル減算
		enemy_chase_.spawn_interval_ -= sub_spawn_interval;
		//最低スポンインターバル未満にしない
		if (enemy_chase_.spawn_interval_ <= enemy_chase_.spawn_interval_low_) {
			enemy_chase_.spawn_interval_ = enemy_chase_.spawn_interval_low_;
		}
		//hp加算
		enemy_chase_.hp_ += add_hp;
		//speed加算
		enemy_chase_.speed_ += add_speed;
		break;
	case ENEMYTYPE::big:
		//スポンインターバル減算
		big_enemy_.spawn_interval_ -= sub_spawn_interval;
		//最低スポンインターバル未満にしない
		if (big_enemy_.spawn_interval_ <= big_enemy_.spawn_interval_low_) {
			big_enemy_.spawn_interval_ = big_enemy_.spawn_interval_low_;
		}
		//hp加算
		big_enemy_.hp_ += add_hp;
		//speed加算
		big_enemy_.speed_ += add_speed;
	default:
		break;
	}	
}

int Spawner::EnemyDupe(int model_hdl, DxLib::VECTOR scale) {
	//ランダムな角度（生成方向）
	rad_ = rand() % 360;
	float x = cos(rad_) * map_rad_;
	float z = sin(rad_) * map_rad_;
	//normal_enemy_複製
	int ene = MV1DuplicateModel(model_hdl);
	//初期位置に移動
	MV1SetPosition(ene, DxLib::VECTOR{ x,0.0f,z });
	//サイズ変更
	MV1SetScale(ene, scale);

	return ene;
}

Shared<dxe::InstMesh> Spawner::ShadowDupe(int enedupe) {
	auto shadow = shadow_mesh_pool_->CreateInstMesh();
	shadow->setPosition({ MV1GetPosition(enedupe).x, shadow_pos_y_, MV1GetPosition(enedupe).z });
	shadow->setRotation(shadow_down_);
	shadow->setUseTextureIndex(0);
	shadow->setScale({ 30.0f,30.0f,0 });

	return shadow;
}
