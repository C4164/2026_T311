#include "Input.h"

bool Input::KeyHold[256] = {};
bool Input::KeyDown[256] = {};
bool Input::KeyUp[256] = {};

void Input::Init()
{
	for (int i = 0; i < 256; i++)
	{
		KeyHold[i] = false;
		KeyDown[i] = false;
		KeyUp[i] = false;
	}
}

void Input::OnKeyDown(int vk)
{
	//ƒL[‚ª‰Ÿ‚³‚ê‚½uŠÔ‚Ì‚Ý‚ðtrue‚É‚·‚é
	if (!KeyHold[vk]) { KeyDown[vk] = true; }
	KeyHold[vk] = true;
}

void Input::OnKeyUp(int vk)
{
	KeyHold[vk] = false;
	KeyUp[vk] = true;
}

void Input::Reset()
{
	for (int i = 0; i < 256; i++)
	{
		KeyDown[i] = false;
		KeyUp[i] = false;
	}
}

bool Input::IsKeyHold(int vk) { return KeyHold[vk]; }
bool Input::IsKeyDown(int vk) { return KeyDown[vk]; }
bool Input::IsKeyUp(int vk) { return KeyUp[vk]; }