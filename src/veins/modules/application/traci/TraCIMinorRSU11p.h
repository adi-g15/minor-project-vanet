#pragma once

#include <veins/modules/application/ieee80211p/MinorBaseApplLayer.h>
#include <veins/modules/application/traci/TraCIMinor11pMessage_m.h>

// @minor We could make it more complex
using IdType = int;

namespace veins {

class VEINS_API TraCIMinorRSU11p : public MinorBaseApplLayer {
    std::vector<IdType> known_cars;
    std::vector<IdType> blacklisted_cars;

    IdType rsu_id;
    static inline IdType id_counter = 0;

public:
    TraCIMinorRSU11p();

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;
};

} // namespace veins

Define_Module(veins::TraCIMinorRSU11p);
