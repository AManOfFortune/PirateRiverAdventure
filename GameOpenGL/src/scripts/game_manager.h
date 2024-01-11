#pragma once

#include "tiles/tile.h"
#include "units/unit.h"
#include "levels/level.h"

class GameManager
{
public:
    // Singleton pattern
    static GameManager& GetInstance()
    {
        static GameManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    GameManager(GameManager const&) = delete;
    void operator=(GameManager const&) = delete;
    // End Singleton pattern

    // Observer pattern
    void AddUnitToListeningToPlayerMovement(std::shared_ptr<Unit> unit);
    void NotifyUnitsListeningToPlayerMovement(bool playerMoveEnded);
    // End Observer pattern

    void SetTileContainingPlayer(std::shared_ptr<Tile> tile);
    std::shared_ptr<Tile> GetTileContainingPlayer() const;

    void StartGame(std::shared_ptr<Scene> activeScene);
    void ResetLevel();
    void NextLevel();

private:
    // Singleton pattern
    GameManager() {}
    // End Singleton pattern

    // Observer pattern
    std::vector<std::shared_ptr<Unit>> unitsListeningToPlayerMovement_;
    // End Observer pattern

    std::shared_ptr<Tile> tileContainingPlayer_;
    std::shared_ptr<Level> currentLevel_;
    std::shared_ptr<Scene> activeScene_;


    
};