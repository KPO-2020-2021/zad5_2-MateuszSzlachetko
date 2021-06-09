#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <cstdio>
#include "Vector3D.h"
#include "Matrix3x3.h"
#include "lacze_do_gnuplota.hh"

class SceneObject
{
private:
    static int Total_scene_objects;

protected:
    std::string File_path;

    Vector3D position;
    Matrix3x3 orientation;

    int ID;

public:
    SceneObject();

    bool Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector);

    virtual void Write_to_file() const;

    virtual std::string Get_typeID() const;

    virtual Vector3D Get_position() const;

    virtual std::string Get_file_path() const;

    bool Add_files_names(PzG::LaczeDoGNUPlota &Link, int colour);

    bool Remove_files_names(PzG::LaczeDoGNUPlota &Link);

    static int Get_total() { return Total_scene_objects; };
};

#endif // SCENEOBJECT_H