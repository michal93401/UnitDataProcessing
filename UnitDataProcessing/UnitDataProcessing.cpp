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
            searchByName();
            break;
        case 2:
            searchMakingFilter();
            break;
        case 3:
            searchUsingMadeFilter();
            break;
        case 4:
            run_ = false;
            break;
        }

        if (run_) {
            std::wstring contin;
            std::wcout << std::wstring{ L"\nPokračovať ďalej na voľbu možností? : [Y/N]" } << std::endl;
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
    //std::wcin >> row;
    _setmode(_fileno(stdin), _O_U16TEXT);
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
    for (int i = 0; i <= int(TerritorialUnitTypes::Town); i++)
    {
        std::wcout << unitTypeToString(TerritorialUnitTypes(i)) << std::wstring{ L" : " } << i << std::endl;
    }
    TerritorialUnitTypes type = TerritorialUnitTypes(convertUserInputToNumber(int(TerritorialUnitTypes::Town)));
    std::wcout << std::wstring{ L"\nZadajte meno vybranej jednotky : " } << std::endl;
    auto name = getUserRequest();
    TerritorialUnit* unit = nullptr;
    if (type == TerritorialUnitTypes::Town) {
        unit = findCityByName(name);
    }
    else {
        unit = data_->findUnitByName(type, name);
    }
    if (unit != nullptr) {
        writeUnitInfo(unit);
    }
    else {
        std::wcout << std::wstring{ L"Táto územná jednotka nebola nájdená." } << std::endl;
    }
}

