#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>
#include <vector>

enum class BlockType {
    Dirt,
    Grass,
    Stone
};

class Block {
public:
    Block();
    Block(glm::vec3 position, BlockType blockType, bool isActive = true);
    
    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& position);

    BlockType getBlockType() const;
    void setBlockType(BlockType blockType);

    bool getIsActive() const;
    void setIsActive(bool isActive);

    const std::vector<float>& getVertices() const;

private:
    glm::vec3 position;
    BlockType blockType;
    bool isActive;
    std::vector<float> vertices;

    void initializeVertices();
    glm::vec3 getColorForBlockType(BlockType blockType) const;
};

#endif // BLOCK_H
