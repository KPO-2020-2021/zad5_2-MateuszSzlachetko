#ifndef SCENE_H
#define SCENE_H

/** @file
 */

#include "Plateau.h"
#include "Drone.h"
#include <chrono>
#include <thread>
#include <list>
#include <memory>

/** @class Scene
 * 
 * Class which holds drones objects
 * and let's user operate on it.
 */
class Scene
{
private:
    Drone Drones[2];

    Drone *Active_drone;

    PzG::LaczeDoGNUPlota Link;

    std::list<std::shared_ptr<SceneObject>> Obstacles;

    std::string surface;

    void Draw_surface(int x_min, int x_max, int y_min, int y_max);

public:
    bool Add_obstacle();

    bool Remove_obstacle(int index);

    /** @fn  Scene()
    *   @brief Default constructor
    *   
    *   Set of surface,files handle,GNUplot link settings
    */
    Scene();

    /** @fn  bool Choose_drone(int index)
    *   @brief Drone chooser
    *   
    *   Set active drone pointer to specific drone,based
    *   on index.
    */
    bool Choose_drone(int index);

    /** @fn  void List_drones()
    *   List stored drones positions
    */
    void List_drones();

    /** @fn  void Draw()
    *   this link draw method
    */
    void Draw();

    /** @fn  void Draw_path(std::vector<Vector3D> total_path)
    *   @brief Draw path
    * 
    *   Draw active's drone path,previously calculated
    */
    void Draw_path(std::vector<Vector3D> total_path);

    /** @fn  bool Calculate_path(double angle, double length, std::vector<Vector3D> &total_path)
    *   @brief Calculate drone's path
    * 
    *   Calculate drone's path according to passed parameters
    * 
    *   Set rotation angle and scale rotated route vector with length
    */
    bool Calculate_path(double angle, double length, std::vector<Vector3D> &total_path);

    /** @fn  bool Animate(double angle, std::vector<Vector3D> &total_path)
    *   @brief Fly animation
    * 
    *   Animate drone's movement.Hard coded route,fly up,go forward land down.
    *   Everything across the route.
    */
    bool Animate(double angle, std::vector<Vector3D> &total_path);

    /** @fn  bool Round_route(double radius)
    *   @brief Round fly animation
    * 
    *   Animate drone's movement.Drone go up and forward across passed radius.
    *   Then rotates around it's previous center.
    *   After movement goes back to older position.
    * 
    *   MODIFICATION METHOD
    */
    bool Round_route(double radius);

    /** @fn  bool Change_colour(int colour)
    *   @brief Change active drone color
    * 
    *   GNUplot method which changes active drone's color according to
    *   passed value.
    * 
    *   EXTENSION
    */
    bool Change_colour(int colour);

    /** @fn  bool Add_drone(int drone_id, Drone drone)
    *   @brief Add drone to scene
    * 
    *   Takes passed drone and applies it to tab of drones
    *   according to passed index
    */
    bool Add_drone(int drone_id, Drone drone);

    /** @fn  bool Remove_drone(int drone_id)
    *   @brief Removes drone from scene
    * 
    *   Removes specified drone from scene(deletes its files)
    */
    bool Remove_drone(int drone_id);
};

#endif // SCENE_H