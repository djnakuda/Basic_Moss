#ifndef BOOLEANEXPRESSION_H
#define BOOLEANEXPRESSION_H

#include "Token.h"
#include <iostream>

class ArithmeticExpression;

class BooleanExpression : public Token
{
public:
	virtual ~BooleanExpression() {}
};

class BinaryBooleanExpression : public BooleanExpression
{
public:
	BinaryBooleanExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~BinaryBooleanExpression();
	virtual void print(std::ostream& o) const override;

	/**
	* Return the arithmetic expression that is on the left hand side of a binary boolean operator. 
	*/
	ArithmeticExpression* const GetLhs() const { return mLhs; }

	/**
	* Return the arithmetic expression that is on the left hand side of a binary boolean operator.
	*/
	ArithmeticExpression* const GetRhs() const { return mRhs; }
protected:
	virtual char GetOperator() const = 0;
private:
	ArithmeticExpression* mLhs;
	ArithmeticExpression* mRhs;
};

class LessThanExpression : public BinaryBooleanExpression
{
public:
	LessThanExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~LessThanExpression() {}
	virtual std::string GetClassId() const override { return "LessThanExpression"; };
protected:
	virtual char GetOperator() const override { return '<'; }
};

class GreaterThanExpression : public BinaryBooleanExpression
{
public:
	GreaterThanExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~GreaterThanExpression() {}
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "GreaterThanExpression"; };
protected:
	virtual char GetOperator() const override { return '>'; }
};

class EqualToExpression : public BinaryBooleanExpression
{
public:
	EqualToExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~EqualToExpression() {}
	virtual std::string GetClassId() const override { return "EqualToExpression"; };
protected:
	virtual char GetOperator() const override { return '='; }
};

#endif