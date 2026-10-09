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

string toBinary(string c, string tempBook){
    //literally just its index...
    int ind = tempBook.find(c);
    //FIXME -arduino- int ind = tempBook.indexOf(c);

    //establish bit length of binary: 2,4,6,8 max
    string bitLength = "";
    for (int bl = 1; bl < tempBook.size(); bl*2){
        bitLength = bitLength + "0";
    }

    //set bitlength accordingly
}


//assume you are inputted a valid string (string) and the base to convert to (int)
string conversion(string x, int base){
    string converted = "";
    //setting base to the book
    const string currentBook = book.substr(0,base);
    //FIXME -arduino- const string currentBook = book.substring(0,base);

    //convert to binary (easiest)
    for (int a = 0; a < x.size(); a++){
        for (int b = 0; b < currentBook.size(); b++){
            
        }
    }

    return converted;
}


int main()
{
    cout << toBinary("7", "012345678");

    return 0;
}
