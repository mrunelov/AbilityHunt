/*
	The Console handles all text streaming to present 
	information to the user. 

*/

#ifndef AH_CONSOLE_H
#define AH_CONSOLE_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <memory>

#include "command.h"
#include "commandParser.h"

namespace ah
{

class Console
{
public:

	static const int SPEED_VERY_SLOW;
	static const int SPEED_SLOW;
	static const int SPEED_NORMAL;
	static const int SPEED_FAST;
	static const int SPEED_INSTANT;
	static const int SPEED_DEFAULT;

	static const std::string SPACE;	
	static const std::string TAB;
	static const std::string NEWLINE;
	static const std::string ENDL;
	//static const std::string PROMPT;	

	static const std::string QUOTE_FORMAT;
	static const std::string TOOLTIP_FORMAT;

	static Console& instance() //singleton
	{
        static Console consoleInstance;
        //consoleInstance = new Console(std::cin, std::cout);
        return consoleInstance;
	}

	void indent(int x = 1);
	void dedent(int x = 1);
	int currentIndention();
	void forceIndent();
	void writeIndent();
	bool isWritingLine();
	void nextLine();
	void flush();
	void sleep(int ms);
	std::string readString();

private:
	Console();
	~Console();

	template<typename T> 
	void doWrite(const T& content, int speed, bool pressEnter, bool newline)
	{
		//new line, or continue or current
		if(!writingLine_) writeIndent(); 
		writingLine_ = true;

		if(speed == SPEED_INSTANT)
		{
			//output the content
			out_ << content; 
		}
		else
		{
			//output the content at lower speed
			std::stringstream ss;
			ss << content;
			std::string rawcontent = ss.str();
			
			int ms_per_char = 1000.0/speed;
			for(char& c : rawcontent)
			{
				out_ << c; 
				flush();
				sleep(ms_per_char);
			}
		}

		//end of line?
		if(newline) //TODO: check for Console::ENDL/Console::NEWLINE too
		{
			out_ << NEWLINE;
			writingLine_ = false;
		}

		//writing is finished. Flush
		//flush();

		if(pressEnter) //TODO: do not output the \n
		{
			enterToContinue();
		}
	}

public:
	/*
		Write content and end with linebreak.
		NO enterToConinue
	*/
	template<typename T> 
	void writeLine(const T& content, int speed = SPEED_DEFAULT)
	{
		doWrite(content, speed, false, true);
	}

	/*
		Write content, without linebreak
		NO enterToConinue
	*/
	template<typename T> 
	void write(const T& content, int speed = SPEED_DEFAULT)
	{
		doWrite(content, speed, false, false);
	}

	/*
		Write content, with linebreak
		Press Enter to continue
	*/
	template<typename T> 
	void writeLineStop(const T& content, int speed = SPEED_DEFAULT)
	{
		doWrite(content, speed, true, true);
	}

	/*
		Write content, without linebreak
		Press Enter to continue
	*/
	template<typename T> 
	void writeStop(const T& content, int speed = SPEED_DEFAULT)
	{
		doWrite(content, speed, true, false);
	}

	/*
		Stream text to the console.
		* Default speed, 
		* no linebreaks, 
		* no press enter to continue
	*/
	template<typename T> Console& operator<<(const T& v) 
	{
		doWrite(v, SPEED_DEFAULT, false, false);
		return *this;
	}

	//Input
	void enterToContinue();
	Command enterCommand();
	int choose(const std::vector<std::string>& choices);
	bool isInt(const std::string& s);
	int readInt(int a, int b);

private:
	std::istream& in_;
	std::ostream& out_;
	int indent_;
	bool writingLine_;
	CommandParser commandParser;
};



} // namespace ah







#endif // AH_CONSOLE_H
