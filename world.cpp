#ifndef _world_
#define _world_

#include <iostream>

#include <glm/glm.hpp>

#include <world.h>

World::World()
{
    initWorld();
}

std::vector<glm::vec3> World::blockToTriangles(int x, int y, int z)
{
    return {
        { x + 0.0f, y + 0.0f, z + 0.0f},
        { x + 0.0f, y + 0.0f, z + 1.0f},
        { x + 0.0f, y + 1.0f, z + 1.0f},
        { x + 1.0f, y + 1.0f, z + 0.0f},
        { x + 0.0f, y + 0.0f, z + 0.0f},
        { x + 0.0f, y + 1.0f, z + 0.0f},
        { x + 1.0f, y + 0.0f, z + 1.0f},
        { x + 0.0f, y + 0.0f, z + 0.0f},
        { x + 1.0f, y + 0.0f, z + 0.0f},
        { x + 1.0f, y + 1.0f, z + 0.0f},
        { x + 1.0f, y + 0.0f, z + 0.0f},
        { x + 0.0f, y + 0.0f, z + 0.0f},
        { x + 0.0f, y + 0.0f, z + 0.0f},
        { x + 0.0f, y + 1.0f, z + 1.0f},
        { x + 0.0f, y + 1.0f, z + 0.0f},
        { x + 1.0f, y + 0.0f, z + 1.0f},
        { x + 0.0f, y + 0.0f, z + 1.0f},
        { x + 0.0f, y + 0.0f, z + 0.0f},
        { x + 0.0f, y + 1.0f, z + 1.0f},
        { x + 0.0f, y + 0.0f, z + 1.0f},
        { x + 1.0f, y + 0.0f, z + 1.0f},
        { x + 1.0f, y + 1.0f, z + 1.0f},
        { x + 1.0f, y + 0.0f, z + 0.0f},
        { x + 1.0f, y + 1.0f, z + 0.0f},
        { x + 1.0f, y + 0.0f, z + 0.0f},
        { x + 1.0f, y + 1.0f, z + 1.0f},
        { x + 1.0f, y + 0.0f, z + 1.0f},
        { x + 1.0f, y + 1.0f, z + 1.0f},
        { x + 1.0f, y + 1.0f, z + 0.0f},
        { x + 0.0f, y + 1.0f, z + 0.0f},
        { x + 1.0f, y + 1.0f, z + 1.0f},
        { x + 0.0f, y + 1.0f, z + 0.0f},
        { x + 0.0f, y + 1.0f, z + 1.0f},
        { x + 1.0f, y + 1.0f, z + 1.0f},
        { x + 0.0f, y + 1.0f, z + 1.0f},
        { x + 1.0f, y + 0.0f, z + 1.0f}
    };
}

void World::initWorld()
{

}

