#ifndef PYRAMID_H
#define PYRAMID_H

#include "SceneObject.h"
#include <fstream>
#include <iomanip>

class Pyramid : public SceneObject
{
private:
    Vector3D base[4];

    Vector3D center[2];

public:
    Pyramid(double side_length, double height);

    void Write_to_file() const override;

    std::string Get_file_path() const override;

    std::string Get_typeID() const override;

    bool Set_in_scene(double x, double y, double orientation_angle);

    Pyramid Rotation(Matrix3x3 &rotation_matrix);

    Pyramid Translate(Vector3D translation_vector);

    friend std::ofstream &operator<<(std::ofstream &ofs, const Pyramid &rm);
};

#endif // PYRAMID_H