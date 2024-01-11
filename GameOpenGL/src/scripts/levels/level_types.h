#pragma once
#include "scripts/units/unit_types/player.h"
#include "scripts/units/unit_types/grunt.h"

class LevelIntroduction : public Level
{
public:
	LevelIntroduction() {
		tileString_ =
			"GGGGGGGGGGGGGGGGGGGGG"
			"G GG GG GG GG GG GG G"
			"GGGGGGGGGGGGGGGGGGG|G"
			"GGGGGGGGGGGGGGGGGGG|G"
			"G GG GG GG GG -- -- G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"G GG GG GG GG GG1-- G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"GGGGGGGGGGGGG|GGGGG|G"
			"G GG GG -- -- -- -- G"
			"GGGGGGG|GGGGG|GGGGG|G"
			"GGGGGGG|GGGGG|GGGGG|G"
			"G GG GG -- -- --2GGPG"
			"GGGGGGGGGGGGGGGGGGGGG"
			;
		levelWidth_ = 7;

		AddUnit('P', std::make_shared<Player>());
		AddUnit('1', std::make_shared<Grunt>(Tile::Direction::Right));
		AddUnit('2', std::make_shared<Grunt>(Tile::Direction::Left));
	}
};
REGISTER_LEVEL(LevelIntroduction);
