#ifndef FIGURE_H
#define FIGURE_H

/** @file 
 *  @brief Figure
 */

#include "Matrix3x3.h"
#include "Vector3D.h"
#include <string>

/** @class Figure
 *  General figure object class
 */
class Figure
{
private:
    std::string name;

public:
    /** @fn  Vector(std::string n)
    *   @brief string constructor
    *   
    *   name variable applied with passed string
    */
    Figure(std::string n);

    /** @fn  std::string Update_name(std::string &append)
    *   @brief name variable appender
    *   
    *   append current name value with passed string fragment
    */
    std::string Update_name(std::string append);

    /** @fn  std::string Update_name(std::string &append)
    *   @brief returns current name value 
    */
    std::string Get_name() const;
};

#endif // FIGURE_H