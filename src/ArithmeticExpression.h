#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H

#include "Token.h"
#include <iostream>

class ArrayVariable;
class IntVariable;

class ArithmeticExpression : public Token
{
public:
  virtual ~ArithmeticExpression() {}
};

class ConstantArithmeticExpression : public ArithmeticExpression
{
public:
	ConstantArithmeticExpression(int value);
	virtual ~ConstantArithmeticExpression() {}
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "ConstantArithmeticExpression"; };

	/**
	* Return the value of this constant.
	*/
	int GetConstantValue() { return mValue; }
private:
	int mValue;
};

class VariableArithmeticExpression : public ArithmeticExpression
{
public:
	virtual ~VariableArithmeticExpression() {}
};

class IntVariableArithmeticExpression : public VariableArithmeticExpression
{
public:
	IntVariableArithmeticExpression(IntVariable* variable);
	virtual ~IntVariableArithmeticExpression();
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "IntVariableArithmeticExpression"; };

	/**
	* Return the int variable used by this expression.
	*/
	IntVariable* GetIntVariable() { return mVariable; }
private:
	IntVariable* mVariable;
};

class ArrayVariableArithmeticExpression : public VariableArithmeticExpression
{
public:
	ArrayVariableArithmeticExpression(ArrayVariable* variable, ArithmeticExpression* index);
	virtual ~ArrayVariableArithmeticExpression();
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "ArrayVariableArithmeticExpression"; };

	/**
	* Return the array variable used by this expression.
	*/
	ArrayVariable* GetArrayVariable() { return mVariable; }

	/**
	* Return the array index used by this expression.
	*/
	ArithmeticExpression* GetArrayIndex() { return mIndex; }
private:
	ArrayVariable* mVariable;
	ArithmeticExpression* mIndex;
};

class BinaryArithmeticExpression : public ArithmeticExpression
{
public:
	BinaryArithmeticExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~BinaryArithmeticExpression();
	virtual void print(std::ostream& o) const override;
	
	/**
	* Return the arithmetic expression that is on the left hand side of a binary arithmetic operator. 
	*/
	ArithmeticExpression* const GetLhs() const { return mLhs; }
	
	/**
	* Return the arithmetic expression that is on the left hand side of a binary arithmetic operator. 
	*/
	ArithmeticExpression* const GetRhs() const { return mRhs; }
protected:
	virtual char GetOperator() const = 0;
private:
	ArithmeticExpression* mLhs;
	ArithmeticExpression* mRhs;
};

class AdditionExpression : public BinaryArithmeticExpression
{
public:
	AdditionExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~AdditionExpression() {}
	virtual std::string GetClassId() const override { return "AdditionExpression"; };
protected:
	virtual char GetOperator() const override { return '+'; }
};

class SubtractionExpression : public BinaryArithmeticExpression
{
public:
	SubtractionExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~SubtractionExpression() {}
	virtual std::string GetClassId() const override { return "SubtractionExpression"; };
protected:
	virtual char GetOperator() const override { return '-'; }
};

class MultiplicationExpression : public BinaryArithmeticExpression
{
public:
	MultiplicationExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~MultiplicationExpression() {}
	virtual std::string GetClassId() const override { return "MultiplicationExpression"; };
protected:
	virtual char GetOperator() const override { return '*'; }
};

class DivisionExpression : public BinaryArithmeticExpression
{
public:
	DivisionExpression(ArithmeticExpression* lhs, ArithmeticExpression* rhs);
	virtual ~DivisionExpression() {}
	virtual std::string GetClassId() const override { return "DivisionExpression"; };
protected:
	virtual char GetOperator() const override { return '/'; }
};

#endif