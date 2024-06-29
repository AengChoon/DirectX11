#pragma once

class Game
{
public:
	Game();

	~Game();

	void Init(HWND WindowHandle);

	void Update();

	void Render();
};

