#include "level.h"
#include "scripts/tiles/tile_factory.h"
#include "scripts/game_manager.h"
#include "scripts/camera_controller.h"

void Level::AttachToScene(std::shared_ptr<Scene> scene)
{
	scene_ = scene;
	Reset();
}

void Level::Reset()
{
	// ------ 1. Parse level string ------
	std::vector<std::shared_ptr<Tile>> tiles = ParseLevel(tileString_, levelWidth_, tileWidth_);

	scene_->ClearScene();

	// ------ 2. Add tiles to scene ------
	for (std::shared_ptr<Tile> tile : tiles) {
		tile->AttachToScene(scene_);
	}

	// ------ 3. Add units to scene ------
	for (auto const& unit : units_) {
		unit.second->AttachToScene(scene_);
		GameManager::GetInstance().AddUnitToListeningToPlayerMovement(unit.second);
	}

	// ------ 4. Add items to scene ------
	for (auto const& item : items_) {
		item.second->AttachToScene(scene_);
	}

	// ------ 4. Add camera to scene ------
	Entity camera = scene_->CreateEntity("Camera");
	camera.AddComponent<CameraComponent>();
	camera.AddComponent<ScriptComponent>().Bind<CameraController>();

	// ------ 5. Set camera position ------
	int levelHeight = (int) (tiles.size() / levelWidth_);
	glm::vec2 cameraPosition = { levelWidth_ / 2, -levelHeight / 2 };
	camera.GetComponent<TransformComponent>().SetPosition(glm::vec3(cameraPosition, 0.0f));
}

Level::Level()
{
	tileString_ = "";
	units_ = std::unordered_map<char, std::shared_ptr<Unit>>();
	tileWidth_ = 3;
	levelWidth_ = 0;
	keysRequiredToExit_ = 0;
}

void Level::AddUnit(char key, std::shared_ptr<Unit> unit)
{
	units_.insert(std::make_pair(key, unit));
}

void Level::AddItem(char key, std::shared_ptr<Item> item)
{
	items_.insert(std::make_pair(key, item));
}

std::vector<std::shared_ptr<Tile>> Level::ParseLevel(std::string levelString, int width, int tileWidth)
{
	std::vector<std::shared_ptr<Tile>> result;

	for (int i = 0, posCounter = 0; i < levelString.length(); i += tileWidth, posCounter++) {
		std::string currentTile = levelString.substr(i, tileWidth) + levelString.substr(i + (width * tileWidth), tileWidth) + levelString.substr(i + (width * tileWidth * 2), tileWidth);
		// Get unit on tile (middle character)
		char unitOnTile = currentTile[(const unsigned __int64) tileWidth * 1.5];
		// Remove unit from tile to leave blank tile string
		currentTile[(const unsigned __int64) tileWidth * 1.5] = ' ';

		// ------ 1. Create correct tile type -----
		std::shared_ptr<Tile> tile = TileFactory::createTile(currentTile);

		// ------ 2. Set tile position ------
		int posX = posCounter % width;
		int posY = -(posCounter / width);
		int posZ = 0;

		glm::vec3 tilePosition = glm::vec3(posX, posY, posZ);

		tile->SetPosition(tilePosition);

		// ------ 3. Set unit positions ------
		if (units_.find(unitOnTile) != units_.end()) {
			units_.at(unitOnTile)->SetCurrentTile(tile);
		}

		// ------ 4. Set item positions ------
		if (items_.find(unitOnTile) != items_.end()) {
			items_.at(unitOnTile)->SetPosition(tilePosition);
			tile->SetItemOnTile(items_.at(unitOnTile));
		}

		// ------ 5. Add tile to result -------
		result.push_back(tile);

		// Skip 2 rows of characters if we are at the end of a row
		if ((i + tileWidth) % (width * tileWidth) == 0 && i != 0) {
			i += (width * tileWidth * 2);
		}
	}

	// ------ 4. Set dynamic tile properties ------
	for (int posCounter = 0; posCounter < result.size(); posCounter++) {

		std::shared_ptr<Tile> tile = result.at(posCounter);

		if (tile == nullptr) continue;

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
