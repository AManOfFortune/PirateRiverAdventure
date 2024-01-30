#include "level_factory.h"
#include "scripts/tiles/tile_factory.h"
#include "level_types.h"

void LevelFactory::RegisterLevel(std::function<std::shared_ptr<Level>()> creator)
{
	getLevelRegistry()->push_back(creator);
}

std::shared_ptr<Level> LevelFactory::GetNextLevel()
{
	// Instantiate next level
	std::shared_ptr<Level> level = getLevelRegistry()->at(currentLevelIndex_)();
	// Increment current level index
	currentLevelIndex_ = (currentLevelIndex_ + 1) % getLevelRegistry()->size();

	return level;
}

std::shared_ptr<std::vector<std::function<std::shared_ptr<Level>()>>> LevelFactory::getLevelRegistry()
{
	return levelRegistry_;
}
