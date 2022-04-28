#pragma once

#include <veins/modules/application/ieee80211p/MinorBaseApplLayer.h>

namespace veins {

/**
 * @brief
 * A tutorial demo for TraCI. When the car is stopped for longer than 10 seconds
 * it will send a message out to other cars containing the blocked road id.
 * Receiving cars will then trigger a reroute via TraCI.
 * When channel switching between SCH and CCH is enabled on the MAC, the message is
 * instead send out on a service channel following a Service Advertisement
 * on the CCH.
 *
 * @author Christoph Sommer : initial DemoApp
 * @author David Eckhoff : rewriting, moving functionality to MinorBaseApplLayer, adding WSA
 *
 */

using IdType = int;

class VEINS_API TraCIMinor11p : public MinorBaseApplLayer {
public:
    const std::string public_key;
    void initialize(int stage) override;
    TraCIMinor11p();

private:
    const int private_key;
    std::vector<IdType> agreed_cars;

protected:
    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
};

} // namespace veins