void UnitDataProcessing::searchMakingFilter()
{
    std::wcout << std::wstring{ L"\n--------------------------------------------------------" } << std::endl;
    std::wstring contin = { L"" };
    TerritorialUnitTypes type1 = TerritorialUnitTypes(0);
    TerritorialUnitTypes type2 = TerritorialUnitTypes(0);
    Education education1 = Education(0);
    Education education2 = Education(0);
    auto filters = new Filter_CompositeAND();
    auto filteredContainer = data_->getAllUnits();

    std::wcout << std::wstring{ L"Použiť filter UJTyp? [Y/N]" } << std::endl;
    contin = getUserRequest();
    bool ujtype = contin == std::wstring{ L"n" } || contin == std::wstring{ L"N" } ? false : true;
    if (ujtype) {
        std::wcout << std::wstring{ L"\nZvolte typ územnej jednotky." } << std::endl;
        for (int i = 0; i <= int(TerritorialUnitTypes::Town); i++)
        {
            std::wcout << unitTypeToString(TerritorialUnitTypes(i)) << std::wstring{ L" : " } << i << std::endl;
        }
        type1 = TerritorialUnitTypes(convertUserInputToNumber(int(TerritorialUnitTypes::Town)));
        auto criterium = new CriteriaTerritorialUnitType();
        auto filter = new Filter_TypeEquals<TerritorialUnit, TerritorialUnitTypes>(criterium, type1);
        //filteredContainer = data_->getFilteredUnits(*filter, type1);
        filters->registerFilter(filter);
        //criterium = nullptr;
        //delete filter;
    }

    std::wcout << std::wstring{ L"Použiť filter UJPríslušnosť? [Y/N]" } << std::endl;
    contin = getUserRequest();
    bool ujaffil = contin == std::wstring{ L"n" } || contin == std::wstring{ L"N" } ? false : true;
    if (ujaffil) {
        //if (type == TerritorialUnitTypes(-1)) {
            for (int i = 0; i <= int(TerritorialUnitTypes::Town); i++)
            {
                std::wcout << unitTypeToString(TerritorialUnitTypes(i)) << std::wstring{ L" : " } << i << std::endl;
            }
            type2 = TerritorialUnitTypes(convertUserInputToNumber(int(TerritorialUnitTypes::Town)));
        //}
        std::wcout << std::wstring{ L"\nZadajte meno vybranej jednotky : " } << std::endl;
        auto name = getUserRequest();
        TerritorialUnit* unit = nullptr;
        if (type2 == TerritorialUnitTypes::Town) {
            unit = findCityByName(name);
        }
        else {
            unit = data_->findUnitByName(type2, name);
        }
        if (unit == nullptr) {
            std::wcout << std::wstring{ L"Táto územná jednotka nebola nájdená." } << std::endl;
        }
        auto criterium = new CriteriaTerritorialUnitAffiliation(*unit);
        auto filter = new Filter_CriteriaAffi(criterium);
        //filteredContainer = filterOnContainer(*filter, filteredContainer);
        filters->registerFilter(filter);
        //criterium = nullptr;
        //delete filter;
    }

    std::wcout << std::wstring{ L"Použiť filter UJVzdelaniePočet? [Y/N]" } << std::endl;
    contin = getUserRequest();
    bool ujeducount = contin == std::wstring{ L"n" } || contin == std::wstring{ L"N" } ? false : true;
    int mincount = -1;
    int maxcount = -1;
    if (ujeducount) {
        for (int i = 0; i <= int(Education::NEZISTENE); i++) // i = 1?
        {
            std::wcout << educationToString(Education(i)) << std::wstring{ L": " } << i << std::endl;
        }
        education1 = Education(convertUserInputToNumber(int(Education::NEZISTENE)));
        std::wcout << std::wstring{ L"Min počet: [-1 ak nechcete špecifikovať]" };
        try
        {
            mincount = std::stoi(getUserRequest());
        }
        catch (const std::exception&)
        {
            mincount = -1;
        }
        std::wcout << std::wstring{ L"Max počet: [-1 ak nechcete špecifikovať]" };
        try
        {
            maxcount = std::stoi(getUserRequest());
        }
        catch (const std::exception&)
        {
            maxcount = -1;
        }
        auto criterium = new CriteriaTerritorialUnitEducationCount(education1);
        if (mincount != -1 && maxcount != -1) {
            auto filter = new Filter_Range<TerritorialUnit, int>(criterium, mincount, maxcount);
            //filteredContainer = filterOnContainer(*filter, filteredContainer);
            filters->registerFilter(filter);
            //criterium = nullptr;
            //delete filter;
        }
        if (mincount != -1 && maxcount == -1) {
            auto filter = new Filter_TypeMore<TerritorialUnit, int>(criterium, mincount);
            //filteredContainer = filterOnContainer(*filter, filteredContainer);
            filters->registerFilter(filter);
            //criterium = nullptr;
            //delete filter;
        }
        if (mincount == -1 && maxcount != -1) {
            auto filter = new Filter_TypeLess<TerritorialUnit, int>(criterium, maxcount);
            //filteredContainer = filterOnContainer(*filter, filteredContainer);
            filters->registerFilter(filter);
            //criterium = nullptr;
            //delete filter;
        }
    }

    std::wcout << std::wstring{ L"Použiť filter UJVzdelaniePodiel? [Y/N]" } << std::endl;
    contin = getUserRequest();
    bool ujeduportion = contin == std::wstring{ L"n" } || contin == std::wstring{ L"N" } ? false : true;
    int minportion = -1;
    int maxportion = -1;
    if (ujeduportion) {
        for (int i = 0; i <= int(Education::NEZISTENE); i++) // i = 1?
        {
            std::wcout << educationToString(Education(i)) << std::wstring{ L": " } << i << std::endl;
        }
        education2 = Education(convertUserInputToNumber(int(Education::NEZISTENE)));
        std::wcout << std::wstring{ L"Min percentualny počet: [-1 ak nechcete špecifikovať]" };
        try
        {
            minportion = std::stoi(getUserRequest());
        }
        catch (const std::exception&)
        {
            minportion = -1;
        }
        std::wcout << std::wstring{ L"Max percentualny počet: [-1 ak nechcete špecifikovať]" };
        try
        {
            maxportion = std::stoi(getUserRequest());
        }
        catch (const std::exception&)
        {
            maxportion = -1;
        }
        auto criterium = new CriteriaTerritorialUnitEducationPortion(education1);
        if (mincount != -1 && maxcount != -1) {
            auto filter = new Filter_Range<TerritorialUnit, double>(criterium, mincount, maxcount);
            //filteredContainer = filterOnContainer(*filter, filteredContainer);
            filters->registerFilter(filter);
            //criterium = nullptr;
            //delete filter;
        }
        if (mincount != -1 && maxcount == -1) {
            auto filter = new Filter_TypeMore<TerritorialUnit, double>(criterium, mincount);
            //filteredContainer = filterOnContainer(*filter, filteredContainer);
            filters->registerFilter(filter);
            //criterium = nullptr;
            //delete filter;
        }
        if (mincount == -1 && maxcount != -1) {
            auto filter = new Filter_TypeLess<TerritorialUnit, double>(criterium, maxcount);
            //filteredContainer = filterOnContainer(*filter, filteredContainer);
            filters->registerFilter(filter);
            //criterium = nullptr;
            //delete filter;
        }
    }

    filteredContainer = filterOnContainer(*filters, filteredContainer);
    std::wcout << std::wstring{ L"Usporiadať? [Y/N]" } << std::endl;
    contin = getUserRequest();
    bool sorting = contin == std::wstring{ L"n" } || contin == std::wstring{ L"N" } ? false : true;
    int sortNumber = -1;
    bool vzostupne = true;
    if (sorting) {
        std::wcout << 1 << std::wstring{ L" : Podľa Názvu" } << std::endl;
        std::wcout << 2 << std::wstring{ L" : Podľa VzdelaniaPočet" } << std::endl;
        std::wcout << 3 << std::wstring{ L" : Podľa VzdelaniaPodiel" } << std::endl;
        sortNumber = convertUserInputToNumber(3);
        std::wcout << std::wstring{ L"Vzostupne? [Y/N]" } << std::endl;
        contin = getUserRequest();
        if (contin == std::wstring{ L"n" } || contin == std::wstring{ L"N" }) {
            vzostupne = false;
        }
        switch (sortNumber)
        {
        case 1: 
        {
            auto criteria = new CriteriaTerritorialUnitName();
            userSort<TerritorialUnit, std::wstring>(filteredContainer, criteria, vzostupne);
            delete criteria;
        }
        case 2:
        {
            auto criteria = new CriteriaTerritorialUnitEducationCount(education1);
            userSort<TerritorialUnit, int>(filteredContainer, criteria, vzostupne);
            delete criteria;
        }
        case 3:
        {
            auto criteria = new CriteriaTerritorialUnitEducationPortion(education2);
            userSort<TerritorialUnit, double>(filteredContainer, criteria, vzostupne);
            delete criteria;
        }
        default:
            break;
        }
    }

    for (auto item : *filteredContainer) {
        std::wcout << std::wstring{ L"-------------------------------------------------------" } << std::endl;
        writeUnitInfo(item);
    }
    delete filters;
    contin.~basic_string();
    delete filteredContainer;
}

