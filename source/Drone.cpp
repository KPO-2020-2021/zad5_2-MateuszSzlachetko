#include "Drone.h"

int Drone::id = 0;

void Drone::Create_directory()
{
    // Create specific directory for current drone
    directory.append(std::to_string(id + 1));
    directory.append("/");

    // make directory c_str == const char * from string | Values for permissions
    mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    id++;
}

Drone::Drone()
{
    Create_directory();

    Matrix3x3 base({1, 0, 0,
                    0, 1, 0,
                    0, 0, 1});

    Vector3D init_body_height({0, 0, 0});

    body = Cuboid(-15, -15, 0, 15, 15, 30);

    body.Move(base, Vector3D(), directory + body.Get_name());

    std::string appender;
    for (int i = 0; i < 4; ++i)
    {
        rotors[i] = Rotor({10, 0, 0, 5, 8.66, 10});

        // Update rotor file name
        appender.append(std::to_string(i + 1));
        appender.append(".dat");
        rotors[i].Update_name(appender);

        // reset appender
        appender = std::string();
    }
    // Move rotors to body corners

    rotors[0].Translate(body[7]);
    rotors[1].Translate(body[5]);
    rotors[2].Translate(body[6]);
    rotors[3].Translate(body[4]);

    // Save rotors positions
    rotors[0].Write_to_file(directory + rotors[0].Get_name());
    rotors[1].Write_to_file(directory + rotors[1].Get_name());
    rotors[2].Write_to_file(directory + rotors[2].Get_name());
    rotors[3].Write_to_file(directory + rotors[3].Get_name());
}

Drone::Drone(Cuboid b, Rotor r)
{
    Create_directory();

    Matrix3x3 base({1, 0, 0,
                    0, 1, 0,
                    0, 0, 1});

    Vector3D init_push;

    body = b;

    Vector<double, 2> position = Position();

    if (position[0] != 0 && position[1] != 0 && body[0][2] != 0)
        init_push = Vector3D({-position[0], -position[1], ((-1) * body[0][2])});
    else if (position[0] != 0 && position[1] != 0)
        init_push = Vector3D({-position[0], -position[1], 0});

    body.Translate(init_push);

    body.Move(base, Vector3D(), directory + body.Get_name());

    std::string appender;
    for (int i = 0; i < 4; ++i)
    {
        rotors[i] = r;

        // Update rotor file name
        appender.append(std::to_string(i + 1));
        appender.append(".dat");
        rotors[i].Update_name(appender);

        // reset appender
        appender = std::string();
    }
    // Move rotors to body corners

    rotors[0].Translate(body[7]);
    rotors[1].Translate(body[5]);
    rotors[2].Translate(body[6]);
    rotors[3].Translate(body[4]);

    // Save rotors positions
    rotors[0].Write_to_file(directory + rotors[0].Get_name());
    rotors[1].Write_to_file(directory + rotors[1].Get_name());
    rotors[2].Write_to_file(directory + rotors[2].Get_name());
    rotors[3].Write_to_file(directory + rotors[3].Get_name());

    // To set drone if needed to the starting position
    Move(base, Vector3D({position[0], position[1], 0}));
}

void Drone::Add_files_names(PzG::LaczeDoGNUPlota &Link)
{
    // whole line for drone's body converted to char *
    Link.DodajNazwePliku((directory + body.Get_name()).c_str())
        .ZmienSposobRys(PzG::SR_Ciagly)
        .ZmienSzerokosc(2)
        .ZmienKolor(8);

    // whole line for drone's rotor converted to char *
    for (int i = 0; i < 4; ++i)
    {
        Link.DodajNazwePliku((directory + rotors[i].Get_name()).c_str())
            .ZmienSposobRys(PzG::SR_Ciagly)
            .ZmienSzerokosc(2)
            .ZmienKolor(8);
    }
}

void Drone::Add_files_names(PzG::LaczeDoGNUPlota &Link, int colour)
{
    // whole line for drone's body converted to char *
    Link.DodajNazwePliku((directory + body.Get_name()).c_str())
        .ZmienSposobRys(PzG::SR_Ciagly)
        .ZmienSzerokosc(2)
        .ZmienKolor(colour);

    // whole line for drone's rotor converted to char *
    for (int i = 0; i < 4; ++i)
    {
        Link.DodajNazwePliku((directory + rotors[i].Get_name()).c_str())
            .ZmienSposobRys(PzG::SR_Ciagly)
            .ZmienSzerokosc(2)
            .ZmienKolor(colour);
    }
}

void Drone::Remove_files_names(PzG::LaczeDoGNUPlota &Link)
{
    // whole line for drone's body converted to char *
    Link.UsunNazwePliku((directory + body.Get_name()).c_str());

    // whole line for drone's rotor converted to char *
    for (int i = 0; i < 4; ++i)
    {
        Link.UsunNazwePliku((directory + rotors[i].Get_name()).c_str());
    }
}

Drone Drone::Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector)
{
    Propeller_rotation();

    // Move drone in space

    body.Move(rotation_matrix, translation_vector, directory + body.Get_name());

    rotors[0].Move(rotation_matrix, translation_vector, directory + rotors[0].Get_name());
    rotors[1].Move(rotation_matrix, translation_vector, directory + rotors[1].Get_name());
    rotors[2].Move(rotation_matrix, translation_vector, directory + rotors[2].Get_name());
    rotors[3].Move(rotation_matrix, translation_vector, directory + rotors[3].Get_name());

    return *this;
}

void Drone::Propeller_rotation()
{
    // This method does not destroy object even though it is modified
    // it is possible to do it without changing it at all but it is worthless

    Matrix3x3 rotors_right, rotors_left;

    set_Rotation_OZ(rotors_left, 4);
    set_Rotation_OZ(rotors_right, -4);

    // Move to default
    rotors[0].Translate((body[7]) * (-1));
    rotors[1].Translate((body[5]) * (-1));
    rotors[2].Translate((body[6]) * (-1));
    rotors[3].Translate((body[4]) * (-1));

    //  2   3   |   direction
    //  0   1   v
    // Rotate in default
    rotors[0].Rotation(rotors_left);
    rotors[1].Rotation(rotors_right);
    rotors[2].Rotation(rotors_right);
    rotors[3].Rotation(rotors_left);

    // Move back
    rotors[0].Translate(body[7]);
    rotors[1].Translate(body[5]);
    rotors[2].Translate(body[6]);
    rotors[3].Translate(body[4]);
}

Cuboid Drone::operator[](int index) const
{
    if (index != 0)
        throw std::invalid_argument("Index out of range");
    else
    {
        return body; // return copy,which let's us only to read the value
    }
}

Vector<double, 2> Drone::Position()
{
    Vector<double, 2> center, temp1, temp2;

    temp1[0] = body[0][0] + (body.Get_position())[0]; // model + total position (x)
    temp1[1] = body[0][1] + (body.Get_position())[1]; // model + total position (y)

    temp2[0] = body[3][0] + (body.Get_position())[0];
    temp2[1] = body[3][1] + (body.Get_position())[1];

    // two points in total position
    center = (temp1 + temp2) / 2;

    return center;
}