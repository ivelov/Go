#ifndef OBJECTS_H
#define OBJECTS_H
#include <SFML/Graphics.hpp>
#include "Graphics.h"
using namespace sf;
class Circles{
public:
    bool enabled,checked;
    int struc;
    static int strucCountB,strucCountW;
    Circles();
};

class CirTransAndScoreRects
{public:
    bool enW, enB;
    CirTransAndScoreRects();
};



#endif // OBJECTS_H
