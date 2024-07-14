#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class ResourceManager {
private:
	//�ꖇ�摜�֘ALoadGraph�œǂݍ��ނ���
	//�摜�̃p�X��csv�p
	std::vector <std::vector<tnl::CsvCell>> graphics_csv_;
	//�摜��ۑ�����map
	std::unordered_map <std::string, int> graphics_map_;

public:
	//�摜��ǂݍ��ފ֐�
	int LoadGraph_(std::string graph_name);
	//�摜���폜����֐�
	void DeleteGraph_(std::string graph_name);

//-----------------------------------------------------------------------------------------------
 
private:
	//�A�j���[�V�����֘A�ƃ}�b�v�`�b�vLoadDivGraph�œǂݍ��ނ���
	//�A�j���[�V�����̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> animation_csv_;
	//�A�j���[�V������ۑ�����map
	std::unordered_map <std::string, std::shared_ptr<std::vector<int>>> animation_map_;
	//csv�t�@�C���̃A�C�e��
	enum ANIMATION_CSV_ITEM {
		PATH = 1,
		TOTAL_DIV_NUM,
		X_DIV_NUM,
		Y_DIV_NUM,
		X_SIZE,
		Y_SIZE,
	};

public:
	//�A�j���[�V�����ƃ}�b�v�`�b�v��ǂݍ��ފ֐�
	std::shared_ptr<std::vector<int>> LoadAnim_(std::string animation_name);

//------------------------------------------------------------------------------------------------

private:
	//�e�N�X�`���֌W
	//�e�N�X�`���̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> texture_csv_;
	//�e�N�X�`����ۑ�����map
	std::unordered_map <std::string, Shared<dxe::Texture>> texture_map_;
	
public:
	//�e�N�X�`����ǂݍ��ފ֐�
	Shared<dxe::Texture > LoadTexture_(std::string texture_name);

//-----------------------------------------------------------------------------------------------

private:
	//���֌W
	//���̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> sound_csv_;
	//����ۑ�����map
	std::unordered_map <std::string, int> sound_map_;

public:
	//����ǂݍ��ފ֐�
	int LoadSound_(std::string sound_name);

//-----------------------------------------------------------------------------------------------

private:
	//mv1��3D���f���֌W
	//���f���̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> mv1model_csv_;
	//���f����ۑ�����map
	std::unordered_map <std::string, int> mv1model_map_;
	//csv�t�@�C���̃A�C�e��
	enum MV1MODEL_CSV_ITEM {
		MODEL_NAME = 0,
		MODEL_FILE_PATH
	};

public:
	//���f����ǂݍ��ފ֐�
	int LoadMV1Model_(std::string model_name);

//-----------------------------------------------------------------------------------------------

private:
	//�p�[�e�B�N���֌W
	//�p�[�e�B�N���̃p�X��csv
	std::vector<std::vector<tnl::CsvCell>> ptcl_csv_;
	//�p�[�e�B�N����ۑ�����map
	std::unordered_map < std::string, Shared<dxe::Particle>> ptcl_map_;

public:
	//�p�[�e�B�N����ǂݍ��ފ֐�
	Shared<dxe::Particle> LoadPtcl_(std::string ptcl_name);

//-----------------------------------------------------------------------------------------------

private:
	//�R���X�g���N�^
	ResourceManager();

public:
	//�N���X�̃C���X�^���X
	static ResourceManager* GetInstance_ResourceManager();
	//static�N���X��delete
	static void Destroy();
};
