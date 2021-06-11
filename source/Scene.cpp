#include "Scene.h"

Scene::Scene()
{
    surface = "../data/surface.dat";
    Draw_surface(-50, 350, -50, 350);

    Active_drone = NULL;

    Link.Inicjalizuj();
    Link.ZmienTrybRys(PzG::TR_3D);

    Link.UstawZakresX(-50, 350);
    Link.UstawZakresY(-50, 350);
    Link.UstawZakresZ(-50, 150);
    Link.UstawRotacjeXZ(64, 65);

    Link.DodajNazwePliku(surface.c_str());

    Link.Rysuj();
}

Scene::~Scene()
{
    if (!Obstacles.empty())
    {
        std::list<std::shared_ptr<SceneObject>>::iterator i;

        i = Obstacles.begin();

        for (int j = 0; j < Obstacles.size(); j++, i++)
        {
            std::cout << "Deleting " << (*i)->Get_file_path() << std::endl;
            (*i)->Remove_files_names(Link);
        }
    }

    remove(surface.c_str());
}

void Scene::Draw_surface(int x_min, int x_max, int y_min, int y_max)
{
    std::ofstream Data_file;

    // init default value for actual x and y
    double x_actual = x_min, y_acutal = y_min;

    // calculate how many times it should be printed (depending on grid size)
    int x_times = (x_max - x_min) / 20;
    int y_times = (y_max - y_min) / 20;

    Data_file.open(surface, std::ios::trunc);

    if (Data_file.is_open())
    {
        for (int i = 0; i <= y_times; ++i)
        {
            for (int j = 0; j <= x_times; ++j)
            {
                Data_file << Vector3D({x_actual, y_acutal, 0}) << std::endl;
                x_actual += 20; // enlarge element with grid size
            }
            Data_file << std::endl;

            x_actual = x_min; // reset x to default
            y_acutal += 20;   // enlarge element with grid size
        }
    }
    else
    {
        throw std::invalid_argument("[Surface]file opening error\n");
    }

    Data_file.close();
}

bool Scene::Add_drone(int drone_id, Drone drone)
{
    if (drone_id < 0 || drone_id > 1) // amount of drones
        return false;

    Drones[drone_id] = drone;
    Drones[drone_id].Add_files_names(Link);

    return true;
}

bool Scene::Remove_drone(int drone_id)
{
    if (drone_id < 0 || drone_id > 1) // amount of drones
        return false;

    Drones[drone_id].Remove_files_names(Link);

    return true;
}

void Scene::List_drones()
{
    std::cout << "0 - Position (x,y) " << Drones[0].Position() << std::endl; // pass x,y values
    std::cout << "1 - Position (x,y) " << Drones[1].Position() << std::endl;
}

void Scene::Draw()
{
    Link.Rysuj();
}

bool Scene::Choose_drone(int index)
{
    if (index < 0 || index > 1) // amount of drones
        return false;

    Active_drone = &Drones[index];
    return true;
}

bool Scene::Calculate_path(double angle, double length, std::vector<Vector3D> &total_path)
{
    if (Active_drone == NULL)
    {
        std::cerr << "No active drone chosen" << std::endl;
        return false;
    }
    Matrix3x3 r;
    set_Rotation_OZ(r, angle);

    Vector3D height({0, 0, 100}); // Move drone into the air
    Vector3D route({length, 0, 0});

    route = r * route; // move route in space

    total_path.push_back(height);
    total_path.push_back(route);
    total_path.push_back(height * (-1)); // x,y are 0 so only height will be decreased

    Draw_path(total_path);

    return true;
}

void Scene::Draw_path(std::vector<Vector3D> total_path)
{
    std::ofstream Data_file;
    Vector3D pos;
    // pass x,y value of active drone
    pos[0] = (Active_drone->Position())[0];
    pos[1] = (Active_drone->Position())[1];

    Data_file.open("../data/path.dat", std::ios::trunc);

    if (Data_file.is_open())
    {
        Data_file << pos << std::endl;

        Data_file << pos + total_path[0] << std::endl;

        Data_file << pos + total_path[0] + total_path[1] << std::endl;

        Data_file << pos + total_path[0] + total_path[1] + total_path[2] << std::endl;
    }
    else
    {
        throw std::invalid_argument("[Surface]file opening error\n");
    }
    Link.DodajNazwePliku("../data/path.dat");
    Draw();

    Data_file.close();
}

