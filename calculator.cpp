/***************************
* Рексиус Анастасия        *
* ПИ-221                   *
* Арифметика длинных чисел *
****************************/

#include <bits/stdc++.h>

using namespace std;

bool signMinus(string number) {
  if (number[0] == '-') {
    return true;
  } else {
    return false;
  }
} 

void removeMinus(string &number) { //модуль числа
  string newNumber = "";
  
  for (int numeralIndex = 1; numeralIndex < number.length(); ++numeralIndex) {
    newNumber = newNumber + number[numeralIndex];
  }
  
  number = newNumber;
} 

void swapNumbers(string &firstNumber, string &secondNumber) { //поменять числа местами для некоторых функций
  string intermediateVariable = firstNumber; 
  firstNumber = secondNumber;
  secondNumber = intermediateVariable;
} 

char comparison(string firstNumber, string secondNumber) { //функция для сравнения чисел 
  if (signMinus(firstNumber) == 0 && signMinus(secondNumber) == 0) {
    if (firstNumber.length() == secondNumber.length()) {
      for (int numeralIndex = 0; numeralIndex < firstNumber.length(); ++numeralIndex) {
        if (firstNumber[numeralIndex] > secondNumber[numeralIndex]) {
          return '>';
        } else if (firstNumber[numeralIndex] < secondNumber[numeralIndex]) {
          return '<';
        }
      }
      return '=';
    } else if (firstNumber.length() > secondNumber.length()) {
      return '>';
    } else if (firstNumber.length() < secondNumber.length()) {
      return '<';
    }
  } else if (signMinus(firstNumber) == 1 && signMinus(secondNumber) == 1) {
    if (firstNumber.length() == secondNumber.length()) {
      for (int numeralIndex = 1; numeralIndex < firstNumber.length(); ++numeralIndex) {
        if (firstNumber[numeralIndex] > secondNumber[numeralIndex]) {
          return '<';
        } else if (firstNumber[numeralIndex] < secondNumber[numeralIndex]) {
          return '>';
        }
      }
      return '=';
    } else if (firstNumber.length() > secondNumber.length()) {
      return '<';
    } else if (firstNumber.length() < secondNumber.length()) {
      return '>';
    }
  } else {
    if (signMinus(firstNumber) == 0) {
      return '>';
    } else {
      return '<';
    }
  }
  return 0; 
} 

string subtraction(string firstNumber, string secondNumber, bool minus);

string sum(string firstNumber, string secondNumber, bool minus) { //функция для суммы
  enum sign { NEG, POS } numberSign;
  
  if (signMinus(firstNumber) == 1 && signMinus(secondNumber) == 1) {
    removeMinus(firstNumber);
    removeMinus(secondNumber);
    
    if (comparison(firstNumber, secondNumber) == '<') {
      swapNumbers(firstNumber, secondNumber);
    }
    
    return sum(firstNumber, secondNumber, true);
  } else if (signMinus(firstNumber) == 1) {
    removeMinus(firstNumber);
    
    if (comparison(firstNumber, secondNumber) == '>') {
      return subtraction(firstNumber, secondNumber, true);
    } else if (comparison(firstNumber, secondNumber) == '<' || comparison(firstNumber, secondNumber) == '=') {
      swapNumbers(firstNumber, secondNumber);
      return subtraction(firstNumber, secondNumber, false);
    }
  } else if (signMinus(secondNumber) == 1) {
    removeMinus(secondNumber);
    
    if (comparison(firstNumber, secondNumber) == '>') {
      return subtraction(firstNumber, secondNumber, false);
    } else if (comparison(firstNumber, secondNumber) == '<') {
      swapNumbers(firstNumber, secondNumber);
      return subtraction(firstNumber, secondNumber, true);
    }
  } else {
    if (minus == true) {
      numberSign = NEG;
    } else {
      numberSign = POS;
    }
    
    if (comparison(firstNumber, secondNumber) == '<') {
      swapNumbers(firstNumber, secondNumber);
      
      numberSign = POS;
    }
    
    int firstNumberLength = firstNumber.length();
    int secondNumberLength = secondNumber.length();
    
    string numberComplement = "", numberResult = "";
    int numeralIntegerDiv = 0;
    
    for (int numeralIndex = secondNumberLength - 1; numeralIndex >= 0; --numeralIndex) {
      int firstNumberIndex = numeralIndex + (firstNumberLength - secondNumberLength),
      numeralsSum = (secondNumber[numeralIndex] - '0') + (firstNumber[firstNumberIndex] - '0') + numeralIntegerDiv,
      numeralRemainderDiv = (numeralsSum % 10);
  
      numberComplement = to_string(numeralRemainderDiv) + numberComplement;
      numeralIntegerDiv = numeralsSum / 10;
      --firstNumberIndex;
    }
    
    int index = (firstNumberLength - secondNumberLength) - 1;
    
    if (index >= 0) {
      while (numeralIntegerDiv != 0 && index >= 0) {
        int numeralsSum = (firstNumber[index] - '0') + numeralIntegerDiv;
        int numeralRemainderDiv = (numeralsSum % 10);
        numberComplement = to_string(numeralRemainderDiv) + numberComplement;
        numeralIntegerDiv = numeralsSum / 10;
          
        --index;
      }
    } 
    
    if (numeralIntegerDiv != 0) {
        numberComplement = to_string(numeralIntegerDiv) + numberComplement;
    }
    
    for (int numeralIndex = 0; numeralIndex <= index; ++numeralIndex) {
      numberResult = numberResult + firstNumber[numeralIndex];
    }
    
    numberResult = numberResult + numberComplement;
    
    if (numberSign == NEG) {
      return '-' + numberResult;
    } else {
      return numberResult;
    }
  }
  return 0;
} 

