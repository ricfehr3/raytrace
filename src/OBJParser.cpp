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
    std::vector<Vec3> verticesPos;
    std::vector<Vec3> verticesNorm;
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
            Vec3 vertexPos(v[0], v[1], v[2]);
            verticesPos.push_back(vertexPos);
        }

        // get a vertex normal
        if(id_char == "vn")
        {
            float vn[3];
            for(int i=0; i<3; i++)
            {
                objfile >> temp;
                vn[i] = ::atof(temp.c_str());
            }
            Vec3 vertexNorm(vn[0], vn[1], vn[2]);
            verticesNorm.push_back(vertexNorm);
        }

        // create faces
        if(id_char == "f")
        {
            std::string delimiterNoTex = "//";
            std::string delimiterTex = "/";

            bool hasNorm = false;
            bool hasTex = false;

            int v[3];
            int vn[3];

            for (int i=0; i<3; i++)
            {
                objfile >> temp;
                if(temp.find(delimiterNoTex) != std::string::npos)
                {
                    hasNorm = true;
                    size_t pos = 0;
                    std::string token;
                    std::vector<std::string> vertexValStr;
                    while((pos = temp.find(delimiterNoTex)) != std::string::npos)
                    {
                        token = temp.substr(0, pos);
                        vertexValStr.push_back(token);
                        temp.erase(0, pos + delimiterNoTex.length());
                    }
                    vertexValStr.push_back(temp);
                    
                    v[i] = ::atoi(vertexValStr[0].c_str()) - 1;
                    vn[i] = ::atoi(vertexValStr[1].c_str()) - 1;

                    vertexValStr.clear();
                }
                else if(temp.find(delimiterTex) != std::string::npos)
                {
                    hasNorm = true;
                    hasTex = true;
                    
                }
                else
                {
                    v[i] = ::atoi(temp.c_str()) - 1;
                }
            }

            Vertex v0;
            Vertex v1;
            Vertex v2;

            if(hasTex)
            {

            }

            if(hasNorm)
            {
                v0.vn = verticesNorm[vn[0]];
                v1.vn = verticesNorm[vn[1]];
                v2.vn = verticesNorm[vn[2]];
            }

            v0.v = verticesPos[v[0]];
            v1.v = verticesPos[v[1]];
            v2.v = verticesPos[v[2]];

            Triangle tri(v0, v1, v2);

            if(!hasNorm)
                tri.calculateFlatNormals();
            
            tris.push_back(tri);
        }
    }

    mesh.tris = tris;
}
