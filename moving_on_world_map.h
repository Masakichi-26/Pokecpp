#ifndef _MOVING_ON_WORLD_MAP_H_
#define _MOVING_ON_WORLD_MAP_H_
#include "Trainer.h"

void move_location_on_world_map(Trainer& tnr);
void display_current_location_options(Trainer& tnr);
void determine_new_location(Trainer& tnr, std::string& sel, int& len, bool& loop_reset);

#endif