void UnitDataProcessing::searchUsingMadeFilter()
{
    std::wcout << std::wstring{ L"\n--------------------------------------------------------" }  << std::endl;
    std::wcout << 1 << std::wstring{ L" = Informácie o obci Frička." } << std::endl;
    /*std::wcout << 2 << std::wstring{ L" = Obce s počtom vysokoškolákov aspoň 3000." } << std::endl;
    std::wcout << 3 << std::wstring{ L" = Obce s podielom ľudí bez vzdelania menej ako 5%." } << std::endl;
    std::wcout << 4 << std::wstring{ L" = Počet stredoškolsky vzdelaných nad 1000 a podiel vysokoškolsky vzdelaných viac ako 30%." } << std::endl;
    std::wcout << 5 <<std::wstring{ L" = Všetky obce podľa názvu vzostupne." } << std::endl;
    std::wcout << 6 << std::wstring{ L" = Všetky obce podľa počtu obyvateľov s učňovským vzdelaním medzi 100 a 200 zostupne." } << std::endl;
    std::wcout << 7 << std::wstring{ L" = Všetky obce podľa podielu obyvateľov s vyšším odborným vzdelaním s podielom najviac 5%." } << std::endl;
    std::wcout << 8 << std::wstring{ L" = Informácie o okrese Trnava." } << std::endl;
    std::wcout << 9 << std::wstring{ L" = Informácie o Prešovskom kraji." } << std::endl;
    std::wcout << 10 << std::wstring{ L" = Informácie o okresoch s počtom vysokoškolsky vzdelaných ľudí aspoň 5000." } << std::endl;
    std::wcout << 11 << std::wstring{ L" = Informácie o krajoch s podielom ľudí bez vzdelania menej ako 5%." } << std::endl;
    std::wcout << 12 << std::wstring{ L" = Informácie o obciach Žilinského kraja, kde počet stredoškolsky vzdelaných ľudí je nad 1000 a podiel vysokoškolsky vzdelaných ľudí je viac ako 30%." } << std::endl;
    std::wcout << 13 << std::wstring{ L" = Informácie o okresoch Košického kraja, kde počet obyvateľov so stredným vzdelaním je aspoň 50000." } << std::endl;
    std::wcout << 14 << std::wstring{ L" = Všetky obce Banskobystrického kraja podľa názvu vzostupne." } << std::endl;
    std::wcout << 15 << std::wstring{ L" = Všetky okresy Nitrianskeho kraja podľa názvu." } << std::endl;
    std::wcout << 16 << std::wstring{ L" = Všetky kraje podľa počtu obyvateľov s učňovským vzdelaním s počom najviac 200000." } << std::endl;
    std::wcout << 17 << std::wstring{ L" = Všetky okresy podľa podielu obyvateľov s vyšším odborným vzdelaním s podielom najviac 3% vzostupne." } << std::endl;*/
    std::wcout << std::wstring{ L"\n--------------------------------------------------------" } << std::endl;

    int choice = convertUserInputToNumber(1);
    structures::ArrayList<TerritorialUnit*>* filteredUnits = nullptr;
    switch (choice)
    {
    case 1:
    {
        auto town = findCityByName(std::wstring{ L"Frička" });
        writeUnitInfo(town);
        town = nullptr;
        break;
    }
    case 2:
    {
        auto criteria = getCriteriaEduCount(Education::VYSOKE);
        auto filter = new Filter_TypeEqualMore<TerritorialUnit, int>(criteria, 3000);
        filteredUnits = data_->getFilteredUnits(*filter, TerritorialUnitTypes::Town);
        delete criteria;
        delete filter;
        break;
    }
    default:
        break;
    }

    filteredUnits = nullptr;
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
        if (action > 0 && action <= max) {
            break;
        }
        else {
            std::wcout << std::wstring{ L"Zvolte si akciu z dostupných možností." } << std::endl;
        }
    }
    return action;
}

