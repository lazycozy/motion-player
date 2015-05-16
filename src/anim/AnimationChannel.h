/*
 * AnimationChannel.h
 *
 *  Created on: May 12, 2015
 *      Author: cozy
 */

#ifndef ANIM_ANIMATIONCHANNEL_H_
#define ANIM_ANIMATIONCHANNEL_H_

#include <map>

typedef unsigned int AnimFrame;

typedef struct {
	AnimFrame frame;
	float value;
} KeyFrame;

class AnimationChannel {
public:
	AnimationChannel();
	virtual ~AnimationChannel();

	void setTotalFrame(AnimFrame maxFrame);
	void setRange(float min, float max);
	AnimFrame addKeyFrame(AnimFrame, float value);

	float value();
	void setFrame(AnimFrame frame);
	void nextFrame();

private:
	AnimFrame _frame;
	float _value;
	float _min, _max;

	std::map<AnimFrame, float> _keyframes;
	KeyFrame _prev_key;
	KeyFrame _next_key;
};

#endif /* ANIM_ANIMATIONCHANNEL_H_ */
