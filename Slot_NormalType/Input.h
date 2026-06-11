#pragma once

class Input
{
public:
	static void Init();
	static void OnKeyDown(int vk);
	static void OnKeyUp(int vk);

	static void Reset();

	static bool IsKeyHold(int vk);
	static bool IsKeyDown(int vk);
	static bool IsKeyUp(int vk);

private:
	static bool KeyHold[256];
	static bool KeyDown[256];
	static bool KeyUp[256];
};