#pragma once

template<typename ObjectType>
class Filter
{
public:
	virtual bool pass(const ObjectType& object) = 0;
};