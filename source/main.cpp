#include <iostream>
#include "Scene.h"
#include "Drone.h"

void Display_menu();

int main()
{
    system("clear");

    // Plateau test(100, 50, 30);

    // PzG::LaczeDoGNUPlota Lacze;
    // Lacze.DodajNazwePliku(test.Get_file_path().c_str())
    //     .ZmienSposobRys(PzG::SR_Ciagly)
    //     .ZmienSzerokosc(2)
    //     .ZmienKolor(8);
    // Lacze.DodajNazwePliku(test.Get_file_path().c_str())
    //     .ZmienSposobRys(PzG::SR_Punktowy)
    //     .ZmienSzerokosc(1)
    //     .ZmienKolor(5);
    // Lacze.Inicjalizuj();
    // Lacze.ZmienTrybRys(PzG::TR_3D);
    // Lacze.UstawZakresX(-200, 200);
    // Lacze.UstawZakresY(-200, 200);
    // Lacze.UstawZakresZ(-100, 120);
    // Lacze.UstawRotacjeXZ(64, 65);

    // Lacze.Rysuj();
    // std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));

    // test.Set_in_scene(50, 50, 25);

    // Lacze.Rysuj();
    //std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
    {
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

            if (option != 'a' && option != 'c' && option != 'r' && option != 'm' && option != 'q' && option != 'd' && option != 'l')
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
            case 'a':
                scene_3D.Add_obstacle();
                break;
            default:
                break;
            }
        } while (option != 'q');
    }

    std::cout << Vector<double, 3>::Get_total() << std::endl;
    std::cout << Vector<double, 3>::Get_Actual() << std::endl;
}

void Display_menu()
{
    std::cout << "\n c-choose drone" << std::endl;
    std::cout << " r-insert route" << std::endl;
    std::cout << " d-change active drone colour" << std::endl;
    std::cout << " l-round route from modification" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << " a-add obstacle" << std::endl;
    std::cout << " m-show menu" << std::endl
              << std::endl;
    std::cout << " q-quit" << std::endl;
}