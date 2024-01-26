#pragma once
#include "scripts/items/item.h"

class Tile
{
public:
    enum Direction
	{
		Top,
		Bottom,
		Left,
		Right
	};

    glm::vec3 GetPosition();
    const std::string& GetRepresentation() const;
    std::shared_ptr<Tile> GetConnection(Direction direction);
    bool IsWalkable(Direction direction) const;
    bool IsExit() const;
    std::shared_ptr<Item> GetItemOnTile() const;

    void SetPosition(glm::vec3 position);
    void AddConnection(std::shared_ptr<Tile>, Direction direction);
    void SetItemOnTile(std::shared_ptr<Item> item);

    void AttachToScene(std::shared_ptr<Scene> scene);

protected:
    Tile();
    std::string stringRepresentation_;

    // Render properties
    glm::vec3 position_;
    glm::vec3 size_;
    glm::vec4 color_;

    // Logic properties
    bool isWalkable_[4];
    std::shared_ptr<Tile> connections_[4];
    bool isExit_;
    std::shared_ptr<Item> item_;
};
