#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <stdbool.h>
#include <sys/time.h>

#include "kit_tools/mzapo_parlcd.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"
#include "game_objects/aliens.h"
#include "game_objects/space_ship.h"
#include "game_model/model.h"
#include "game_view/view.h"
#include "game_objects/bullets.h"
#include "game_objects/game_text.h"
#include "game_objects/walls.h"
#include "game_objects/lives.h"
#include "game_objects/flying_saucer.h"



#define OBJECTS_NUM (GAME_TEXT+1)

int main(int argc, char *argv[]) {
    printf("Started\n");

    objects_t** objects = malloc(OBJECTS_NUM*sizeof(objects_t));

    objects[ALIENS] = create_aliens();
//    objects[ALIENS]->color = ORANGE;
    objects[ALIENS]->color = WHITE;

    objects[FLYING_SAUCER] = create_flying_saucer();
    objects[FLYING_SAUCER]->color = RED;

    objects[BULLETS] = create_bullets();
    objects[BULLETS]->color = WHITE;

    objects[SPACE_SHIP] = create_space_ship();
    objects[SPACE_SHIP]->color = RED;
//    objects[SPACE_SHIP]->color = GREEN;

    objects[WALLS] = create_walls();
    objects[WALLS]->color = WHITE;

    objects[LIVES] = create_lives();
//    objects[LIVES]->color = WHITE;
    objects[LIVES]->color = WHITE;

    objects[GAME_TEXT] = create_game_text();
    objects[GAME_TEXT]->color = RED;

    init_model();
    init_drawing();

//    struct timespec loop_delay;
//    loop_delay.tv_sec = 0;
//    loop_delay.tv_nsec = 1000/10 * 1000 * 1000;

//    int frames = 0;
//    struct timeval start_time, end_time;
//    double elapsed_time;

//    gettimeofday(&start_time, NULL);
    int game_state = -1;

    while(true){

        render(objects, OBJECTS_NUM);

        game_state = advance_state(objects, OBJECTS_NUM);
        if(game_state == 0){
//            objects[ALIENS] = create_aliens();
//            objects[ALIENS]->color = WHITE;

            reset_aliens(objects[ALIENS]);
        }
//        frames++;
//
//        gettimeofday(&end_time, NULL);
//        elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

//        if(elapsed_time >= 1.0){
//            printf("FPS: %.2f\n", frames / elapsed_time);
//            frames = 0;
//            start_time = end_time;
//        }
//        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    return 0;
}