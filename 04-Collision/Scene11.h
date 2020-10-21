#include "Scenes.h"
#include "Load_resources.h"


#include "Brick.h"
#include "Simon.h" 
#include "Map.h"
#include "Camera.h"
#include "Grid.h"
#include "Items.h" 
#include "BoardGame.h"
#include "Dagger.h"
#include "HitEffect.h"

class Scene_1 : public Scenes
{
public:
	Simon * simon;
	Map * TileMap;
	Camera *camera;
	Grid * gridGame;

	BoardGame * board;
	//Data * _data;

	vector<LPGAMEOBJECT> listObj;
	vector <Items*> listItem;
	vector <HitEffect*> listEffect;

public:
	Scene_1();
	~Scene_1();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	void CheckCollision();
	void CheckCollisionWeapon();
	void CheckCollisionSimonWithItem();

	Items * GetNewItem(int Id, def_ID Type, float X, float Y);
};