std::vector<glm::vec3> getCube(int x, int y, int z)
{
    return {
        { x + 0.0f, y + 0.0f, z + 0.0f }, // Looking from -z towards +z
        { x + 1.0f, y + 0.0f, z + 0.0f },
        { x + 1.0f, y + 1.0f, z + 0.0f },
        { x + 0.0f, y + 0.0f, z + 0.0f },
        { x + 0.0f, y + 1.0f, z + 0.0f },
        { x + 1.0f, y + 1.0f, z + 0.0f }, // end
        { x + 0.0f, y + 0.0f, z + 0.0f }, // looking from -x towards +x
        { x + 0.0f, y + 0.0f, z + 1.0f },
        { x + 0.0f, y + 1.0f, z + 1.0f },
        { x + 0.0f, y + 0.0f, z + 0.0f },
        { x + 0.0f, y + 1.0f, z + 0.0f },
        { x + 0.0f, y + 1.0f, z + 1.0f }, // end
        { x + 1.0f, y + 0.0f, z + 1.0f }, // Looking from +z
        { x + 0.0f, y + 0.0f, z + 1.0f },
        { x + 0.0f, y + 1.0f, z + 1.0f },
        { x + 1.0f, y + 0.0f, z + 1.0f },
        { x + 1.0f, y + 1.0f, z + 1.0f },
        { x + 0.0f, y + 1.0f, z + 1.0f }, // end
        { x + 1.0f, y + 0.0f, z + 0.0f }, // Looking from +x
        { x + 1.0f, y + 1.0f, z + 0.0f },
        { x + 1.0f, y + 1.0f, z + 1.0f },
        { x + 1.0f, y + 0.0f, z + 0.0f },
        { x + 1.0f, y + 0.0f, z + 1.0f },
        { x + 1.0f, y + 1.0f, z + 1.0f }, // end
        { x + 0.0f, y + 0.0f, z + 0.0f }, // Looking from -y
        { x + 0.0f, y + 0.0f, z + 1.0f },
        { x + 1.0f, y + 0.0f, z + 1.0f },
        { x + 0.0f, y + 0.0f, z + 0.0f },
        { x + 1.0f, y + 0.0f, z + 0.0f },
        { x + 1.0f, y + 0.0f, z + 1.0f }, // end
        { x + 0.0f, y + 1.0f, z + 0.0f }, // Looking from +y
        { x + 0.0f, y + 1.0f, z + 1.0f },
        { x + 1.0f, y + 1.0f, z + 1.0f },
        { x + 0.0f, y + 1.0f, z + 0.0f },
        { x + 1.0f, y + 1.0f, z + 0.0f },
        { x + 1.0f, y + 1.0f, z + 1.0f } // end
    };
    // return {
    //     { x + 0.0f, y + 0.0f, z + 0.0f}, // zy side
    //     { x + 0.0f, y + 0.0f, z + 1.0f},
    //     { x + 0.0f, y + 1.0f, z + 1.0f},
    //     { x + 1.0f, y + 1.0f, z + 0.0f},
    //     { x + 0.0f, y + 0.0f, z + 0.0f},
    //     { x + 0.0f, y + 1.0f, z + 0.0f}, // end
    //     { x + 1.0f, y + 0.0f, z + 1.0f}, // 
    //     { x + 0.0f, y + 0.0f, z + 0.0f},
    //     { x + 1.0f, y + 0.0f, z + 0.0f},
    //     { x + 1.0f, y + 1.0f, z + 0.0f},
    //     { x + 1.0f, y + 0.0f, z + 0.0f},
    //     { x + 0.0f, y + 0.0f, z + 0.0f},
    //     { x + 0.0f, y + 0.0f, z + 0.0f},
    //     { x + 0.0f, y + 1.0f, z + 1.0f},
    //     { x + 0.0f, y + 1.0f, z + 0.0f},
    //     { x + 1.0f, y + 0.0f, z + 1.0f},
    //     { x + 0.0f, y + 0.0f, z + 1.0f},
    //     { x + 0.0f, y + 0.0f, z + 0.0f},
    //     { x + 0.0f, y + 1.0f, z + 1.0f},
    //     { x + 0.0f, y + 0.0f, z + 1.0f},
    //     { x + 1.0f, y + 0.0f, z + 1.0f},
    //     { x + 1.0f, y + 1.0f, z + 1.0f},
    //     { x + 1.0f, y + 0.0f, z + 0.0f},
    //     { x + 1.0f, y + 1.0f, z + 0.0f},
    //     { x + 1.0f, y + 0.0f, z + 0.0f},
    //     { x + 1.0f, y + 1.0f, z + 1.0f},
    //     { x + 1.0f, y + 0.0f, z + 1.0f},
    //     { x + 1.0f, y + 1.0f, z + 1.0f},
    //     { x + 1.0f, y + 1.0f, z + 0.0f},
    //     { x + 0.0f, y + 1.0f, z + 0.0f},
    //     { x + 1.0f, y + 1.0f, z + 1.0f},
    //     { x + 0.0f, y + 1.0f, z + 0.0f},
    //     { x + 0.0f, y + 1.0f, z + 1.0f},
    //     { x + 1.0f, y + 1.0f, z + 1.0f},
    //     { x + 0.0f, y + 1.0f, z + 1.0f},
    //     { x + 1.0f, y + 0.0f, z + 1.0f}
    // };
}

#endif /* _world_ */