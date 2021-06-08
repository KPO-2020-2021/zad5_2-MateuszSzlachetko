#include "Rotor.h"

Rotor::Rotor() : Figure("rotor")
{
    // Default values from example drone project

    vertices[0] = Vector3D({5, 0, -5});
    vertices[1] = Vector3D({5, 0, 5});
    vertices[2] = Vector3D({2.5, 4.33, -5});
    vertices[3] = Vector3D({2.5, 4.33, 5});
    vertices[4] = Vector3D({-2.5, 4.33, -5});
    vertices[5] = Vector3D({-2.5, 4.33, 5});
    vertices[6] = Vector3D({-5, 0, -5});
    vertices[7] = Vector3D({-5, 0, 5});
    vertices[8] = Vector3D({-2.5, -4.33, -5});
    vertices[9] = Vector3D({-2.5, -4.33, 5});
    vertices[10] = Vector3D({2.5, -4.33, -5});
    vertices[11] = Vector3D({2.5, -4.33, 5});

    center[0] = (vertices[0] + vertices[7]) / 2;
    center[1] = (vertices[0] + vertices[7]) / 2;

    position = Vector3D();

    orientation = Matrix3x3({1, 0, 0,
                             0, 1, 0,
                             0, 0, 1});
}

Rotor::Rotor(double x, double y, double z, double a, double b, double c) : Figure("rotor")
{
    // x value on x axis,   a- value on x axis for rotor corner b-value on y axis for rotor corner
    // z,c values on z axis-height
    // everything needed for saving rotor for gnuplot;

    vertices[0] = Vector3D({x, y, z});
    vertices[1] = Vector3D({x, y, c});
    vertices[2] = Vector3D({a, b, z});
    vertices[3] = Vector3D({a, b, c});
    vertices[4] = Vector3D({-a, b, z});
    vertices[5] = Vector3D({-a, b, c});
    vertices[6] = Vector3D({-x, y, z});
    vertices[7] = Vector3D({-x, y, c});
    vertices[8] = Vector3D({-a, -b, z});
    vertices[9] = Vector3D({-a, -b, c});
    vertices[10] = Vector3D({a, -b, z});
    vertices[11] = Vector3D({a, -b, c});

    center[0] = (vertices[0] + vertices[7]) / 2;
    center[1] = (vertices[0] + vertices[7]) / 2;

    // przy odwrotnej kolejności rotor jest lekko zapadnięty i lepiej to wygląda.
    center[0][2] = z;
    center[1][2] = c;

    position = Vector3D();

    orientation = Matrix3x3({1, 0, 0,
                             0, 1, 0,
                             0, 0, 1});
}

std::ofstream &operator<<(std::ofstream &ofs, const Rotor &r)
{
    ofs << std::setprecision(10) << std::fixed;

    ofs << r.center[0] << std::endl;
    ofs << r.vertices[0] << std::endl;
    ofs << r.vertices[1] << std::endl;
    ofs << r.center[1] << "\n#\n\n";

    ofs << r.center[0] << std::endl;
    ofs << r.vertices[2] << std::endl;
    ofs << r.vertices[3] << std::endl;
    ofs << r.center[1] << "\n#\n\n";

    ofs << r.center[0] << std::endl;
    ofs << r.vertices[4] << std::endl;
    ofs << r.vertices[5] << std::endl;
    ofs << r.center[1] << "\n#\n\n";

    ofs << r.center[0] << std::endl;
    ofs << r.vertices[6] << std::endl;
    ofs << r.vertices[7] << std::endl;
    ofs << r.center[1] << "\n#\n\n";

    ofs << r.center[0] << std::endl;
    ofs << r.vertices[8] << std::endl;
    ofs << r.vertices[9] << std::endl;
    ofs << r.center[1] << "\n#\n\n";

    ofs << r.center[0] << std::endl;
    ofs << r.vertices[10] << std::endl;
    ofs << r.vertices[11] << std::endl;
    ofs << r.center[1] << "\n#\n\n";

    ofs << r.center[0] << std::endl;
    ofs << r.vertices[0] << std::endl;
    ofs << r.vertices[1] << std::endl;
    ofs << r.center[1] << "\n#\n\n";

    return ofs;
}

void Rotor::Write_to_file(std::string filename) const
{
    // Apply reference model
    Rotor temp = (*this);

    temp.Rotation(temp.orientation);
    temp.Translate(temp.position);

    std::ofstream Data_file;

    Data_file.open(filename, std::ios::trunc);

    if (Data_file.is_open())
    {

        Data_file << temp;
    }
    else
    {
        throw std::invalid_argument("[Rotor]file opening error\n");
    }

    Data_file.close();
}

Rotor Rotor::Rotation(Matrix3x3 &rotation_matrix)
{
    for (int i = 0; i < 12; ++i)
    {
        vertices[i] = rotation_matrix * vertices[i];
    }
    center[0] = rotation_matrix * center[0];
    center[1] = rotation_matrix * center[1];

    return *this;
}

Rotor Rotor::Translate(Vector3D translation_vector)
{
    for (int i = 0; i < 12; ++i)
    {
        vertices[i] = translation_vector + vertices[i];
    }
    center[0] = translation_vector + center[0];
    center[1] = translation_vector + center[1];

    return *this;
}

Rotor Rotor::Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector, std::string filename)
{
    // update total position
    this->orientation = rotation_matrix * orientation;
    this->position = position + translation_vector;

    // Send position to the file
    (*this).Write_to_file(filename);

    return *this;
}

Rotor Rotor::Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector)
{
    // update total position
    this->orientation = rotation_matrix * orientation;
    this->position = position + translation_vector;

    return *this;
}

bool operator==(const Rotor &r1, const Rotor &r2)
{
    for (int i = 0; i < 12; ++i)
    {
        if (!(r1.vertices[i] == r2.vertices[i]))
            return false;
    }

    if (!(r1.center[0] == r2.center[0]))
        return false;

    if (!(r1.center[1] == r2.center[1]))
        return false;

    return true;
}

Vector3D Rotor::operator[](int index) const
{
    if (index < 0 || index > 11)
        throw std::invalid_argument("Index out of range");
    else
    {
        return vertices[index]; // return copy,which let's us only to read the value
    }
}