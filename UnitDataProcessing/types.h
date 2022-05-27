#pragma once

#include <chrono>

namespace structures
{
    using byte = unsigned char;
    using Microseconds = std::chrono::microseconds;
}

enum Education {
	BEZ_UKONCENEHO_VZDELANIA,
	ZAKLADNE,
	STREDNE_ODBORNE,
	STREDNE_MATURITA,
	VYSSIE_ODBORNE,
	VYSOKE,
	BEZ_VZDELANIA,
	NEZISTENE
};

enum class TerritorialUnitTypes {
	State,
	Region,
	District,
	Town
};

enum EVS {
	PreProductive,
	Productive,
	PostProductive
};

enum Pohlavie {
	Man,
	Woman
};