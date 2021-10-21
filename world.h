#ifndef _world_h_
#define _world_h_

#include <glm/glm.hpp>
#include <vector>

#define WORLD_SIZE_X 5
#define WORLD_SIZE_Y 3
#define WORLD_SIZE_Z 4

struct Block
{
    unsigned int type; /* 0 == air */
    unsigned char color[3]{ 150, 150, 150 };
};

class World
{
public:
    World();

    std::vector<glm::vec3> blockToTriangles(int x, int y, int z);
    void initWorld();
private:
    Block blocks[WORLD_SIZE_X][WORLD_SIZE_Y][WORLD_SIZE_Z];

};

/**
 * Get vertices of a cube positioned at x, y, z.
 */
std::vector<glm::vec3> getCube(int x, int y, int z);

#endif /* _world_h_ */