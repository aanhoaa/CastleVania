#include "FontGame.h"



FontGame::FontGame()
{
	texture = new Load_img_file("Resources\\font\\1.png", 13, 3, 37, 0);
	sprite = new Load_resources(texture, 0);

}


FontGame::~FontGame()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(sprite);
}

void FontGame::Draw(int x, int y, string s)
{
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			sprite->SelectIndex(s[i] - 'A');
		}
		else
			if (s[i] >= '0' && s[i] <= '9')
			{
				sprite->SelectIndex(s[i] - '0' + 26);
			}
			else
				sprite->SelectIndex(36);
		sprite->Draw(x + i * texture->FrameWidth, y);
	}
}