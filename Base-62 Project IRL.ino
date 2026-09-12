//---------------------- IN REAL LIFE ----------------------
//Note: All "Review Anchors" must be converted from tinkercad/irl

//REVIEW - LCD Imports/init
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x27, 16, 2); //Top/Left Display
LiquidCrystal_I2C lcd2(0x26, 16, 2); //Bottom/Right Display

//Servo Imports/init
#include <Servo.h>
Servo keyboardMotor;

//Global var.
const int mainButton = 8; const int piezo = 9; const int serv = 10;
const int potent1 = A0; const int potent2 = A1; const int potent3 = A2;
const int button1 = 2; const int button2 = 3; const int button3 = 4;

//derive all characters through this list
const String book = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


void setup() 
{
    Serial.begin(9600);

    //Pin settings
    myServo.attach(serv);
    pinMode(piezo, OUTPUT);

    //REVIEW - initialization function
    lcd1.init();
    lcd2.init();
    lcd1.backlight();
    lcd2.backlight();

}

void loop()
{
    //starting placement
    lcd1.setCursor(0, 0);
    lcd2.setCursor(0, 0);


    //printing
    lcd.print("hello world");
    
}


