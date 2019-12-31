#ifndef HITABLE_HPP
#define HITABLE_HPP

#include "Mesh.hpp"

class Hitable
{
public:
    virtual bool testHit();

private:
    Mesh m_mesh;
};

#endif
