/*
 * AnimationChannel.cpp
 *
 *  Created on: May 12, 2015
 *      Author: cozy
 */

#include "AnimationChannel.h"
#include <limits>
#include <iostream>

namespace anim {

AnimationChannel::AnimationChannel()
: _min(std::numeric_limits<float>::min()), _max(std::numeric_limits<float>::max()), _prev_key(0), _next_key(0)
{
	// TODO Auto-generated constructor stub

}

AnimationChannel::~AnimationChannel() {
	// TODO Auto-generated destructor stub
}

void AnimationChannel::setRange(float min, float max) {
	_min = min;
	_max = max;
}

void AnimationChannel::setTrim(float trim)
{
	_trim = trim;
}

void AnimationChannel::addKeyFrame(Frame frame, float value) {
	KeyFrame key;
	key.frame = frame;
	key.value = value;
	_keys.insert(std::map<u32,KeyFrame>::value_type(frame, key));
	std::cout << "add key frame to channel frame:"<< frame << " value:" << value << std::endl;
}

Frame AnimationChannel::setFrame(Frame frame) {
	_next_key = findNextKeyFrame(frame);
	_prev_key = findPrevKeyFrame(frame);
	if (!_next_key || !_prev_key) {
		std::cout << "Not found key frame" << std::endl;
		return FRAME_INVALID;
	}
	_value = (_next_key->value - _prev_key->value) * (frame - _prev_key->frame) / (_next_key->frame - _prev_key->frame) + _prev_key->value;
	std::cout << "id:" << _id << " " << _value << std::endl;
	if (_value > _max) {
		_value = _max;
	}
	if (_value < _min) {
		_value = _min;
	}
	_value += _trim;
	_frame = frame;

	return _frame;
}

Frame AnimationChannel::nextFrame() {
	return setFrame(_frame + 1);
}

float AnimationChannel::value() {
	return _value;
}

KeyFrame* AnimationChannel::findNextKeyFrame(u32 frame)
{
	KeyFrames::iterator ikey = _keys.begin();
	for (; ikey != _keys.end(); ++ikey) {
		KeyFrame& key = ikey->second;
		if (key.frame > frame) {
			return &ikey->second;
		}
	}
	return 0;
}

KeyFrame* AnimationChannel::findPrevKeyFrame(u32 frame)
{
	KeyFrame* prevKey = 0;
	KeyFrames::iterator ikey = _keys.begin();
	for (; ikey != _keys.end(); ++ikey) {
		KeyFrame& key = ikey->second;
		if (key.frame > frame) {
			break;
		}
		prevKey = &ikey->second;
	}
	return prevKey;
}

} // namespace anim

