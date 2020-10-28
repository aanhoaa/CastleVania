#include "BoardGame.h"

BoardGame::BoardGame(int X, int Y)
{
	texture = new Load_img_file("Resources\\blackboard.png");
	sprite = new Load_resources(texture, 0);
	x = X;
	y = Y;
}

void BoardGame::Render(Camera * camera, Simon *simon, int TimeRemaining, Weapons *weap, int stage)
{
	sprite->Draw(x, y);

	font.Draw(x, y + 10, "SCORE-" + Show(std::to_string(simon->GetPoint()),(UINT)6));
	font.Draw(x, y + 28, "PLAYER");
	font.Draw(x, y + 46, "ENEMY");
	font.Draw(x + 210, y + 10, "TIME" + Show(std::to_string(TimeRemaining), (UINT)4));
	font.Draw((x + 380), y + 10, "STAGE");
	font.Draw(x + 460, y + 10, Show(std::to_string(stage),2));
	font.Draw(x + 415, y + 32, Show(std::to_string(simon->GetHeartCollect()),2)); // Số lượng tim nhặt dc
	font.Draw(x + 415, y + 52, Show(std::to_string(simon->GetLife()), 2)); // Số lượng tim nhặt dc

	heartPoint.Draw(x + 100, y + 25, simon->GetHP(), 5); // display life simon

	if (weap != NULL)
	{
		if (weap->GetType() == def_ID::DAGGER)
		{
			weap->RenderItem(330, 35);
		}
	}
}

BoardGame::~BoardGame()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(sprite);
}

string BoardGame::Show(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}
