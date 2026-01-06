#include <stdio.h>
#include <math.h>  // For fabs function to handle floating-point comparison

/*
This program calculates whether it's more beneficial to pay off a loan before investing
or to make only minimum payments on a loan while investing the remaining money.
*/

// Function for User input + validation
void get_user_inputs(double *owed_amount, double *interest, double *minimum_payment, double *retirement_money, int *current_age, int *retired_age, double *rate_of_return) {
    do {
        printf("Enter how much you owe in loans: ");
        scanf("%lf", owed_amount);
    } while (*owed_amount < 0);

    do {
        printf("Enter the annual interest rate of the loans: ");
        scanf("%lf", interest);
    } while (*interest < 0);

    do {
        printf("Enter your minimum monthly loan payment: ");
        scanf("%lf", minimum_payment);
    } while (*minimum_payment < 0);

    // Monthly contribution: has to be greater than or equal to minimum payment
    do {
        printf("Enter how much money you will be putting towards loans/retirement each month: ");
        scanf("%lf", retirement_money);
    } while (*retirement_money < *minimum_payment);

    // Current age: can't be negative
    do {
        printf("Enter your current age: ");
        scanf("%d", current_age);
    } while (*current_age < 0);

    // Retirement age: must be greater than or equal to current age
    do {
        printf("Enter the age you plan to retire at: ");
        scanf("%d", retired_age);
    } while (*retired_age < *current_age);

    // Annual rate of return has to be greater than or equal to 0
    do {
        printf("Enter your predicted annual rate of return: ");
        scanf("%lf", rate_of_return);
    } while (*rate_of_return < 0);
}

// Function to calculate final balance if only minimum payments are made
double loan_strategy(double owed_amount, double interest, double minimum_payment, double retirement_money, double rate_of_return, int months_to_retirement) {
    double loan_balance = owed_amount;
    double investment_balance = 0.0;
    double loan_monthly_rate = interest / 12;
    double investment_monthly_rate = rate_of_return / 12;

    for (int month = 0; month < months_to_retirement; month++) {
        // Apply monthly interest to loan
        loan_balance += loan_balance * loan_monthly_rate;

        // Apply monthly interest to investments
        investment_balance += investment_balance * investment_monthly_rate;

        // Deduct minimum payment from loan balance
        loan_balance -= minimum_payment;

        // If loan is overpaid, add the excess to investments and set loan balance to zero
        if (loan_balance < 0) {
            investment_balance += fabs(loan_balance);
            loan_balance = 0;
        }

        // Add remaining money to investments
        investment_balance += retirement_money - minimum_payment;
    }

    // After retirement, any remaining loan balance will be deducted from investments
    return investment_balance - loan_balance;
}

// Function to calculate investment balance if loan is paid off first
double investment_strategy(double owed_amount, double interest, double retirement_money, double rate_of_return, int months_to_retirement) {
    double loan_balance = owed_amount;
    double investment_balance = 0.0;
    double loan_monthly_rate = interest / 12;
    double investment_monthly_rate = rate_of_return / 12;

    for (int month = 0; month < months_to_retirement; month++) {
        if (loan_balance > 0) {
            // Apply loan interest and pay full retirement money toward the loan
            loan_balance += loan_balance * loan_monthly_rate;
            loan_balance -= retirement_money;
            if (loan_balance < 0) {
                investment_balance += -loan_balance;
                loan_balance = 0;
            }
        } else {
            // Add entire retirement money to investment if loan is cleared
            investment_balance += investment_balance * investment_monthly_rate + retirement_money;
        }
    }

    // After retirement, any remaining loan balance will be deducted from investments
    return investment_balance - loan_balance;
}

// Updated function to compare strategies with simplified comparison
void compare_strategies(double balance_min_payment, double balance_full_repayment, double retirement_money) {
    if (balance_min_payment + 0.00001 >= balance_full_repayment) {
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
        printf("If you do you will have $%.2f when you retire as opposed to $%.2f if you paid off your loan before investing.\n", balance_min_payment, balance_full_repayment);
    } else {
        printf("You should apply all $%.2f towards your loan before making any investments.\n", retirement_money);
        printf("If you do you will have $%.2f when you retire as opposed to $%.2f if you only made minimum payments.\n", balance_full_repayment, balance_min_payment);
    }
}

int main() {
    // Defining variables
    double owed_amount, interest, minimum_payment, retirement_money, rate_of_return;
    int current_age, retired_age;

    // Run function to get input
    get_user_inputs(&owed_amount, &interest, &minimum_payment, &retirement_money, &current_age, &retired_age, &rate_of_return);

    // Calculate the number of months to retirement
    int months_to_retirement = (retired_age - current_age) * 12;

    // Calculate total money for each of the two strategies
    double balance_min_payment = loan_strategy(owed_amount, interest, minimum_payment, retirement_money, rate_of_return, months_to_retirement);
    double balance_full_repayment = investment_strategy(owed_amount, interest, retirement_money, rate_of_return, months_to_retirement);

    // Compare the total money from both the strategies
    compare_strategies(balance_min_payment, balance_full_repayment, retirement_money);

    return 0;
}
