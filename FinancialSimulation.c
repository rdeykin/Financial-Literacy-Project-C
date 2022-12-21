
#include "FinancialSimulation.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>



void savingsPlacement(FinancialIdentity *name, double interestRate){
  name->savings *= 1 + interestRate;
  //make savings placement
}

void debt(FinancialIdentity *name, double interestRate, double addlPay){
  double debtToBePaid;
  if(name->debt > 0){
  debtToBePaid = ((name->debt)*0.03) + addlPay;
  name->yearsWithDebt +=1;
  }
  else{
    debtToBePaid = 0.0;
    name->debt = 0;
    return;
  }
  if(debtToBePaid > name->debt){
    debtToBePaid = name->debt;
  }
  for(int i = 0; i < 12; i++){
    if(name->debt > 0){
    if(name->checking >= debtToBePaid){
      name->checking = name->checking - debtToBePaid;
      name->debt = name->debt - debtToBePaid;
      name->debtPaid += debtToBePaid;
    }

    if(debtToBePaid > name->checking){
      double diff = debtToBePaid - name->checking;
      name->checking = 0;
      name->savings = name->savings - diff;
      name->debt = name->debt - debtToBePaid;
      name->debtPaid += debtToBePaid;

    }
  }
  else{
    return;
  }
 }
 name->debt *= (1 + interestRate);
}


void rent(FinancialIdentity *name, double rentAmount){
  double rentToBePaid = rentAmount * 12;
  if(name->checking >= rentToBePaid){
    name->checking = name->checking - rentToBePaid;
  }

   else{
    double diff = rentToBePaid - name->checking;
    name->checking = 0;
    name->savings = name->savings - diff;
  }
  name->yearsRented ++;
}

void house(FinancialIdentity *name, double mortgageAmount, double interestRate, int mortgageTerm){
  double yearCount;
  double numberOfPayments = 360;
  double monthlyInterest = interestRate / 12;
  double discountFactor = (pow(1.0 + monthlyInterest, numberOfPayments) -1.0) / (monthlyInterest * pow(1.0 + monthlyInterest, numberOfPayments));
  double monthlyPayment = mortgageAmount / discountFactor;
  for (int i = 0; i < 12; i++){
    if (name->mortgage > 0){
    if(monthlyPayment > name->mortgage){
      monthlyPayment = name->mortgage;
    }
    if(name->checking >= monthlyPayment){
      name->mortgage = name->mortgage - monthlyPayment;
      name->checking = name->checking - monthlyPayment;
    }
    else{
      double diff = monthlyPayment - name->checking;
      name->checking = 0;
      name->savings = name->savings - diff;
      name->mortgage = name->mortgage - monthlyPayment;
    }
    name->mortgage *= (1 + monthlyInterest);
    yearCount++;
  }
 }
}

int* simulate(FinancialIdentity *person, double yearlySalary, bool financiallyLiterate){
  int* wealthArray = (int*)malloc(41*sizeof(int));
  int wealthValue = (person->checking + person->savings) - (person->debt + person->mortgage);
  wealthArray[0] = wealthValue;
  printf("year 0");
  printf("\n");
  PrintPerson(person);
  printf("\n");
  for(int i = 1; i < 41; i++){
    person->savings += (yearlySalary * 0.2);
    person->checking += (yearlySalary * 0.3);

    if(!person->ownsHouse){
      if(financiallyLiterate == true && person->savings >= 42000){
        //buy a house
        person->savings -= 42000;
        person->ownsHouse = true;
        person->mortgage = 210000 - 42000;
      }
      if(financiallyLiterate == false && person->savings >= 10500){
        //buy a house
        person->savings -= 10500;
        person->ownsHouse = true;
        person->mortgage = 210000 - 10500;
      }
    }


  if(person->ownsHouse == true){
    if(financiallyLiterate == true && person-> mortgage > 0){
      //make financially literate mortgage payment for the year
      double payment = 210000 - 42000;
      house(person, payment , 0.045, 30);
    }
    if(financiallyLiterate == false && person->mortgage > 0){
      //make non financially literate mortgage payment for the year
      double payment = 210000 - 10500;
      house(person, payment, 0.05, 30);
    }
  }

  if(financiallyLiterate == true){
    //make financially literate savings placement
    savingsPlacement(person, 0.07);
    debt(person, 0.2, 100);
  }
  if(financiallyLiterate == false){
    //make non financially literate savings placement
    savingsPlacement(person, 0.01);
    debt(person, 0.2, 1);
  }
  if(!person->ownsHouse){
    rent(person, 950);
    //rent a house
  }

  wealthValue = (person->checking + person->savings) - (person->debt + person->mortgage);
  wealthArray[i] = wealthValue;
  //calculate weath values and add them to the wealthArray
  printf("year %d", (i));
  printf("\n");
  PrintPerson(person);
  printf("\n");
}
  return wealthArray;
}

int main(int argc, char* argv[]){

FinancialIdentity financiallyLiterate;
financiallyLiterate.savings = 5000.0;
financiallyLiterate.checking= 0.0;
financiallyLiterate.debt = 52500.0;
financiallyLiterate.mortgage = 0.0;
financiallyLiterate.yearsWithDebt = 0.0;
financiallyLiterate.yearsRented = 0.0;
financiallyLiterate.debtPaid = 0.0;
financiallyLiterate.ownsHouse = false;

FinancialIdentity nonfinanciallyLiterate;
nonfinanciallyLiterate.savings = 5000.0;
nonfinanciallyLiterate.checking= 0.0;
nonfinanciallyLiterate.debt = 52500.0;
nonfinanciallyLiterate.mortgage = 0.0;
nonfinanciallyLiterate.yearsWithDebt = 0.0;
nonfinanciallyLiterate.yearsRented = 0.0;
nonfinanciallyLiterate.debtPaid = 0.0;
nonfinanciallyLiterate.ownsHouse = false;








int* flArray = simulate(&financiallyLiterate, 69000, true);
printf("\n");
int* nflArray = simulate(&nonfinanciallyLiterate, 69000, false);
FILE *Floutput;
Floutput = fopen("output_fl.txt", "w");
for(int i = 0; i < 41; i++){
  fprintf(Floutput, "%d\n",flArray[i]);
}
fclose(Floutput);
FILE *nFloutput;
nFloutput = fopen("output_nfl.txt", "w");
for(int i = 0; i < 41; i++){
  fprintf(nFloutput, "%d\n",nflArray[i]);
}
fclose(nFloutput);
return 0;
}
