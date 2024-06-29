#pragma once

class CGame
{
public:
	CGame();

	~CGame();

	void Init(HWND InWindowHandle);

	void Update();

	void Render();

private:
	HWND WindowHandle;

	uint32 Width;

	uint32 Height;

};

