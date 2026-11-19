# How to build this project:
> You can skip 90% of this guide by just studying the exploded view GIF, Tinkercad Ciruit, and/or the latest version of the fusion model located in the "Fusion Model" folder
>> The other 10% are in the "Absurd solution" section below
>> Also note that you need to change the memory address of the 

- Exploded View
    <p align="left">
    <img src="./images/model.gif" width="300" height="300" alt="Exploded GIF of the model">
    </p>

- Other views that may be of use
    -  Front view
    <p align="left">
    <img src="images\IMG_20261116_181931559_HDR.jpg" width="300" height="300" alt="Somewhat a front view of the project">
    </p>

    - Side view
    <p align="left">
    <img src="images\IMG_20261116_181937933_HDR.jpg" width="300" height="300" alt="Somewhat a side view (button side)">
    </p>

    - Top interior view
    <p align="left">
    <img src="images\IMG_20261116_181944027_HDR.jpg" width="300" height="300" alt="Inside view of the stuff from top">
    </p>

    - General interior view
    <p align="left">
    <img src="images\IMG_20261116_182015321_HDR.jpg" width="300" height="300" alt="Inside view of the stuff from front">
    </p>

### Connecting the circuits
    - As long as everything gets connected right, it really doesn't matter how it all interconnects
    - The tinkercad simulation displays it all connected via 3 breadboards, I suggest for the sake of space, follow the second image where the breadboards for the LCD and general components are combined into 2 breadboards
        - Basically, the keyboard is one one breadboard, and everything is on the other

- (first image) Tinkercad simulation
<p align="left">
    <img src="./images/tinkercad.png" width="300" height="300" alt="Tinkercad circuit">
</p>

- (second image) IRL circuit
<p align="left">
    <img src="./images/IMG_20261014_134852695_HDR_preview.jpeg" width="300" height="300" alt="In real life circuit demonstration">
</p>

-  Leave the project like this when you're just about ready to attach the servo motor horn mechanism (the one that activates/ejects the keyboard)
    <p align="left">
    <img src="images\IMG_20261116_180416869_HDR.jpg" width="300" height="300" alt="Enclosure opened into 2 parts with components in view and plugged in with code loading into it">
    </p>


# Absurd solution:
> This section defines how I made the locking mechanism
> It is in my opinion the easiest way of implementing the keyboard locking mechanism as 3D printing Servo Horns with a 0.4mm nozzle apparently does not compare to a regular servo horn drilled (trust me I tried)
>> You will NOT need the servo motor horn clasp thing anymore...

- Servo motor horn clasp thing
//here

- Start by drilling the servo horn...
    - Basically, take a generic servo horn you get from an arduino kit and drill the 2nd hole after the big hole
- The measurements of the holes are as follows (if someone wants to model this):
    - Servo motor horn measurement general width
        <p align="left">
        <img src="images\IMG_20261116_185517776_HDR~2.jpg" width="300" height="300" alt="Servo motor horn measurement general width">
        </p>
    - Servo motor horn measurement hole width
        <p align="left">
        <img src="images\IMG_20261116_185553493_HDR~2.jpg" width="300" height="300" alt="Servo motor horn measurement hole width">
        </p>
    - Servo motor horn measurement hole placement distance
        <p align="left">
        <img src="images\IMG_20261116_185634792_HDR~2.jpg" width="300" height="300" alt="Servo motor horn measurement hole placement distance">
        </p>

### Positioning notes
- First connect the mechanism to the breadboard




- Load the program into the arduino and press the side button to turn the system "on" it should be 
- The mechanism should be placed parallel to the surface when it is extended in the keyboard's activated position


- Servo motor horn position (dormant)
    <p align="left">
    <img src="images\IMG_20261116_182005501_HDR.jpg" width="300" height="300" alt="Servo motor horn unactivated">
    </p>

- Servo motor horn position (ejected/activated)
    <p align="left">
    <img src="images\IMG_20261116_181137076_HDR.jpg" width="300" height="300" alt="Servo motor horn activated">
    </p>

- Trust this activated servo motor horn position more than the firat image...
    <p align="left">
    <img src="images\IMG_20261116_185953055_HDR.jpg" width="300" height="300" alt="Servo motor horn activated with better view">
    </p>

- Breadboard latch module (basically the main mechanism)
    <p align="left">
    <img src="images\IMG_20261116_185928461_HDR.jpg" width="300" height="300" alt="Breadboard latch and mechniasmain mechanism">
    </p>