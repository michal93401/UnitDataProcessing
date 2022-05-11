#pragma once

template<typename ObjectType, typename ResultType>
class Criteria {
public:
	virtual ResultType evaluate(const ObjectType& object) = 0;
};