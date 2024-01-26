#pragma once
#include "scripts/units/unit.h"

class Player : public Unit
{
public:
	Player();

	void AttachToScene(std::shared_ptr<Scene> scene) override;
	void OnPlayerMovement(std::shared_ptr<Tile> tile, bool playerMoveEnded) override {};

	void SetCurrentTile(std::shared_ptr<Tile> tile) override;

	void AddItemToInventory(std::shared_ptr<Item> item);

	template <typename ItemType>
	std::vector<std::shared_ptr<Item>> GetItemsOfType() const {
		std::vector<std::shared_ptr<Item>> result;

		// Use std::copy_if to copy items of the desired type to the result vector
		std::copy_if(inventory_.begin(), inventory_.end(), std::back_inserter(result),
			[](const std::shared_ptr<Item>& item) {
				// Replace ItemType with the actual type you are checking for
				return dynamic_cast<ItemType*>(item.get()) != nullptr;
			});

		return result;
	};

private:
	std::vector<std::shared_ptr<Item>> inventory_;
};
