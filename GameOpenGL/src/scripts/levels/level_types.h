#pragma once
#include "scripts/units/unit_types/player.h"

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

		AddUnit('P', std::make_shared<Player>());
	}
};
REGISTER_LEVEL(LevelIntroduction);
