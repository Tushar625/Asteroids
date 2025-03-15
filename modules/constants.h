#pragma once


#define STAR_COUNT 200
#define STAR_MIN_VELOCITY 2
#define STAR_MAX_VELOCITY 5


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


#define VIRTUAL_WIDTH 426
#define VIRTUAL_HEIGHT 240


#define SMALL_FONT_SIZE 8
#define MEDIUM_FONT_SIZE 16
#define LARGE_FONT_SIZE 64


/*
	All the sprites are considered square, so their length = breadth = size
*/


#define SPACESHIP_ACCN 100.0f	// when thrust is applied
#define SPACESHIP_ROTATION_SPEED 200.0f
#define	SPACESHIP_SIZE 20
#define	SPACESHIP_HALF_SIZE 10


#define ASTEROID_MIN_VELOCITY 25
#define ASTEROID_MAX_VELOCITY 50
#define ASTEROID_ROTATION_SPEED 10.0f
#define ASTEROID_SIZE 20


#define BULLET_LIFE_TIME .375f
#define BULLET_VELOCITY 500
#define BULLET_SIZE 2
#define BULLET_HALF_SIZE 1


#define MAX_HEALTH 3
#define MAX_SCORE 20	// score = MAX_SCORE / scale of asteroid sprite



enum ECS_ENTITY_TYPE { SPACESHIP_ENTITY, ASTEROID_ENTITY, BULLET_ENTITY };

enum ECS_COMPONENTS { ENTITY_TYPE, SPRITE, VELOCITY };