string subtraction(string firstNumber, string secondNumber, bool minus) { //для вычитания
  enum sign { NEG, POS } numberSign;
  
  if (comparison(firstNumber, secondNumber) == '=') {
    return "0";
  } else if (signMinus(firstNumber) == 1 && signMinus(secondNumber) == 1) { 
    removeMinus(firstNumber);
    removeMinus(firstNumber);
    
    if (comparison(firstNumber, secondNumber) == '>') {
      return subtraction(firstNumber, secondNumber, true);
    } else {
      swapNumbers(firstNumber, secondNumber);
      
      return subtraction(firstNumber, secondNumber, false);
    }
  } else if (signMinus(firstNumber) == 1) { 
    removeMinus(firstNumber);
    
    if (comparison(firstNumber, secondNumber) == '<') {
      swapNumbers(firstNumber, secondNumber);
    }
    
    return sum(firstNumber, secondNumber, true);
  } else if (signMinus(secondNumber) == 1) { 
    removeMinus(secondNumber);
    
    if (comparison(firstNumber, secondNumber) == '<') {
      swapNumbers(firstNumber, secondNumber);
    }
    
    return sum(firstNumber, secondNumber, false);
  } else { 
    if (minus == true) {
      numberSign = NEG;
    } else {
      numberSign = POS;
    }
    
    if (comparison(firstNumber, secondNumber) == '<') {
      swapNumbers(firstNumber, secondNumber);
      numberSign = NEG;
    }
    
    int firstNumberLength = firstNumber.length();
    int secondNumberLength = secondNumber.length();
    string numberComplement = "", numberResult = "";
    
    for (int numeralIndex = secondNumberLength - 1; numeralIndex >= 0; --numeralIndex) {
      int firstNumberIndex = numeralIndex + (firstNumberLength - secondNumberLength),
      numeralsSub = (firstNumber[firstNumberIndex] - '0') - (secondNumber[numeralIndex] - '0');
      
      if (numeralsSub < 0) {
        numeralsSub = 10 + numeralsSub;
        numberComplement = to_string(numeralsSub) + numberComplement;
        
        if (firstNumber[firstNumberIndex - 1] == '0') {
          int firstNumberIndexZero = firstNumberIndex - 1;
          while (firstNumber[firstNumberIndexZero] == '0') {
            firstNumber[firstNumberIndexZero] = '9';
            
            --firstNumberIndexZero;
          }
          
          firstNumber[firstNumberIndexZero] = char(firstNumber[firstNumberIndexZero] - 1);
        } else {
          firstNumber[firstNumberIndex - 1] = char(firstNumber[firstNumberIndex - 1] - 1);
        }
      } else {
        numberComplement = to_string(numeralsSub) + numberComplement;
      }
      
      --firstNumberIndex;
    }
    
    for (int numeralIndex = 0; 
    numeralIndex < (firstNumberLength - secondNumberLength); ++numeralIndex) {
      numberResult = numberResult + firstNumber[numeralIndex];
    }
    
    numberResult = numberResult + numberComplement;
    
    string numberResultNew = "";
    
    if (numberResult[0] == '0') {
      int numeralIndex = 0;
      
      while (numberResult[numeralIndex] == '0') {
        ++numeralIndex;
      }
      
      while (numeralIndex < numberResult.length()) {
        numberResultNew = numberResultNew + numberResult[numeralIndex];
        
        ++numeralIndex;
      }
      
      numberResult = numberResultNew;
    }
    
    if (numberSign == NEG) {
      return '-' + numberResult;
    } else {
      return numberResult;
    }
  }
  return "Ошибка! Введите числа в нужной форме.";
}

