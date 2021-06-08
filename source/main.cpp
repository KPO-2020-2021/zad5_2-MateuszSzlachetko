#include <iostream>
#include "Scene.h"
#include "Drone.h"

void Display_menu();

int main()
{
    system("clear");
    std::cout << "TEST" << std::endl;

    Scene scene_3D;

    char option = ' ';
    int i = 0, o = 0;
    int current_drone = -1;
    int colour = 1;
    double radius = 0;
    double angle = 0;
    double length = 0;
    std::vector<Vector3D> total_path;

    scene_3D.Add_drone(0, Drone());
    scene_3D.Add_drone(1, Drone(Cuboid({150, 150, 0, 200, 180, 20}), Rotor({10, 0, 0, 5, 8.66, 10})));
    scene_3D.Draw();
    Display_menu();
    do
    {
        std::cout << "Choice (m-menu):\t";
        std::cin >> option;
        //system("clear");

        if (option != 'c' && option != 'r' && option != 'm' && option != 'q' && option != 'd' && option != 'l')
        {
            std::cerr << "[ERROR] Invalid menu argument" << std::endl;
            option = ' ';
        }

        switch (option)
        {
        case 'm':
            Display_menu();
            break;
        case 'c':
            std::cout << "Choose drone 0-1" << std::endl;
            scene_3D.List_drones();

            std::cin >> option;
            if (option != '0' && option != '1')
            {
                std::cerr << "[ERROR] Invalid drone choice" << std::endl;
                option = ' ';
                break;
            }
            scene_3D.Choose_drone((int)option - 48);
            break;
        case 'r':
            std::cout << "Insert direction (angle in degrees)" << std::endl;
            std::cin >> angle;
            std::cout << "Insert length" << std::endl;
            std::cin >> length;
            if (scene_3D.Calculate_path(angle, length, total_path))
                scene_3D.Animate(angle, total_path);
            break;
        case 'd':
            std::cout << "Insert colour" << std::endl;
            std::cin >> colour;
            if (std::cin.fail())
            {
                throw std::invalid_argument("Wrong colour passed");
            }
            scene_3D.Change_colour(colour);
            break;
        case 'l':
            std::cout << "Insert radius" << std::endl;
            std::cin >> radius;
            if (std::cin.fail())
            {
                throw std::invalid_argument("Wrong radius passed");
            }
            scene_3D.Round_route(radius);
            break;
        default:
            break;
        }
    } while (option != 'q');

    std::cout << Vector<double, 3>::Get_total() << std::endl;
    std::cout << Vector<double, 3>::Get_Actual() << std::endl;
}

void Display_menu()
{
    std::cout << "\n c-choose drone" << std::endl;
    std::cout << " r-insert route" << std::endl;
    std::cout << " d-change active drone colour" << std::endl;
    std::cout << " l-round route from modification" << std::endl;
    std::cout << " m-show menu" << std::endl
              << std::endl;
    std::cout << " q-quit" << std::endl;
}