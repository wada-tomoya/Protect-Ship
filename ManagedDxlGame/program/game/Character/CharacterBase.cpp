#include "CharacterBase.h"

void CharacterBase::Anim_Play(std::shared_ptr<std::vector<int>> animhdl, float delta_time) {
	//listのサイズ
	int hdlsize_ = animhdl->size();

	//アニメーション再生
	anim_time_ += delta_time;
	for (; anim_time_ > anim_speed_;) {
		anim_frame_++;
		anim_frame_ %= hdlsize_;
		anim_time_ = 0;
	}
}

void CharacterBase::Texture_Anim_Play(int texture_dir, float delta_time) {
	
}