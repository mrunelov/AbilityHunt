/*
	The Narrator is a static class that helps with creating sentences.
*/

#ifndef AH_NARRATOR_H
#define AH_NARRATOR_H

#include <string>
#include <vector>
#include <sstream>

namespace ah
{

class Narrator
{
public:
	static const std::string QUOTE_FORMAT;
	static const std::string TOOLTIP_FORMAT;
	static const std::vector<std::string> PHRASES_NOTICE_SINGLE;
	static const std::vector<std::string> PHRASES_NOTICE_SINGLE_ACTOR;
	static const std::vector<std::string> PHRASES_NOTICE_PLURAL;
	static const std::vector<std::string> PHRASES_NOTICE_PLURAL_ACTORS;

	static std::string quoteBy(const std::string& name, const std::string& line);
	static std::string tooltip(const std::string& tip);

	static void tip(const std::string& tooltip);
	static void quote(const std::string& name, const std::string& line);
	static void enumerate(const std::vector<std::string>& v);
	static void describeNoticeActors(const std::vector<std::string>& descriptions);
	static int dialogue(const std::string& name, const std::string& question, const std::vector<std::string>& choices);
	static int dialogue(const std::string& question, const std::vector<std::string> choices);

private:
	Narrator();
	~Narrator();

	static std::string randomPhrase(const std::vector<std::string>& phrases);
	static std::string singleReplace(const std::string&, const std::string&, const std::string&);
	static std::string singleReplace(std::string&, const std::string&, const std::string&);
};

} //namespace ah

#endif //AH_NARRATOR_H