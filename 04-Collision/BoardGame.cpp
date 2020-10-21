#include "BoardGame.h"

BoardGame::BoardGame(int X, int Y)
{
	texture = new Load_img_file("Resources\\blackboard.png");
	sprite = new Load_resources(texture, 0);
	x = X;
	y = Y;
}

void BoardGame::Render(Camera * camera, Simon *simon, Weapons *weap, int stage)
{
	sprite->Draw(x, y);

	font.Draw(x, y + 15, "SCORE-" + ShowPoint(std::to_string(simon->GetPoint()),(UINT)6));
	font.Draw(x, y + 33, "PLAYER");
	font.Draw(x, y + 51, "ENEMY");
	font.Draw(x + 210, y + 15, "TIME");
	font.Draw((x + 400 - 20), y + 15, "STAGE");
	font.Draw(x + 400 + 60, y + 15, std::to_string(stage));
	font.Draw(x + 400 + 15, y + 15 + 18, std::to_string(simon->GetHeartCollect())); // Số lượng tim nhặt dc
	heartPoint.Draw(x + 100, y + 30, simon->GetHP(), 5); // display life simon

	if (weap != NULL)
	{
		if (weap->GetType() == def_ID::DAGGER)
		{
			weap->RenderItem(330, 40);
		}
	}
}

BoardGame::~BoardGame()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(sprite);
}

string BoardGame::ShowPoint(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}
