import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;

network CarsRSU extends Scenario
{
    @display("bgb=619,416");
    submodules:
        rsu[1]: RSU {
            @display("p=512,325;i=veins/sign/yellowdiamond;is=vs");
        }
}
