#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

class Token
{
public:
	virtual ~Token() {}
	virtual void print(std::ostream& o) const = 0;
	virtual std::string GetClassId() const = 0;
};

#endif