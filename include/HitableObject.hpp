#ifndef HITABLEOBJECT_HPP
#define HITABLEOBJECT_HPP

#include "SceneObject.hpp"

class HitableObject : SceneObject
{
public:
    virtual bool testHit();

private:
};

#endif
