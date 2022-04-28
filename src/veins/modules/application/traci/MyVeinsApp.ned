package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.MinorBaseApplLayer;

//
// network description file for your Veins Application. Add parameters here
//
simple MyVeinsApp extends MinorBaseApplLayer
{
    @class(veins::MyVeinsApp);
    string appName = default("My first Veins App!");
}
