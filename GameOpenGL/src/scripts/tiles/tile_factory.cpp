#include "tile_factory.h"
#include "tile_types.h"

void TileFactory::registerTileType(std::function<std::shared_ptr<Tile>()> creator) {
    getTileRegistry()->emplace(creator()->GetRepresentation(), creator);
}

std::shared_ptr<Tile> TileFactory::createTile(const std::string& representation) {
    auto tileRegistry = getTileRegistry();
    auto it = tileRegistry->find(representation);
    if (it != tileRegistry->end()) {
        return (it->second)();
    }
    return nullptr; // Unknown tile type
}

std::shared_ptr<std::unordered_map<std::string, std::function<std::shared_ptr<Tile>()>>> TileFactory::getTileRegistry() {
    return tileRegistry_;
}

