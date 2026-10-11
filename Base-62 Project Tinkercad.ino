//---------------------- TINKERCAD ----------------------

//NOTE ------ [LCD imports/init] ------
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd1(0); //Top/Left Display
Adafruit_LiquidCrystal lcd2(0); //Bottom/Right Display



//NOTE ------ [Normal imports] ------
//Servo Imports/init
#include <Servo.h>
Servo keyboardMotor;



//NOTE ------ [C++ imports] ------
#include <string.h>
#include <stdint.h>
using namespace std;

//setting definitions
#define MAX_BOOK_LENGTH 62
#define MAX_INPUT_LENGTH 16 //limit to 16 in the LCD
#define MAX_BITS 256 //binary buffer/temp storagfe
#define UNARY_SYM '1'



//NOTE ------ [Global variables] ------
//connection variables
const int mainButtonLink = 8; const int piezoLink = 9; const int servoLink = 10;
const int[] potentLink = {A0, A1, A2};
const int[] buttonLink = {2, 3, 4};

//screen stuff
string screen[] = {"****************", "****************", "****************", "****************"};

//operation variables
string currentScreen = "default"
bool power = false; //tracks turning machine on/off
int fromBase = 10; //conversion from base setting
int toBase = 10; //conversion to base setting
char operationType = '+'; //operation setting
char value1[] = "0"; //input value (only updates after confirmation)
char value2[] = "0"; //input value (only updates after confirmation)
char result[] = "0"; // calculation or conversion result

int currentDegree[] = {0, 0, 0}; //potentiometer current degree
int scrollPlacement[] = {1, 1, 1, 1}; //scrolling in a 4-sector screen
char potentInput[] = "0Aa"; //input value for potentiometer (only value1 / value2 inputting)
int potentBases[] = {0,32}; //input value for potentiometer (only value1 / value2 inputting)