Town* UnitDataProcessing::findCityByName(std::wstring name)
{
    Town* town = data_->findCityByName(name);
    if (town != nullptr) {
        auto duplicates = data_->findCityDuplicates(name);
        if (!duplicates->isEmpty()) {
            duplicates->insert(town, 0);
            std::wcout << std::wstring{ L"Našlo sa viac obcí s daným názvom. Špecifikujte, ktorú ste hľadali." } << std::endl;
            for (int i = 0; i < duplicates->size(); i++) //i = 1 ?
            {
                auto temp = duplicates->at(i);
                std::wcout << duplicates->at(i)->getHigherUnit()->getOfficialTitle() << std::wstring{ L" : " };
                std::wcout << duplicates->at(i)->getOfficialTitle() << std::wstring{ L" : "} << duplicates->at(i)->getCode() << std::wstring{ L" : " } << (i + 1) << std::endl;
            }
            int choice = convertUserInputToNumber(duplicates->size());
            return duplicates->at(choice - 1);
        }
    }
    return town;
}

void UnitDataProcessing::writeUnitInfo(TerritorialUnit* unit)
{
    std::wcout << unitTypeToString(unit->getType()) << std::wstring{ L": " } << unit->getOfficialTitle() << std::wstring{ L" " } << unit->getCode() << std::endl;
    std::wcout << std::wstring{ L"Štatistika o vzdelaní: " } << std::endl;
    for (int i = 0; i <= int(Education::NEZISTENE); i++) // i = 1?
    {
        std::wcout << educationToString(Education(i)) + std::wstring{ L": " } << unit->getEducation(Education(i)) << std::endl;
    }
    std::wcout << unit->getOfficialTitle() << std::wstring{ L" - Patrí do vyššieho celku: " } << std::endl;
    auto parent = unit->getHigherUnit();
    while (parent != nullptr) {
        std::wcout << unitTypeToString(parent->getType()) << std::wstring{ L": " } << parent->getOfficialTitle() << std::endl;
        parent = parent->getHigherUnit();
    }
}

