/*
 * AnimationChannel.h
 *
 *  Created on: May 12, 2015
 *      Author: cozy
 */

#ifndef ANIM_ANIMATIONCHANNEL_H_
#define ANIM_ANIMATIONCHANNEL_H_

#include <map>

namespace anim {

typedef unsigned int u32;

typedef struct {
	u32 frame;
	float value;
} KeyFrame;

typedef std::map<u32,KeyFrame> KeyFrames;

class AnimationChannel {
public:
	AnimationChannel();
	virtual ~AnimationChannel();

	void setTotalFrame(u32 maxFrame);
	void setRange(float min, float max);
	void addKeyFrame(u32 frame, float value);

	float value();
	void setFrame(u32 frame);
	void nextFrame();

private:
	u32 _id;
	u32 _frame;
	float _value;
	float _min, _max;

	KeyFrames _keys;
	KeyFrame* _prev_key;
	KeyFrame* _next_key;

	KeyFrame* findNextKeyFrame(u32 frame);
	KeyFrame* findPrevKeyFrame(u32 frame);
};

} // namespace anim

#endif /* ANIM_ANIMATIONCHANNEL_H_ */
