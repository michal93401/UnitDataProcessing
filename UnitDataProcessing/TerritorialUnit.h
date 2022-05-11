#pragma once
#include <string>

class TerritorialUnit {
public:
	TerritorialUnit(std::wstring officialTitle, std::wstring code, std::wstring type);
private:
	std::wstring officialTitle_;
	std::wstring code_;
	std::wstring type;
};