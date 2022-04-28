#include "TraCIMinorRSU11p.h"

using namespace veins;

TraCIMinorRSU11p::TraCIMinorRSU11p() : veins::MinorBaseApplLayer(), rsu_id(TraCIMinorRSU11p::id_counter++) {
    std::system("notify-send \"RSU Created\"");
}

void TraCIMinorRSU11p::onWSA(DemoServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void TraCIMinorRSU11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIMinor11pMessage* wsm = check_and_cast<TraCIMinor11pMessage*>(frame);

    std::system("notify-send \"RSU Update\" \"RSU ko message mila\"");

    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    auto* new_wsm = wsm->dup();
    new_wsm->setDemoData("rsu: ye naya wala");
    sendDown(new_wsm);
    // @adig delay agar hata de to kaaphi jaldi reply dikha deta hai, demo ke time delay hata dena chahe to
    // sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}
