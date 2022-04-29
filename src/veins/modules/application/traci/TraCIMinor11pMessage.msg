import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

namespace veins;

packet TraCIMinor11pMessage extends BaseFrame1609_4 {
    string sentData;
    LAddress::L2Type senderAddress = -1;
    int serial = 0;
}
