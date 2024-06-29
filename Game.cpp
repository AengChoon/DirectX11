#include "pch.h"
#include "Game.h"

CGame::CGame()
	: WindowHandle(nullptr)
	, Width(0)
	, Height(0)
{
}

CGame::~CGame()
{
}

void CGame::Init(const HWND InWindowHandle)
{
	WindowHandle = InWindowHandle;
	Width = GWindowSizeX;
	Height = GWindowSizeY;
}

void CGame::Update()
{
}

void CGame::Render()
{
}
