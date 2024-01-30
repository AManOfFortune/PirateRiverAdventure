#include "player_mover_script.h"
#include "scripts/game_manager.h"

void PlayerMoverScript::OnCreate()
{
}

void PlayerMoverScript::OnDestroy()
{
}

void PlayerMoverScript::OnUpdate(DeltaTime ts)
{
	auto& transform = GetComponent<TransformComponent>();
	auto currentTile = GameManager::GetInstance().GetTileContainingPlayer();

	// If current position is not the same as the tile position, move to the tile position
	if (currentTile->GetPosition() != transform.GetPosition()) {
		glm::vec3 newPos = MoveOverTime(transform.GetPosition(), currentTile->GetPosition(), moveSpeedInSeconds_, currentTime_, ts);
		transform.SetPosition(newPos);

		// If the player has reached the tile position, reset the current time and notify the game manager
		if (newPos == currentTile->GetPosition()) {
			currentTime_ = 0.0f;
			GameManager::GetInstance().NotifyUnitsListeningToPlayerMovement(true);
		}

		// Return to lock player input until the player has reached the tile position
		return;
	}

	std::shared_ptr<Tile> tileToMoveTo = nullptr;
	Tile::Direction moveDirection = Tile::Direction::None;

	if (Input::IsKeyPressed(CG_KEY_A))
		moveDirection = Tile::Direction::Left;
	if (Input::IsKeyPressed(CG_KEY_D))
		moveDirection = Tile::Direction::Right;
	if (Input::IsKeyPressed(CG_KEY_S))
		moveDirection = Tile::Direction::Bottom;
	if (Input::IsKeyPressed(CG_KEY_W))
		moveDirection = Tile::Direction::Top;

	if (moveDirection != Tile::Direction::None) {
		GameManager::GetInstance().GetPlayer()->SetFacingDirection(moveDirection);
		tileToMoveTo = currentTile->GetConnection(moveDirection);
	}

	// If move is possible set the new tile containing the player & notify the game manager
	if (tileToMoveTo != nullptr) {
		GameManager::GetInstance().SetTileContainingPlayer(tileToMoveTo);
		GameManager::GetInstance().NotifyUnitsListeningToPlayerMovement(false);
	}
}

// Function to move from start to end position over a given time duration
glm::vec3 PlayerMoverScript::MoveOverTime(const glm::vec3& startPos, const glm::vec3& endPos, float durationInSeconds, float& currentTime, float deltaTime)
{
	// Update the current time based on deltaTime
	currentTime += deltaTime;

	// Ensure currentTime is within the duration
	currentTime = glm::clamp(currentTime, 0.0f, durationInSeconds);

	// Calculate the interpolation factor (between 0 and 1)
	float t = currentTime / durationInSeconds;

	// Perform linear interpolation between start and end positions
	glm::vec3 interpolatedPos = glm::mix(startPos, endPos, t);

	return interpolatedPos;
}