string multiplication(string firstNumber, string secondNumber) {
  enum sign { NEG, POS } numberSign;
  
  if (firstNumber == "0" || secondNumber == "0") {
    return "0";
  }
  
  if (signMinus(firstNumber) == 1 && signMinus(secondNumber) == 0) {
    removeMinus(firstNumber);
    numberSign = NEG;
  } else if (signMinus(firstNumber) == 0 && signMinus(secondNumber) == 1) {
    removeMinus(secondNumber);
    numberSign = NEG;
  } else if (signMinus(firstNumber) == 1 && signMinus(secondNumber) == 1) {
    removeMinus(firstNumber);
    removeMinus(secondNumber);
  }

  if (comparison(firstNumber, secondNumber) == '<') {
    swapNumbers(firstNumber, secondNumber);
  }
  
  int firstNumberLength = firstNumber.length(), secondNumberLength = secondNumber.length();
  
  string sumOfMultiplacation[secondNumberLength], numeralMultiplication, resultMultiplication = "";
  int sumOfMultiplacationIndex = 0;

  for (int numeralIndex = secondNumberLength - 1; numeralIndex >= 0; --numeralIndex) {
    string sumAdditional = "0", numeralTwo = "";
    numeralTwo = secondNumber[numeralIndex];
    resultMultiplication = "";
    
    for (int numberOneIndex = firstNumberLength - 1; numberOneIndex >= 0; --numberOneIndex) {
      string numeralMultiplication = "0", numeralOne = "";
      numeralOne = firstNumber[numberOneIndex];

      int numeralOneInt = stoi(numeralOne);
      
      for (int sumCount = 0; sumCount < numeralOneInt; ++sumCount) {
        numeralMultiplication = sum(numeralMultiplication, numeralTwo, false);
      }
      
      numeralMultiplication = sum(numeralMultiplication, sumAdditional, false);
     
      if (comparison(numeralMultiplication, "9") == '>') {
        resultMultiplication = numeralMultiplication[numeralMultiplication.length() - 1] + resultMultiplication;
        sumAdditional = numeralMultiplication[numeralMultiplication.length() - 2];
      } else {
        resultMultiplication = numeralMultiplication + resultMultiplication;
        sumAdditional = "0";
      }
    }
    
    if (comparison(sumAdditional, "0") == '>') {
      resultMultiplication = sumAdditional + resultMultiplication;
    }
    
    for (int index = 0; index < sumOfMultiplacationIndex; ++index) {
      resultMultiplication = resultMultiplication + '0';
    }
    
    sumOfMultiplacation[sumOfMultiplacationIndex] = resultMultiplication;
    ++sumOfMultiplacationIndex;
  }
  
  resultMultiplication = sumOfMultiplacation[0];
  
  for (int index = 0; index <= sumOfMultiplacationIndex - 2; ++index) {
    resultMultiplication = sum(resultMultiplication, sumOfMultiplacation[index + 1], false);
  }
  
  
  if (numberSign == NEG) {
    return '-' + resultMultiplication;
  } else {
    return resultMultiplication;
  }
}

string division(string firstNumber, string secondNumber, bool minus) {
  enum sign { NEG, POS } numberSign;
  
  if (minus == false) {
    if (signMinus(firstNumber) == 1 && signMinus(secondNumber) == 0) {
      removeMinus(firstNumber);
      numberSign = NEG;
    } else if (signMinus(firstNumber) == 0 && signMinus(secondNumber) == 1) {
      removeMinus(secondNumber);
      numberSign = NEG;
    } else if (signMinus(firstNumber) == 1 && signMinus(secondNumber) == 1) {
      removeMinus(firstNumber);
      removeMinus(secondNumber);
    }
  } else {
    numberSign = NEG; 
  }
  
  if (comparison(firstNumber, secondNumber) == '<') {
    return "0";
  } else if (comparison(firstNumber, secondNumber) == '=') {
    if (numberSign == NEG) {  
      return "-1";
    } else {
      return "1";
    }
  }
  
  string numberDifference = subtraction(firstNumber, secondNumber, false);
  string multiplier = "2";
  
  while (comparison(multiplier, numberDifference) == '<' || comparison(multiplier, numberDifference) == '=') {
    if (multiplication(secondNumber, multiplier) == firstNumber) {
      if (numberSign == NEG) {
        return '-' + multiplier;
      } else {
        return multiplier;
      }
    }
    multiplier = sum(multiplier, "1", false);
  }
  
  firstNumber = subtraction(firstNumber, "1", false);
  
  if (numberSign == NEG) {
    return division(firstNumber, secondNumber, true);
  } else {
    return division(firstNumber, secondNumber, false);
  }
}

int main() {
  string firstNumber, secondNumber;
  string choice;
  
  cout << "Введите два числа: " << endl;
  cin >> firstNumber >> secondNumber;
  cout << "Введите +, -, *, / или =" << endl;
  cin >> choice;
  if (choice == "+") {
      cout << "Сложение чисел: \n"
           << firstNumber << " + " << secondNumber << " = " << sum(firstNumber, secondNumber, false) << endl;
  } else if (choice == "-") {
      cout << "Вычитание чисел: \n"
           << firstNumber << " - " << secondNumber << " = " << subtraction(firstNumber, secondNumber, false) << endl;
  } else if (choice == "*") {
      cout << "Произведение чисел: \n" 
           << firstNumber << " * " << secondNumber << " = " << multiplication(firstNumber, secondNumber) << endl;
  } else if (choice == "/") {
      cout << "Деление чисел: \n" 
           << firstNumber << " / " << secondNumber << " = " << division(firstNumber, secondNumber, false) << endl;
  } else if (choice == "=") {
      cout << "Сравнение чисел: \n" 
        << firstNumber << " " << comparison(firstNumber, secondNumber) << " " << secondNumber << endl;
  }
}