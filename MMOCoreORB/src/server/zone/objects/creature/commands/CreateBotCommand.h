#ifndef CREATEBOTCOMMAND_H_
#define CREATEBOTCOMMAND_H_

#include "QueueCommand.h"
#include "server/zone/managers/playerbots/PlayerbotManager.h"

class CreateBotCommand : public QueueCommand {
public:
    CreateBotCommand(const String& name, ZoneProcessServer* server)
        : QueueCommand(name, server) {
    }

    int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
        if (!checkStateMask(creature))
            return INVALIDSTATE;

        if (!checkInvalidLocomotions(creature))
            return INVALIDLOCOMOTION;

        // Only staff should be able to use this for now
        if (!creature->getPlayerObject()->isPrivileged()) {
            creature->sendSystemMessage("You must be privileged to use this command.");
            return GENERALERROR;
        }

        StringTokenizer args(arguments.toString());
        if (!args.hasMoreTokens()) {
            creature->sendSystemMessage("Usage: /createbot <name>");
            return GENERALERROR;
        }

        String botName = args.getStringToken();

        ManagedReference<CreatureObject*> bot = server::zone::managers::playerbots::PlayerbotManager::instance()->createBot(botName);

        if (bot != nullptr) {
            creature->sendSystemMessage("Bot \\#00FF00" + botName + "\\#FFFFFF created successfully.");
            return SUCCESS;
        } else {
            creature->sendSystemMessage("Failed to create bot.");
            return GENERALERROR;
        }
    }
};

#endif // CREATEBOTCOMMAND_H_