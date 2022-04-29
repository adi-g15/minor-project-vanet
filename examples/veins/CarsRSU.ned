import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;

network CarsRSU extends Scenario
{
    @display("bgb=619,416");
    submodules:
        rsu[1]: RSU {
            @display("p=201,205;i=veins/sign/yellowdiamond;is=vs");
        }
}
