#include <stdio.h>
#include <stdbool.h>
#include <math.h>
typedef struct FinancialIdentity{
  double savings;
  double checking;
  double debt;
  double mortgage;
  double yearsWithDebt;
  double yearsRented;
  double debtPaid;
  bool ownsHouse;
} FinancialIdentity;

void savingsPlacement(FinancialIdentity *name, double interestRate);

void debt(FinancialIdentity *name, double interestRate, double addlePay);

void rent(FinancialIdentity *name, double rentAmount);

void house(FinancialIdentity *name, double mortgageAmount, double interestRate, int mortgageTerm);

int*  simulate(FinancialIdentity *person, double yearlySalary, bool financiallyLiterate);

void PrintPerson(FinancialIdentity *person){
  printf("savings %f, checking %f, debt %f, mortgage %f, debt paid %f", person->savings, person->checking, person->debt, person->mortgage, person->debtPaid);
}
