#pragma once
#include <array>
#include "GameObject.h"

class UI
{
public:
	UI() = default;
	~UI() = default;

	void Init();

private:
	std::array<GameObject*, 8>gridLines;
	float lineWidth = 0.1f;
};