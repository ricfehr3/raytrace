#ifndef HITABLEOBJECT_HPP
#define HITABLEOBJECT_HPP

#include "SceneObject.hpp"

class HitableObject : public SceneObject
{
public:
    virtual bool testHit();

private:
};

#endif
