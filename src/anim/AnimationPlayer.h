/*
 * AnimationPlayer.h
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#ifndef ANIM_ANIMATIONPLAYER_H_
#define ANIM_ANIMATIONPLAYER_H_

#include "File.h"

namespace anim {

class AnimationPlayer {
public:
	AnimationPlayer();
	virtual ~AnimationPlayer();

	void makeJoints(File* file);
	void makeChannels(File* file);

	void resetFrame();
	int  nextFrame();
	float getValue(int channel);

private:
	int _curFrame;
	std::list<AnimationChannel> _channels;
};

} // namespace anim

#endif /* ANIM_ANIMATIONPLAYER_H_ */
