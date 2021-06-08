#ifndef DRONE_H
#define DRONE_H

/** @file
 */

#include "Rotor.h"
#include "Cuboid.h"
#include "lacze_do_gnuplota.hh"
#include <sys/stat.h>
#include <sys/types.h>

/** @class Drone
 * 
 * Class which represents a Drone.
 */
class Drone
{
private:
    Cuboid body;

    Rotor rotors[4];

    std::string directory = "../data/drone";

    static int id;

public:
    /** @fn  Drone()
    *   @brief Default constructor
    *   
    *   Each vertice is filled
    *   appropriate scaled value centered in global (0,0,0)
    */
    Drone();

    /** @fn  Drone(Cuboid b, Rotor r)
    *   @brief cuboid and rotor constructor
    *   
    *   Passed parameters are filled to drone's body and each rotor.It always brings the model to center
    *   applying init push to keep drone in passed position(virtually).
    */
    Drone(Cuboid b, Rotor r);

    /** @fn  Drone Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector)
    *   @brief Move drone in space
    *   
    *   Drone's components are moved in space,Rotors are extra rotated to perform their center rotation
    */
    Drone Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector);

    /** @fn  void Propeller_rotation()
    *   @brief Unit rotors
    *   
    *   Drone's rotors are rotated to imitate moving motors.Two of them are twisted 4 degrees to the left the
    *   other pair is twisted 4 degrees in the other direction
    */
    void Propeller_rotation();

    /** @fn  void Create_directory()
    *   @brief Drone's data
    *   
    *   It creates extra directory for drone's data,keeps workspace clean.
    */
    void Create_directory();

    /** @fn  void Add_files_names(PzG::LaczeDoGNUPlota &LLink)
    *   @brief Drone-gnuplot
    *   
    *   Adds drone's files to Gnuplot link
    */
    void Add_files_names(PzG::LaczeDoGNUPlota &Link);

    /** @fn  void Add_files_names(PzG::LaczeDoGNUPlota &Link, int colour)
    *   @brief Drone-gnuplot
    *   
    *   Adds drone's files to Gnuplot link,change colour according to
    *   passed value.
    */
    void Add_files_names(PzG::LaczeDoGNUPlota &Link, int colour);

    /** @fn  void Remove_files_names(PzG::LaczeDoGNUPlota &Link)
    *   @brief Drone-gnuplot
    *   
    *   Removes drones files from GNUplot link.
    */
    void Remove_files_names(PzG::LaczeDoGNUPlota &Link);

    /** @fn  Vector<double, 2> Position()
    *   @brief Returns drone's (x,y)
    *   
    *   Returns current drone's position (x,y value of the center)
    */
    Vector<double, 2> Position();

    /** @fn  Cuboid operator[](int index) const
    *   brief Returns drone's body
    */
    Cuboid operator[](int index) const;
};

#endif // DRONE_H