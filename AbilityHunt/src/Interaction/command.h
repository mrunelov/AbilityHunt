/*
	A Command is mapped from a command input string by the CommandParser.
	It consist of an ability, the raw string that was parsed, and also 
	additional info about the input.
*/

#ifndef AH_COMMAND_H
#define AH_COMMAND_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>

#include "../abilities.h"

namespace ah
{

struct Command
{
	Command() 
	{
		//std::cout << ("=> Default Constructor") << std::endl;
	}
	
	~Command() {}

	//copy constructor and asgn
	Command(const Command& other) 
		: success(other.success),
		  raw_input(other.raw_input),
		  ability(other.ability)
	{
		//std::cout << ("=> Copy Constructor") << std::endl;
	}

	Command& operator=(const Command& other)
	{
		success = other.success;
		raw_input = other.raw_input;
		ability = other.ability;

		//std::cout << ("=> Copy Assignment") << std::endl;

		return *this;
	}

	//move constructor and asgn
	Command(const Command&& other)
		: success(other.success),
		  raw_input(other.raw_input),
		  ability(other.ability)
	{
		//std::cout << ("=> Move Constructor") << std::endl;
	}
	
	Command& operator=(const Command&& other)
	{
		success = other.success;
		raw_input = other.raw_input;
		ability = other.ability;
		//std::cout << ("=> Move Assignment") << std::endl;
		return *this;	
	}


	bool success;
	std::string raw_input;
	ability_t ability;
};

} //namespace ah

#endif //AH_COMMAND_H