#pragma once
#include "scripts/items/item_types.h"
#include "scripts/items/decoration_types.h"
#include "scripts/units/unit_types/player.h"
#include "scripts/units/unit_types/grunt.h"

class LevelTutorial : public Level
{
public:
	LevelTutorial() {
		tileString_ =
			"WWWWWWWWWWWWWWWEEE"
			"W WW WW WW7WW8WE2E"
			"GGGGGGGGGGGGGGGE|E"
			"GGGGGGGGGGGGGGGG|G"
			"G3GG4GG5GG6GG -- G"
			"GGGGGGGGGGGGG|GGGG"
			"GGGGGGGGGGGGG|GGGG"
			"G GG1-- -- -- GG G"
			"GGGGGGG|GGGGGGGGGG"
			"GGGGGGG|GGGGGGGGGG"
			"GP-- -- GG GG GG G"
			"GGGGGGGGGGGGGGGGGG"
			;
		levelWidth_ = 6;
		keysRequiredToExit_ = 1;

		AddUnit('P', std::make_shared<Player>(Tile::Direction::Right));
		AddItem('1', std::make_shared<Key>());
		AddItem('2', std::make_shared<Exit>());

		AddItem('3', std::make_shared<BrickWall>(BrickWall::WallType::StraightFacingDown));
		AddItem('4', std::make_shared<BrickWall>(BrickWall::WallType::StraightFacingDown));
		AddItem('5', std::make_shared<BrickWall>(BrickWall::WallType::StraightFacingDown));
		AddItem('6', std::make_shared<BrickWall>(BrickWall::WallType::CornerBottomRight));
		AddItem('7', std::make_shared<BrickWall>(BrickWall::WallType::CornerTopLeft));
		AddItem('8', std::make_shared<BrickWall>(BrickWall::WallType::CornerBottomRight));
	}
};
REGISTER_LEVEL(LevelTutorial);

class LevelGruntIntroduction : public Level
{
public:
	LevelGruntIntroduction() {
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
REGISTER_LEVEL(LevelGruntIntroduction);
