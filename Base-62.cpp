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

/* 
BULLETIN BOARD - What got built so far by Videsh.
- conversion()  : converts a string from one base to another (custom charset supported)
- calculation() : does + - * / on two strings in the same base, returns a string
- Helpers added (not classes, just free functions):
    - (Will Update as I go)
- Design Notes:
    - (Again, will update as I go)
*/

#include <iostream>
#include <string>
using namespace std;

//derive chars thru list
const string book = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//char --> digit val within given charset, or-1 if char not found
int valueOf(char c, const string &charset) {
    for (int i = 0; i < (int)charset.size(); i++)
        if (charset[i] == c) return i;
    return -1;
}

// string (in 'base') --> decimal. Sets of=false on any invalid input.
long long toDecimal(const string &input, int base, const string &charset, bool &ok) {
    ok = true;

    //base limit check: has to fiit inside charset and be positional
    if (base < 2 || base > (int)charset.size()) {
        ok = false;
        return 0;
    }

    string s = input;
    bool negative = false;
    if (!s.empty() && s[0] == '-') {
        negative = true;
        s = s.substr(1);
    }
    if (s.empty()) { // "" or just "-" is invalid
        ok = false;
        return 0;
    }

    long long value = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int digit = valueOf(s[i], charset);
        if (digit < 0 || digit >= base) { //out of range fir this base
            ok = false;
            return 0;
        }
    }
    return negative ? -value : value;
}