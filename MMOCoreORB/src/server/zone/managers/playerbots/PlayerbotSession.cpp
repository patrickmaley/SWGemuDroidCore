#include "PlayerbotSession.h"
#include "server/zone/ZoneClientSessionImplementation.h"

PlayerbotSession::PlayerbotSession(ZoneProcessServer* serv) : ZoneClientSession(serv) {
    // We don't have a real BaseClientProxy / network session
    setLoggingName("PlayerbotSession");
}

PlayerbotSession::~PlayerbotSession() {
}

void PlayerbotSession::disconnect(bool lockPlayer) {
    // Do nothing (or clean up bot-specific things later)
    info("PlayerbotSession::disconnect() called - ignoring", true);
}

void PlayerbotSession::sendMessage(BaseMessage* msg) {
    // Critical: Do NOT send anything over the network
    // Just delete the message so we don't leak memory
    delete msg;
}

void PlayerbotSession::sendMessage(StandaloneBaseMessage* msg) {
    delete msg;
}