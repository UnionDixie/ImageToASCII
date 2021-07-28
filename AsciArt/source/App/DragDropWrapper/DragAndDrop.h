#pragma once

#include <string>
#include <queue>
#include <Windows.h>// :(
#include <SFML/System/Utf.hpp>
#include <iostream>

class DragAndDrop
{
public:
	DragAndDrop() = default;
	~DragAndDrop() = default;
	void SetHandle(HWND appHwnd);
public:
	//true if empty
	bool haveImages() const;
	std::queue<std::string>& getImageToConvert();
};

