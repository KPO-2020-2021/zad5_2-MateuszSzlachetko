#ifndef ROUNDMOUNTAIN_H
#define ROUNDMOUNTAIN_H

#include "SceneObject.h"
#include <fstream>
#include <iomanip>

class RoundMountain : public SceneObject
{
private:
    Vector3D base[18];

    Vector3D center[2];

public:
    RoundMountain(double radius, double height);

    void Write_to_file() const override;

    std::string Get_file_path() const override;

    std::string Get_typeID() const override;

    bool Set_in_scene(double x, double y);

    RoundMountain Rotation(Matrix3x3 &rotation_matrix);

    RoundMountain Translate(Vector3D translation_vector);

    friend std::ofstream &operator<<(std::ofstream &ofs, const RoundMountain &rm);
};

#endif // ROUNDMOUNTAIN_H