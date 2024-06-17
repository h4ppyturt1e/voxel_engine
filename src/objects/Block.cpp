#include "Block.h"

const std::vector<glm::vec3> CUBE_POSITIONS = {
    // Front face
    {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f},
    // Back face
    {-0.5f, -0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
    // Left face
    {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
    // Right face
    { 0.5f,  0.5f,  0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f, -0.5f},
    // Top face
    {-0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f,  0.5f},
    // Bottom face
    {-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}
};

Block::Block() : position(0.0f, 0.0f, 0.0f), blockType(BlockType::Dirt), isActive(true) {
    initializeVertices();
}

Block::Block(glm::vec3 position, BlockType blockType, bool isActive) 
    : position(position), blockType(blockType), isActive(isActive) {
    initializeVertices();
}

glm::vec3 Block::getPosition() const {
    return position;
}

void Block::setPosition(const glm::vec3& position) {
    this->position = position;
}

BlockType Block::getBlockType() const {
    return blockType;
}

void Block::setBlockType(BlockType blockType) {
    this->blockType = blockType;
    initializeVertices();
}

bool Block::getIsActive() const {
    return isActive;
}

void Block::setIsActive(bool isActive) {
    this->isActive = isActive;
}

const std::vector<float>& Block::getVertices() const {
    return vertices;
}

glm::vec3 Block::getColorForBlockType(BlockType blockType) const {
    switch (blockType) {
        case BlockType::Dirt: return glm::vec3(0.59f, 0.29f, 0.0f);
        case BlockType::Grass: return glm::vec3(0.0f, 1.0f, 0.0f);
        case BlockType::Stone: return glm::vec3(0.5f, 0.5f, 0.5f);
        default: return glm::vec3(1.0f, 1.0f, 1.0f);
    }
}

void Block::initializeVertices() {
    glm::vec3 color = getColorForBlockType(blockType);

    vertices.clear();
    for (const auto& pos : CUBE_POSITIONS) {
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        vertices.push_back(color.r);
        vertices.push_back(color.g);
        vertices.push_back(color.b);
    }
}
