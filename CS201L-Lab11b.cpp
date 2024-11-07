#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "LinkedList.h"  // Include the header for the LinkedList and Stack
#include "Functions.h"   

using namespace std;

int main() {
    // Open input and output files
    ifstream data("data.txt");
    ofstream report("report.txt");
    ofstream err("error.txt");

    if (!data.is_open() || !report.is_open() || !err.is_open()) {
        err << "Error opening files." << endl;
        return 1;
    }

    string line;

    // Process each line from the input file
    while (getline(data, line)) {
        stringstream ss(line);  // Create a stringstream to parse the line
        Stack myStack;  // Create instance of Stack to store operands
        string token;
        bool invalidExpression = false; 
        string errorMessage = ""; 

        // Store the original expression for logging
        string originalExpression = line;

        try {
            // Process each token in the line
            while (ss >> token) {
                if (isDigit(token)) {
                    // If the token is a number, convert it to an integer and push onto the stack
                    Data tempData;
                    tempData.operand = stoi(token); // Convert string to integer
                    myStack.addNode(tempData); // Push operand to stack
                }
                else if (isOperator(token)) {
                    // If the token is an operator, perform the operation
                    if (myStack.isEmpty()) {
                        // Check if there's enough data to pop for operation
                        throw runtime_error("Too few operands for operation.");
                    }

                    // Delete the top two values from the stack (right operand first, then left operand)
                    Data operand2 = myStack.delNode();  // Right operand
                    if (myStack.isEmpty()) {
                        throw runtime_error("Too few operands for operation.");
                    }
                    Data operand1 = myStack.delNode();  // Left operand
                    int result = 0;

                    // Perform operation based on the operator
                    if (token == "+") {
                        result = operand1.operand + operand2.operand;
                    }
                    else if (token == "-") {
                        result = operand1.operand - operand2.operand;
                    }
                    else if (token == "*") {
                        result = operand1.operand * operand2.operand;
                    }
                    else if (token == "/") {
                        if (operand2.operand == 0) {
                            // Division by zero error
                            throw runtime_error("Operation will result in divide by 0.");
                        }
                        result = operand1.operand / operand2.operand;
                    }

                    // Push the result back onto the stack
                    Data resultData;
                    resultData.operand = result;
                    myStack.addNode(resultData);
                }
                else {
                    // Invalid token 
                    errorMessage = "Input value not recognized.";
                    invalidExpression = true;
                    break;
                }
            }

            // After processing the line there should be one value on stack
            if (!invalidExpression) {
                if (myStack.isEmpty()) {
                    errorMessage = "No result in stack.";
                }
                else {
                    // The result should be the only remaining value in the stack
                    Data finalResult = myStack.delNode();
                    if (!myStack.isEmpty()) {
                        // Too many values left in the stack (invalid postfix expression)
                        errorMessage = "Too few operations to complete calculation.";
                    }
                    else {
                        // Successfully computed the result
                        report << "PROCESSING POSTFIX EXPRESSION: " << originalExpression
                            << " = " << finalResult.operand << endl;
                        continue;
                    }
                }
            }
        }
        catch (const runtime_error& e) {
            // Catch any errors (e.g., insufficient operands, division by zero)
            errorMessage = e.what();
        }

        // If there's an error or invalid expression, output the error message
        if (!invalidExpression && !errorMessage.empty()) {
            report << "PROCESSING POSTFIX EXPRESSION: " << originalExpression
                << " = " << errorMessage << endl;
        }
        else if (invalidExpression) {
            report << "PROCESSING POSTFIX EXPRESSION: " << originalExpression
                << " = " << errorMessage << endl;
        }
    }

    // Close the files
    data.close();
    report.close();
    err.close();

    cout << "Postfix evaluation complete. Check report.txt for results and error.txt for issues.\n";
    return 0;
}
