#pragma once

class GameContext
{
public:
	static GameContext& GetInstance()
	{
		static GameContext instance;
		return instance;
	}

	void Update(float deltaTime);

private:
	GameContext() = default;
};