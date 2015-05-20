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

void anim::AnimationPlayer::makeJoints(File* file) {
	const File::Joints& joints = file->getConfigurations().joints;
	File::Joints::const_iterator ite;
	for (ite = joints.begin(); ite != joints.end(); ++ite) {

	}
}

void anim::AnimationPlayer::resetFrame() {
}

void anim::AnimationPlayer::nextFrame() {
}

} // namespace anim
