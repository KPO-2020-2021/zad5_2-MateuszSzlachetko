#ifndef MATRIX3X3_H
#define MATRIX3X3_H

/** @file 
 *  @brief Specified Matrices
 *  
 * Typedef of Matrix3x3 and Matrix4x4
 * 
 * Functions for setting rotation matrix
 * and for it's combination from modification
*/

#include "Matrix.h"

typedef Matrix<double, 3> Matrix3x3;

/** @fn void set_Rotation_OX(Matrix3x3 &m, double angle);
 *  @brief Sets rotation matrix X
 * 
 * Using Euler formulas,and deg-rad calculation
 * (X axis)
 * @param m -matrix which will be manipulated
 * @param angle -rotation angle in degrees
 */
void set_Rotation_OX(Matrix3x3 &m, double angle);

/** @fn void set_Rotation_OY(Matrix3x3 &m, double angle);
 *  @brief Sets rotation matrix Y
 * 
 * Using Euler formulas,and deg-rad calculation
 * (Y axis)
 * @param m -matrix which will be manipulated
 * @param angle -rotation angle in degrees
 */
void set_Rotation_OY(Matrix3x3 &m, double angle);

/** @fn void set_Rotation_OZ(Matrix3x3 &m, double angle);
 *  @brief Sets rotation matrix Z
 * 
 * Using Euler formulas,and deg-rad calculation
 * (Z axis)
 * @param m -matrix which will be manipulated
 * @param angle -rotation angle in degrees
 */
void set_Rotation_OZ(Matrix3x3 &m, double angle);

#endif // MATRIX3X3_H