/*
 * AnimationLoader.h
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#ifndef ANIM_ANIMATIONLOADER_H_
#define ANIM_ANIMATIONLOADER_H_

#include <string>

class AnimationLoader {
public:
	AnimationLoader();
	virtual ~AnimationLoader();

	static void loadJSON(const char* path);
};

#endif /* ANIM_ANIMATIONLOADER_H_ */
