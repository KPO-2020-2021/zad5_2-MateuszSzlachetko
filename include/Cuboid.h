#ifndef CUBOID_H
#define CUBOID_H

/** @file
 */

#include "Figure.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include <fstream>
#include <iomanip>
#include <string>

constexpr unsigned int SIZE = 8;

/** @enum File_mode
 * 
 *  Enum for operating Write_to_file method
 *  
 *  2 modes for different efect
 */
enum File_mode
{
    Overwrite,
    Append
};

/** @class Cuboid
 * 
 * Class which represents a cuboid.
 */
class Cuboid : public Figure
{
private:
    Vector3D vertices[SIZE];

    Vector3D position;
    Matrix3x3 orientation;

public:
    /** @fn  Cuboid()
    *   @brief Default constructor
    *   
    *   Each vertice is filled
    *   with zeros (0).
    */
    Cuboid();

    /** @fn  Cuboid(double x1, double y1, double z1, double x2, double y2, double z2)
    *   @brief Oposite vertices constructor
    *   
    *   Passed parameters are representing first vertice,and a vertice oposing to it.
    */
    Cuboid(double x1, double y1, double z1, double x2, double y2, double z2);

    /** @fn  Cuboid(std::vector<Vector3D> &vectors)
    *   @brief Vector constructor
    *   
    *   Passed vectors are applied one by one to each vertice.
    * 
    *   The way in which they should be applied is specified on main page.
    */
    Cuboid(std::vector<Vector3D> &vectors);

    /** @fn  Cuboid Rotation(Matrix3x3 &rotation_matrix)
    *   @brief Rotation
    *   
    *   Each vertice is multiplied by
    *   @param rotation_matrix 
    *  
    *   which product is another vertice,rotated according to passed matrix.
    */
    Cuboid Rotation(Matrix3x3 &rotation_matrix);

    /** @fn  Cuboid Translate(Vector3D translation_vector)
    *   @brief Translation
    *   
    *   Each vertice is enlarged by
    *   @param translation_vector 
    *  
    *   Basic vector sum.
    */
    Cuboid Translate(Vector3D translation_vector);

    /** @fn  Cuboid Scale(double scalar)
    *   @brief Scale cuboid
    *   
    *   Each vertice is multiplied by passed
    *   @param scalar 
    * 
    *   Which leds to increase or decrease of it's size.
    */
    Cuboid Scale(double scalar);

    /** @fn  void Side_length() const
    *   @brief Check length of cuboid sides
    *   
    *   A lot of comparisons are made in order to find,
    *   long,short and vertical sides.
    * 
    *   Aftercalculating it,it displays length of specific sides.
    */
    void Side_length() const;

    /** @fn std::ostream &operator<<(std::ostream &os, const Cuboid &c)
    *   @brief Cuboid display
    *   
    *   Each vertice of Cuboid(which is actually a Vector)
    *   is outputed in a loop,vertice by vertice.With 10 dec. places precision.
    */
    friend std::ostream &operator<<(std::ostream &os, const Cuboid &c);

    /** @fn std::ofstream &operator<<(std::ofstream &ofs, const Cuboid &c)
    *   @brief Cuboid file display
    *   
    *   Each vertice of Cuboid(which is actually a Vector)
    *   is outputed in a loop,in a specific way for gnuplot.With 10 dec. places precision.
    */
    friend std::ofstream &operator<<(std::ofstream &ofs, const Cuboid &c);

    /** @fn bool operator==(const Cuboid &c1, const Cuboid &c2)
    *   @brief Cuboid comparison
    * 
    *  Every vertices from passed Cuboids are checked if they are equal.
    *  
    *  If yes
    *  @return true
    * 
    *  If no
    *  @return false
    */
    friend bool operator==(const Cuboid &c1, const Cuboid &c2);

    /** @fn void Write_to_file(std::string filename, File_mode mode) const
    *   @brief Write to file method
    *   
    *   After connecting to a file,depending on current mode it overwrites contents of the
    *   file or append it.It also makes sure if everything went right with opening file etc.
    *  
    */
    void Write_to_file(std::string filename, File_mode mode) const;

    /** @fn Vector3D operator[](int index) const
    *   @brief Cuboid index operator
    * 
    *   Array type of operator.Passing const object,only for reading.
    */
    Vector3D operator[](int index) const;

    /** @fn Vector3D &operator[](int index)
    *   @brief Cuboid index operator
    * 
    *   Array type of operator.Passing non-const object,for setting value of specific cell.
    */
    Vector3D &operator[](int index);

    /** @fn Cuboid Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector, std::string filename)
    *   @brief Move Cuboid in 3D
    * 
    *  Increse total rotation and position,and send current values to file (after applying reference model)
    */
    Cuboid Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector, std::string filename);

    /** @fn Cuboid Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector)
    *   @brief Move Cuboid in 3D
    * 
    *  Increse total rotation and position
    */
    Cuboid Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector);

    /** @fn Vector3D Get_position() const
    *   @brief Cuboid position (x,y,z)
    * 
    *  Returns current (total) position.
    */
    Vector3D Get_position() const;
};

#endif // CUBOID_H