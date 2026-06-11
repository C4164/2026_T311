#pragma once

class Render
{
public:
	//ƒVƒ“ƒOƒ‹ƒgƒ“
	static Render& GetInstance()
	{
		static Render instance;
		return instance;
	}

	void Draw()const;

private:
	Render() = default;
};