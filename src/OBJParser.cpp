#include <sstream>

#include "OBJParser.hpp"
#include "Mesh.hpp"
#include "Vec3.hpp"
#include "Triangle.hpp"

void OBJParser::ParseMesh(const std::string &filename, Mesh& mesh)
{
    std::ifstream objfile(filename);    
    if(objfile.fail())
    {
        std::cout << "Error, file not found: " << filename << std::endl;
        return;
    }

    std::string id_char;
    std::vector<Vec3> vertices;
    std::vector<Triangle> tris;
    //while(std::getline(objfile, line))
    while((objfile >> id_char))
    {
        std::string temp;
        // get a vertex
        if(id_char == "v")
        {
            float v[3];
            for(int i=0; i<3; i++)
            {
                objfile >> temp;
                v[i] = ::atof(temp.c_str());
            }
            Vec3 vertex(v[0], v[1], v[2]);
            vertices.push_back(vertex);
        }

        // create faces
        if(id_char == "f")
        {
            int v[3];
            for (int i=0; i<3; i++)
            {
                objfile >> temp;
                v[i] = ::atoi(temp.c_str()) - 1;
            }
            Triangle tri(vertices[v[0]], vertices[v[1]], vertices[v[2]]);
            tris.push_back(tri);
            /*
            std::vector<int> tokens;
            std::string token;
            char delimiter = '/';
            while(objfile >> temp)
            {    
                std::istringstream tokenStream(temp);
                while(std::getline(tokenStream, token, delimiter))
                {
                    tokens.push_back(::atoi(token.c_str()) - 1);
                }

                Triangle tri(vertices[tokens[0]], vertices[tokens[1]], vertices[tokens[2]]);
                tris.push_back(tri);
                tokens.clear();
            }
            */
        }
    }

    mesh.tris = tris;
    std::cout << "From OBJParser... " << mesh.tris.size() << std::endl;
}
