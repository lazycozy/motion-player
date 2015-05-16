/*
 * AnimationPlayer.h
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#ifndef ANIM_ANIMATIONPLAYER_H_
#define ANIM_ANIMATIONPLAYER_H_

class AnimationPlayer {
public:
	AnimationPlayer();
	virtual ~AnimationPlayer();

	void load(const char* path);
	void reset();
	void next();

private:
	//AnimationManager* _manager;
};

#endif /* ANIM_ANIMATIONPLAYER_H_ */