bool Scene::Animate(double angle, std::vector<Vector3D> &total_path)
{
    Vector3D Vertical_flight, Horizontal_flight;
    int i = 0, frames = 60;

    Matrix3x3 rot{1, 0, 0,
                  0, 1, 0,
                  0, 0, 1};
    Matrix3x3 rot2;

    Vertical_flight = total_path[0];
    total_path.erase(total_path.begin());

    Vertical_flight = Vertical_flight / 120; // 120 parts | height passed in parts/frames seconds

    while (i < 120) // go up
    {
        Active_drone->Move(rot, Vertical_flight);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / frames));
        Draw();
        i++;
    }
    i = 0;

    if (angle < 0)
        set_Rotation_OZ(rot2, -1);
    else
        set_Rotation_OZ(rot2, 1);
    while (i < std::abs(angle)) // Rotate
    {
        Active_drone->Move(rot2, Vector3D());
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / frames));
        Draw();
        i++;
    }
    i = 0;

    Horizontal_flight = total_path[0];
    total_path.erase(total_path.begin());
    Horizontal_flight = Horizontal_flight / 120;

    while (i < 120) // go forward
    {
        Active_drone->Move(rot, Horizontal_flight);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / frames));
        Draw();
        i++;
    }
    i = 0;

    if (angle < 0)
        set_Rotation_OZ(rot2, 1);
    else
        set_Rotation_OZ(rot2, -1);
    while (i < std::abs(angle)) // Rotate backward
    {
        Active_drone->Move(rot2, Vector3D());
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / frames));
        Draw();
        i++;
    }
    i = 0;

    Vertical_flight = total_path[0];
    total_path.erase(total_path.begin());

    Vertical_flight = Vertical_flight / 120;

    while (i < 120) // go down
    {
        Active_drone->Move(rot, Vertical_flight);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / frames));
        Draw();
        i++;
    }
    i = 0;

    std::this_thread::sleep_for(std::chrono::nanoseconds(500000000));
    Link.UsunNazwePliku("../data/path.dat");
    Draw();
    return true;
}

bool Scene::Change_colour(int colour)
{
    if (Active_drone == NULL)
    {
        std::cerr << "No active drone chosen" << std::endl;
        return false;
    }

    if (Active_drone == &Drones[0])
    {
        Drones[0].Remove_files_names(Link);
        Drones[0].Add_files_names(Link, colour);
    }

    if (Active_drone == &Drones[1])
    {
        Drones[1].Remove_files_names(Link);
        Drones[1].Add_files_names(Link, colour);
    }

    Draw();

    return true;
}

bool Scene::Round_route(double radius)
{
    if (Active_drone == NULL)
    {
        std::cerr << "No active drone chosen" << std::endl;
        return false;
    }
    Matrix3x3 rot{1, 0, 0,
                  0, 1, 0,
                  0, 0, 1};

    Matrix3x3 rot1{1, 0, 0,
                   0, 1, 0,
                   0, 0, 1};

    Vector3D Radius({radius, 0, 0});

    Vector3D init({Radius[0] / 120, 0, 0.8333});

    for (int i = 0; i < 120; ++i) // put into orbit
    {
        Active_drone->Move(rot, init);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 60));
        Draw();
    }

    Active_drone->Move(rot, Radius * (-1)); // Move drone to the center
    set_Rotation_OZ(rot1, 1);

    for (int i = 0; i < 360; ++i)
    {
        Active_drone->Move(rot1, Radius); // Move to orbit,rotate
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 90));
        Draw();
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 90));
        Active_drone->Move(rot, Radius * (-1)); // Move drone to the center
        Radius = rot1 * Radius;                 // rotate the radius
    }
    Active_drone->Move(rot, Radius); // Move to orbit

    for (int i = 0; i < 120; ++i) // Get drone back
    {
        Active_drone->Move(rot, init * (-1));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 60));
        Draw();
    }

    return true;
}

