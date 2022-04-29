* Dekh ideas se jeet, ab time kam hai actual code ka... Plus features and diverse tech

* Jaise ek wo paper to hai hi, thik... aur jikra kar dena ki after reading various papers, this was before we talked with sir actually, for some preparations

> * Phir, docker image bhi banana jo wo simulation ko run kar paye
> * Ek simple python script, jo basically wo w3... etc wale script ko call kare, for eg. ham city ka name de bas, baaki wo random location chun le... simple bhi new bhi
> * Phir, OS Cashier aur worldline type ideas, jaise ki jo good cars hongi unko kuchh points milega, aur verified cars ka already ek initial good points hoga
> * Authentication three way type, mtlb pehle car kuchh bheje server ko, phir server kisi value ke saath reply kare, aur baaki cars ko bhi bhej de, phir hamara car un cars se direct verify kar paye... For eg. ye kuchh public-private keys ki tarah ek dusre se linked ho sakta hai

> * Phir future suggestion me bolna ki cluster based protocols me ye aur bhi behtar hoga.

* saari gadiyan rsu ko message bhejegi (currently broadcast to all, baaki gadiyan should ignore, or accept in emergency cases). Then RSU verifies and broadcast to all , with array of car ids that it thinks are in the network


* This design of consensus, helps cars to notify others about cars that they think are problematic, cars will decide if the actually not car, with more cars agreed, the chain of others will match.

Secondly, since we are identifying cars using hash of a random id given to them, like a private and public key, connected to list of cars a car identifies, privacy is also maintained

* Aur points assigned to a car wala cheez bhi rakh sakte hai

* Private key can be used to check if RSU's update contains it's names, plus it is used to ensure privacy, so no one else can pin point that this car is connected to these
