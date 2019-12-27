#ifndef OBJPARSER_HPP
#define OBJPARSER_HPP

#include <string>
#include <vector>
#include <fstream>

class Mesh;
class Vec3;

class OBJParser
{
public:
    static void ParseMesh(const std::string &filename, Mesh& mesh);
private:
};

#endif
