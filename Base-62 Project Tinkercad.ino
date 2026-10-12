//---------------------- TINKERCAD ----------------------

//NOTE ------ [LCD imports/init] ------
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd1(7); //Top/Left Display
Adafruit_LiquidCrystal lcd2(6); //Bottom/Right Display



//NOTE ------ [Normal imports] ------
#include <Servo.h>
Servo keyboardMotor;



//setting definitions
#define MAX_BOOK_LENGTH 62
#define MAX_VALUE_LENGTH 14
#define MAX_INPUT_LENGTH 16 //limit to 16 in the LCD
#define MAX_BITS 64 //binary buffer/temp storage
#define UNARY_SYM '1'



//NOTE ------ [Global variables] ------
//connection variables
const int mainButtonLink = 8; const int piezoLink = 9; const int servoLink = 10;
const int potentLink[] = {A0, A1, A2};
const int buttonLink[] = {2, 3, 4};

//screen stuff
char screen[4][17] = {"****************", "****************", "****************", "****************"};
char lastScreen[4][17] = {"", "", "", ""};

//operation variables
char currentScreen[24] = "default";
bool power = false; //tracks turning machine on/off
bool lastButtonState = HIGH;
int fromBase = 10; //conversion from base setting
int toBase = 10; //conversion to base setting
char operationType = '+'; //operation setting
char value1[16] = "0"; //input value (only updates after confirmation)
char value2[16] = "0"; //input value (only updates after confirmation)
char resultStr[33] = "0"; // calculation or conversion result

int currentDegree[3] = {0, 0, 0}; //potentiometer current degree
int currentRow = 1; //selected row on a scrolling screen
char potentInput[4] = {'0', 'A', 'a', '\0'};
int potentBases[2] = {1, 32};
int potentChange = 0;
int activePot = 1;
int inputField = 0;

bool lastBtn[3] = {HIGH, HIGH, HIGH};
bool btnPressed[3] = {false, false, false};



//STUB ------ [C++ code] ------
//SECTION
//derive chars thru list
const char BOOK[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const uint8_t BOOK_LENGTH = 62;

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
    return bits;
}

//special cases (in a sense):
//conversions for unary
uint16_t fromUnary(const char* s, char sym = UNARY_SYM){
    uint16_t count = 0;
    for (const char* p = s; *p; p++){
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
    output[val] = '\0';
    return (uint8_t)val;
}

//conversion to binary
uint8_t toBinary(char c, uint8_t base, char* outputt, uint8_t outputSize){
    int16_t ind = bookIndex(c, base);
    if (ind < 0) {
        return 0;
    }

    uint8_t bits = bitLength(base);
    if (bits + 1 > outputSize){
        return 0;
    }

    for (uint8_t i = 0; i < bits; i++){
        outputt[bits-1-i] = char('0' + (ind & 1));
        ind >>= 1;
    }

    outputt[bits] = '\0';
    return bits;
}

//conversion part 1 through constant division
bool digitsToBaseStr(char* digits, uint16_t digitsLength, uint8_t fromB, uint8_t toB, char* output, uint16_t outputSize){
    //get rid of leading 0s
    uint16_t startingVal = 0;
    while (startingVal < digitsLength && digits[startingVal] == 0){
        startingVal++;
    }
    if (startingVal == digitsLength){
        if (outputSize < 2){
            return false;
        }
        output[0] = BOOK[0];
        output[1] = '\0';
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
            uint16_t current = carry * fromB + (uint8_t)digits[i];
            uint16_t conv = current / toB;
            carry = current % toB;

            if (convlength > 0 || conv != 0){
                digits[convlength++] = (char)conv;
            }
        }

        if (tempLength >= sizeof(temp)){
            return false;
        }

        temp[tempLength++] = BOOK[carry];
        length = convlength;
    }

    if (tempLength + 1 > outputSize){
        return false;
    }

    for (uint16_t i = 0; i < tempLength; i++){
        output[i] = temp[tempLength - 1 - i];
    }
    output[tempLength] = '\0';
    return true;
}

