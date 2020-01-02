#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <memory>

#include "Vec3.hpp"

class SceneObject : std::enable_shared_from_this<SceneObject>
{
public:
    Vec3 position;
    Vec3 direction;

    template <typename Derived>
    std::shared_ptr<Derived> shared_from_base()
    {
        return std::static_pointer_cast<Derived>(shared_from_this());
    }
private:

protected:
};

#endif
