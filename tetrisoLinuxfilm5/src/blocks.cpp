#include "block.h"
#include "posicion.h"

class LBlock :public Block
{
    public:
    LBlock()
    {
        id = 1;
        pozycje[0] = {Posicion(0,2), Posicion(1,0), Posicion(1,1), Posicion(1,2)};
        pozycje[1] = {Posicion(0,1), Posicion(1,1), Posicion(2,1), Posicion(2,2)};
        pozycje[2] = {Posicion(1,0), Posicion(1,1), Posicion(1,2), Posicion(2,0)};
        pozycje[3] = {Posicion(0,0), Posicion(0,1), Posicion(1,1), Posicion(2,1)};
        Move(0, 3);
    }
};

class JBlock :public Block
{
    public:
    JBlock()
    {
        id = 2;
        pozycje[0] = {Posicion(0,0), Posicion(1,0), Posicion(1,1), Posicion(1,2)};
        pozycje[1] = {Posicion(0,1), Posicion(0,2), Posicion(1,1), Posicion(2,1)};
        pozycje[2] = {Posicion(1,0), Posicion(1,1), Posicion(1,2), Posicion(2,2)};
        pozycje[3] = {Posicion(0,1), Posicion(1,1), Posicion(2,0), Posicion(2,1)};
        Move(0, 3);
    }
};

class IBlock :public Block
{
    public:
    IBlock()
    {
        id = 3;
        pozycje[0] = {Posicion(1,0), Posicion(1,1), Posicion(1,2), Posicion(1,3)};
        pozycje[1] = {Posicion(0,2), Posicion(1,2), Posicion(2,2), Posicion(3,2)};
        pozycje[2] = {Posicion(2,0), Posicion(2,1), Posicion(2,2), Posicion(2,3)};
        pozycje[3] = {Posicion(0,1), Posicion(1,1), Posicion(2,1), Posicion(3,1)};
        Move(-1, 3);
    }
};

class OBlock :public Block
{
    public:
    OBlock()
    {
        id = 4;
        pozycje[0] = {Posicion(0,0), Posicion(0,1), Posicion(1,0), Posicion(1,1)};
        Move(0, 4);
    }
};

class SBlock :public Block
{
    public:
    SBlock()
    {
        id = 5;
        pozycje[0] = {Posicion(0,1), Posicion(0,2), Posicion(1,0), Posicion(1,1)};
        pozycje[1] = {Posicion(0,1), Posicion(1,1), Posicion(1,2), Posicion(2,2)};
        pozycje[2] = {Posicion(1,1), Posicion(1,2), Posicion(2,0), Posicion(2,1)};
        pozycje[3] = {Posicion(0,0), Posicion(1,0), Posicion(1,1), Posicion(2,1)};
        Move(0, 3);
    }
};

class TBlock :public Block
{
    public:
    TBlock()
    {
        id = 6;
        pozycje[0] = {Posicion(0,1), Posicion(1,0), Posicion(1,1), Posicion(1,2)};
        pozycje[1] = {Posicion(0,1), Posicion(1,1), Posicion(1,2), Posicion(2,1)};
        pozycje[2] = {Posicion(1,0), Posicion(1,1), Posicion(1,2), Posicion(2,1)};
        pozycje[3] = {Posicion(0,1), Posicion(1,0), Posicion(1,1), Posicion(2,1)};
        Move(0, 3);
    }
};

class ZBlock :public Block
{
    public:
    ZBlock()
    {
        id = 7;
        pozycje[0] = {Posicion(0,0), Posicion(0,1), Posicion(1,1), Posicion(1,2)};
        pozycje[1] = {Posicion(0,2), Posicion(1,1), Posicion(1,2), Posicion(2,1)};
        pozycje[2] = {Posicion(1,0), Posicion(1,1), Posicion(2,1), Posicion(2,2)};
        pozycje[3] = {Posicion(0,1), Posicion(1,0), Posicion(1,1), Posicion(2,0)};
        Move(0, 3);
    }
};