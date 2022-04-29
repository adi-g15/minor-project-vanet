## Access Control in VANET

### Minor Project 1

<span>Abhay, Aditya, Rabin</span><span>Mentor: Dr. Bhaskar Mondal</span>

> This describes our initial idea till now, and maybe vague at points. Including claims that are not our goal, but included as interesting for future consideration
>
> Minor Project topic is at section 4

### 1. Overview & Design

<img width="50%" src="https://i.imgur.com/6oIWJj3.png" />

Basically, VANET interface will have some function calls, which I call 'syscall' (named after System calls in Operating Systems) interface.

It allows: 
  1. Modular Interface
  2. Adding/Removing willl be easier
  3. The design allows, for minimising some layers of abstraction, even customed Operating System should work as long as they follow the interface, thus increasing available processing power

### 2. Car Internal Decision System

At minimum, it will require minor changes atleast to incorporate VANET, such as proviging sensor data to VANET system.

We also suggest using a Decision Tree based (prevents black-box problems) ML model to decide further action based on data from VANET, sensors and other subsystems.

To access VANET subsystem events, the steps are loosely:
  1. Initialise VANET system (provide car data etc.)
  2. ... Any other actions, then start broadcast using `start_broadcasting()` syscall.
  3. Use polling to access VANET events (lesser interval between polling, may increase safety but costlier).

It should also provide a function for VANET to also get sensor data, for eg.

```c
/**
 * @returns array of {uint64, uint64, byte array}
 *     First uint64 represents sensor type
 *     Second uint64 represents sensor UUID or any other unique identifier
 *     Third is data bytes received from sensor (the internal system may modify it as long as VANET implementation understands what these random bytes mean)
 **/

array(uint64, uint64, byte[]) get_sensor_data();
```

### 3. VANET syscalls

The VANET subsystem should provide functions (aka. syscalls) like:

```c
void     set_payload(byte[]);
void     set_broadcast_rate(float);

/* should have vehicle information according to an agreed standard format */
void     set_broadcast_header(byte[]);
void     start_broadcast();
void     stop_broadcast();

/*This `event` type depends on the implentation, though we suggest it to be an integer, like in operating systems, where they return a file descriptor instead of a platform specific file object*/
event[] poll_events();
```

This way, broadcasting may internally be using Bluetooth Low Energy (BLE), WiFi, or any other tech, and will require minor or no change in car's system which is using this syscall interface.

> VANET subsystem should do internal state-keeping when required, for eg. an event queue, which will store events until he car system uses poll_events() to get them.

> We are using broadcasting to send data to others & polling to get data from VANET subsystem, these maybe costly if we see on processing power, though embedded systems in vehicles should be enough to do these.

> Payload may/may not include sensor data

The modular design allows for simple modifications for use in simulations.

#### 3.1 VANET routing protocol

We are going to use already available protocols such as the reactive & topology drive AODV protocol [[#17]()], or reactive & cluster-based LORA-CBF protocol [[#45]()]

> Prefer cluster-based

When using cluster-based protocol, in a cluster, only vehicles moving in same direction should be considered, it also helps since relative speed being lesser, the connection can be better with vehicles moving in same direction.

Single vehicles will be their own clusters.

### 4. Security & Access Control

1. NOW [[#](51)] and SEVECOM [[#52]()] as a baseline for improved security
2. Public key signatures while communicating \[IEEE 1609.2\] (similar paper - [#[54]()])
3. To help privacy, two nodes in a cluster may 'swap' their identifier/key and then re-register with their respective clusters (similar paper - [[#55]()])

### 5. Debugging Interface

All nodes send their status to a server, data being something like:

```c
{
   cluster_id,
   my_data			// may include GPS location, etc.
}
```

Each node sends those data to some remote server, and remote debug server can visualise it using, say graphs. With nodes with same cluster id the debug server can assign the node to a specific node.

![](https://i.imgur.com/YnUqQJJ.png)

