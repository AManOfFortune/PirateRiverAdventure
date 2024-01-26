#pragma once
#include "scripts/items/item_types.h"
#include "scripts/units/unit_types/player.h"
#include "scripts/units/unit_types/grunt.h"

class LevelIntroduction : public Level
{
public:
	LevelIntroduction() {
		tileString_ =
			"GGGGGGGGGGGGGGGGGGEEE"
			"G GG GG GG GG GG GE E"
			"GGGGGGGGGGGGGGGGGGE|E"
			"GGGGGGGGGGGGGGGGGGG|G"
			"G GG GG GG GG --4-- G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"G GG GG GG GG GG1-- G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"G GG GG -- -- -- -- G"
			"GGGGGGG|GGGGG|GGGGG|G"
			"GGGGGGG|GGGGG|GGGGG|G"
			"G GG GG --3-- --2GGPG"
			"GGGGGGGGGGGGGGGGGGGGG"
			;
		levelWidth_ = 7;
		keysRequiredToExit_ = 2;

		AddUnit('P', std::make_shared<Player>());
		AddUnit('1', std::make_shared<Grunt>(Tile::Direction::Right));
		AddUnit('2', std::make_shared<Grunt>(Tile::Direction::Left));

		AddItem('3', std::make_shared<Key>());
		AddItem('4', std::make_shared<Key>());
	}
};
REGISTER_LEVEL(LevelIntroduction);
