#ifndef FRIENDLYENV_H
#define FRIENDLYENV_H
#include "environment.h"

namespace ah {
class FriendlyEnvironment : public Environment {
public:
    FriendlyEnvironment() : Environment() {}
    FriendlyEnvironment(const std::string& name, const std::string& shortdescr, const std::string& longdescr) : Environment(name,shortdescr,longdescr) {}
    virtual ~FriendlyEnvironment();

    bool is_friendly() override { return true; }
};

} // end namespace ah


#endif
