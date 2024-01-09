#include "level_data.h"

LevelData::LevelData() {
	level_ =
		"GGGGGGGGGGGGGGGGGGGGG"
		"G GG GG GG GG GG GG G"
		"GGGGGGGGGGGGGGGGGGG|G"
		"GGGGGGGGGGGGGGGGGGG|G"
		"G GG GG GG GG -- -- G"
		"GGGGGGGGGGGGG|GGGGG|G"
		"GGGGGGGGGGGGG|GGGGG|G"
		"G GG GG GG GG GG -- G"
		"GGGGGGGGGGGGG|GGGGG|G"
		"GGGGGGGGGGGGG|GGGGG|G"
		"G GG GG -- -- -- -- G"
		"GGGGGGG|GGGGG|GGGGG|G"
		"GGGGGGG|GGGGG|GGGGG|G"
		"G GG GG -- -- -- GGPG"
		"GGGGGGGGGGGGGGGGGGGGG"
		;
	levelWidth_ = 7;
	tileWidth_ = 3;
}

std::vector<std::shared_ptr<Tile>> LevelData::GetNextLevel()
{
	return ParseLevel(level_, levelWidth_, tileWidth_);
}

std::vector<std::shared_ptr<Tile>> LevelData::ParseLevel(std::string levelString, int width, int tileWidth) {
	std::vector<std::shared_ptr<Tile>> result;

	for (int i = 0, posCounter = 0; i < levelString.length(); i += tileWidth, posCounter++) {
		std::string currentTile = levelString.substr(i, tileWidth) + levelString.substr(i + (width * tileWidth), tileWidth) + levelString.substr(i + (width * tileWidth * 2), tileWidth);
		// Get unit on tile (middle character)
		char unitOnTile = currentTile[tileWidth * 1.5];
		// Remove unit from tile to leave blank tile string
		currentTile[tileWidth * 1.5] = ' ';

		// ------ 1. Create correct tile type -----
		std::shared_ptr<Tile> tile = TileFactory::createTile(currentTile);

		// ------ 2. Set unit toggles ------
		switch (unitOnTile) {
		case 'P':
			tile->SetHasPlayer(true);
			break;
		default:
			break;
		}

		// ------ 3. Add tile to result -------
		result.push_back(tile);

		// Skip 2 rows of characters if we are at the end of a row
		if ((i + tileWidth) % (width * tileWidth) == 0 && i != 0) {
			i += (width * tileWidth * 2);
		}
	}

	// ------ 4. Set dynamic tile properties ------
	for(int posCounter = 0; posCounter < result.size(); posCounter++) {

		std::shared_ptr<Tile> tile = result.at(posCounter);

		if (tile == nullptr) continue;

		int posX = posCounter % width;
		int posY = -(posCounter / width);
		int posZ = 0.0f;

		glm::vec3 tilePosition = glm::vec3(posX, posY, posZ);

		// Set position
		tile->SetPosition(tilePosition);

		// Add top
		if (tile->IsWalkable(Tile::Direction::Top)) {
			std::shared_ptr<Tile> topNeighbour = result.at(posCounter - width);
			tile->AddConnection(topNeighbour, Tile::Direction::Top);
		}
		// Add bottom
		if (tile->IsWalkable(Tile::Direction::Bottom)) {
			std::shared_ptr<Tile> bottomNeighbour = result.at(posCounter + width);
			tile->AddConnection(bottomNeighbour, Tile::Direction::Bottom);
		}
		// Add left
		if (tile->IsWalkable(Tile::Direction::Left)) {
			std::shared_ptr<Tile> leftNeighbour = result.at(posCounter - 1);
			tile->AddConnection(leftNeighbour, Tile::Direction::Left);
		}
		// Add right
		if (tile->IsWalkable(Tile::Direction::Right)) {
			std::shared_ptr<Tile> rightNeighbour = result.at(posCounter + 1);
			tile->AddConnection(rightNeighbour, Tile::Direction::Right);
		}
	}

	return result;
}
