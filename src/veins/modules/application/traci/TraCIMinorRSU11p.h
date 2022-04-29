#pragma once

#include <veins/modules/application/ieee80211p/MinorBaseApplLayer.h>
#include <veins/modules/application/traci/TraCIMinor11pMessage_m.h>

// @minor We could make it more complex
using IdType = std::string;

namespace veins {

class VEINS_API TraCIMinorRSU11p : public MinorBaseApplLayer {
    std::set<IdType> known_cars;
    std::set<IdType> blacklisted_cars;

    int rsu_id;
    static inline int id_counter = 0;

public:
    TraCIMinorRSU11p();

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;
};

} // namespace veins

Define_Module(veins::TraCIMinorRSU11p);
