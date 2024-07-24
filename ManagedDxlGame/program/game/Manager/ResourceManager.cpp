#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	//�摜csv�ǂݍ���
	graphics_csv_ = tnl::LoadCsv("csv/Resource_csv/graph.csv");
	//�A�j���[�V����csv�ǂݍ���
	animation_csv_ = tnl::LoadCsv("csv/Resource_csv/animation.csv");
	//�e�N�X�`��csv�ǂݍ���
	texture_csv_ = tnl::LoadCsv("csv/Resource_csv/texture.csv");
	//��csv�ǂݍ���
	sound_csv_ = tnl::LoadCsv("csv/Resource_csv/sound.csv");
	//mv1���f��csv�ǂݍ���
	mv1model_csv_ = tnl::LoadCsv("csv/Resource_csv/mv1model.csv");
	//�p�[�e�B�N��csv�ǂݍ���
	ptcl_csv_ = tnl::LoadCsv("csv/Resource_csv/ptcl.csv");
}

ResourceManager::~ResourceManager() {
	graphics_csv_.clear();
	graphics_map_.clear();
	animation_csv_.clear();
	animation_map_.clear();
	texture_csv_.clear();
	texture_map_.clear();
	sound_csv_.clear();
	sound_map_.clear();
	mv1model_csv_.clear();
	mv1model_map_.clear();
	ptcl_csv_.clear();
	ptcl_map_.clear();
}

void ResourceManager::Destroy() {
	delete GetInstance_ResourceManager();
}

ResourceManager* ResourceManager::GetInstance_ResourceManager() {
	static ResourceManager* instance(nullptr);
	if (!instance) {
		instance = new ResourceManager();
	}
	return instance;
}

int ResourceManager::LoadGraph_(const std::string& graph_name) {
	//map����graph_name�ɑΉ�����摜�n���h����������
	auto it = graphics_map_.find(graph_name);

	//���łɃ��[�h���Ă���ꍇ�A���̉摜�n���h����������
	if (it != graphics_map_.end()) {
		return graphics_map_[graph_name];
	}

	//���[�h���ĂȂ��ꍇ�A�摜�ǂݍ���
	for (int y = 0; y < graphics_csv_.size(); ++y) {
		//���O����v���镨��T��
		if (graphics_csv_[y][0].getString().c_str() == graph_name) {
			int gpc_hdl = LoadGraph(graphics_csv_[y][1].getString().c_str(), true);

			//map�ɓǂݍ��񂾉摜��ۑ�
			graphics_map_.insert(std::make_pair(graph_name,gpc_hdl));

			//�摜�n���h����Ԃ�
			return gpc_hdl;
		}
	}
	//��v���镨���Ȃ������ꍇ
	return 0;
}

std::shared_ptr<std::vector<int>> ResourceManager::LoadAnim_(const std::string& animation_name) {
	//animation_name�ɑΉ�����A�j���[�V�����n���h����T��
	auto it = animation_map_.find(animation_name);

	//���łɃ��[�h���Ă���ꍇ�A���̃A�j���[�V�����n���h����������
	if (it != animation_map_.end()) {
		return animation_map_[animation_name];
	}

	//���[�h���Ă��Ȃ��ꍇ�A�ǂݍ���
	for (int y = 0; y < animation_csv_.size(); ++y) {
		//���O����v���镨��T��
		if (animation_csv_[y][0].getString().c_str() == animation_name) {

			std::shared_ptr<std::vector<int>> anim_hdl_
				= std::make_shared<std::vector<int>>(animation_csv_[y][ANIMATION_CSV_ITEM::TOTAL_DIV_NUM].getInt());

			//anim_hdl_��csv����ǂݎ�����f�[�^������
			LoadDivGraph(animation_csv_[y][ANIMATION_CSV_ITEM::PATH].getString().c_str(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::TOTAL_DIV_NUM].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::X_DIV_NUM].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::Y_DIV_NUM].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::X_SIZE].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::Y_SIZE].getInt(),
				anim_hdl_->data());

			//animation_map_�ɕۑ�
			animation_map_.insert(std::make_pair(animation_name, anim_hdl_));

			//�A�j���[�V�����n���h����������
			return anim_hdl_;
		}
	}
	//���O����v���镨���Ȃ��ꍇ
	return nullptr;
}

