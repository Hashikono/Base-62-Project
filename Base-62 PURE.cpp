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

*/

#include <iostream>
#include <string>
using namespace std;

//derive chars thru list
const string book = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//FIXME - so much to fix when porting to arduino...
string toBinary(char c, const string& tempBook){
    //literally just its index...
    int ind = tempBook.find(c);
    //FIXME -arduino- int ind = tempBook.indexOf(c);

    //establish bit length of binary: 2,4,6,8 max
    size_t bitLength = 0;
    size_t bl = 1;
    while (bl < tempBook.size()){
        bl = bl * 2;
        bitLength++;
    }

    //set bitlength accordingly
    string bits(bitLength, '0');
    for (size_t iii = 0; iii < bitLength; iii++){
        //infill right & shifting :/
        size_t position = bitLength - (1+iii); 
        bits[position] = char('0'+ (ind & 1));
        ind >>= 1;
    }

    return bits;
}


//assume you are inputted a valid string (string), the current base, and the base to convert to (int)
string conversion(string x, int fromBase, int toBase){
    string converted = "";
    //setting bases to books
    const string fromBook = book.substr(0, fromBase);
    const string toBook = book.substr(0, toBase);
    //FIXME -arduino- const string fromBook = book.substring(0, fromBase);
    //FIXME -arduino- const string toBook = book.substring(0, toBase);


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
