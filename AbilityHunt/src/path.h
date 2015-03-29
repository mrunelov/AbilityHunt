/*
	A Path is a connection between two environments - graph edges.
	They describe how the nodes (environments) are connected and
	how, if they require some item or ability to go through etc.

*/

#ifndef AH_PATH_H
#define AH_PATH_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <memory>

#include "entity.h"
#include "actor.h"

namespace ah
{

class Environment;
//typedef std::shared_ptr<Environment> EnvPtr;

class Path : public Entity
{
public:
	int to_;

	Path(int to, 
		const std::string& name, 
		const std::string& entrance,
		const std::string& pathdescription);
	virtual ~Path();

	bool openTo(const Actor& actor) const;
	void setPassword(const std::string& pass);
    virtual void update() {}

protected:
private:
	bool has_password_;
	std::string password_;

};

} //namespace ah

#endif //AH_PATH_H