CriteriaTerritorialUnitAffiliation* UnitDataProcessing::getCriteriaAff(TerritorialUnit& unit)
{
    return new CriteriaTerritorialUnitAffiliation(unit);
}
CriteriaTerritorialUnitEducationCount* UnitDataProcessing::getCriteriaEduCount(Education education) {
    return new CriteriaTerritorialUnitEducationCount(education);
}
CriteriaTerritorialUnitEducationPortion* UnitDataProcessing::getCriteriaEduPortion(Education education) {
    return new CriteriaTerritorialUnitEducationPortion(education);
}
CriteriaTerritorialUnitName* UnitDataProcessing::getCriteriaName() {
    return new CriteriaTerritorialUnitName();
}
CriteriaTerritorialUnitType* UnitDataProcessing::getCriteriaType() {
    return new CriteriaTerritorialUnitType();
}

structures::ArrayList<TerritorialUnit*>* UnitDataProcessing::filterOnContainer(Filter<TerritorialUnit>& filter, structures::ArrayList<TerritorialUnit*>* units) {
    auto filtered = new structures::ArrayList<TerritorialUnit*>();
    for (auto item : *units) {
        if (filter.pass(*item)) {
            filtered->add(item);
        }
    }
    delete units;
    return filtered;
}

template<typename T, typename ValueType>
void UnitDataProcessing::userSort(structures::ArrayList<TerritorialUnit*>* units, CriteriaTerritorialUnit<ValueType>* criteria, bool vzostupne) {
    if (units->size() == 0) {
        std::wcout << std::wstring{ L"Nič na triedenie! Neboli nájdené žiadne jednotky." } << std::endl;
    }
    else {
        auto quick = new structures::QuickSort<TerritorialUnit, ValueType>();
        //auto sorterr = new Sorter<ValueType>(criteria);
        //sorterr->sort(units, vzostupne);
        //auto shell = new structures::ShellSort<TerritorialUnit, ValueType>();
        quick->sort(units, criteria, vzostupne);
        //shell->sort(units, criteria, vzostupne);
    }
}

//template<typename ResultType>
//CriteriaTerritorialUnit<ResultType>* UnitDataProcessing::getCriteriaByType(int type, TerritorialUnit& unit, Education education) {
//    /*if (type == -1) {
//        std::wcout << std::wstring{ L"Critérium príslušnosť" } << 1 << std::endl;
//        std::wcout << std::wstring{ L"Critérium počtu ľudí so vzdelaním" } << 2 << std::endl;
//        std::wcout << std::wstring{ L"Critérium podielu ľudí so vzdelaním" } << 3 << std::endl;
//        std::wcout << std::wstring{ L"Critérium meno" } << 4 << std::endl;
//        std::wcout << std::wstring{ L"Critérium typ" } << 5 << std::endl;
//        type = convertUserInputToNumber(5);
//    }*/
//    switch (type)
//    {
//    case 1:
//    {
//        auto c1 = new CriteriaTerritorialUnitAffiliation(unit);
//        return c1;
//    }
//    default:
//        break;
//    }
//}

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
        return { L"" };
    }
}

std::wstring genderToString(Pohlavie type) {
    switch (type) {
    case Pohlavie::Man:
        return { L"mužov" };
    case Pohlavie::Woman:
        return { L"žien" };
    default:
        return { L"" };
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
        return { L"" };
    }
}
