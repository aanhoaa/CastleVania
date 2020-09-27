#include "Map.h"
#include "debug.h"


Map::Map()
{
	LoadMap();
}


Map::~Map()
{
}

void Map::LoadMap()
{
	ReadMapTXT("Resources/map/1.txt");
	TileTexture = new Load_img_file("Resources/map/1.png", ColTile, RowTile, CountTileFrame);
	TileSprite = new Load_resources(TileTexture, 0);

	ScreenColumn = Window_Width / TileTexture->FrameWidth;
	ScreenRow = Window_Height / TileTexture->FrameHeight;
}

void Map::ReadMapTXT(char * filename)
{
	ifstream fileIn;
	fileIn.open(filename, ios::in);

	if (fileIn)
	{
		fileIn >> RowMatrix >> ColumnMatrix >> ColTile >> RowTile >> CountTileFrame;
		//DebugOut(L"[INFO] So luong CountTitle: %d\n", CountTileFrame);
		for (int i = 0; i < RowMatrix; i++)
		{
			for (int j = 0; j < ColumnMatrix; j++)
			{
				fileIn >> TileMap[i][j];
			}
		}
		fileIn.close();
	}


}

void Map::DrawMap()
{
	for (int i = 0; i < (ScreenRow); i++)
	{
		for (int j = 0; j < (ScreenColumn); j++)
		{
			TileSprite->SelectIndex(TileMap[i][j]);
			TileSprite->Draw(0 + j * TILE_FRAME_HEIGHT, 0 + i * TILE_FRAME_WIDTH);
		}
	}
	//TileSprite->SelectIndex(TileMap[0][0]);
	//TileSprite->Draw(0, 0);

}