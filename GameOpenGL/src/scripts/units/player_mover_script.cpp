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

		if(newPos == currentTile->GetPosition())
			currentTime_ = 0.0f;

		// Return to lock player input until the player has reached the tile position
		return;
	}

	std::shared_ptr<Tile> tileToMoveTo = nullptr;

	if (Input::IsKeyPressed(CG_KEY_A))
		tileToMoveTo = currentTile->GetConnection(Tile::Direction::Left);
	if (Input::IsKeyPressed(CG_KEY_D))
		tileToMoveTo = currentTile->GetConnection(Tile::Direction::Right);
	if (Input::IsKeyPressed(CG_KEY_S))
		tileToMoveTo = currentTile->GetConnection(Tile::Direction::Bottom);
	if (Input::IsKeyPressed(CG_KEY_W))
		tileToMoveTo = currentTile->GetConnection(Tile::Direction::Top);

	// If move is possible set the new tile containing the player
	if (tileToMoveTo != nullptr) {
		GameManager::GetInstance().SetTileContainingPlayer(tileToMoveTo);
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