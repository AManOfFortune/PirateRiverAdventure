#include "tile.h"
#include "scripts/game_manager.h"

glm::vec3 Tile::GetPosition() {
    return position_;
}

void Tile::SetPosition(glm::vec3 position) {
    position_ = position;
}

void Tile::AddConnection(std::shared_ptr<Tile> tile, Direction direction) {
    connections_[direction] = tile;
}

void Tile::SetItemOnTile(std::shared_ptr<Item> item)
{
	item_ = item;
}

std::shared_ptr<Tile> Tile::GetConnection(Direction direction)
{
    return connections_[direction];
}

const std::string& Tile::GetRepresentation() const {
    return stringRepresentation_;
}

bool Tile::IsWalkable(Direction direction) const
{
    return isWalkable_[direction];
}

bool Tile::IsExit() const
{
    return isExit_;
}

std::shared_ptr<Item> Tile::GetItemOnTile() const
{
    return item_;
}

void Tile::AttachToScene(std::shared_ptr<Scene> scene)
{
    // Create tile at position
    Entity entity = scene->CreateEntity("Tile", position_);
    // Add sprite renderer component
    
    // TODO: Update to take in Subtexture2D -> SpriteSheets work! Raoul
    entity.AddComponent<SpriteRendererComponent>(texture_);
}

Tile::Tile() {
    size_ = glm::vec3(1.0f, 1.0f, 1.0f);
    position_ = glm::vec3(0.0f);
    stringRepresentation_ = "";
    for (int i = 0; i < 4; i++) { isWalkable_[i] = false; };
    for(int i = 0; i < 4; i++) { connections_[i] = nullptr;	}
    isExit_ = false;

    textureAtlas_ = Texture2D::Create("assets/textures/NinjaAdventure/Backgrounds/Tilesets/TilesetWater.png");
    defaultAtlasSize_ = glm::vec2(28, 17);

    SetTexture(1, 1);
}

void Tile::SetTexture(int xCoord, int yCoord)
{
	texture_ = SubTexture2D::CreateFromCoords(textureAtlas_, { xCoord, yCoord }, defaultAtlasSize_);
}
