/*//TODO - Hello :>
- Make an algorithm that detects the base limit converson
    - Decimal example; 9 -> 10
    - Hexadecimal; F -> 10
- You can also make an optional arguement that allows them to input their own set of characters to use
    - Decimal example; instead of 0-9, they can replace it to be A-J
- One function should be for conversions
- Another function for calculations
    - basic arithmetics to start: + - * /
    - add more functions??? (not sure arduino could support it)
    - Maybe convert everthing to decimal or binary and reconvert it after doing the calculation
- Any other functions you think would help :>
- Try not to make this into a class
- Inputs to these functions will most likely begin as a string
- Functions should also detect for invalid inputs

- name the first function: conversion()
- name the second function: calculation()
- if you make anything else after this please just list them in a bulletin
    - (like turn this section into a bulletin board)
- one module on the LCD is always reserved for system
- convert all strings into a list of char to reduce system usage (albeit it does sound stupid)
- program works for possible valeus that you can input...

- when the user chanegs bases for inputs, clear their selection so only valid inputs can persist
*/

//arduino compatibility
#include <iostream> //temporary
#include <string.h>
#include <stdint.h>
using namespace std;

//setting definitions
#define MAX_BOOK_LENGTH 62
#define MAX_INPUT_LENGTH 16 //limit to 16 in the LCD
#define MAX_BITS 256 //binary buffer/temp storagfe
#define UNARY_SYM '1'

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

//SECTION - special cases (in a sense):
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


//conversion to binary -> making all o fthsi arduino compatible is killing me
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
//!SECTION
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
}


//conversion validation / part 2
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


int main()
{
    //std::cout << "hello world: " << toBinary('7', "0123456789ABCDEF");
    //std::cout << "hello world: " << conversion("0572", 8, 2);

    return 0;
}
