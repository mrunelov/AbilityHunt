#include "path.h"

namespace ah
{

Path::Path(int to, const std::string& name, const std::string& entrance, const std::string& pathdescription)
	: Entity(name, entrance, pathdescription),
	  to_(to),
	  has_password_(false)
{
}

bool Path::openTo(const Actor& actor) const
{
	if(!actor.is_player())
		return true;

	//player needs item?

	//player needs code?
	if(has_password_)
	{
		Console::instance().writeLine("password required");
		Console::instance().indent();
		//Console::instance().write("pass: ");
		std::string input = Console::instance().readString();
		Console::instance().dedent();
		if(input ==password_)
		{
			Console::instance().writeLineStop("Check!");
			return true;
		}
		else
		{
			Console::instance().writeLineStop("Incorrect.");
			return false;
		}
	}

	return true;

}

Path::~Path()
{

}

void Path::setPassword(const std::string& pass)
{
	has_password_ = true;
	password_ = pass;
}

} //namespace ah
