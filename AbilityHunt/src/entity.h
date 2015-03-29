/*
	An entity has information about how it is described,
	how it is identified in the game,
	and is also updateable
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>
#include <unordered_map>

#include "Interaction/console.h"
#include "Interaction/narrator.h"

namespace ah {


class Entity 
{
public:

	Entity(const std::string& name = "(name)", 
		const std::string& shortdescr = "(brief)", 
		const std::string& longdescr = "(description)");
	Entity(const Entity& other);
	Entity(const Entity&& other);
	Entity& operator=(const Entity& other);
	Entity& operator=(const Entity&& other);

    virtual ~Entity();


	/*
		the name of the entity, work as an identifier too
	*/
	virtual std::string name() const { return name_; }

	/*
		A brief description of the entity.

		examples:
			"You found a path down along a small river"
			"You find yourself in a misty meadow."
			"A worn piece of cloth"

	*/
	virtual std::string short_description() const { return short_descr_; }

	/*
		A more thorough description of the entity.

		examples:
			"The rives seems to lead towards... Along the river there is a ..."
			"Closer up, you see that it is covered in a thin layer of ooze."
	*/
	virtual std::string long_description() const { return long_descr_; }

	/*
		called automatically when entering rooms etc.
		defaults to brief the short description but can be overidden
	*/
	virtual void brief() { Console::instance().write(short_description()); }

	/*
		Longer description triggered when actively choosing it, 
		for instance when looking around or listening

		defaults to describe the long description, butcan be overidden

	*/
	virtual void describe() { Console::instance().write(long_description()); }

	/*
		called once each frame
	*/
	virtual void update() = 0;

	bool notable() const;
	void make_notable(bool value);


	bool operator==(const Entity& other) const;
	bool operator!=(const Entity& other) const;

protected:
	std::string name_;
	std::string short_descr_;
	std::string long_descr_;

	bool notable_;
private:

};

} // end namespace

#endif
