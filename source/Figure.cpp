#include "Figure.h"

Figure::Figure(std::string n)
{
    name = n;
}

std::string Figure::Update_name(std::string append)
{
    return (name.append(append));
}

std::string Figure::Get_name() const
{
    return name;
}