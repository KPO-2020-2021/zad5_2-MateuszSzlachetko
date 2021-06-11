#include "Pyramid.h"

#include "Pyramid.h"

Pyramid::Pyramid(double side_length, double height)
{
    center[0] = Vector3D({0, 0, 0});
    center[1] = Vector3D({0, 0, height});

    double a = side_length / 2;

    base[0] = Vector3D({-a, a, 0});
    base[1] = Vector3D({a, a, 0});
    base[2] = Vector3D({a, -a, 0});
    base[3] = Vector3D({-a, -a, 0});

    ID = Get_total();

    File_path = "../data/Pyramid" + std::to_string(ID) + ".dat";

    Write_to_file();
}

std::ofstream &operator<<(std::ofstream &ofs, const Pyramid &rm)
{
    ofs << std::setprecision(10) << std::fixed;

    for (int i = 0; i < 4; ++i)
    {
        ofs << rm.center[0] << std::endl;
        ofs << rm.base[i] << std::endl;
        ofs << rm.center[1] << "\n#\n\n";
    }

    ofs << rm.center[0] << std::endl;
    ofs << rm.base[0] << std::endl;
    ofs << rm.center[1] << "\n#\n\n";

    return ofs;
}

void Pyramid::Write_to_file() const
{
    Pyramid temp = (*this);

    temp.Rotation(temp.orientation);
    temp.Translate(temp.position);

    std::ofstream Data_file;

    Data_file.open(File_path, std::ios::trunc);

    if (Data_file.is_open())
    {

        Data_file << temp;
    }
    else
    {
        throw std::invalid_argument("[Round Mountain]file opening error\n");
    }

    Data_file.close();
}

Pyramid Pyramid::Rotation(Matrix3x3 &rotation_matrix)
{
    for (int i = 0; i < 4; ++i)
    {
        base[i] = rotation_matrix * base[i];
    }
    center[0] = rotation_matrix * center[0];
    center[1] = rotation_matrix * center[1];

    return *this;
}

Pyramid Pyramid::Translate(Vector3D translation_vector)
{
    for (int i = 0; i < 4; ++i)
    {
        base[i] = translation_vector + base[i];
    }
    center[0] = translation_vector + center[0];
    center[1] = translation_vector + center[1];

    return *this;
}

std::string Pyramid::Get_file_path() const
{
    return std::string(File_path);
}

std::string Pyramid::Get_typeID() const
{
    return std::string(" Pyramid ID :" + std::to_string(ID));
}

bool Pyramid::Set_in_scene(double x, double y, double orientation_angle)
{
    Matrix3x3 t;
    set_Rotation_OZ(t, orientation_angle);

    Move(t, Vector3D({x, y, 0}));

    Write_to_file();

    return true;
}