#include "Data.h"
#include <iostream>
#include "UnitDataProcessing.h"

UnitDataProcessing::UnitDataProcessing()
{
	data_ = new Data();
	loaded_ = false;
	run_ = false;
}

UnitDataProcessing::~UnitDataProcessing()
{
	delete data_;
}

void UnitDataProcessing::load()
{
	std::string message = "";
	if (data_->loadData(message)) {
		loaded_ = true;
	}
	else {
		loaded_ = false;
		std::cout << message << std::endl;
		std::wcout << "Check file path in Data.cpp" << std::endl;
	}
}

void UnitDataProcessing::start()
{
	if (loaded_) {
		run_ = true;
		std::wcout << "Succesfully started!" << std::endl;
	}
	else {
		std::wcout << "Failed to load data!" << std::endl;
		return;
	}
	
	while (run_)
	{
		data_->print();
	}

}
