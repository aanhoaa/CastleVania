#include "BoardGame.h"

BoardGame::BoardGame(int X, int Y)
{
	texture = new Load_img_file("Resources\\blackboard.png");
	sprite = new Load_resources(texture, 0);
	x = X;
	y = Y;
}

void BoardGame::Render(Camera * camera, Simon *simon)
{
	sprite->Draw(x, y);

	font.Draw(x, y + 15, "SCORE-");
	font.Draw(x, y + 33, "PLAYER");
	font.Draw(x, y + 51, "ENEMY");
	font.Draw(x + 210, y + 15, "TIME");
	font.Draw((x + 400), y + 15, "STAGE");
	font.Draw(x + 400 + 15, y + 15 + 18, std::to_string(simon->GetHeartCollect())); // Số lượng tim nhặt dc
	heartPoint.Draw(x + 100, y + 30, simon->GetLife(), 5); // display life simon
}

BoardGame::~BoardGame()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(sprite);
}