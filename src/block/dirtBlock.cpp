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

DirtBlock::DirtBlock(const glm::vec3& position) : Block(position) {

    createTextureBuffer();
}

void DirtBlock::createTextureBuffer() {
    if (vbo == 0) {
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, textureCoord.size() * sizeof(GLfloat), textureCoord.data(), GL_STATIC_DRAW);

        // Texture coordinate attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
    }
}

/*


TODO: Test if creating another block would be an issue given the current structure of the game

I guess the blocks are sharing same VAO so creating another texture would be difficult.
What needs to be done is that each type of block must have its own mesh instance

*/
