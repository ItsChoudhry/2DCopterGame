#include "Animation.hpp"

Animation::Animation() {}

Animation::Animation(int t_index, int t_numFrames, int t_animationSpeed)
{
    index = t_index;
    numFrames = t_numFrames;
    animationSpeed = t_animationSpeed;
}