//main conversion validation / part 2
bool conversion(const char* x, uint8_t fromB, uint8_t toB, char* output, uint16_t outputSize){
    //simple tests
    if (!x || !*x) return false;
    if (fromB < 1 || toB < 1) return false;
    if (fromB > BOOK_LENGTH || toB > BOOK_LENGTH) return false;

    //unary > unary
    if (fromB == 1 && toB == 1){
        uint16_t conv = fromUnary(x);
        if (conv == 0){
            if (outputSize < 1) return false;
            output[0] = '\0';
            return true;
        }
        return toUnary(conv, output, (uint8_t)(outputSize > 255 ? 255 : outputSize)) > 0;
    }

    //unary > arbitrary
    if (fromB == 1){
        uint16_t conv = fromUnary(x);
        if (conv == 0){
            if (outputSize < 2){
                return false;
            }
            output[0] = BOOK[0];
            output[1] = '\0';
            return true;
        }

        char buffer[MAX_BITS];
        uint16_t num = 0;
        while (conv > 0) {
            buffer[num++] = (char)(conv % toB);
            conv /= toB;
        }

        if (num + 1 > outputSize){
            return false;
        }

        for (uint16_t i = 0; i < num; i++){
            output[i] = BOOK[(uint8_t) buffer[num - 1 - i]];
        }

        output[num] = '\0';
        return true;
    }

    //arbitrary > unary
    if (toB == 1){
        uint32_t value = 0;
        for (const char* pos = x; *pos; pos++){
            int16_t dig = bookIndex(*pos, fromB);
            if (dig < 0) return false;
            value = value * fromB + dig;
            if (value > 65535UL) return false;
        }

        if (value == 0){
            if (outputSize < 1) return false;
            output[0] = '\0';
            return true;
        }
        return toUnary((uint16_t)value, output, (uint8_t)(outputSize > 255 ? 255 : outputSize)) > 0;
    }

    //arbitrary > arbitrary
    char digits[MAX_INPUT_LENGTH];
    uint16_t dgLen = 0;
    for (const char* p = x; *p; p++) {
        if (dgLen >= MAX_INPUT_LENGTH){
            return false;
        }
        int16_t dig = bookIndex(*p, fromB);
        if (dig < 0) return false;
        digits[dgLen++] = (char)dig;
    }
    return digitsToBaseStr(digits, dgLen, fromB, toB, output, outputSize);
}

