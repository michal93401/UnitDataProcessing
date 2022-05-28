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
    _setmode(_fileno(stdout), _O_U16TEXT);
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
        switch (userRequest())
        {
        case 1:
        {
            searchByName();
            break;
        }
        case 2:
        {
            searchMakingFilter();
            break;
        }
        case 3:
        {
            searchUsingMadeFilter();
            break;
        }
        case 4:
        {
            run_ = false;
            break;
        }
        }

        if (run_) {
            std::wstring contin;
            std::wcout << "\nPokračovať ďalšiu na voľbu možností? : [Y/N]" << std::endl;
            contin = getUserRequest();
            if (contin == std::wstring { L"n" } || contin == std::wstring { L"N" }) {
                run_ = false;
            }
        }
    }
}

std::wstring UnitDataProcessing::getUserRequest()
{
    std::wstring row;
    std::getline(std::wcin, row);
    return row;
}

int UnitDataProcessing::userRequest()
{
    std::wcout << std::wstring { L"\nZvolte si akciu z dostupných možností."} << std::endl;
    int action = 0;
    while (true) {
        std::wcout << std::wstring{ L"Nájsť informácie podľa mena : " } << 1 << std::endl;
        std::wcout << std::wstring{ L"Vlastné výstupy : " } << 2 << std::endl;
        std::wcout << std::wstring{ L"Predpripravené výstupy : " } << 3 << std::endl;
        std::wcout << std::wstring{ L"Ukončiť : " } << 4 << std::endl;
        try
        {
            action = std::stoi(getUserRequest());
        }
        catch (const std::exception&)
        {
            std::wcout << std::wstring{ L"Nepodporovaný vstup! Zvolte jedno z ponúkaných čísiel." } << std::endl;
            action = 0;
        }
        if (action > 0 && action < 5) {
            break;
        }
        else {
            std::wcout << std::wstring{ L"Zvolte si akciu z dostupných možností." } << std::endl;
        }
    }
    return action;
}

void UnitDataProcessing::searchByName()
{
    std::wcout << std::wstring{ L"\nZvolte typ územnej jednotky." } << std::endl;
    for (int i = 1; i <= int(TerritorialUnitTypes::Town); i++)
    {
        std::wcout << unitTypeToString(TerritorialUnitTypes(i)) << std::wstring{ L" : " } << i << std::endl;
    }
    TerritorialUnitTypes type = TerritorialUnitTypes(convertUserInputToNumber(int(TerritorialUnitTypes::Town)));
    std::wcout << std::wstring{ L"Zadajte meno vybranej jednotky : " } << std::endl;
    auto name = getUserRequest();
    TerritorialUnit* unit = nullptr;
    if (type == TerritorialUnitTypes::Town) {
        unit = findCityByName(name);
    }
    else {
        unit = data_->findUnitByName(type, name);
    }
    if (unit != nullptr) {
        writeUnitInfo(name);
    }
    else {
        std::wcout << std::wstring{ L"Táto územná jednotka nebola nájdená." } << std::endl;
    }
}

void UnitDataProcessing::searchMakingFilter()
{
}

void UnitDataProcessing::searchUsingMadeFilter()
{
}

int UnitDataProcessing::convertUserInputToNumber(int max)
{
    int action = 0;
    while (true) {
        try
        {
            action = std::stoi(getUserRequest());
        }
        catch (const std::exception&)
        {
            std::wcout << std::wstring{ L"Nepodporovaný vstup! Zvolte jedno z ponúkaných čísiel." } << std::endl;
            action = 0;
        }
        if (action > 0 && action < max) {
            break;
        }
        else {
            std::wcout << std::wstring{ L"Zvolte si akciu z dostupných možností." } << std::endl;
        }
    }
    return action;
}

std::wstring educationToString(Education type) {
    switch (type) {
    case Education::BEZ_UKONCENEHO_VZDELANIA:
        return { L"Bez ukončeného vzdelania od 0 do 14 rokov" };
    case Education::ZAKLADNE:
        return { L"Základné vzdelanie" };
    case Education::STREDNE_ODBORNE:
        return { L"Stredné odborné vzdelanie" };
    case Education::STREDNE_MATURITA:
        return { L"Stredné vzdelanie s maturitou" };
    case Education::VYSSIE_ODBORNE:
        return { L"Vyššie odborné vzdelanie" };
    case Education::VYSOKE:
        return { L"Vysokoškolské vzdelanie" };
    case Education::BEZ_VZDELANIA:
        return { L"Bez ukončeného vzdelania nad 15 rokov (vrátane)" };
    case Education::NEZISTENE:
        return { L"Nezistené vzdelanie" };
    default:
        return { L"Neidentifikované vzdelanie" };
    }
}

std::wstring genderToString(Pohlavie type) {
    switch (type) {
    case Pohlavie::Man:
        return { L"mužov" };
    case Pohlavie::Woman:
        return { L"žien" };
    default:
        return { L"Neidentifikované pohlavie" };
    }
}

std::wstring unitTypeToString(TerritorialUnitTypes type) {
    switch (type) {
    case TerritorialUnitTypes::Town:
        return { L"obec" };
    case TerritorialUnitTypes::District:
        return { L"okres" };
    case TerritorialUnitTypes::Region:
        return { L"kraj" };
    case TerritorialUnitTypes::State:
        return { L"štát" };
    default:
        return { L"Neidentifikovaná územná jednotka" };
    }
}
