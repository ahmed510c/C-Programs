#include <stdio.h>
#include <math.h>

int main(void) {
    // Declare variables for the amount borrowed, annual interest rate, and number of payments
    double amountBorrowed;
    double annualInterestRate;
    int numPayments;

    // Prompt user for the amount borrowed
    // EXACT layout and words, including '$' and newlines
    printf("Please enter the amount of money you borrowed: $");
    scanf("%lf", &amountBorrowed);
    printf("\n");

    // Prompt user for the annual interest rate
    // EXACT layout and words, including newlines
    printf("Please enter the annual interest rate: ");
    scanf("%lf", &annualInterestRate);
    printf("\n");

    // Prompt user for the number of payments
    // EXACT layout and words, including newlines
    printf("Please enter the number of payments to be made: ");
    scanf("%d", &numPayments);
    printf("\n");

    // Convert annual interest rate to monthly
    double monthlyInterestRate = annualInterestRate / 12;

    // Calculate the monthly payment using the standard loan formula:
    // Monthly Payment = P * ( r / (1 - (1 + r)^(-n)) )
    // where P is amountBorrowed, r is monthlyInterestRate, and n is numPayments.
    double monthlyPayment;

    // Handle the case if monthlyInterestRate is 0 to avoid division by zero
    if (monthlyInterestRate == 0.0) {
        monthlyPayment = amountBorrowed / numPayments;
    } else {
        monthlyPayment = amountBorrowed * (monthlyInterestRate) 
                         / (1 - pow(1 + monthlyInterestRate, -numPayments));
    }

    // Calculate total amount paid and the cost of the loan
    double totalPaid = monthlyPayment * numPayments;
    double loanCost = totalPaid - amountBorrowed;

    // Print the results EXACTLY as in the examples (with two decimal places)
    // Matches the wording, spacing, and punctuation.
    printf("A loan of $%.2f with an annual interest of %.2f paid off over %d months will have monthly payments of $%.2f.\n",
           amountBorrowed, annualInterestRate, numPayments, monthlyPayment);
    printf("\n");
    printf("In total, you will pay $%.2f, making the cost of your loan $%.2f.\n",
           totalPaid, loanCost);

    return 0;
}
