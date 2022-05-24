#pragma once
#include <string>

class TerritorialUnit {
public:
	TerritorialUnit(std::wstring officialTitle, std::wstring code, std::wstring type);
private:
	std::wstring officialTitle_;
	std::wstring code_;
	std::wstring type_;
	TerritorialUnit* higherUnit_ = nullptr;
};

inline TerritorialUnit::TerritorialUnit(std::wstring officialTitle, std::wstring code, std::wstring type) :
	officialTitle_(officialTitle), code_(code), type_(type) {
}