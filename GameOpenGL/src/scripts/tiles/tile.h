#pragma once
#include "core/core.h"

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

    void SetPosition(glm::vec3 position);
    void AddConnection(std::shared_ptr<Tile>, Direction direction);
    void SetHasPlayer(bool hasPlayer);

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

private:
    // Unit properties
    bool hasPlayer_;

};
