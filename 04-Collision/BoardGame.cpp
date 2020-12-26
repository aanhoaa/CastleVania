#include "BoardGame.h"

BoardGame::BoardGame(int X, int Y)
{
	texture = LoadTexture::GetInstance()->GetTexture(BLACKBOARD);
	sprite = new Load_resources(texture, 0);
	x = X;
	y = Y;
}

void BoardGame::Render(Simon *simon, int  _hpBoss, int TimeRemaining, Weapons *weap, int stage)
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

	heartPoint.Draw(x + 100, y + 25, simon->GetHP(), _hpBoss); // display life simon

	if (weap != NULL)
	{
		switch (weap->GetType())
		{
		case def_ID::DAGGER:
		{
			weap->RenderItem(330, 40);
			break;
		}
		case def_ID::HOLYWATER:
		{
			weap->RenderItem(332, 33);
			break;
		}
		case def_ID::AXE:
		{
			weap->RenderItem(332, 33);
			break;
		}
		default:
			break;
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
