/*
 * AnimationPlayer.cpp
 *
 *  Created on: May 15, 2015
 *      Author: cozy
 */

#include "AnimationPlayer.h"

namespace anim {

AnimationPlayer::AnimationPlayer() {
	// TODO Auto-generated constructor stub

}

AnimationPlayer::~AnimationPlayer() {
	// TODO Auto-generated destructor stub
}

void AnimationPlayer::makeJoints(File* file) {
	const File::Joints& joints = file->getConfigurations().joints;
	File::Joints::const_iterator ite;
	for (ite = joints.begin(); ite != joints.end(); ++ite) {

	}
}

void AnimationPlayer::makeChannels(File* file) {

}

void AnimationPlayer::resetFrame() {
	_curFrame = 0;
	std::list<AnimationChannel>::iterator ite;
	for (ite = _channels.begin(); ite != _channels.end(); ++ite) {
		ite->setFrame(0);
	}
}

int AnimationPlayer::nextFrame() {
	int nextFrame = _curFrame + 1;

	std::list<AnimationChannel>::iterator ite;
	for (ite = _channels.begin(); ite != _channels.end(); ++ite) {
		ite->nextFrame();
	}

	_curFrame++;
	return _curFrame;
}

float AnimationPlayer::getValue(int channel) {
}

} // namespace anim

