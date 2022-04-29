#include <veins/modules/application/traci/TraCIMinor11p.h>
#include <veins/modules/application/traci/TraCIMinor11pMessage_m.h>
#include <cstdlib>
#include <string_view>
#include <random>

// hash ke liye library use kar rha hu
#include "hash/khash.h"

using namespace veins;

Define_Module(veins::TraCIMinor11p);

std::string get_hash(int private_key) {
    char tmpstr[100];
    snprintf(tmpstr, 100, "%x", khash64_fn(private_key, 0));

    return tmpstr;
}

TraCIMinor11p::TraCIMinor11p():
        public_key(get_hash(private_key)),
        private_key(rand())
{
    static int count = 1;
/*    auto* module = getSimulation()->componentv;

    char cmd[100];
    snprintf(cmd, 100, "notify-send \"Parent: %p\"", (void*)module);
    std::system(cmd);
*/
/*
    cModule* rsuModule = getParentModule()->getSubmodule("rsu");
    if( rsuModule == nullptr ) {
        std::system("notify-send \"Invalid hai bhai !\"");
    } else {
        std::system("notify-send \"Mil gaya bhai !\"");
    }
*/

    char msg[100];
    snprintf(msg, 100, "notify-send \"Car #%d\"", count++);
//    std::system(msg);
}

void TraCIMinor11p::initialize(int stage)
{
    MinorBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }

    if( this->sendBeacons == true ) {
        TraCIMinor11pMessage* wsm = new TraCIMinor11pMessage();
        populateWSM(wsm);

        char msg[100];
        snprintf(msg, 100, "#%s:lane=%s", this->public_key.c_str(), mobility->getRoadId().c_str());
        wsm->setsentData(msg);

        sendDown(wsm);
    }
}

void TraCIMinor11p::onWSA(DemoServiceAdvertisment* wsa)
{
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        if (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service");
        }
    }
}

void TraCIMinor11p::onWSM(BaseFrame1609_4* frame)
{
    TraCIMinor11pMessage* wsm = check_and_cast<TraCIMinor11pMessage*>(frame);

    findHost()->getDisplayString().setTagArg("i", 1, "green");

    char s[100] = "";
    std::snprintf(s, 100, "Myself: %s, Message kind: %d", this->getFullName(), wsm->getKind());
//    std::system(("notify-send \"onWSM wala\" \"" + std::string(s) + "\"").c_str());

    auto msg_data = wsm->getsentData();

    auto starts_with = [](const char* msg, const char* prefix) -> bool {
        auto sz = strlen(msg);
        auto prefix_sz = strlen(prefix);

        if(sz < prefix_sz) { return false; }

        for(int i=0; i<prefix_sz; ++i) {
            if(msg[i] != prefix[i]) { return false; }
        }

        return true;
    };

    if(starts_with(msg_data, "rsu:")) {
        std::snprintf(s, 100, "RSU wala message: %s", msg_data);
        std::system(("notify-send \"Broadcast from RSU\" \"" + std::string(s) + "\"").c_str());

    } else if (starts_with(msg_data, "#")) {
        // SKIP, rsu should handle this
    } else if (mobility->getRoadId()[0] != ':') {
        // @adig - By default, RSU is replying with a new lane for the vehicle to take
        traciVehicle->changeRoute(msg_data, 9999);
    }

    if (!sentMessage) {
        sentMessage = true;
        // repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), wsm->dup());
    }
}

void TraCIMinor11p::handleSelfMsg(cMessage* msg)
{
    if (TraCIMinor11pMessage* wsm = dynamic_cast<TraCIMinor11pMessage*>(msg)) {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 3) {
            // stop service advertisements
            stopService();
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else {
        MinorBaseApplLayer::handleSelfMsg(msg);
    }
}

void TraCIMinor11p::handlePositionUpdate(cObject* obj)
{
    MinorBaseApplLayer::handlePositionUpdate(obj);

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            char cmd[100];
            snprintf(cmd, 100, "notify-send \"An accident has happened\" \"Car ID: #%s\"", this->public_key.c_str());
            std::system(cmd);

            findHost()->getDisplayString().setTagArg("i", 1, "red");
            sentMessage = true;

            TraCIMinor11pMessage* wsm = new TraCIMinor11pMessage();
            populateWSM(wsm);

            char msg[100];
            snprintf(msg, 100, "#%s:lane=%s:in-accident", this->public_key.c_str(), mobility->getRoadId().c_str());
            wsm->setsentData(msg);

            // host is standing still due to crash
            if (dataOnSch) {
                startService(Channel::sch2, 42, "Traffic Information Service");
                // started service and server advertising, schedule message to self to send later
                scheduleAt(computeAsynchronousSendingTime(1, ChannelType::service), wsm);
            }
            else {
                sendDown(wsm);
            }
        }
    }
    else {
        lastDroveAt = simTime();
    }
}
