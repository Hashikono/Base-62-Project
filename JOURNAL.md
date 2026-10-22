## Base-62: Project Journal

> Records & notes of our progress by the hour
> Lowk forgot to make these hourly (going by lapse/github commits)
> The ANNOYING complexity of the OS resulted in the project being about 60% Fusion-ing | 39% VS Code-ing | 1% Losing my mind trying to find standardized Arduino (seemingly-proprietary) parts
> Some hourly activity for VS Code might be off (Question mark?) 'cause Github doesn't save time [Check Github / Hackatime for full history]

#### Hashikono:
1. VS Code
    - Setting everything up on both programs
    - 2 versions were made to account for arduino and tinkercad
    - Established basic imports for every theoretical module used
    - Made a to-do list to track everything in the code ('cause I'm lazy to port it somewhere else)
    - Made the unprogrammed tinker-cad design off camera 'cause I forgot to record my lapse session...
    <p align="left">
    <img src="./images/tinkercad.png" width="300" height="300" alt="Rough Draft - Home view">
    </p>
2. Fusion
    - Made a quick mock model
    - Designed it after a retro computer
    - Might end up making this parametric to fit a laser cutter
    - Small servo motor mechanism to shoot out the keyboard (though the mechanism might be faulty???)
3. Fusion / VS Code
    - Finished the mock model of the calculator/computer to show to a friend (literally sped ran making the model)
    - Debating between using splines and parametric curves for the top
        - Splines are annoying to deal with in laser cutting so I'm good
    - Speed-runned learning how to use markdown
    - Setup the journal that you're reading right now
    - Mock model images
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-18 1.png" width="300" height="300" alt="Rough Draft - Home view">
    </p>
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-18 2.png" width="300" height="300" alt="Rough Draft - Front view">
    </p>
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-18 3.png" width="300" height="300" alt="Rough Draft - Side view">
    </p>
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-18 4.png" width="300" height="300" alt="Rough Draft - Inside view">
    </p>
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-18 5.png" width="300" height="300" alt="Rough Draft - Functional view">
    </p>

4. Fusion
    - Began designing the base and general layout of the computer (on the cleaned parametric version)
    - Was trying to import stuff from Grab CAD etc.
    - Created the initial walls for the platform
    - Parameter tweaking for the size of the slots to piece the wood togetehr after
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-20 1.png" width="300" height="300" alt="Cleaned - Initial placement">
    </p>
5. Fusion
    - Imported a servo motor to use for the keyboard dispenser (it moves 180 degrees which is perfect)
    - Created the servo horn brace (connects to the breadboard keyboard)
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-20 2.png" width="300" height="300" alt="Motor placement tweaking">
    </p>
    - configuring rotational alignment to not scrape against the wood (was rotating it wayy too many times)
    - Made a custom horn extension to connect with the pin that moves the keyboard
    <p align="left">
    <img src="./images/スクリーンショット 2026-09-20 3.png" width="300" height="300" alt="Servo Motor custom horn extension">
    </p>
    - Added initial mechanism fo rolling-out keyboard (breadbaord latch, etc.)
6. VS Code
    - Began implementing some of the structure for the main calculation/conversion functions in Base-62 Pure (had to start over due to the previous algorithm not being optimized enough for 2kb of RAM)
    - Worked mainly on the conversion function
    - Conversion function originally relied on the base 2 system conversion like octal to hexadecimal 
7. VS Code
    - "Finished" the conversion function (I thought at least)
    - Began outputting correctly for Binary, Hexadecimal, Octal, Decimal, and any other base that's 2^x
    - Outputted some stuff for higher bases but they were wrong
    - Turns out arbitrary base converters are annoying because an algorithm for using binary as a median only works for binary type systems...sigh
    - Started thinking about another algorithm for the conversion platform
8. VS Code
    - Began by adding Unary support, still don't know why I decided to NOt give up on it
    - Many small bugs along the way (semi-colons are killing me)
9. VS Code
    - Used a conversion method that uses constant division to piece together remainders (long process I didn't want to think about but it's the only way)
    - theoretically actually finished the conversion function, should work now??
    - Dealing with strings as inputs so made and rebugged digitsToBaseString()
    - Began coding the calculator function (basically setting up the operators etc.)
10. VS Code
    - Turns out the calculator function was NOT easy
        - Using decimal as a median for conversion  
        - Originally used truncation for decimals (NOT trying to deal with big numbers in the code)
    - Added several helped functions to aid with the procresses
        - validChar() was teh most prominent to deal with the weird inputs made through the physical keyboard median
11. VS Code
    - Created the screenSwitch() function to easily switch screens between different parts of the OS
    - Wrote down the manual for how to actually operate the computer (may add to the side panel later)
    - Cleaned up inconsistencies and parenthesis coded it
12. VS Code
    - Mainly dealt with potentiometer mapping
    - map() is so useful
    - Converted potentiometer changes to the active potentiometer
        - In an ideal system, there isn't any noise in the potentiometer
        - Tinkercad decided to simulate noise in button inputs but not potentiometers???
    - Continued/finished making the calculator function
13. VS Code
    - Why did I think I would need a "baseTo" in conversions???
        - Fixed the additional input place
    - potentiometer sets baseFrom and baseTo values now
    - potentiometer sets operation values now
    - minor bug fixes with semicolons and incorrect if statement conditions
