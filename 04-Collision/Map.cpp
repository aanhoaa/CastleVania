﻿#include "Map.h"
#include "debug.h"


Map::Map()
{
	//LoadMap();
}


Map::~Map()
{
}

void Map::LoadMap(eMap mMap)
{
	switch (mMap)
	{
	case eMap::mMap1:
		ReadMapTXT("Resources/map/1.txt");
		TileTexture = new Load_img_file("Resources/map/1.png", ColTile, RowTile, CountTileFrame);
		break;
	case eMap::mMap2:
		ReadMapTXT("Resources/map/2.txt");
		TileTexture = new Load_img_file("Resources/map/2.png", 18, 5, 90);
		break;
	default:
		DebugOut(L"[MAP] Load map fail!");
		return;
		break;
	}

	TileSprite = new Load_resources(TileTexture, 100);

	MapWidth = (TileTexture->FrameWidth)*(ColumnMatrix);  // Chiều dài của MAP
	MapHeight = (TileTexture->FrameHeight)*(RowMatrix); //  chiều cao của MAP

	ScreenColumn = Window_Width / TileTexture->FrameWidth; 
	ScreenRow = Window_Height / TileTexture->FrameHeight;
}

void Map::ReadMapTXT(char * filename)
{
	ifstream fileIn;
	fileIn.open(filename, ios::in);

	if (fileIn)
	{
		fileIn >> RowMatrix >> ColumnMatrix >> ColTile >> RowTile >> CountTileFrame >> BoardHeight;
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

void Map::DrawMap(Camera *camera)
{
	row = int(camera->GetY_cam()) / TileTexture->FrameHeight;
	column = int(camera->GetX_cam()) / TileTexture->FrameWidth;

	x = -(int(camera->GetX_cam()) % TileTexture->FrameWidth); // xác định vị trí x bắt đầu vẽ các tile theo loop 
	y = -(int(camera->GetY_cam()) % TileTexture->FrameHeight); // xác định vị trí y bắt đầu vẽ các tile theo loop

	//DebugOut(L"[INFO] X: %d\n", x); 
	//DebugOut(L"[INFO] Column: %d\n", column); // -18

	// render các tiled lên màn hình cam
	for (int i = 0; i < ScreenRow + 1; i++)
	{
		//if (y + TileTexture->FrameWidth * i >=  AutoFit)
		{
			for (int j = 0; j < ScreenColumn + 1; j++) // sC+1 để load 1 col sau cam, khi cam tới sẽ có hình luôn(nếu k sẽ đen)
			{
				// dk cho phần cuối map
				if (!(row + i < 0 /*nằm ngoài cam*/|| row + i>RowMatrix  /* vượt quá row trong txt*/|| j + column < 0 || j + column > ColumnMatrix))
				{
				//	DebugOut(L"[INFO] Res ne: %d\n", x + TileTexture->FrameWidth*j); // 0
					TileSprite->SelectIndex(TileMap[row + i][column + j]);
					TileSprite->Draw(x + TileTexture->FrameWidth*j, y + TileTexture->FrameHeight*i + BoardHeight);
				}
			}
		}
		//y = y + TileTexture->FrameHeight;
		//	x = -int(camera->GetViewport().x) % TileTexture->FrameHeight;
	}
}

int Map::GetMapWidth()
{
	return (TileTexture->FrameWidth)*(ColumnMatrix);  // Chiều dài của MAP
}
int Map::GetMapHeight()
{
	return (TileTexture->FrameHeight)*(RowMatrix); //  chiều cao của MAP
}