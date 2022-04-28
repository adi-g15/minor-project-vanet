#include <veins/modules/application/traci/TraCIMinor11p.h>
#include <veins/modules/application/traci/TraCIMinor11pMessage_m.h>
#include <cstdlib>
#include <string_view>

using namespace veins;

Define_Module(veins::TraCIMinor11p);

void TraCIMinor11p::initialize(int stage)
{
    MinorBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
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
    std::system(("notify-send \"onWSM wala\" \"" + std::string(s) + "\"").c_str());

    auto msg_data = wsm->getDemoData();

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
            std::system("notify-send \"Gaadi ruki hui hai\" \"From Veins\"");

            findHost()->getDisplayString().setTagArg("i", 1, "red");
            sentMessage = true;

            TraCIMinor11pMessage* wsm = new TraCIMinor11pMessage();
            populateWSM(wsm);
            wsm->setDemoData(mobility->getRoadId().c_str());

            // host is standing still due to crash
            if (dataOnSch) {
                startService(Channel::sch2, 42, "Traffic Information Service");
                // started service and server advertising, schedule message to self to send later
                scheduleAt(computeAsynchronousSendingTime(1, ChannelType::service), wsm);
            }
            else {
                // send right away on CCH, because channel switching is disabled
                sendDown(wsm);
            }
        }
    }
    else {
        lastDroveAt = simTime();
    }
}
