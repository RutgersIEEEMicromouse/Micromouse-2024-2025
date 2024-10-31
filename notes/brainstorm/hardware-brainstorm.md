# Brainstorming

## Design Goals

- Make bot smaller.
- Continuous movements.
    - Diagonals.
    - curve turns.
- Different Microcontroller.
- No Object Oriented Programming.

## Stage One - Parts Decisions

### Microcontroller - Raspberry Pi PICO vs. Arduino Nano 

| microcontroller | Raspberry Pi PICO | Arduino Nano IOT |
|---|---|---|
| Pros | Cheap, reliable, more memory | IMU included, IOT device |
| Cons | Doesn't have IMU, Bigger form factor | Expensive, waste of IMU if dead |



### Other Parts - Wall Sensors

- For the past two years, we've used VL6180 and VL5131X sensors from Polulu. They use $I_2 C$, allowing for reading from multiple devices only using two pins. On paper, this is a good solution, but after two years of use, bottlenecks appeared.
    - Response times were abysmal. For example, if we wanted to take readings while moving the bot, it'd cause issues due to it's response time.
    - Pointless. We use 5 gpio pins in the end to shut down sensors when assigning sensors.

**Alternatives**

- Polulu Digital Distance Sensors 15cm
    - Model number 0J13203



### Motor Controller

- We want to experiment with the 0j13974, which is a motor driver that operates off $I_2 C$.


### Misc

- We want the following:
    - Buzzer
    - Battery Indicator
    - Neopixel
    - switch
    - one battery
    - fuse
    - 12V LiPo battery

