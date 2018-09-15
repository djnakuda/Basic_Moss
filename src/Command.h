#ifndef COMMAND_H
#define COMMAND_H

#include "Token.h"
#include <iostream>

class ArithmeticExpression;
class BooleanExpression;
class VariableArithmeticExpression;

class Command : public Token
{
public:
	Command(int line);
	virtual ~Command() {}

	/**
	* Return the line number of this command.
	*/
	int GetLineNumber() const { return mLineNumber; }
private:
	int mLineNumber;
};

class PrintCommand : public Command
{
public:
	PrintCommand(int line, ArithmeticExpression* exp);
	virtual ~PrintCommand();
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "PrintCommand"; };

	/**
	* Return the arithmetic expression that is being printed. 
	*/
	ArithmeticExpression* GetArithmeticExpression() { return mAexp; }
private:
	ArithmeticExpression* mAexp;
};

class LetCommand : public Command
{
public:
	LetCommand(int line, VariableArithmeticExpression* var, ArithmeticExpression* exp);
	virtual ~LetCommand();
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "LetCommand"; };

	/**
	* Return the variable whose value is changed by LET.
	*/
	VariableArithmeticExpression* GetVariableExpression() { return mVariable; }

	/**
	* Return the arithmetic expression that is assigned to a variable.
	*/
	ArithmeticExpression* GetArithmeticExpression() { return mAexp; }
private:
	VariableArithmeticExpression* mVariable;
	ArithmeticExpression* mAexp;
};

class JumpCommand : public Command
{
public:
	JumpCommand(int line, int dst);
	virtual ~JumpCommand() {}
	void PrintDestination(std::ostream& o) const;

	/**
	* Return the destination line number use by GOTO, GOSUB, and IF THEN.
	*/
	int GetDstLine() const { return mDstLine; }
private:
	int mDstLine;
};

class GoToCommand : public JumpCommand
{
public:
	GoToCommand(int line, int dst);
	virtual ~GoToCommand() {}
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "GoToCommand"; };
};

class IfThenCommand : public JumpCommand
{
public:
	IfThenCommand(int line, BooleanExpression* exp, int dst);
	virtual ~IfThenCommand();
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "IfThenCommand"; };

	/**
	* Return the boolean expression that determines whether IF THEN should trigger a jump.
	*/
	BooleanExpression* GetBooleanExpression() { return mBexp; }
private:
	BooleanExpression* mBexp;
};

class GoSubCommand : public JumpCommand
{
public:
	GoSubCommand(int line, int dst);
	virtual ~GoSubCommand() {}
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "GoSubCommand"; };
};

class ReturnCommand : public Command
{
public:
	ReturnCommand(int line);
	virtual ~ReturnCommand() {}
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "ReturnCommand"; };
};

class EndCommand : public Command
{
public:
	EndCommand(int line);
	virtual ~EndCommand() {}
	virtual void print(std::ostream& o) const override;
	virtual std::string GetClassId() const override { return "EndCommand"; };
};

#endif