#ifndef ADVICE_RECURSIVE_PARSER_H
#define ADVICE_RECURSIVE_PARSER_H

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

class ArithmeticExpression;
class ArrayVariable;
class BooleanExpression;
class Command;
class IntVariable;
class Variable;

/**
* A recursive parser for parsing BASIC program.
*/
class RecursiveParser
{
private:
	typedef std::vector<Command*> CommandSequence;
	typedef std::vector<std::string> VariableList;
	typedef std::map<std::string, IntVariable*> IntVariableMap;
	typedef std::map<std::string, ArrayVariable*> ArrayVariableMap;

public:
	/**
	* Parser a given program file that is loaded in program.
	* This will fill in lists of commands, int variable names, and array variable names. 
	* This assumes that the file is properly opened.
	*/
	RecursiveParser(std::ifstream& program);

	/**
	* Return the list of commands in the order they appear in the BASIC program.
	* Do not free any memory used by the Commands. They are freed in ~RecursiveParser().
	*/
	CommandSequence& GetCommands();

	/**
	* Return the list of all int variable names in alphabetic order.
	* The list will not contain any duplicates.
	*/
	VariableList& GetIntVariables();

	/**
	* Return the list of all array variable names in alphabetic order.
	* The list will not contain any duplicates.
	*/
	VariableList& GetArrayVariables();

	/**
	* Free all memory allocated by the parser, including commands, int variables,
	* array variables, boolean expressions, and arithmetic expressions.
	*/
	~RecursiveParser();

private:
	Command* ParseCommand(const std::string& line);
	ArithmeticExpression* ParseArithmeticExpression(std::stringstream& line);

	int GetDstLine(std::stringstream& line);
	void RemoveWhiteSpaces(std::stringstream& line);

	template<typename T>
	T* FindOrCreateVariableInMap(const std::string& name, std::map<std::string, T*>& variables);

private:
	CommandSequence mCommands;
	IntVariableMap mIntVariables;
	ArrayVariableMap mArrayVariables;
	VariableList mIntVariableList;
	VariableList mArrayVariableList;
};

#endif