#pragma once

#include "tiles/tile.h"

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

    void SetTileContainingPlayer(std::shared_ptr<Tile> tile);
    std::shared_ptr<Tile> GetTileContainingPlayer() const;

private:
    // Singleton pattern
    GameManager() {}
    // End Singleton pattern

    std::shared_ptr<Tile> tileContainingPlayer_;
};