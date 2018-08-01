#pragma once

#include <string>
#include <vector>

class CDebug {
public:
	~CDebug();


	// Singleton Methods
	static CDebug& GetInstance();
	static void DestroyInstance();

	void Draw();

	void SetDebugText(int Line, std::string _text);

private:
	CDebug();

	// Singleton Instance
	static CDebug* s_pDebug;

	std::vector<std::string> Stringtext;

};