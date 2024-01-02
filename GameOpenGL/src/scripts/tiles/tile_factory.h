#pragma once

#include "tile.h"
#include <unordered_map>
#include <functional>
#include <memory>

class TileFactory {
public:
	static void registerTileType(std::function<std::shared_ptr<Tile>()> creator);

	static std::shared_ptr<Tile> createTile(const std::string& representation);

private:
	static std::shared_ptr<std::unordered_map<std::string, std::function<std::shared_ptr<Tile>()>>> getTileRegistry();

	inline static std::shared_ptr<std::unordered_map<std::string, std::function<std::shared_ptr<Tile>()>>> tileRegistry_ = std::make_shared<std::unordered_map<std::string, std::function<std::shared_ptr<Tile>()>>>();
};

// Macro to register a tile type
#define REGISTER_TILE_TYPE(type) \
	static bool type##Registered = []() { \
		TileFactory::registerTileType([]() { return std::make_shared<type>(); }); \
		return true; \
	}()

