#ifndef PLAYERBOTSESSION_H_
#define PLAYERBOTSESSION_H_

#include "server/zone/ZoneClientSession.h"
#include "server/zone/ZoneProcessServer.h"

namespace server {
namespace zone {
namespace managers {
namespace playerbots {

class PlayerbotSession : public ZoneClientSession {
public:
    PlayerbotSession(ZoneProcessServer* serv);
    virtual ~PlayerbotSession();

    // Override to prevent real network activity
    virtual void disconnect(bool lockPlayer = true) override;
    virtual void sendMessage(BaseMessage* msg) override;
    virtual void sendMessage(StandaloneBaseMessage* msg) override;

    bool isPlayerBot() const {
        return true;
    }
};

} // namespace playerbots
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::playerbots;

#endif // PLAYERBOTSESSION_H_