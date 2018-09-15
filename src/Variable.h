#ifndef VARIABLE_H
#define VARIABLE_H

#include "Token.h"

#include <iostream>
#include <map>
#include <string>

class Variable
{
public:
	Variable(const std::string& name);
	virtual ~Variable() {}
	virtual std::string GetClassId() const = 0;
	
	/**
	* Return the name of a variable.
	*/
	const std::string& GetName() const { return mName; }
private:
	std::string mName;
};

class IntVariable : public Variable
{
public:
	IntVariable(const std::string& name);
	virtual ~IntVariable() {}
	virtual std::string GetClassId() const override { return "IntVariable"; };
};

class ArrayVariable : public Variable
{
public:
	ArrayVariable(const std::string& name);
	virtual ~ArrayVariable();
	virtual std::string GetClassId() const override { return "ArrayVariable"; };
};

#endif