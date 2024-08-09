#pragma once
#include "Actor.h"

enum class NewPlayerState
{
    Idle,
    Walk,
    Jump,
    Fall,
    GroundAttack,
    AirAttack,
    Dash,
    Hit,
    Dead,

    NewPlayerState_End
};

class CNewPlayer :
    public Actor<CNewPlayer, NewPlayerState>
{
};

