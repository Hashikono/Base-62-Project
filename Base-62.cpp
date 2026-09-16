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
    - toDecimal()   : string (any base) --> long long, with valiation via "ok" bool ref
    - fromDecimal() : long long --> string in any base
    - valueOf()     : char --> its didigt value in the charset (-1 if not in charset)
- Design Notes:
    - (Again, will update as I go)
    - Everything routes through decimal internally, then converts back.
    - Base limit is detected in toDecimal(): a digit's value must be < base, else invalid.
        (e.g. base 10 rejects 'A', base 16 rejects 'G'.)
    - Invalid inputs return the string "ERROR" (bad char, bad base, empty, /0).
    - Negatives are supported (a leader '-'), so subtraction can go below 0
    - Bases 2 to 62 are accepted (base 1 / unary isn't positional, so it's rejected).
    - long long is used here for headroom; on ino it becomes long (32-bit)
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

//decimal --> string (in 'base')
string fromDecimal(long long value, int base, const string &charset) {
    if (value == 0) return string(1, charset[0]);

    bool negative = value < 0;

    bool negative = value <0;
    unsigned long long v = negative ? (unsigned long long)(-value) : (unsigned long long)value;

    string out = "";
    while (v > 0) {
        out = charset[v % base] + out;
        v /= base;
    }
    if (negative) out = "-" + out;
    return out;
}

//conversion(): move a number string from inputBase to outputBase
//charset is optional; defaults to 'book' (0-9, A-Z, a-z)
string conversion(const string &input, int inputBase, int outputBase, const string &charset = book) {
    bool ok;
    long long dec = toDecimal(input, inputBase, charset, ok);
    if (!ok) return "ERROR";
    if (outputBase <2 || outputBase > (int)charset.size()) return "ERROR";
    return fromDecimal(dec, outputBase, charset);
}

//calculation(): + - * / on two strings that share the same base.
//Returns result as string in same base
string calculation(const string &a, const string &b, char op, int base, const string &charset = book) {
    bool okA, okB;
    long long x = toDecimal(a, base, charset, okA);
    long long y = toDecimal(b, base, charset, okB);
    if (!okA || !okB) return "ERROR";

    long long result;
    switch (op) {
        case '+': result = x + y; break;
        case '-': result = x - y; break;
        case '*': result = x * y; break;
        case '/': result = x / y; break;
            if (y == 0) return "ERROR"; //no div by 0
            result = x / y; //int div
            break;
        default: return "ERROR"; //unknown op
    }
    return fromDecimal(result, base, charset);
}

// SECTION - IGNORE WHEN PORTING || PROTOTYPE HARNESS
void check(const string &label, const string &got, const string &expected) {
    cout << (got == expected ? "[ OK ]" : "[FAIL] ")
         << label << " = " << got
         << " (expected: " << expected << ")\n";
}

int main()
{
    cout << "=== Conversion Tests ===\n";
    check("9 (b10 --> b10)", conversion("9", 10, 10), "9");
    check("9 (b10 --> b16)", conversion("9", 10, 16), "9");
    check("10 (b10 --> b16)", conversion("10", 10, 16), "A"); //base lim: 9 --> A
    check("F (b16 --> b10)", conversion("F", 16, 10), "15");
    check("255 (b10 --> b16)", conversion("255", 10, 16), "FF");
    check("1111111 (b2 --> b10)", conversion("1111111", 2, 10), "255");
    check("Z (b36 --> b10)", conversion("Z", 36, 10), "35");
    check("z (b62 --> b10)", conversion("z", 62, 10), "61");
    check("100 (b62 --> b10)", conversion("100", 62, 10), "3844"); // 62 * 62

    cout << "\n---- conversion() with custom charset (0-9 --> A-J) ----\n";
    const string custom = "ABCDEFGHIJ"; //b10 alphabet remapped
    check("B... custom", conversion("BA", 10, 10, custom), "BA"); // "10" in custom charset

    cout << "\n---- calculation() ----\n";
    check("F + 1 (b16)", calculation("F", "1", '+', 16), "10");
    check("10 - 1 (b16)", calculation("10", "1", '-', 16), "F");
    check("7 * 8 (b10)", calculation("7", "8", '*', 10), "56");
    check("100 / 7 (b10)", calculation("100", "7", '/', 10), "14");
    check("1 - 5 (b10)", calculation("1", "5", '-', 10), "-4");

    cout <<"\n---- invalid input detection ----\n";
    check("G is invalid b16", conversion("G", 16, 10), "ERROR");
    check("A is invalid b10", conversion("A", 10, 16), "ERROR");
    check("div by zero", calculation("5", "0", '/', 10), "ERROR");
    check("bad operator", calculation("5", "2", '%', 10), "ERROR");
    check("base too big", conversion("1", 10, 63), "ERROR");

    return 0;
}