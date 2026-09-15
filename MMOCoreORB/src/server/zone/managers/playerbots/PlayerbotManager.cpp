#include "PlayerbotManager.h"
#include "PlayerbotSession.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/ServerCore.h"

PlayerbotManager::PlayerbotManager() : Logger("PlayerbotManager") {
    setLogging(true);
    setGlobalLogging(true);
}

PlayerbotManager::~PlayerbotManager() {
}

ManagedReference<CreatureObject*> PlayerbotManager::createBot(const String& name, const String& templateName) {
    ZoneServer* zoneServer = ServerCore::getZoneServer();
    if (zoneServer == nullptr) {
        error("ZoneServer is null");
        return nullptr;
    }

    // 1. Create a fake session
    ZoneProcessServer* processServer = zoneServer->getZoneProcessServer();
    PlayerbotSession* botSession = new PlayerbotSession(processServer);

    // 2. Create the CreatureObject (player)
    ManagedReference<CreatureObject*> bot = zoneServer->createObject(templateName.hashCode(), 2).castTo<CreatureObject*>();

    if (bot == nullptr) {
        error("Failed to create bot CreatureObject with template: " + templateName);
        delete botSession;
        return nullptr;
    }

    Locker locker(bot);

    // 3. Basic initialization
    bot->createChildObjects();
    bot->setCustomObjectName(name, false);

    // 4. Link the session to the player
    botSession->setPlayer(bot);
    bot->setClient(botSession);

    // 5. Get PlayerObject and do basic setup
    ManagedReference<PlayerObject*> ghost = bot->getPlayerObject();
    if (ghost != nullptr) {
        // You can set account ID later. For now we use a dummy one.
        ghost->setAccountID(999999); // temporary
    }

    // 6. Place the bot in the world (Example: Tutorial planet or Corellia)
    // For first test we just leave it without inserting into a zone yet.

    info("Successfully created bot: " + name, true);

    return bot;
}