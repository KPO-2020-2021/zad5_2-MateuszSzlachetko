#ifndef Rotor_H
#define Rotor_H

#include "Figure.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include <fstream>
#include <iomanip>

class Rotor : public Figure
{
private:
    Vector3D vertices[12];

    Vector3D center[2];

    Vector3D position;
    Matrix3x3 orientation;

public:
    /** @fn  Rotor()
    *   @brief Default constructor
    *   
    *   Each vertice is filled
    *   with values from example rotor file.
    */
    Rotor();

    /** @fn  Rotor(double x, double y, double z, double a, double b, double c)
    *   @brief Double constructor
    *   
    *   Whole rotor is made from passed values,further explanation in body.
    *   Easily extendable to diffrent figures.
    */
    Rotor(double x, double y, double z, double a, double b, double c);

    /** @fn  Rotor Rotation(Matrix3x3 &rotation_matrix)
    *   @brief Rotation
    *   
    *   Each vertice is multiplied by
    *   @param rotation_matrix 
    *  
    *   which product is another vertice,rotated according to passed matrix.
    */
    Rotor Rotation(Matrix3x3 &rotation_matrix);

    /** @fn  Rotor Translate(Vector3D translation_vector)
    *   @brief Translation
    *   
    *   Each vertice is enlarged by
    *   @param translation_vector 
    *  
    *   Basic vector sum.
    */
    Rotor Translate(Vector3D translation_vector);

    /** @fn Rotor Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector, std::string filename)
    *   @brief Move Rotor in 3D
    * 
    *  Increse total rotation and position,and send current values to file (after applying reference model)
    */
    Rotor Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector, std::string filename);

    /** @fn Rotor Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector)
    *   @brief Move Rotor in 3D
    * 
    *  Increse total rotation and position
    */
    Rotor Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector);

    /** @fn std::ofstream &operator<<(std::ofstream &ofs, const Rotor &r)
    *   @brief Filestream operator
    * 
    *  Send rotor in specific sequence to file
    *  For gnuplot drawing
    */
    friend std::ofstream &operator<<(std::ofstream &ofs, const Rotor &r);

    /** @fn bool operator==(const Rotor &r1, const Rotor &r2)
    *   @brief Rotor comparison
    * 
    *  Every vertices from passed Rotors are checked if they are equal.
    *  
    *  If yes
    *  @return true
    * 
    *  If no
    *  @return false
    */
    friend bool operator==(const Rotor &r1, const Rotor &r2);

    /** @fn Vector3D operator[](int index) const
    *   @brief Rotor index operator
    * 
    *   Array type of operator.Passing const object,only for reading.
    */
    Vector3D operator[](int index) const;

    /** @fn void Write_to_file(std::string filename, File_mode mode) const
    *   @brief Write to file method
    *   
    *   After connecting to a file,it overwrites contents of the file.
    *   It also makes sure if everything went right with opening file etc.
    *  
    */
    void Write_to_file(std::string filename) const;
};

#endif // Rotor_H