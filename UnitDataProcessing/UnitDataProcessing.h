#pragma once
#include "Data.h"

class UnitDataProcessing {
public:
	UnitDataProcessing();
	~UnitDataProcessing();
	void load();
	void start();
private:
	Data* data_;
	bool loaded_;
	bool run_;
};