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

	void resetFrame();
	void nextFrame();

private:
	//AnimationManager* _manager;
};

} // namespace anim

#endif /* ANIM_ANIMATIONPLAYER_H_ */
