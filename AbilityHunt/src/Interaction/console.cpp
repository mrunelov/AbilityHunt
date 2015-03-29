#include "console.h"

#include <time.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "commandParser.h"

namespace ah
{

// Constants
const int Console::SPEED_VERY_SLOW	= 2;
const int Console::SPEED_SLOW		= 30;
const int Console::SPEED_NORMAL		= 70;
const int Console::SPEED_FAST		= 130;
const int Console::SPEED_INSTANT 	= 1000;
const int Console::SPEED_DEFAULT	= SPEED_FAST;

const std::string Console::SPACE 	= " ";
const std::string Console::TAB 		= "    ";
const std::string Console::NEWLINE 	= "\n";
const std::string Console::ENDL 	= "\n";

Console::Console()
	: indent_(0),
	  in_(std::cin),
	  out_(std::cout),
	  writingLine_(false),
	  commandParser()
{
}

Console::~Console()
{
}

void Console::indent(int x) 
{
	indent_ += x;
}

void Console::dedent(int x)
{
	indent_ = std::max(0, indent_ - x);
}

void Console::forceIndent()
{
	writingLine_ = false;
}

int Console::currentIndention()
{
	return indent_;
}

void Console::writeIndent()
{
	for(int i = 0; i < indent_; ++i)
		std::cout << TAB;
}

bool Console::isWritingLine()
{
	return writingLine_;
}

void Console::nextLine()
{
	out_ << ENDL;
	writingLine_ = false;
}

void Console::flush()
{
	//out_ << "flushing";
	out_ << std::flush;
}

void Console::sleep(int ms) // TODO: more precise timing
{
	if(ms < 0) return;

	clock_t finish = clock() + ms * CLOCKS_PER_SEC/1000.0;
	while(clock() < finish);
}

/* Input */

void Console::enterToContinue()
{
	in_.clear();
	in_.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	forceIndent();
}

std::string Console::readString()
{
	write("> ");
	std::string input;
	in_ >> input;
	//in_.get();
	return input;
}

int Console::readInt(int a, int b) 
{
	//cout << "(" << a << ", " << b << ")" << endl;
	int num;
	bool valid = false;
	do 
	{
		//cout << PROMPT;
		write("> ");
		in_ >> num;
		if(in_.good() && num >= a && num < b)  {
			valid = true;
		}
		forceIndent();
	} while(!valid);

	forceIndent();
	return num;
}

int Console::choose(const std::vector<std::string>& choices)
{
	int result = 0;
	bool success = false;
	while(!success)
	{
		//TODO: use getline
		std::string input = readString();
		//in_.get(); //here be dragons
		forceIndent();

		if(isInt(input))
		{
			result = std::atoi(input.c_str());
			if(result >= 0 && result < choices.size())
				success = true;
		}
		else
		{
			//find which choice it was?
			for(int i = 0; i < choices.size(); ++i)
			{
				if(input == choices[i])
				{
					result = i;
					success = true;
					break;
				}
			}
		}
	}
	return result;
}

bool Console::isInt(const std::string& s)
{
	//http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

	char * p ;
	strtol(s.c_str(), &p, 10) ;

	return (*p == 0);
}

Command Console::enterCommand()
{
    std::string input = readString();
    in_.get(); 		// Here be dragons.

    Command command = commandParser.parse(input);
    forceIndent();

    return command;
}

} // namespace ah

