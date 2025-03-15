#pragma once



// game engine components

#include"BBS/game.h"

#include"BBS/asset/particle_system/exhaust.h"

#include"BBS/asset/particle_system/space_explosion.h"

#include"BBS/asset/SFML_Text/tools.h"

#include"BBS/utility/collision_fun.h"



// standard c++ components

#include<iostream>	// only for debugging

#include<string>

#include<vector>

#include<numbers>

#include<concepts>

#include<cmath>



// game modules

#include"Constants.h"

#include"night_sky.h"

#include"vector_sprite.h"

#include"assets.h"

#include"space_ship.h"

#include"asteroid.h"

#include"bullet.h"

#include"game_states/state_data.h"

#include"game_states/state_functions.h"

// game states

#include"game_states/initial_state.h"

#include"game_states/game_state.h"

#include"game_states/game_over_state.h"

#include"game_states/highest_score_state.h"