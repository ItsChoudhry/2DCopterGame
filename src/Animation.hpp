#pragma once

class Animation
{
public:
    unsigned int index;
    unsigned int numFrames;
    unsigned int animationSpeed;
    Animation();
    Animation(int t_index, int t_numFrames, int t_animationSpeed);
};
