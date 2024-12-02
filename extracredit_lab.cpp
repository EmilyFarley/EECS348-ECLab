#include <iostream>
#include <iomanip> 
#include <string>  

using namespace std;

//function to extract numeric value from a string
double extractNumeric(const string& inputString) {
    //check if string is empty or too long
    if (inputString.empty() || inputString.length() > 20) {
        return -999999.99; //return  error value
    }

    //flags to track parsing states
    bool isSignPresent = false; //checks if sign is present
    bool isDecimalPointPresent = false; // checks if decimal point is present
    bool isDigitFound = false;  //checks if digits are found
    double extractedValue = 0.0; //store the numeric result
    double fractionalMultiplier = 0.1; //for handling fractional digits

    //loop through each character in string
    for (size_t index = 0; index < inputString.length(); index++) {
        char currentChar = inputString[index]; //current 

        //ceck for a sign at beginning
        if ((currentChar == '+' || currentChar == '-') && index == 0) {
            isSignPresent = true; //mark that sign is present
        }
        //if the character is digit
        else if (isdigit(currentChar)) {
            isDigitFound = true; //mark that digits are found
            if (isDecimalPointPresent) {
                //build fraction part
                extractedValue += (currentChar - '0') * fractionalMultiplier;
                fractionalMultiplier *= 0.1; //move to the next place
            } else {
                //build integer part
                extractedValue = extractedValue * 10 + (currentChar - '0');
            }
        }
        //check for the first decimal point
        else if (currentChar == '.' && !isDecimalPointPresent) {
            isDecimalPointPresent = true; 
        }
        //if invalid character is found
        else {
            return -999999.99; //return an error value
        }
    }

    //no digits found return an error
    if (!isDigitFound) {
        return -999999.99;
    }

    //apply negative sign 
    if (inputString[0] == '-') {
        extractedValue = -extractedValue;
    }

    return extractedValue; //return parsed numeric value
}


int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}
