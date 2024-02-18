#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class ResourceManager {
private:
	//一枚画像関連LoadGraphで読み込むもの
	//画像のパスのcsv用
	std::vector <std::vector<tnl::CsvCell>> graphics_csv_;
	//画像を保存するmap
	std::unordered_map <std::string, int> graphics_map_;

//-----------------------------------------------------------------------------------------------
 
	//アニメーション関連とマップチップLoadDivGraphで読み込むもの
	//アニメーションのパスのcsv
	std::vector <std::vector<tnl::CsvCell>> animation_csv_;
	//アニメーションを保存するmap
	std::unordered_map <std::string, std::shared_ptr<std::vector<int>>> animation_map_;
	//csvファイルのアイテム
	enum ANIMATION_CSV_ITEM {
		PATH = 1,
		TOTAL_DIV_NUM,
		X_DIV_NUM,
		Y_DIV_NUM,
		X_SIZE,
		Y_SIZE,
	};

//------------------------------------------------------------------------------------------------

	//テクスチャ関係
	//テクスチャのパスのcsv
	std::vector <std::vector<tnl::CsvCell>> texture_csv_;
	//テクスチャを保存するmap
	std::unordered_map <std::string, Shared<dxe::Texture>> texture_map_;
	
//-----------------------------------------------------------------------------------------------

	//音関係
	//音のパスのcsv
	std::vector <std::vector<tnl::CsvCell>> sound_csv_;
	//音を保存するmap
	std::unordered_map <std::string, int> sound_map_;

//-----------------------------------------------------------------------------------------------
	//コンストラクタ
	ResourceManager();

public:
	static ResourceManager* GetInstance_ResourceManager();

//----------------------------------------------------------------------------------------------

	//画像を読み込む関数
	int LoadGraph_(std::string graph_name);
	//画像を削除する関数
	void DeleteGraph_(std::string graph_name);

//-----------------------------------------------------------------------------------------------

	//アニメーションとマップチップを読み込む関数
	std::shared_ptr<std::vector<int>> LoadAnim_(std::string animation_name);

//-----------------------------------------------------------------------------------------------

	//テクスチャを読み込む関数
	Shared<dxe::Texture > LoadTexture_(std::string texture_name);

//-----------------------------------------------------------------------------------------------

	//音を読み込む関数
	int LoadSound_(std::string sound_name);

};