14. VS Code
    - Established the default function (when the machine powers "off", it will reset all variables)
    - Scrolling works sometimes?? (original system was overcomplicated so potentiometer 1 maps only to the 2-4 level screens)
    - Apparently the screen automatically skips the home screen due to external power running through the system
    - Fixed tinkercad by getting rid of resistors for buttons (yes it's bad practice ik...but it works :/)
15. VS Code
    - LCD display errors (print function mess-ups)
    - Memory address swaps for the physical LCDs (apparently every library has a different way to establish it)
    - initialization/setup() issues
    - made row value functions and a few other functions to aid with scrolling
    - Redid some of the default values
16. VS Code
    - Literally spent mostly dealing with try to get scroll to work again 'cause of how messed up the code is...
        - included valueRow(), RowPrint(), and a few others to help with scrolling and display discrepancies 
    - Added minor servo motor support (the keyboard mover) to whenever the system turns on
    - Trying to find out why tinkercad keeps giving me a generic error
    - Fixed typos in comments (accidentally placed "*/" together to represent multiplication/division)
17. VS Code
    - Tinkercad keeps crashing everytime I try to run the calculator function with the conversion function
    - Added the Piezo support for button presses
    - Resorting to crossing my fingers and trying IRL on an actual arduino (hopefully nothing melts...)
    - Began porting tinkercad.ino to IRL.ino
18. VS Code
    - Finalized the program (cleaned up some stuff)
    - Fixed the to-do list and tried to recreate IRL
    - Quickly added noise reduction for potentiometers (during testing the noise kept making certain potentiometers constantly update over and disabling some of the keyboard)
    <p align="left">
    <img src="./images/IMG_20261014_134852695_HDR_preview.jpeg" width="300" height="300" alt="In real life circuit demonstration">
    </p>
19. Fusion
    - Finally got a motive to come back to this after taking some rest from coding...
    - Finalized the peg-movement thing that attaches to the servo motor
    - Used a single-horned ending for the servo motor to save on space
    - Added tolerance between the 3D printed parts to allow for gravity to keep the "keyboard" downn (the pins)
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 1.png" width="300" height="300" alt="Pin view for motor-keyboard system">
    </p>
    - Added bracers to the arduino to keep it in place
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 11.png" width="300" height="300" alt="Arduino bracer to keep it in place">
    </p>
    - Began filling up the remainder of the frames for the keyboard enclosure
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 2.png" width="300" height="300" alt="Motor keyboard system full">
    </p>
20. Fusion
    - Finished the keyboard container of the box (final top frame has an area for the cables to pass through)
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 3.png" width="300" height="300" alt="Keyboard container top view">
    </p>
    - Added anchors to the top to give space/connection to the screen/monitor section
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 4.png" width="300" height="300" alt="Screen enclosure anchors">
    </p>
    - Finalized the base of the screen portion of the model
    - Corrected a couple inconsistent (set) measurements along the way
21. Fusion
    - Added holes to the side panels of the keyboard enclosure to allow for the servo motor cable to pass through
    - Added the LCD placement and carving into the LCD panel
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 5.png" width="300" height="300" alt="LCD panel">
    </p>
    - Finished the side panels of the "screen enclosure" and added a flappable lid
    - the flappable lid genuinely took more geometry than necessary
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 6.png" width="300" height="300" alt="Screen enclosure lid">
    </p>
22. Fusion
    - Looked for some buttons and potentiometers (the arduino specifci potentiometers took WAYY too long to find)
    - Placed the buttons in their positions on the breadboard
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 7.png" width="300" height="300" alt="Circuit view with buttons">
    </p>
    - Added a hole on the side of one of the keyboard enclosure panels to act as the one/off button
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 8.png" width="300" height="300" alt="Power button on right panel">
    </p>
    - Had to quite literally re-assemble the potentiometer myself because the assemly file was broken...
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 9.png" width="300" height="300" alt="Disassembled view of the potentiometer">
    </p>
    - Placed the potentiometers and an additional piezo accordingly to the breadboards
    - made custom potentioemter knobs to accomodate the size of the keyboard enclosure
    <p align="left">
    <img src="./images/スクリーンショット 2026-10-20 10.png" width="300" height="300" alt="Custom shorted potentioemeter knob">
    </p>
23. Fusion
    - Added tolerance to the frames for easy attachments
        - I do NOT want to sand 50+ attachement locations due to poor wood quality
        - <p align="left">
            <img src="./images/スクリーンショット 2026-10-20 12.png" width="300" height="300" alt="Tolerance example on a triangular panel">
            </p>
    - Created the exploded view GIF (maybe watching this in reverse would help with assembly)
        - Also to show how many absurd parts this thing annoyingly took
        - <p align="left">
            <img src="./images/スクリーンショット 2026-10-20 13.png" width="300" height="300" alt="Exploded view creation & editting">
            </p>
    - Extracting sketches for laser cutting / porting into github
    - Was thinking about creating PRUSA slice files and CorelDraw files for easy porting/printing
        - I don't think anyone has an old MK-4 Prusa Printer that's compatible with the slice file anymore so I'll leave it as is
24-27. VS Code (May have spent more than 3 hours but I lost track of times atp)
    - Spent about 5 minutes rendering the model and porting it to Github
    - This README/JOURNAL
    - Screenshotting and adding instructions to everything
    - Porting the models to the Github
    - Fixing broken links and weird markdown rendering in Github
    - Fixing apparently all the alt texts and weird markdown stuff that was happening with lists in the JOURNAL
28. IRL
    - 3D printed all parts (pins, component bracing stuff, etc.)
    <p align="left">
    <img src="./images/pending.png" width="300" height="300" alt="[pending]">
    </p>
    - laser cutting the frames
        - Gotta love that smell of burnt wood ```:>```
        - <p align="left">
        <img src="./images/pending.png" width="300" height="300" alt="[pending]">
        </p>
    - Assembling the computer/calculator/whatever you will call this thing
    <p align="left">
    <img src="./images/pending.png" width="300" height="300" alt="[pending]">
    </p>



#### arivvid27:
> However long he spent making the original simplified prototype for the conversion/calculation functiosn