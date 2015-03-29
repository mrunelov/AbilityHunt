/*
	Class that holds the Map, all Actors and the Player
*/

#ifndef AH_WORLD_H
#define AH_WORLD_H
#include "environment.h"
#include "friendlyenvironment.h"

namespace ah
{
	class World
	{
	public:
		World();
		~World();

		void initialize();

		void update();
		void draw();

		std::shared_ptr<Environment> getEnvironment(const std::string name);
		
		std::shared_ptr<Environment> environment_;
		std::shared_ptr<Actor> player_;
		std::shared_ptr<Actor> elliot_;
        std::vector<std::shared_ptr<Environment>> environments_;

        bool quit();

    protected:
    private:
    	bool quit_;

	};

} // namespace ah

#endif // AH_WORLD_H

