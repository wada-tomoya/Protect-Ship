#include "CharacterBase.h"

void CharacterBase::Anim_Play(const std::shared_ptr<std::vector<int>>& animhdl, const float& delta_time) {
	//listのサイズ
	int hdlsize_ = static_cast<int>(animhdl->size());

	//アニメーション再生
	anim_time_ += delta_time;
	for (; anim_time_ > anim_speed_;) {
		anim_frame_++;
		anim_frame_ %= hdlsize_;
		anim_time_ = 0;
	}
}

void CharacterBase::Texture_Anim_Play(const int& mesharray_index, const float& delta_time) {
	if (is_move_) {
		anim_time_ += delta_time;
		for (; anim_time_ > anim_speed_;) {
			render_++;
			render_ %= mesharray_index;
			anim_time_ = 0;
		}
	}
}