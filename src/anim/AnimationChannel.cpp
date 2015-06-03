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
: _id(0),
  _frame(0),
  _value(0),
  _min(std::numeric_limits<float>::min()),
  _max(std::numeric_limits<float>::max()),
  _trim(0),
  _prev_key(0),
  _next_key(0)
{
	// TODO Auto-generated constructor stub

}

AnimationChannel::~AnimationChannel() {
	// TODO Auto-generated destructor stub
}

void AnimationChannel::setId(int id)
{
	_id = id;
}

void AnimationChannel::setRange(float min, float max) {
	_min = min;
	_max = max;
}

void AnimationChannel::setTrim(float trim)
{
	_trim = trim;
}

void AnimationChannel::addKeyFrame(Frame frame, float value, int function) {
	KeyFrame key;
	key.frame = frame;
	key.value = value;
	key.function = function;
	_keys.insert(std::map<u32,KeyFrame>::value_type(frame, key));
	//std::cout << "add key frame to channel frame:"<< frame << " value:" << value << std::endl;
}

Frame AnimationChannel::setFrame(Frame frame) {
	_next_key = findNextKeyFrame(frame);
	_prev_key = findPrevKeyFrame(frame);
	if (!_next_key || !_prev_key) {
		std::cout << "Not found key frame" << std::endl;
		return FRAME_INVALID;
	}
	if (_prev_key->function == 3) {
		_value = calcValueEaseInOut(_prev_key, _next_key, frame);
	} else {
		_value = calcValueLinear(_prev_key, _next_key, frame);
	}
	//std::cout << "setFrame(" << frame << ") id:" << _id << " " << _value << std::endl;
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

void AnimationChannel::hermite( float t, float *h1, float *h2, float *h3, float *h4 )
{
	float t2;
	float t3;

	t2 = t * t;
	t3 = t * t2;

	*h2 = 3.0f * t2 - t3 - t3;
	*h1 = 1.0f - *h2;
	*h4 =  t3 - t2;
	*h3 = *h4 - t2 + t;
}

float AnimationChannel::calcValueLinear(const KeyFrame* k0, const KeyFrame* k1, Frame frame)
{
	return (k1->value - k0->value) * (frame - k0->frame) / (k1->frame - k0->frame) + k0->value;
}

float AnimationChannel::calcValueEaseIn(const KeyFrame* k0, const KeyFrame* k1, Frame frame)
{
	// TODO:change the collect fomula
	return calcValueLinear(k0, k1, frame);
}

float AnimationChannel::calcValueEaseOut(const KeyFrame* k0, const KeyFrame* k1, Frame frame)
{
	// TODO:change the collect fomula
	return calcValueLinear(k0, k1, frame);
}

float AnimationChannel::calcValueEaseInOut(const KeyFrame* k0, const KeyFrame* k1, Frame frame)
{
	// TODO:change the collect fomula
	float in = 0.f, out = 0.f;
	float h1, h2, h3, h4;
	float t = (float)(frame - k0->frame) / (float)(k1->frame - k0->frame);
	hermite(t, &h1, &h2, &h3, &h4);
	float value = h1 * k0->value + h2 * k1->value + h3 * out + h4 * in;
	//std::cout << "h1=" << h1 << " h2=" << h2 << " h3=" << h3 << " h4=" << h4 << " v=" << value << std::endl;
	return value;
}

} // namespace anim

