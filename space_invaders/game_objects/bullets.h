#ifndef SPACE_INVADERS_BULLETS_H
#define SPACE_INVADERS_BULLETS_H

#include "object_structure.h"
#include "aliens.h"

#define BULLETS_NUM (ALIENS_NUM+1)

objects_t* create_bullets();
void move_space_ship_bullet(object_desc_t* bullet, int pos_x, bool red_knob_pressed);
void try_to_attack_space_ship(objects_t* bullets, objects_t* aliens);

#endif //SPACE_INVADERS_BULLETS_H
