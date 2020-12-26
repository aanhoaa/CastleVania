#pragma once
#include <unordered_map>
#include "define.h"
#include "Load_img_file.h"

class LoadTexture
{
	unordered_map<def_ID, Load_img_file*> Textures;

public:
	static LoadTexture* __Instance;
	static LoadTexture* GetInstance();

	void AddTexture(def_ID type, Load_img_file* texture);
	Load_img_file* GetTexture(def_ID type);

	void LoadResource();

	LoadTexture();
	~LoadTexture();
};