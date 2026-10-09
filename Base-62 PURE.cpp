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
    return val;
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

    for (uint8_t i = 0; i < bits i++){
        outputt[bits-1-i] = char('0' + (ind & 1)); //AND gates...used only in minecraft
        ind >>= 1; //shifting binary right
    }

    outputt[bits] = '\0'; //sneaky way to make a string
    return bits;
}
//!SECTION

//assume you are inputted a valid string (string), the current base, and the base to convert to (int)
string conversion(string x, int fromBase, int toBase){
    string converted = "";
    //setting bases to books
    const string fromBook = book.substr(0, fromBase);
    const string toBook = book.substr(0, toBase);
    /


    //convert to binary (easiest)
    string binaryTemp = "";
    for (size_t a = 0; a < x.size(); a++){
        char tempC = x[a];
        binaryTemp += toBinary(tempC, fromBook);
    }

    //convert to the desired base:
    //binary length
    int convBinLen = toBinary(toBook[toBook.size()-1], toBook).size();
    int remainder = binaryTemp.size() % convBinLen;
    
    //add empty 0s
    if (remainder != 0){
        size_t extra = convBinLen - remainder;
        binaryTemp = string(extra, '0') + binaryTemp;
    }

    //actual conversion
    for (int y = 0; y < binaryTemp.size()/convBinLen; y++){
        size_t start = y*convBinLen;
        string partition = binaryTemp.substr(start, convBinLen);
        //FIXME -arduino- string partition = binaryTemp.substring(start, convBinLen);

        //partition conversion - yes I stole that term from mint cinnamon
        size_t val = 0;
        for (size_t j = 0; j < partition.size(); j++){
            //gotta love c++ ascii conversions
            val = val * 2 + (partition[j] - '0');
        }

        converted += toBook[val];
    }


    //return binaryTemp;
    return converted;
}


int main()
{
    cout << "hello world: " << toBinary('7', "0123456789ABCDEF");
    cout << "hello world: " << conversion("0572", 8, 2);

    return 0;
}
