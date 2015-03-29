#include "entity.h"

using std::string;

namespace ah
{

Entity::~Entity() {}

Entity::Entity(const std::string& name, const std::string& shortdescr, const std::string& longdescr)
	: name_(name),
	  short_descr_(shortdescr),
	  long_descr_(longdescr),
	  notable_(false)
{
}

//copy constructor and asgn
Entity::Entity(const Entity& other) 
	: name_(other.name_),
	  short_descr_(other.short_descr_),
	  long_descr_(other.long_descr_),
	  notable_(false)
{
	//std::cout << ("=> Copy Constructor") << std::endl;
}

Entity& Entity::operator=(const Entity& other)
{
	name_ = other.name_;
	short_descr_ = other.short_descr_;
	long_descr_ = other.long_descr_;
	notable_ = other.notable_;

	//std::cout << ("=> Copy Assignment") << std::endl;
	return *this;
}

//move constructor and asgn
Entity::Entity(const Entity&& other)
	: name_(other.name_),
	  short_descr_(other.short_descr_),
	  long_descr_(other.long_descr_),
	  notable_(other.notable_)
{
	//std::cout << ("=> Move Constructor") << std::endl;
}

Entity& Entity::operator=(const Entity&& other)
{
	name_ = other.name_;
	short_descr_ = other.short_descr_;
	long_descr_ = other.long_descr_;
	notable_ = other.notable_;

	//std::cout << ("=> Move Assignment") << std::endl;
	return *this;	
}

bool Entity::notable() const
{
	return notable_;
}
void Entity::make_notable(bool value)
{
	notable_ = value;
}

bool Entity::operator==(const Entity& other) const 
{
	return name() == other.name();
}

bool Entity::operator!=(const Entity& other) const 
{
	return name() != other.name();
}

} // namespace ah
