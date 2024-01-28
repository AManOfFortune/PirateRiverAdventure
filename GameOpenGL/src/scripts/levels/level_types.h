#pragma once
#include "scripts/items/item_types.h"
#include "scripts/units/unit_types/player.h"
#include "scripts/units/unit_types/grunt.h"

class LevelIntroduction : public Level
{
public:
	LevelIntroduction() {
		tileString_ =
			"WWWWWWWWWWWWWWWWWWEEE"
			"W WW WW WW WW WW WE5E"
			"WWWWWWWWGGGGGGGGGGE|E"
			"WWWWWWWWGGGGGGGGGGG|G"
			"W WW WW GG GG --4-- G"
			"WWWWWWWWGGGGG|GGGGG|G"
			"WWWWWWWGGGGGG|GGGGG|G"
			"W WW WG GG GG GG1-- G"
			"WWGGGGGGGGGGG|GGGGG|G"
			"WGGGGGGGGGGGG|GGGGG|G"
			"G GG GG -- -- -- -- G"
			"GGGGGGG|GGGGG|GGGGG|G"
			"GGGGGGG|GGGGG|GGGGG|G"
			"G GG GG --3-- --2GGPG"
			"GGGGGGGGGGGGGGGGGGGGG"
			;
		levelWidth_ = 7;
		keysRequiredToExit_ = 2;

		AddUnit('P', std::make_shared<Player>(Tile::Direction::Top));
		AddUnit('1', std::make_shared<Grunt>(Tile::Direction::Right));
		AddUnit('2', std::make_shared<Grunt>(Tile::Direction::Left));

		AddItem('3', std::make_shared<Key>());
		AddItem('4', std::make_shared<Key>());
		AddItem('5', std::make_shared<Exit>());
	}
};
REGISTER_LEVEL(LevelIntroduction);
