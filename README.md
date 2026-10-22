# Base-62-Project
An Arduino calculator/converter for arbitrary bases from 1-62 using an oversimplified keyboard and very slow LCDs...

# Why did I make this:
Always wanted to make some sort of computer with the arduino and found that no one has tried to optimize the universal base converter into an incredibly weak system, much less even make a clauclator out of it...

# Did I regret this:
Made me grateful of modern computer memory capacity **:l**
2 kb is painful to work with

# How to read the manual/operate:
```
    - Module Format: [Applicable region] [function/values] [interaction type]
    - Parenthesis: [default value] <clarification> {max digit length allowed} (notes)
    - % = scroll-able position
    - # = value placeholder
```

## Main OS:
```
    - Start screen (press the on button to return to this screen)
        - At boot:
        - Update and check all potentiometer states
        - Reset all variables to default

    - Main screen:
        - % Base <setting screen> (sets the bases)
        - % Operation <setting screen> (sets the operation in calc. mode)
        - % Conversion <screen> (only converts)
        - % Calculation <screen> (Calculates and converts)

    - Base setting screen:
        - % Base From: # [10] {2} (sets to potentiometer degree)
        - % Base To: # [10] {2}
        - % back

    - Operation setting screen
        - % Operation: # [+] {1}
        - % back

    - Conversion screen
        -   "From" Value:
        - % # [0] {14}

    - Conversion execute screen:
        -   Result:
        -   # [0] {16}
        -   # [0] {16}
        - % back

    - Calculation screen
        -   Value 1:
        - % # [0] {14}
        -   Value 2:
        - % # [0] {14}

    - calculation execute screen:
        -   Result:
        -   # [0] {16} (part 1 of result)
        -   # [0] {16} (part 2 of result)
        - % back

    main modules:
        - potent1 => inputs 0-9 scrolling / navigation scrolling
        - potent2 => inputs A-Z scrolling / bases 0-31 scrolling / operations +-* / scrolling
        - potent3 => inputs a-z scrolling / bases 32-62 scrolling
        - button1 => calc. & convert enter button
        - button2 => calc. & convert backspace button
        - button3 => navigation selection button / calc. & convert next button
```

# Notes:
- You can always reste the system using the side power button
- The keyboard launches out when the "power" is on

# Pictures!

### Tinkercad:
<p align="left">
    <img src="./images/スクリーンショット 2026-09-18 234531.png" width="200" height="200" alt="hello there">
</p>

### Final CAD model
<p align="left">
    <img src="./images/スクリーンショット 2026-09-18 234531.png" width="200" height="200" alt="hello there">
</p>

### IRL build
<p align="left">
    <img src="./images/スクリーンショット 2026-09-18 234531.png" width="200" height="200" alt="hello there">
</p>

### Exploded view
<p align="left">
    <img src="./images/スクリーンショット 2026-09-18 234531.png" width="200" height="200" alt="hello there">
</p>
> I suggest looking at the 3D model to look at the placement of parts
> you will most likely need to wood-glue the frame together (just don't wood glue the lid of the keyboardEnclosure module)


# Parts list:
- I2C LCDs (x2)
- Breadboards (x2)
- Arduino UNO R3 [preferably R4] (x1)
- CA9 Potentiometers [the Arduino type] (x3)
- Standard push buttons (x4)
- Generic 180 degree Servo motor (x1)
- A whole lot of Male-Male and Male-Female Jumper wires [buy a box and make your own wires]
- 3D printed parts [here](https://github.com/hashikono/base-62-project)
- Laser cut frame [here](https://github.com/hashikono/base-62-project)