bool Scene::Add_obstacle()
{
    std::cout << "Choose object type" << std::endl;
    std::cout << "1.\t Plateau" << std::endl;
    std::cout << "2.\t Round Mountain" << std::endl;
    std::cout << "3.\t Pyramid" << std::endl;
    std::cout << std::endl;

    int Object_type = 0;

    std::cin >> Object_type;

    if ((Object_type != 1 && Object_type != 2 && Object_type != 3) || std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cerr << "Invalid object type" << std::endl;
        return false;
    }
    double Radius, Length, Width, Height, Side_Length;
    int colour;
    double x, y, orientation_angle;

    if (Object_type == 1)
    {

        std::cout << "Insert init values" << std::endl;
        std::cout << "\t Length: ";
        std::cin >> Length;
        std::cout << "\t Width: ";
        std::cin >> Width;
        std::cout << "\t Height: ";
        std::cin >> Height;
        std::cout << "\t Colour: ";
        std::cin >> colour;
        std::cout << std::endl;

        if ((Length <= 0 || Width <= 0 || Height <= 0) || std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cerr << "Invalid init parameters" << std::endl;
            return false;
        }

        std::cout << "Insert init position" << std::endl;
        std::cout << "\t X- coordinate: ";
        std::cin >> x;
        std::cout << "\t Y- coordinate: ";
        std::cin >> y;
        std::cout << "\t Orientation angle: ";
        std::cin >> orientation_angle;
        std::cout << std::endl;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    if (Object_type == 2)
    {
        std::cout << "Insert init values" << std::endl;
        std::cout << "\t Radius: ";
        std::cin >> Radius;
        std::cout << "\t Height: ";
        std::cin >> Height;
        std::cout << "\t Colour: ";
        std::cin >> colour;
        std::cout << std::endl;

        if ((Radius <= 0 || Height <= 0) || std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cerr << "Invalid init parameters" << std::endl;
            return false;
        }

        std::cout << "Insert init position" << std::endl;
        std::cout << "\t X- coordinate: ";
        std::cin >> x;
        std::cout << "\t Y- coordinate: ";
        std::cin >> y;
        std::cout << std::endl;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    if (Object_type == 3)
    {
        std::cout << "Insert init values" << std::endl;
        std::cout << "\t Side length: ";
        std::cin >> Side_Length;
        std::cout << "\t Height: ";
        std::cin >> Height;
        std::cout << "\t Colour: ";
        std::cin >> colour;
        std::cout << std::endl;

        if ((Side_Length <= 0 || Height <= 0) || std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cerr << "Invalid init parameters" << std::endl;
            return false;
        }

        std::cout << "Insert init position" << std::endl;
        std::cout << "\t X- coordinate: ";
        std::cin >> x;
        std::cout << "\t Y- coordinate: ";
        std::cin >> y;
        std::cout << "\t Orientation angle: ";
        std::cin >> orientation_angle;
        std::cout << std::endl;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    switch (Object_type)
    {
    case 1:
    {
        Plateau plateau(Length, Width, Height);
        plateau.Set_in_scene(x, y, orientation_angle);

        Obstacles.push_back(std::make_shared<Plateau>(plateau));

        std::list<std::shared_ptr<SceneObject>>::iterator i;
        i = Obstacles.end();
        --i;
        (*i)->Add_files_names(Link, colour);
        break;
    }
    case 2:
    {
        RoundMountain rm(Radius, Height);
        rm.Set_in_scene(x, y);

        Obstacles.push_back(std::make_shared<RoundMountain>(rm));

        std::list<std::shared_ptr<SceneObject>>::iterator i;
        i = Obstacles.end();
        --i;
        (*i)->Add_files_names(Link, colour);
        break;
    }
    case 3:
    {
        Pyramid p(Side_Length, Height);
        p.Set_in_scene(x, y, orientation_angle);

        Obstacles.push_back(std::make_shared<Pyramid>(p));

        std::list<std::shared_ptr<SceneObject>>::iterator i;
        i = Obstacles.end();
        --i;
        (*i)->Add_files_names(Link, colour);
        break;
    }
    default:
        break;
    }

    Draw();
    return true;
}

bool Scene::Remove_obstacle(int index)
{
    if (index < 0 || index > Obstacles.size() - 1)
    {
        std::cerr << "Index out of range" << std::endl;
        return false;
    }

    if (Obstacles.empty())
    {
        std::cerr << "Obstacles list is empty,no element to delete" << std::endl;
        return false;
    }

    std::list<std::shared_ptr<SceneObject>>::iterator i;

    i = Obstacles.begin();

    for (int j = 0; j < index; i++, j++)
        ;

    (*i)->Remove_files_names(Link);
    Obstacles.remove(*i);

    Draw();

    return true;
}

bool Scene::Print_list_of_obstacles()
{
    if (Obstacles.empty())
    {
        std::cerr << "Obstacles list is empty,no elements to print" << std::endl;
        return false;
    }
    std::list<std::shared_ptr<SceneObject>>::iterator i;

    i = Obstacles.begin();

    std::cout << std::endl;

    for (int j = 0; j < Obstacles.size(); i++, j++)
    {
        std::cout << " " << j << ". " << (*i)->Get_typeID() << " (" << (*i)->Get_position() << " )" << std::endl;
    }

    return true;
}