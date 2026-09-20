#include "PlayerbotSession.h"

PlayerbotSession::PlayerbotSession() : ZoneClientSession(static_cast<BaseClientProxy*>(nullptr)) {
}

PlayerbotSession::~PlayerbotSession() {
}

void PlayerbotSession::disconnect(bool lockPlayer) {
    // Do nothing for bots
}

void PlayerbotSession::sendMessage(BasePacket* msg) {
    delete msg; // prevent memory leak, don't send over network
}