//STUB ------ [C++ code] ------
//SECTION
//derive chars thru list
const char BOOK[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const uint8_t BOOK_LENGTH = 62; //gotta love unsigned integers -_-

//finding c index in book
int16_t bookIndex(char c, uint8_t baseLen){
    for(uint8_t i = 0; i < baseLen; i++){
        if (BOOK[i] == c) {
            return (int16_t)i;
        }
    }
    return -1; //error
}

//set bitlength accordingly
uint8_t bitLength(uint8_t bookSize){
    uint8_t bits = 0;
    uint16_t commonCap = 1;
    while (commonCap < bookSize){
        commonCap <<= 1; //shifting left
        bits++;
    }
    return bits++;
}

//special cases (in a sense):
//conversions for unary
uint16_t fromUnary(const char* s, char sym = UNARY_SYM){
    uint16_t count = 0;
    for (const char* p = s; *p; p++){
        //iterating through a memory address instead of addressing a string
        if(*p == sym) count ++;
    }
    return count;
}

uint8_t toUnary(uint16_t val, char* output, uint8_t outputSize){
    if (val + 1 > outputSize){
        return 0; //though this should rarely happen...
    }
    for (uint16_t i = 0; i < val; i++){
        output[i] = UNARY_SYM;
    }
    output[val] = '\0'; //sneaky-strings againnn
    return (uint8_t)val;
}

//conversion to binary (making all of this arduino compatible is killing me)
uint8_t toBinary(char c, uint8_t base, char* outputt, uint8_t outputSize){
    //literally just its index...
    int16_t ind = bookIndex(c, base);
    if (ind < 0) {
        return 0; //because stupid unary exists
    }

    //bit length setting
    uint8_t bits = bitLength(base);
    if (bits +1> outputSize){
        return 0;
    }

    for (uint8_t i = 0; i < bits; i++){
        outputt[bits-1-i] = char('0' + (ind & 1)); //AND gates...used only in minecraft
        ind >>= 1; //shifting binary right
    }

    outputt[bits] = '\0'; //sneaky way to make a string
    return bits;
}

//conversion part 1 through constant division
bool digitsToBaseStr(char* digits, uint16_t digitsLength, uint8_t fromBase, uint8_t toBase, char* output, uint16_t outputSize){
    //get rid of leading 0s - somehting forgotten in the base 2^x system
    uint16_t startingVal = 0;
    while (startingVal < digitsLength && digits[startingVal] == 0){
        startingVal++;
    }
    //rids corresponding 0s
    if (startingVal == digitsLength){
        //check
        if (outputSize < 2){
            return false;
        }
        output[0] = BOOK[0];
        output[1] = '\0'; //ender
        return true;
    }

    //builds resulting num in buffer
    char temp[MAX_BITS];
    uint16_t tempLength = 0;
    uint16_t length = digitsLength - startingVal;
    memmove(digits, digits + startingVal, length);

    while (length > 0){
        uint16_t carry = 0;
        uint16_t convlength = 0;
        for (uint16_t i = 0; i < length; i++){
            //current number calculated from base and builder carries value
            uint16_t current = carry * fromBase + (uint8_t)digits[i];
            uint16_t conv = current/toBase;
            carry = current % toBase;

            //conv repetition
            if (convlength > 0 || conv != 0){
                digits[convlength++] = (char)conv;
            }
        }

        //invalidation check
        if (tempLength >= sizeof(temp)){
            return  false;
        }

        //tempoart filled with carry value
        temp[tempLength++] = BOOK[carry];
        length = convlength;
    }

    //another corpulent checker
    if (tempLength + 1 > outputSize){
        return false;
    }

    //output handling
    for (uint16_t i = 0; i < tempLength; i++){
        output[i] = temp[tempLength - 1 - i];
    }
    output[tempLength] = '\0'; //ender
    return true;
}

//main conversion validation / part 2
bool conversion(const char* x, uint8_t fromBase, uint8_t toBase, char* output, uint16_t outputSize){
    //simpe tests
    if (!x || !*x) return false; //address
    if (fromBase < 1 || toBase < 1) return false; //emptiness
    if (fromBase > BOOK_LENGTH || toBase > BOOK_LENGTH) return false; //corpulent
    //maybe add a valid inut section (probably unecessary though)

    //unary > unary
    if (fromBase == 1 && toBase == 1){
        uint16_t conv = fromUnary(x);
        return toUnary(conv, output, ((uint8_t)outputSize) > 0 || conv == 0);
    }
    
    //unary > arbitrary
    if (fromBase == 1){
        uint16_t conv = fromUnary(x);
        //conversion @ 0
        if (conv == 0){
            //check
            if (outputSize < 2){
                return false;
            }
            output[0] = BOOK[0];
            output[1] = '\0'; //memory end
            return true;
        }

        //temp storage
        char buffer[MAX_BITS];
        uint16_t num = 0;
        while (conv > 0) {
            buffer[num++] = (char)(conv & toBase); //similar val
            conv /= toBase; // constant division
        }
        
        //corpulent output
        if (num + 1 > outputSize){
            return false;
        }
        
        //filling in digits for arbitrary number conversion
        for (uint16_t i = 0; i < num; i++){
            output[i] = BOOK[(uint8_t) buffer[num - 1 - i]];
        }

        output[num] = '\0';
        return true;
    }

    //arbitrary > unary
    if (toBase == 1){
        uint16_t value = 0;
        //iterating digits/1s...
        for (const char* pos = x; *pos; pos++){
            int16_t dig = bookIndex(*pos, fromBase);
            value *= fromBase;
            value += dig;
        }
    }

    //arbitrary > arbitrary
    char digits[MAX_INPUT_LENGTH];
    uint16_t dgLen = 0;
    for (const char* p = x; *p; p++) {
        //max check
        if (dgLen >= MAX_INPUT_LENGTH){
            return false;
        }
        digits[dgLen++] = (char)bookIndex(*p, fromBase); //sequential digit conversion
    }
    return digitsToBaseStr(digits, dgLen, fromBase, toBase, output, outputSize);

}

//main calculation
bool calculation(const char* oper, char* num1, char* num2, uint8_t fromBase1, uint8_t fromBase2, uint8_t toBase, char* output, uint16_t outputSize){
    //validation for operator (just in case something goes wrong)
    if (!oper || oper[0] == '\0' || oper[1] != '\0'){
        return false;
    }
    if (!num1 || !num2 || !output){
        return false;
    }
    if (toBase < 2 || toBase > BOOK_LENGTH){
        return false;
    }
   
    //set to decimal
    char dec1[64], dec2[64];
    if(!conversion(num1, fromBase1, 10, dec1, sizeof(dec1))){
        return false;
    }
    if(!conversion(num2, fromBase2, 10, dec2, sizeof(dec2))){
        return false;
    }

    long dec1P = atol(dec1); //parsing
    long dec2P = atol(dec2);

    //actual calculations
    long result = 0;
    //cases
    switch(oper[0]) {
        case '+': result = dec1P + dec2P; break;
        case '-': result = dec1P - dec2P; break;
        case '*': result = dec1P * dec2P; break;
        case '/': 
            if (dec2P == 0) return false;
            //SECTION - Truncating:
            //result = dec1P / dec2P;
            //!SECTION
            

            //SECTION - Rounding:
            if ((dec1P >= 0) == (dec2P >= 0)){
                result = (dec1P + dec2P/2) / dec2P;
            } else {
                result = (dec1P - dec2P/2) / dec2P;
            }
            //!SECTION

            break;
        default: return false; //if no operator present (technically shouldn't happen unless the code screw up)
    }
    
    //formatting/decimal conversion
    char decimalResult[32];
    {
        char temp[24];
        uint16_t num = 0;
        bool negativity = (result < 0);
        unsigned long unum = negativity ? (unsigned long)(-result) : (unsigned long) (result);

        //unum establishment
        if (unum == 0){
            temp[num++] = '0';
        }
        while (unum > 0){
            temp[num++] = char('0' + (unum % 10)); unum/=10; //truncation
        }

        //position sector
        uint16_t position = 0;
        if (negativity){
            decimalResult[position++] = '-';
        }
        while (num > 0){
            decimalResult[position++] = temp[--num]; //prefix num to avoid indexing errors
        }
        decimalResult[position] = '\0'; //ender [I should play minecraft soon]
    }

    //revert conversion
    if (decimalResult[0] == '-'){
        if (outputSize < 2){ //potential negative 0
            return false;
        }
        output[0] = '-';
        if (!conversion(decimalResult + 1, 10, toBase, output +1, outputSize - 1)){
            return false;
        }
        return true;
    }
    return conversion (decimalResult, 10, toBase, output, outputSize);
}
//!SECTION



//NOTE ------ [Misc. functions] ------

//LCD Printing
void screenPrint(){
    //Screen 1
    lcd1.setCursor(0, 0);
    lcd1.print(screen[0]);
    lcd1.setCursor(0, 1);
    lcd1.print(screen[1]);

    //Screen 2
    lcd2.setCursor(0, 0);
    lcd2.print(screen[2]);
    lcd2.setCursor(0, 1);
    lcd2.print(screen[3]);
}

//Angle routing for potentiometer
void potentRouting(int potentNum){
    //angle establishment
    int ind = potentNum - 1;
    int rawPotentValue = analogRead(potentLink[ind]);
    currentDegree[ind] = constrain(map(rawPotentValue, 0, 1023, 0, 179), 0, 179)
    
    //value distribution
    const char bookNumbers[] = "0123456789";
    const char bookOperators[] = "+-*/";
    const char bookUpper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char bookLower[] = "abcdefghijklmnopqrstuvwxyz";
    int bookIndex = 0;

    if (potentNum == 1){
        //input
        bookIndex = map(currentDegree[ind], 0, 179, 0, 9);
        potentInput[ind] = bookNumbers[bookIndex];
        
        //scrolling
        for (int i = 0; i < sizeof(scrollPlacement) / sizeof(scrollPlacement[0]; i++){
            scrollPlacement[i] = map(currentDegree[ind], 0, 179, 1, 1+i);
        }
    }

    else if (potentNum == 2){
        //input
        bookIndex = map(currentDegree[ind], 0, 179, 0, 25);
        potentInput[ind] = bookUpper[bookIndex];

        //bases
        potentBases[ind-1] = map(currentDegree[ind], 0, 179, 0, 31);

        //operator
        bookIndex = map(currentDegree[ind], 0, 179, 0, 3);
        operationType = bookOperators[bookIndex];
    }

    else if (potentNum == 3){
        //input
        bookIndex = map(currentDegree[ind], 0, 179, 0, 25);
        potentInput[ind] = bookLower[bookIndex];

        //bases
        potentBases[ind-1] = map(currentDegree[ind], 0, 179, 32, 62);
    }

    /*
    main modules:
        - potent1 => inputs 0-9 scrolling / navigation scrolling
        - potent2 => inputs A-Z scrolling / bases 0-31 scrolling / operations +-*/ scrolling
        - potent3 => inputs a-z scrolling / bases 32-62 scrolling
        - button1 => calc. & convert enter button
        - button2 => calc. & convert backspace button
        - button3 => navigation selection button / calc. & convert next button 
    */
}

void screenSwitch(string target){
    /* Screen template:
        screen = {
        "****************", 
        "****************",
        "****************", 
        "****************"
        };
    */

    //screens
    currentScreen = target;
    if(target == "default){
        screen = {
        "    Press !     ", 
        "    to start    ",
        "     ZzZzZ      ",
        "   ( - . - )    "
        };
    }
    else if (target == "main"){
        screen = {
        "  Base          ", 
        "  Operation     ",
        "  Conversion    ",
        "  Calculation   "
        };
    }
    else if (target == "base setting"){
        screen = {
        "  Base From:    ",
        "  Base To:      ",
        "  back          ",
        "                "
        };
    }
    else if (target == "operation setting"){
        screen = {
        "  Operation:     ",
        "  back          ",
        "                ",
        "                "
        };
    }
    else if (target == "conversion"){
        screen = {
        "  "From" Value: ",
        "                ",
        "  "To" Value:   ",
        "                "
        };
    }
    else if (target == "conversion execute"){
        "****************"
        screen = {
        "  Result:       ",
        "                ",
        "                ",
        "  back          "
        };
    }
    else if (target == "calculation"){
        "****************"
        screen = {
        "  Value 1:      ",
        "                ",
        "  Value 2:      ",
        "                "
        };
    }
    else if (target == "calculation execute"){
        screen = {
        "  Result:       ",
        "                ",
        "                ",
        "  back          "
        };
    }

    screenPrint();
}

void defaults(){
    //reset variables
    fromBase = 10;
    toBase = 10;
    operationType = '+';
    value1[] = "0"; 
    value2[] = "0"; 
    result[] = "0";

    currentDegree[] = {0, 0, 0}; 
    scrollPlacement[] = {1, 1, 1, 1}; 
    potentInput[] = "0Aa"; 
    potentBases[] = {0,32};    

    //reset potentiometers
    for (int pot = 1; pot < 4; pot++){
        potentRouting(pot);
    }
    
    screenSwitch("default");
    screenPrint();
}


//NOTE ------ [Initialization] ------
void setup() 
{
    
    Serial.begin(9600);

    //Pin settings
    myServo.attach(serv);
    pinMode(piezo, OUTPUT);

    lcd1.begin(16, 2);
    lcd2.begin(16, 2);
    lcd1.setBacklight(0);
    lcd2.setBacklight(0);

    defaults();
}



//NOTE - Copy-paste everything in this loop() to the IRL loop()
void loop()
{
    //power toggle
    if (digitalRead(mainButtonLink) == HIGH && power == false){
        power = true;
        screenSwitch("main");
    }
    else if (digitalRead(mainButtonLink) == HIGH && power == true){
        power = false;
        defaults();
    }
    
    //main
    if (power){
        //set scrolling on main screen
        if (currentScreen == "main"){
            
        }
        

    } else {
        defaults();
    }


    /*
    //connection variables
    mainButtonLink = 8; 
    piezoLink = 9; 
    servoLink = 10;
    potentLink = {A0, A1, A2};
    buttonLink = {2, 3, 4};

    
    currentScreen = "default"
    fromBase = 10; 
    toBase = 10;
    operationType = '+'; 
    value1[] = "0"; 
    value2[] = "0";
    result[] = "0"; 
    currentDegree[] = {0, 0, 0}; 
    scrollPlacement[] = {1, 1, 1, 1}; 
    potentInput[] = "0Aa"; 
    potentBases[] = {0,32}; 
    */
    
}


//TODO - Literally a list
// * Add the Tinkercad design/link to github README etc.
//      - Maybe also include pictures of different sections???
// * piece main os together from manual


//NOTE ------ [Manual] ------
/* How to read notes:
    - Module Format: [Applicable region] [function/values] [interaction type] 
    - Parenthesis: [default value] <clarification> {max digit length allowed} (notes)
    - % = selection placeholder (if selected)
    - # = value placeholder

    main os:
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
        - % "From" Value:
        - % # [0] {14} 
        - % "To" Value:
        - % # [0] {14}

    - Conversion execute screen:
        - % Result:
        - # [0] {16} 
        - # [0] {16}
        - % back 

    - Calculation screen
        - % Value 1:
        - % # [0] {14}
        - % Value 2:
        - % # [0] {14}
        
    - calculation execute screen:
        - % Result:
        - # [0] {16} (part 1 of result) 
        - # [0] {16} (part 2 of result)
        - % back 

    main modules:
        - potent1 => inputs 0-9 scrolling / navigation scrolling
        - potent2 => inputs A-Z scrolling / bases 0-31 scrolling / operations +-*/ scrolling
        - potent3 => inputs a-z scrolling / bases 32-62 scrolling
        - button1 => calc. & convert enter button
        - button2 => calc. & convert backspace button
        - button3 => navigation selection button / calc. & convert next button 

*/


