#include "dirtBlock.h"
#include "block.h"

static const std::vector<GLfloat> textureCoord = { 

    0.0f, 0.0625f,     
    0.0f, 0.0f,
    0.0625f, 0.0f,     
    0.0625f, 0.0625f, 

    0.0625f, 0.0625f,  
    0.0625f, 0.0f,    
    0.125f, 0.0f,     
    0.125f, 0.0625f,   

    0.0625f, 0.0625f,  
    0.0625f, 0.0f,    
    0.125f, 0.0f,     
    0.125f, 0.0625f,  

    0.125f, 0.0625f,   
    0.1875f, 0.0625f,  
    0.1875f, 0.0f,     
    0.125f, 0.0f, 

    0.125f, 0.0625f,   
    0.125f, 0.0f,      
    0.0625f, 0.0f,     
    0.0625f, 0.0625f,   

    0.125f, 0.0625f,   
    0.125f, 0.0f,      
    0.0625f, 0.0f,     
    0.0625f, 0.0625f,  
};

GLuint DirtBlock::vbo;
std::unique_ptr<Mesh> DirtBlock::mesh;

DirtBlock::DirtBlock(const glm::vec3& position) : Block(position, "blockTexture") {

    if (!mesh) {
        mesh  = std::make_unique<Mesh>("../assets/cube.obj");
    }

    if (vbo == 0) {
        vbo = createTextureBuffer(textureCoord);
    }
}