Shared<dxe::Texture> ResourceManager::LoadTexture_(const std::string& texture_name) {
	auto it = texture_map_.find(texture_name);
	
	//���łɃ��[�h���Ă���ꍇ
	if (it != texture_map_.end()) {
		//�ǂݍ���ł��镨��Ԃ�
		return texture_map_[texture_name];
	}

	//���[�h���Ă��Ȃ��ꍇ
	for (int y = 0; y < texture_csv_.size(); ++y) {
		//���O����v���镨��T��
		if (texture_csv_[y][0].getString().c_str() == texture_name) {
			
			Shared<dxe::Texture> texture_hdl
				= dxe::Texture::CreateFromFile(texture_csv_[y][1].getString().c_str());

			//���[�h�����e�N�X�`�����}�b�v�ɕۑ�
			texture_map_.insert(std::make_pair(texture_name, texture_hdl));

			//�e�N�X�`���n���h����������
			return texture_hdl;
		}
	}
	//���O�̈�v���镨���Ȃ��ꍇ
	return nullptr;
}

int ResourceManager::LoadSound_(const std::string& sound_name) {
	auto it = sound_map_.find(sound_name);

	//���łɃ��[�h���Ă���ꍇ
	if (it != sound_map_.end()) {
		//�ǂݍ���ł��镨��Ԃ�
		return sound_map_[sound_name];
	}

	//���[�h���Ă��Ȃ��ꍇ
	for (int y = 0; y < sound_csv_.size(); ++y) {
		//���O����v���镨��T��
		if (sound_csv_[y][0].getString().c_str() == sound_name) {
			int sound = LoadSoundMem(sound_csv_[y][1].getString().c_str());

			//map�ɓǂݍ��񂾉���ۑ�
			sound_map_.insert(std::make_pair(sound_name, sound));

			//����Ԃ�
			return sound;
		}
	}
	//���O�̈�v���镨���Ȃ��ꍇ
	return -1;
}

int ResourceManager::LoadMV1Model_(const std::string& model_name) {
	auto it = mv1model_map_.find(model_name);

	//���łɃ��[�h����map�ɕۑ����Ă���ꍇ
	if (it != mv1model_map_.end()) {
		//�ǂݍ���ł��镨��Ԃ�
		return mv1model_map_[model_name];
	}

	//���[�h���Ă��Ȃ��ꍇ
	for (int y = 0; y < mv1model_csv_.size(); ++y) {
		//���O����v���镨��T��
		if (mv1model_csv_[y][MV1MODEL_CSV_ITEM::MODEL_NAME].getString().c_str() == model_name) {
			//���f�����[�h
			int model = MV1LoadModel(mv1model_csv_[y][MV1MODEL_CSV_ITEM::MODEL_FILE_PATH].getString().c_str());
			
			//map�ɓǂݍ��񂾃��f����ۑ�
			mv1model_map_.insert(std::make_pair(model_name, model));

			//mv1���f����Ԃ�
			return model;		
		}
	}
	//��v���閼�O���Ȃ��ꍇ
	return -1;
}

Shared<dxe::Particle> ResourceManager::LoadPtcl_(const std::string& ptcl_name){
	auto it = ptcl_map_.find(ptcl_name);
	//���łɃ��[�h���Ă���ꍇ
	if (it != ptcl_map_.end()) {
		return ptcl_map_[ptcl_name];
	}

	//���[�h���ĂȂ��ꍇ
	for (int y = 0; y < ptcl_csv_.size(); ++y) {
		//���O����v���镨��T��
		if (ptcl_csv_[y][0].getString().c_str() == ptcl_name) {
			//�p�[�e�B�N���ǂݍ���
			Shared<dxe::Particle> ptcl = std::make_shared<dxe::Particle>(ptcl_csv_[y][1].getString().c_str());

			//map�ɕۑ�
			ptcl_map_.insert(std::make_pair(ptcl_name, ptcl));

			return ptcl;
		}
	}

	return nullptr;
}
