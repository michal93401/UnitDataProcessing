#pragma once

template<typename ObjectType, typename ResultType, typename ParameterType>
class ParametricCriteria
{
public:
	virtual ResultType evaluate(const ObjectType& object, const ParameterType& parameter) = 0;
};

