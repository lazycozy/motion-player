/*
 * AnimationTrack.h
 *
 *  Created on: May 12, 2015
 *      Author: cozy
 */

#ifndef ANIM_ANIMATIONTRACK_H_
#define ANIM_ANIMATIONTRACK_H_

#include "AnimationChannel.h"

namespace anim {

typedef unsigned int JointId;

class AnimationTrack {
public:
	AnimationTrack();
	virtual ~AnimationTrack();

	void addChannel(JointId id, AnimationChannel& channel);

private:
	std::map<int, AnimationChannel&> _channels;
};

} // namespace anim

#endif /* ANIM_ANIMATIONTRACK_H_ */
