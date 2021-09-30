#ifndef MODEL_H
#define MODEL_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "common.h"
#include <vector>
#include "Mesh.h"

class Model
{
public:
    Model(char const * path,bool gamma = false): gammaCorrection(gamma)
    {
        loadModel(path);
    }

    void Draw(Shader &shader)
    {
        for(unsigned int i=0;i < meshes.size();i++)
        {
            meshes[i].Draw(shader);
        }
    };

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;

    void loadModel(std::string const path);
    void processNode(aiNode * node,const aiScene * scene);
    Mesh processMesh(aiMesh * mesh,const aiScene * scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial * mat,aiTextureType type,std::string whatType,const aiScene * scene);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
};


#endif // MODEL_H
