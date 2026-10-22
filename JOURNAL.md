## Base-62: Project Journal

> Records & notes of our progress by the hour
> Lowk forgot to make these hourly (going by lapse/github commits)
> The ANNOYING complexity of the OS resulted in the project being about 60% Fusion-ing | 39% VS Code-ing | 1% Losing my mind trying to find standardized Arduino (seemingly-proprietary) parts
> Some hourly activity for VS Code might be off (Question mark?) 'cause Github doesn't save time [Check Github / Hackatime for full history]

#### Week 1:
- Hashikono:
    1. VS Code
        - Setting everything up on both programs
        - 2 versions were made to account for arduino and tinkercad
        - Established basic imports for every theoretical module used
        - Made a to-do list
        - Made the unprogrammed tinker-cad design off camera 'cause I forgot to record my lapse session...
        <p align="center">
        <img src="./images/tinkercad.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
    2. Fusion
        - Made a quick mock model
        - Designed it after a retro computer
        - Might end up making this parametric to fit a laser cutter
        - Small servo motor mechanism to shoot out the keyboard
    3. Fusion / VS Code
        - Finished the mock model of the calculator
        - Debating between using splines and parametric curves for the top
        - Speed-runned learning how to use markdown
        - Setup the journal that you're reading right now
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-18 1.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-18 2.png" width="300" height="300" alt="Rough Draft - Front view">
        </p>
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-18 3.png" width="300" height="300" alt="Rough Draft - Side view">
        </p>
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-18 4.png" width="300" height="300" alt="Rough Draft - Inside view">
        </p>
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-18 5.png" width="300" height="300" alt="Rough Draft - Functional view">
        </p>

    4. Fusion
        - Began designing the base and general layout of the computer
        - Was trying to import stuff from Grab CAD etc.
        - Created the initial walls for the platform
        - Parameter tweaking
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-20 1.png" width="300" height="300" alt="Cleaned - Initial placement">
        </p>
    5. Fusion
        - Imported a servo motor to use for the keyboard dispenser
        - Created the servo horn brace (connects to the breadboard keyboard)
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-20 2.png" width="300" height="300" alt="Cleaned - Initial placement">
        </p>
        - configuring rotational alignment to not scrape against the wood (was rotating it wayy too many times)
        <p align="center">
        <img src="./images/スクリーンショット 2026-09-20 3.png" width="300" height="300" alt="Cleaned - Initial placement">
        </p>
        - Added initial mechanism fo rolling-out keyboard (breadbaord latch, etc.)
    6. VS Code
        - Began implementing some of the structure for the main calculation/conversion functions in Base-62 Pure (had to start over due to the previous algorithm not being optimized enough for 2kb of RAM)
        - Worked mainly on the conversion function
    7. VS Code
        - "Finished" the conversion function
        - Began outputting correctly for Binary, Hexadecimal, Octal, Decimal, and any other base that's 2^x
        - Outputted some stuff for higher bases but they were wrong
    8. VS Code
        - Began by adding Unary support, still don't know why I decided to NOt give up on it
        - Many small bugs along the way
    9. VS Code
        - theoretically actually finished the conversion function, should work now??
        - Dealing with strings as inputs so made and rebugged digitsToBaseString()
        - Began coding the "easy" calculator function
    10. VS Code
        - Turns out the calculator function was NOT easy
        - Added several helped functions to aid with the procresses
    11. VS Code
        - Created the screenSwitch() function to easily switch screens between different parts of the OS
        - Wrote down the manual for how to actually operate the computer (may add to teh side panel later)
        - Cleaned up inconsistencies and parenthesis coded it
    12. VS Code
        - Mainly dealth with potentiometer mapping
        - map() is so useful
        - Converted potentiometer changes to the active potentiometer
        - Continued making the calculator function (converts everything to decimal first before)
    13. VS Code
        - Why did I think I would need a "baseTo" in conversions???
        - potentiometer sets baseFrom and baseTo values now
        - potentiometer sets operation values now
        - minor bug fixes wit semicolons etc.
    14. VS Code
        - Established the default function (when the machine powers "off", it will reset all variables)
        - Scrolling works sometimes?? (original system was overcomplicated so potentiometer 1 maps only to the 2-4 level screens)
        - Apparently the screen automatically skips the home screen due to external power running through the system
        - Fixed tinkercad by getting rid of resistors for buttons (yes it's bad practice ik...but it works :/)
    15. VS Code
        - LCD display errors (print function mess-ups)
        - Memory address swaps?
        - initialization/setup() issues
        - Redid some of the default values
    16. VS Code
        - Literally spent mostly dealing with try to get scroll to work again 'cause of how messed up the code is...
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
        <p align="center">
        <img src="./images/IMG_20261014_134852695_HDR_preview.jpeg" width="300" height="300" alt="Rough Draft - Home view">
        </p>
    19. Fusion
        - Finally got a motive to come back to this after taking some rest from coding...
        - Finalized the peg-movement thing that attaches to the servo motor
        - Used a single-horned ending for the servo motor to save on space
        - Added tolerance between the 3D printed parts to allow for gravity to keep the "keyboard" downn (the pins)
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 1.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        - Added bracers to the arduino to keep it in place
        - Began filling up the remainder of the frames for the keyboard enclosure
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 2.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
    20. Fusion
        - Finished the keyboard container of the box (final top frame has an area for the cables to pass through)
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 3.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        - Added anchors to the top to give space/connection to the screen/monitor section
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 4.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        - Finalized the base of the screen portion of the model
        - Corrected a couple inconsistent (set) measurements along the way
    21. Fusion
        - Added holes to the side panels of the keyboard enclosure to allow for the servo motor cable to pass through
        - Added the LCD placement and carving into the LCD panel
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 5.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        - Finished the side panels of the "screen enclosure" and added a flappable lid
        - the flappable lid genuinely took more geometry than necessary
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 6.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
    22. Fusion
        - Looked for some buttons and potentiometers (the arduino specifci potentiometers took WAYY too long to find)
        - Placed the buttons in their positions on the breadboard
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 7.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        - Added a hole on the side of one of the keyboard enclosure panels to act as the one/off button
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 8.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        - Had to quite literally re-assemble the potentiometer myself because the assemly file was broken...
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 9.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
        - Placed the potentiometers and an additional piezo accordingly to the breadboards
        - made custom potentioemter knobs to accomodate the size of teh keyboard enclosure
        <p align="center">
        <img src="./images/スクリーンショット 2026-10-20 10.png" width="300" height="300" alt="Rough Draft - Home view">
        </p>
    23. Fusion
        - 
    24. VS Code??
        - Spent about 5 minutes rendering the model and porting it to Github
        - This README/JOURNAL
    