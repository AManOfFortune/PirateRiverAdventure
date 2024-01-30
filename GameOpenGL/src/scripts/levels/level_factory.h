#pragma once

#include "level.h"
#include <unordered_map>
#include <functional>
#include <memory>

class LevelFactory {
public:
	static void RegisterLevel(std::function<std::shared_ptr<Level>()> creator);

	static std::shared_ptr<Level> GetNextLevel();

private:
	static std::shared_ptr<std::vector<std::function<std::shared_ptr<Level>()>>> getLevelRegistry();

	inline static int currentLevelIndex_ = 0;

	inline static std::shared_ptr<std::vector<std::function<std::shared_ptr<Level>()>>> levelRegistry_ = std::make_shared<std::vector<std::function<std::shared_ptr<Level>()>>>();
};

// Macro to register a new level
#define REGISTER_LEVEL(level) \
	static bool level##Registered = []() { \
		LevelFactory::RegisterLevel([]() { return std::make_shared<level>(); }); \
		return true; \
	}()
