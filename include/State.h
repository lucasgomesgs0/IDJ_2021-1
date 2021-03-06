#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>

#include "GameObject.h"
#include "Music.h"

class State
{
private:
	Music music;
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;

	void AddObject(int mouseX, int mouseY);
public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
};

#endif
