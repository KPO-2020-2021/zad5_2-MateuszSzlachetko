#include "RoundMountain.h"

RoundMountain::RoundMountain(double radius, double height)
{
    center[0] = Vector3D({0, 0, 0});
    center[1] = Vector3D({0, 0, height});

    Vector3D init({radius, 0, 0});
    Matrix3x3 m;
    double angle = 0;
    //set_Rotation_OZ(m, angle);

    for (int i = 0; i < 18; ++i)
    {
        set_Rotation_OZ(m, angle);
        init = m * Vector3D({radius, 0, 0});
        base[i] = init;
        angle += 20;
    }

    ID = Get_total();

    File_path = "../data/RMountain" + std::to_string(ID) + ".dat";

    Write_to_file();
}

std::ofstream &operator<<(std::ofstream &ofs, const RoundMountain &rm)
{
    ofs << std::setprecision(10) << std::fixed;

    for (int i = 0; i < 18; ++i)
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

void RoundMountain::Write_to_file() const
{
    RoundMountain temp = (*this);

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

RoundMountain RoundMountain::Rotation(Matrix3x3 &rotation_matrix)
{
    for (int i = 0; i < 18; ++i)
    {
        base[i] = rotation_matrix * base[i];
    }
    center[0] = rotation_matrix * center[0];
    center[1] = rotation_matrix * center[1];

    return *this;
}

RoundMountain RoundMountain::Translate(Vector3D translation_vector)
{
    for (int i = 0; i < 18; ++i)
    {
        base[i] = translation_vector + base[i];
    }
    center[0] = translation_vector + center[0];
    center[1] = translation_vector + center[1];

    return *this;
}

std::string RoundMountain::Get_file_path() const
{
    return std::string(File_path);
}

std::string RoundMountain::Get_typeID() const
{
    return std::string(" Round Mountain ID :" + std::to_string(ID));
}

bool RoundMountain::Set_in_scene(double x, double y)
{
    Matrix3x3 t{1, 0, 0, 0, 1, 0, 0, 0, 1};

    Move(t, Vector3D({x, y, 0}));

    Write_to_file();

    return true;
}