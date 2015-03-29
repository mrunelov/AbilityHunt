#include "narrator.h"

#include <random>

#include "console.h"

namespace ah
{

// Constants
const std::string Narrator::QUOTE_FORMAT 	= "[{actor}] - {line}";
const std::string Narrator::TOOLTIP_FORMAT 	= "({tooltip})";

const std::vector<std::string> Narrator::PHRASES_NOTICE_SINGLE 			= {"One thing catches your attention: ", "You see something: "};
const std::vector<std::string> Narrator::PHRASES_NOTICE_SINGLE_ACTOR	= {"You notice someone: ", "You see someone: "};
const std::vector<std::string> Narrator::PHRASES_NOTICE_PLURAL 			= {"Several things you see are noteworthy: ", "You notice the following: "};
const std::vector<std::string> Narrator::PHRASES_NOTICE_PLURAL_ACTORS	= {"There are several actors here: ", "You notice the following actors: "};


std::string Narrator::quoteBy(const std::string& name, const std::string& line)
{
	std::string res = QUOTE_FORMAT;
	singleReplace(res, "{actor}", name);
	singleReplace(res, "{line}", line);
	return res;
}

std::string Narrator::tooltip(const std::string& tip)
{
	return singleReplace(TOOLTIP_FORMAT, "{tooltip}", tip);
}

void Narrator::tip(const std::string& tooltip)
{
	std::string thetip = singleReplace(TOOLTIP_FORMAT, "{tooltip}", tooltip);
	Console::instance().write(thetip);
}

void Narrator::quote(const std::string& name, const std::string& line)
{
	//name
	Console::instance().write("[", Console::SPEED_INSTANT);
	Console::instance().write(name, Console::SPEED_INSTANT);
	Console::instance().write("] - ", Console::SPEED_INSTANT);
	Console::instance().sleep(200);
	
	//line
	Console::instance().writeLine(line); //default speed
}

void Narrator::enumerate(const std::vector<std::string>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{

		Console::instance() << "(" << i << ") " << v[i];
		Console::instance().nextLine();
	}
}

int Narrator::dialogue(const std::string& name, const std::string& question, const std::vector<std::string>& choices)
{
	// format: "(instant)[{actor}] - (normal){line}"
	quote(name, question);
	
	if(choices.empty()) 
	{
		Console::instance().enterToContinue();
		return 0;
	}

	//options
	Console::instance().indent();
	enumerate(choices);

	//let console get the choice
	int choice = Console::instance().choose(choices); // readInt(0, choices.size());
	Console::instance().dedent();
	return choice;
}

int Narrator::dialogue(const std::string& question, const std::vector<std::string> choices)
{
	// format: "(instant)[{actor}] - (normal){line}"
	Console::instance().writeLine(question);
	
	if(choices.empty()) 
	{
		Console::instance().enterToContinue();
		return 0;
	}

	//options
	Console::instance().indent();
	enumerate(choices);

	//let console get the choice
	int choice = Console::instance().choose(choices); // readInt(0, choices.size());
	Console::instance().dedent();
	return choice;
}


void Narrator::describeNoticeActors(const std::vector<std::string>& descriptions)
{
	if(descriptions.size() == 0) return;
	if(descriptions.size() == 1)
	{
		Console::instance().write(randomPhrase(PHRASES_NOTICE_SINGLE_ACTOR));
		Console::instance().writeLine(descriptions[0]);
		return;
	}
	
	//several actors
	Console::instance().write(randomPhrase(PHRASES_NOTICE_PLURAL_ACTORS));
	for(const std::string& descr : descriptions)
	{
		Console::instance().write(descr);
		Console::instance().write(Console::SPACE);
	}
	Console::instance().nextLine();
	
}


/* Private helper functions */

std::string Narrator::randomPhrase(const std::vector<std::string>& phrases)
{
	return phrases[(rand() % phrases.size())];
}

std::string Narrator::singleReplace(const std::string& str, const std::string& pattern, const std::string& replace)
{
	std::string cpy = str;
	return cpy.replace(cpy.find(pattern), pattern.length(), replace);
}

std::string Narrator::singleReplace(std::string& str, const std::string& pattern, const std::string& replace)
{
	return str.replace(str.find(pattern), pattern.length(), replace);
}


} //namespace ah
