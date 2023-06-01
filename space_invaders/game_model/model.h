#ifndef SPACE_INVADERS_MODEL_H
#define SPACE_INVADERS_MODEL_H
#include "game_objects/object_structure.h"

#define EXIT (-2)
#define MENU (-1)
#define WIN 0
#define GAME 1

#define ALIENS          0
#define FLYING_SAUCER   1
#define BULLETS         2
#define SPACE_SHIP      3
#define WALLS           4
#define LIVES           5
#define GAME_TEXT       6
#define MENU_TEXT       7

void init_model();
int process_menu(objects_t** objects, int obj_num);
void prepare_game_scene(objects_t** objects);
int advance_state(objects_t** objects);
void prepare_menu_scene(objects_t** objects, int obj_num);

#endif //SPACE_INVADERS_MODEL_H
