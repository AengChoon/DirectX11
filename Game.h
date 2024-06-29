#pragma once

class CGame
{
public:
	CGame();

	~CGame();

	void Init(HWND WindowHandle);

	void Update();

	void Render();
};

