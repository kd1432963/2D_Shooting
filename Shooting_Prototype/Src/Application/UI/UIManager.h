#pragma once

class UIManager
{
public:

	UIManager() { Init(); }
	
	void Update();
	void Draw2D(int score);

private:

	void Init();

};