//main calculation
bool calculation(const char* oper, char* num1, char* num2, uint8_t fromBase1, uint8_t fromBase2, uint8_t toB, char* output, uint16_t outputSize){
    if (!oper || oper[0] == '\0' || oper[1] != '\0'){
        return false;
    }
    if (!num1 || !num2 || !output){
        return false;
    }
    if (toB < 1 || toB > BOOK_LENGTH){
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
    if (strlen(dec1) > 9 || strlen(dec2) > 9){
        return false;
    }

    long dec1P = atol(dec1);
    long dec2P = atol(dec2);

    long res = 0;
    switch(oper[0]) {
        case '+': res = dec1P + dec2P; break;
        case '-': res = dec1P - dec2P; break;
        case '*':
            if (dec1P != 0 && dec2P > 2147483647L / dec1P) return false;
            res = dec1P * dec2P;
            break;
        case '/':
            if (dec2P == 0) return false;
            //Rounding:
            if ((dec1P >= 0) == (dec2P >= 0)){
                res = (dec1P + dec2P/2) / dec2P;
            } else {
                res = (dec1P - dec2P/2) / dec2P;
            }
            break;
        default: return false;
    }

    //formatting/decimal conversion
    char decimalResult[32];
    {
        char temp[24];
        uint16_t num = 0;
        bool negativity = (res < 0);
        unsigned long unum = negativity ? (unsigned long)(-res) : (unsigned long)(res);

        if (unum == 0){
            temp[num++] = '0';
        }
        while (unum > 0){
            temp[num++] = char('0' + (unum % 10)); unum /= 10;
        }

        uint16_t position = 0;
        if (negativity){
            decimalResult[position++] = '-';
        }
        while (num > 0){
            decimalResult[position++] = temp[--num];
        }
        decimalResult[position] = '\0';
    }

    //revert conversion
    if (decimalResult[0] == '-'){
        if (outputSize < 2){
            return false;
        }
        output[0] = '-';
        return conversion(decimalResult + 1, 10, toB, output + 1, outputSize - 1);
    }
    return conversion(decimalResult, 10, toB, output, outputSize);
}
//!SECTION



//NOTE ------ [Misc. functions] ------

//LCD Printing
void screenPrint(){
    for (int row = 0; row < 4; row++){
        Adafruit_LiquidCrystal& lcd = (row < 2) ? lcd1 : lcd2;
        bool placed = false;
        for (int col = 0; col < 16; col++){
            if (screen[row][col] != lastScreen[row][col]){
                if (!placed){
                    lcd.setCursor(col, row % 2);
                    placed = true;
                }
                lcd.write(screen[row][col]);
                lastScreen[row][col] = screen[row][col];
            }
            else {
                placed = false;
            }
        }
    }
}

//Button chime
void chime(){
    for (int i = 0; i < 60; i++){
        digitalWrite(piezoLink, HIGH);
        delayMicroseconds(250);
        digitalWrite(piezoLink, LOW);
        delayMicroseconds(750);
    }
}

//Angle routing for potentiometer
void potentRouting(int potentNum){
    int ind = potentNum - 1;
    int rawPotentValue = analogRead(potentLink[ind]);
    int newDegree = constrain(map(rawPotentValue, 0, 1023, 0, 179), 0, 179);

    if (newDegree != currentDegree[ind]){
        potentChange = potentNum;
    }
    currentDegree[ind] = newDegree;

    //value distribution
    const char bookNumbers[] = "0123456789";
    const char bookUpper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char bookLower[] = "abcdefghijklmnopqrstuvwxyz";

    if (potentNum == 1){
        potentInput[0] = bookNumbers[newDegree * 10 / 180];
    }
    else if (potentNum == 2){
        potentInput[1] = bookUpper[newDegree * 26 / 180];
        potentBases[0] = 1 + newDegree * 31 / 180;
    }
    else if (potentNum == 3){
        potentInput[2] = bookLower[newDegree * 26 / 180];
        potentBases[1] = 32 + newDegree * 31 / 180;
    }

    /*
    main modules:
        - potent1 => inputs 0-9 scrolling / navigation scrolling
        - potent2 => inputs A-Z scrolling / bases 0-31 scrolling / operations +-* / scrolling
        - potent3 => inputs a-z scrolling / bases 32-62 scrolling
        - button1 => calc. & convert enter button
        - button2 => calc. & convert backspace button
        - button3 => navigation selection button / calc. & convert next button
    */
}

//holds every screen
void screenSwitch(const char* target){
    strcpy(currentScreen, target);
    if (strcmp(target, "default") == 0){
        strcpy(screen[0], "    Press !     ");
        strcpy(screen[1], "    to start    ");
        strcpy(screen[2], "     ZzZzZ      ");
        strcpy(screen[3], "   ( - . - )    ");
    }
    else if (strcmp(target, "main") == 0){
        strcpy(screen[0], "  Base          ");
        strcpy(screen[1], "  Operation     ");
        strcpy(screen[2], "  Conversion    ");
        strcpy(screen[3], "  Calculation   ");
    }
    else if (strcmp(target, "base setting") == 0){
        strcpy(screen[0], "  Base From:    ");
        strcpy(screen[1], "  Base To:      ");
        strcpy(screen[2], "  back          ");
        strcpy(screen[3], "                ");
    }
    else if (strcmp(target, "operation setting") == 0){
        strcpy(screen[0], "  Operation:    ");
        strcpy(screen[1], "  back          ");
        strcpy(screen[2], "                ");
        strcpy(screen[3], "                ");
    }
    else if (strcmp(target, "conversion") == 0){
        strcpy(screen[0], "  \"From\" Value: ");
        strcpy(screen[1], "                ");
        strcpy(screen[2], "                ");
        strcpy(screen[3], "                ");
        inputField = 0;
    }
    else if (strcmp(target, "conversion execute") == 0){
        strcpy(screen[0], "  Result:       ");
        strcpy(screen[1], "                ");
        strcpy(screen[2], "                ");
        strcpy(screen[3], "% back          ");
    }
    else if (strcmp(target, "calculation") == 0){
        strcpy(screen[0], "  Value 1:      ");
        strcpy(screen[1], "                ");
        strcpy(screen[2], "  Value 2:      ");
        strcpy(screen[3], "                ");
        inputField = 0;
    }
    else if (strcmp(target, "calculation execute") == 0){
        strcpy(screen[0], "  Result:       ");
        strcpy(screen[1], "                ");
        strcpy(screen[2], "                ");
        strcpy(screen[3], "% back          ");
    }

    screenPrint();
}

//resets all variables and screens
void defaults(){
    keyboardMotor.write(0);
    fromBase = 10;
    toBase = 10;
    operationType = '+';
    strcpy(value1, "0");
    strcpy(value2, "0");
    strcpy(resultStr, "0");

    currentDegree[0] = currentDegree[1] = currentDegree[2] = 0;
    currentRow = 1;
    inputField = 0;
    activePot = 1;
    strcpy(potentInput, "0Aa");
    potentBases[0] = 1; potentBases[1] = 32;

    for (int pot = 1; pot < 4; pot++){
        potentRouting(pot);
    }
    potentChange = 0;

    screenSwitch("default");
}

//manages scrolling behavior
void scrolling(int rows){
    currentRow = 1 + currentDegree[0] * rows / 180;

    for (int i = 0; i < 4; i++){
        screen[i][0] = ' ';
    }
    screen[currentRow - 1][0] = '%';
}

//fixed selection marker
void marker(int row){
    for (int i = 0; i < 4; i++){
        screen[i][0] = ' ';
    }
    screen[row][0] = '%';
}

//writes a 1-2 digit number at columns 13-14 of a row
void printNumber(int row, int n){
    if (n > 9){
        screen[row][13] = (n / 10) + '0';
        screen[row][14] = (n % 10) + '0';
    } else {
        screen[row][13] = n + '0';
        screen[row][14] = ' ';
    }
}

//actual display of row
void rowPrint(int row, int start, const char* text){
    int pos = start;
    //text throughout row
    while (*text && pos < 16){
        screen[row][pos++] = *text++;
    }
    //endspace filler
    while (pos < 16){
        screen[row][pos++] = ' ';
    }
}

//[LCD] row value set
void valueRow(int row, const char* value, bool act){
    char display[MAX_VALUE_LENGTH + 2];
    strcpy(display, value);
    if (act) {
        int len = strlen(display);
        if(strcmp(value, "0") == 0){
            len = 0;
        }
        if (len < MAX_VALUE_LENGTH){
            display[len] = potentInput[activePot - 1];
            display[len+1] = '\0'; //ender
        }
    }
    rowPrint(row, 2, display);
}

//character validation
bool validChar(char c, int base){
    if (base == 1){
        return c == UNARY_SYM;
    }
    return bookIndex(c, base) >= 0;
}

//displays number in execution screen
void showResult(){
    if (resultStr[0] == '\0'){
        strcpy(resultStr, "0");
    }
    rowPrint(1, 0, resultStr);
    //moving to 2nd row
    if (strlen(resultStr) > 16){
        rowPrint(2, 0, resultStr + 16);
    }
    else {
        rowPrint(2, 0, "");
    }
}

//value editor (for enter/backspace)
void editValue(char* current){
    //enter
    if (btnPressed[0]){
        char pick = potentInput[activePot - 1];
        int length = strlen(current);
        if (strcmp(current, "0") == 0){
            length = 0;
        }
        if (validChar(pick, fromBase) && length < MAX_VALUE_LENGTH){
            current[length] = pick;
            current[length + 1] = '\0'; //ender
        }
    }
    //backspace
    if (btnPressed[1]){
        int length = strlen(current);
        if (length > 1){
            current[length-1] = '\0';
        }
        else {
            strcpy(current, "0");
        }
    }
}


//NOTE ------ [Initialization] ------
void setup() {

    //Serial.begin(9600);

    //Pin settings
    keyboardMotor.attach(servoLink);
    pinMode(piezoLink, OUTPUT);
    pinMode(mainButtonLink, INPUT_PULLUP);
    pinMode(buttonLink[0], INPUT_PULLUP);
    pinMode(buttonLink[1], INPUT_PULLUP);
    pinMode(buttonLink[2], INPUT_PULLUP);

    lcd1.begin(16, 2);
    lcd2.begin(16, 2);
    lcd1.setBacklight(1);
    lcd2.setBacklight(1);

    defaults();
}



//NOTE - Copy-paste everything in this loop() to the IRL loop()
void loop() {
    //button reading
    bool mainButtonState = digitalRead(mainButtonLink);
    bool mainPressed = (mainButtonState == LOW && lastButtonState == HIGH);
    lastButtonState = mainButtonState;

    for (int b = 0; b < 3; b++){
        bool now = digitalRead(buttonLink[b]);
        btnPressed[b] = (now == LOW && lastBtn[b] == HIGH);
        lastBtn[b] = now;
    }

    if (mainPressed || btnPressed[0] || btnPressed[1] || btnPressed[2]){
        chime();
    }

    //power toggle
    if (mainPressed){
        if (power == false){
            power = true;
            screenSwitch("main");
        }
        else {
            power = false;
            defaults();
        }
    }

    //powered
    if (power){
        //tracks potentiometer changes
        potentChange = 0;
        for (int pot = 1; pot < 4; pot++){
            potentRouting(pot);
        }
        if (potentChange != 0){
            activePot = potentChange;
        }
        
        //dealing with motors:
        if (mainPressed){
            if (power == false){
                power = true;
                keyboardMotor.write(180);
                screenSwitch("main");
            }
            else {
                power = false;
                defaults();
            }
        }

        if (strcmp(currentScreen, "main") == 0){
            scrolling(4);
            if (btnPressed[2]){
                const char* toScreen[] = {"base setting", "operation setting", "conversion", "calculation"};
                screenSwitch(toScreen[currentRow - 1]);
            }
        }

        else if (strcmp(currentScreen, "base setting") == 0){
            scrolling(3);

            if (potentChange == 2 || potentChange == 3){
                int newBase = (potentChange == 2) ? potentBases[0] : potentBases[1];
                if (currentRow == 1){
                    fromBase = newBase;
                }
                else if (currentRow == 2){
                    toBase = newBase;
                }
            }

            printNumber(0, fromBase);
            printNumber(1, toBase);

            if (btnPressed[2] && currentRow == 3){
                screenSwitch("main");
            }
        }

        else if (strcmp(currentScreen, "operation setting") == 0){
            scrolling(2);

            const char bookOperators[] = "+-*/";
            if (currentRow == 1 && potentChange == 2){
                operationType = bookOperators[currentDegree[1] * 4 / 180];
            }
            screen[0][13] = operationType;

            if (btnPressed[2] && currentRow == 2){
                screenSwitch("main");
            }
        }

        else if (strcmp(currentScreen, "conversion") == 0){
            editValue(value1);

            char preview[15];
            if (!conversion(value1, fromBase, toBase, preview, sizeof(preview))){
                strcpy(preview, "?");
            }
            valueRow(1, value1, true);
            marker(1);

            if (btnPressed[2]){
                if (!conversion(value1, fromBase, toBase, resultStr, sizeof(resultStr))){
                    strcpy(resultStr, "Error");
                }
                screenSwitch("conversion execute");
                showResult();
            }
        }

        else if (strcmp(currentScreen, "conversion execute") == 0){
            if (btnPressed[2]){
                screenSwitch("main");
            }
        }

        else if (strcmp(currentScreen, "calculation") == 0){
            editValue(inputField == 0 ? value1 : value2);
            valueRow(1, value1, inputField == 0);
            valueRow(3, value2, inputField == 1);
            marker(inputField * 2 + 1);

            if (btnPressed[2]){
                if (inputField == 0){
                    inputField = 1;
                }
                else {
                    char oper[2] = {operationType, '\0'};
                    if (!calculation(oper, value1, value2, fromBase, fromBase, toBase, resultStr, sizeof(resultStr))){
                        strcpy(resultStr, "Error");
                    }
                    screenSwitch("calculation execute");
                    showResult();
                }
            }
        }

        else if (strcmp(currentScreen, "calculation execute") == 0){
            if (btnPressed[2]){
                screenSwitch("main");
            }
        }

        screenPrint();
    }

    delay(10);
}


//TODO - Literally a list
// * Add the Tinkercad design/link to github README etc.
//      - Maybe also include pictures of different sections???
// * make the motor work


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
        -   "From" Value:
        - % # [0] {14}

    - Conversion execute screen:
        - % Result:
        - # [0] {16}
        - # [0] {16}
        - % back

    - Calculation screen
        -   Value 1:
        - % # [0] {14}
        -   Value 2:
        - % # [0] {14}

    - calculation execute screen:
        - % Result:
        - # [0] {16} (part 1 of result)
        - # [0] {16} (part 2 of result)
        - % back

    main modules:
        - potent1 => inputs 0-9 scrolling / navigation scrolling
        - potent2 => inputs A-Z scrolling / bases 0-31 scrolling / operations +-* / scrolling
        - potent3 => inputs a-z scrolling / bases 32-62 scrolling
        - button1 => calc. & convert enter button
        - button2 => calc. & convert backspace button
        - button3 => navigation selection button / calc. & convert next button

*/
