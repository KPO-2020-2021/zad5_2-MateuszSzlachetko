#ifndef PLATEAU_H
#define PLATEAU_H

#include "Cuboid.h"
#include "SceneObject.h"

class Plateau : public SceneObject
{
private:
    Cuboid body;

public:
    Plateau(double length, double width, double height);

    bool Set_in_scene(double x, double y, double orientation_angle);

    void Write_to_file() const override;

    std::string Get_file_path() const override;

    std::string Get_typeID() const override;
};

#endif // PLATEAU_H