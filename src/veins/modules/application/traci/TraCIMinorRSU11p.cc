#include "TraCIMinorRSU11p.h"

using namespace veins;

TraCIMinorRSU11p::TraCIMinorRSU11p() : veins::MinorBaseApplLayer(), rsu_id(TraCIMinorRSU11p::id_counter++) {
    char msg[100];
//    snprintf(msg, 100, "notify-send \"RSU Created: #%d, %d\"", getId(), getSimulation()->getLastComponentId());
    snprintf(msg, 100, "notify-send \"RSU Created: #%d\"", myId/*getId()*/);
    std::system(msg);
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

    char cmd[100];
    snprintf(cmd, 100, "notify-send \"RSU Update\" \"RSU received a message from #%s\"", wsm->getsentData());
    std::system(cmd);

    auto starts_with = [](const char* msg, const char* prefix) -> bool {
        auto sz = strlen(msg);
        auto prefix_sz = strlen(prefix);

        if(sz < prefix_sz) { return false; }

        for(int i=0; i<prefix_sz; ++i) {
            if(msg[i] != prefix[i]) { return false; }
        }

        return true;
    };

    auto msg_data = wsm->getsentData();

    if( starts_with(msg_data, "#") ) {
        std::string msg_str = msg_data;

        auto it = msg_str.find(':');
        auto car_id = msg_str.substr(0, it);

        char s[150];

        /* std::map::insert or std::set::insert, both return a pair, in which the second
         * is a boolean telling if insertion took place, i want this message to be shown
         * once only */
        if( this->known_cars.insert(car_id).second == true ) {
            std::snprintf(s, 150, "notify-send \"Approved Car: #%s\"", car_id.c_str());

            std::system(s);
        }

//        char s[150];
//        std::snprintf(s, 100, "notify-send \" Sent Car Id: %s\"", car_id.c_str());
//        std::system(s);
    }

    std::string car_list = "[";
    int i=0;
    for(const auto& car_id: this->known_cars) {
        car_list = car_list + car_id;

        if(i == this->known_cars.size()-1) {
            car_list.push_back(']');
        } else {
            car_list.push_back(',');
            car_list.push_back(' ');
        }
        ++i;
    }

    if(this->known_cars.empty()) {
        car_list.push_back(']');
    }

    auto* new_wsm = wsm->dup();
    new_wsm->setsentData(("rsu: " + car_list).c_str());
    sendDown(new_wsm);
    // @adig delay agar hata de to kaaphi jaldi reply dikha deta hai, demo ke time delay hata dena chahe to
    // sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}
