#ifndef PLAYERBOTMANAGER_H_
#define PLAYERBOTMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneProcessServer.h"

namespace server {
namespace zone {
namespace managers {
namespace playerbots {

class PlayerbotManager : public Singleton<PlayerbotManager>, public Logger {
public:
    PlayerbotManager();
    ~PlayerbotManager();

    // Create a brand new bot character
    ManagedReference<CreatureObject*> createBot(const String& name, const String& templateName = "object/creature/player/human_male.iff");

    // Future methods
    // ManagedReference<CreatureObject*> loginBot(uint64 objectID);
    // void logoutBot(CreatureObject* bot);
};

} // namespace playerbots
} // namespace managers
} // namespace zone
} // namespace server

#endif // PLAYERBOTMANAGER_H_