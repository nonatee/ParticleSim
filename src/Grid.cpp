#include <vector>
#include "Constants.h"
#include "Grid.h"

ParticleGrid particleGrid(
    SCREEN_WIDTH/GRID_SIZE, std::vector<std::vector<uint16_t>>(SCREEN_HEIGHT/GRID_SIZE)
); 