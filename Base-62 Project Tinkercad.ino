//---------------------- TINKERCAD ----------------------
//Note: All "Review Anchors" must be converted from tinkercad/irl
//NOTE - REMEMBER TO MAKE NOTES IF YOU EDITTED ANYTHING NOT IN LOOP()

//REVIEW - LCD Imports/init
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd1(0); //Top/Left Display
Adafruit_LiquidCrystal lcd2(0); //Bottom/Right Display

//Servo Imports/init
#include <Servo.h>
Servo keyboardMotor;

//Global var.
const int mainButton = 8; const int piezo = 9; const int serv = 10;
const int potent1 = A0; const int potent2 = A1; const int potent3 = A2;
const int button1 = 2; const int button2 = 3; const int button3 = 4;

//derive all characters through this list
const String book = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//FIXME - Added some more variables below
bool io = true;

int inputBase = 2;
int outputBase = 10;

int currentDegree1;
int currentDegree2;
int currentDegree3;

//STUB - VIDESH START CODING THE FUNCTION HERE

void setup() 
{
    Serial.begin(9600);

    //Pin settings
    myServo.attach(serv);
    pinMode(piezo, OUTPUT);

    //REVIEW - initialization function
    lcd1.begin(16, 2);
    lcd2.begin(16, 2);
    lcd1.setBacklight(0);
    lcd2.setBacklight(0);

    //FIXME - changed the stuff below
    //template("****************")

    /Initial display
    lcd1.setCursor(0, 0);
    lcd1.print("    Press !     ");
    lcd1.setCursor(0, 1);
    lcd1.print("    to start    ");

    lcd2.setCursor(0, 0);
    lcd2.print("     ZzZzZ      ");
    lcd2.setCursor(0, 1);
    lcd2.print("   ( - . - )    ");
}

void loop()
{
    //NOTE - Copy-paste everything in this loop() to the IRL loop()
    //starting placement
    lcd1.setCursor(0, 0);
    lcd2.setCursor(0, 0);

    
}


//TODO - Literally a list
// * Solder the A0 (I believe) memory adddress together
// * match the memory address of the coded LCD to the soldered LCD
// * make the degree-servo motor system like in arduino's examples
// * set the potentiometers parameters (initialization) to detect degrees
// * Get the potentiometers to scroll through values when they are turned respectively
//      - input 1 -> 0-9 ; input 2 -> A-Z ; input 3 -> a-z
// * Make a function tht handles displaying on LCD
//      - Use it to replace the cat "initial display" in setup()
// * Add the Tinkercad design/link to github README etc.
//      - Maybe also include pictures of different sections???





