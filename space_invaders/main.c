#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <stdbool.h>

#include "kit_tools/mzapo_parlcd.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"
#include "game_objects/aliens.h"
#include "game_objects/space_ship.h"
#include "game_model/model.h"
#include "game_view/view.h"


int main(int argc, char *argv[]) {
    printf("Started\n");

    objects_t *aliens = create_aliens();
    objects_t *space_ship = create_space_ship();

    init_model();
    init_drawing();

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 1000/30 * 1000 * 1000;

    while(true){

        render(aliens, space_ship);
        advance_state(aliens, space_ship);


        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    return 0;
}