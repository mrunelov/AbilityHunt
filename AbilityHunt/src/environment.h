/*
	An environment is a part of a map, consisting of cells (floor-tiles) and
	a vector of active actors in the environment
*/
#ifndef AH_ENVIRONMENT_H
#define AH_ENVIRONMENT_H

#include <vector>
#include <memory>

#include "actor.h"
#include "item.h"
#include "path.h"
#include "entity.h"

namespace ah
{

const std::string EMPTY = " ";

class Environment : public Entity, public std::enable_shared_from_this<Environment> {
public:

    // 1D stuff
	std::vector<std::shared_ptr<Actor>> actors;
    std::vector<Path> paths;
    std::vector<Item> items;

	Environment();
    Environment(const std::string& name, const std::string& shortdescr, const std::string& longdescr);
	virtual ~Environment() = default;

    //inherited from Entity
	virtual void update() override;
    virtual void brief() override;
    virtual void describe() override;
	virtual bool is_friendly() { return false; }

    // Connections etc
    void addPath(Path);
    void enter(std::shared_ptr<ah::Actor>);
    //void enter_at_update(std::shared_ptr<ah::Actor>);
    void leave(std::shared_ptr<ah::Actor>&);

    //Items
    void add_item(Item);

    void move_to_random_neighbour(std::shared_ptr<Actor>);
    std::shared_ptr<Environment> get_random_neighbour();

protected:
private:
    std::vector<std::shared_ptr<Actor>> actors_that_left;
    std::vector<std::shared_ptr<Actor>> actors_that_entered;

};

} // namespace ah

#endif // AH_ENVIRONMENT_H
