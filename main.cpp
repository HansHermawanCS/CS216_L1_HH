#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

const string IN_FILE_NAME = "input.txt";
const string OUT_FILE_NAME = "output.txt";
const int MAX_SIZE = 5;

void bubbleSort(int targetArr[], int targetArrLength);
void checkFiles();
void switchGetStats(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength);
void switchBubbleSort(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength);
string getStats(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength);
string getAverage(int targetArr[], int targetArrLength);
void getData(int divisByFive[], int divisByNine[], int otherNums[], int &divisByFiveTracker, int &divisByNineTracker, int &otherNumsTracker);
string getMedian(int targetArr[], int targetArrLength);
string getSum(int targetArr[], int targetArrLength);
void invalidInput();
void printMenuChoices();
void printArray(int targetArr[], int arrayLength);
void quitAndOutputToFile(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength);
void switchStatement(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveTracker, int divisByNineTracker, int otherNumsTracker);
int validateInput(string input);

int main() {
  int divisByFive[MAX_SIZE];
  int divisByNine[MAX_SIZE];
  int otherNums[MAX_SIZE];

  int divisByFiveTracker = 0;
  int divisByNineTracker = 0;
  int otherNumsTracker = 0;

  checkFiles();

  getData(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);

  printMenuChoices();
  switchStatement(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
}

void checkFiles(){
  ifstream inFile; 
  ofstream outFile;

  inFile.open(IN_FILE_NAME); 

  if(!inFile){
    cout << "Failed reading input file. Terminating program\n";

    system("pause");
    exit(EXIT_FAILURE);
  }
  inFile.close();

  outFile.open(OUT_FILE_NAME);

  if(!outFile){
    cout << "Failed reading output file. Terminating program\n";

    system("pause");
    exit(EXIT_FAILURE);
  }
  outFile.close();
}

void getData(int divisByFive[], int divisByNine[], int otherNums[], int &divisByFiveTracker, int &divisByNineTracker, int &otherNumsTracker){
  int i_fromFile = 0;
  int numsProcessed = 0;

  ifstream inFile;
  inFile.open(IN_FILE_NAME);

  while(inFile >> i_fromFile){ // While there are still int to read from inFile place each one in i_fromFile
    numsProcessed++;
    if (i_fromFile == 0) {  
        otherNums[otherNumsTracker++] = i_fromFile;
    } else {
      const bool isDivisibleByFive = (i_fromFile % 5 == 0);
      const bool isDivisibleByNine = (i_fromFile % 9 == 0);

      if (isDivisibleByFive && divisByFiveTracker < MAX_SIZE)
        divisByFive[divisByFiveTracker++] = i_fromFile;
      if (isDivisibleByNine && divisByNineTracker < MAX_SIZE)
        divisByNine[divisByNineTracker++] = i_fromFile;
      if (!isDivisibleByFive && !isDivisibleByNine && otherNumsTracker < MAX_SIZE)
        otherNums[otherNumsTracker++] = i_fromFile;
    }
  }

  if(numsProcessed >= MAX_SIZE){
      cout << "Not all numbers have been processed. Only " << numsProcessed << " numbers were processed." << endl;
  }

  if((divisByFiveTracker == 0) && (divisByNineTracker == 0) && (otherNumsTracker == 0)){
    cout << "File empty please have numbers inside input";

    system("pause");
    exit(EXIT_FAILURE);
  } 

  inFile.close();
}

void switchStatement(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveTracker, int divisByNineTracker, int otherNumsTracker){
  int userInput;

  do{
    string stringUserInput;
    getline(cin, stringUserInput);
    userInput = validateInput(stringUserInput);

    cout << "\n";

    switch(userInput){
      case (1):
        switchGetStats(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
        break;
      case (2):
        switchBubbleSort(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
        break;
      case (3):
        quitAndOutputToFile(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
        break;
      default:
        invalidInput();
        break;
    }
  } while (userInput != 3);
}

string getStats(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength){
  string result;

  result += "-Sum-\n";
  result += "divisByFiveSum: ";
  result += getSum(divisByFive, divisByFiveLength);
  result += "\n";

  result += "divisByNineSum: ";
  result += getSum(divisByNine, divisByNineLength);
  result += "\n";

  result += "otherNumsSum: ";
  result += getSum(otherNums, otherNumsLength);
  result += "\n";

  result += "\n-Average-\n";
  result += "divisByFiveAverage: ";
  result += getAverage(divisByFive, divisByFiveLength);
  result += "\n";

  result += "divisByNineAverage: ";
  result += getAverage(divisByNine, divisByNineLength);
  result += "\n";

  result += "otherNumsAverage: ";
  result += getAverage(otherNums, otherNumsLength);
  result += "\n";
  
  result += "\n-Median-\n";
  result += "divisByFiveMedian: ";
  result += getMedian(divisByFive, divisByFiveLength);
  result += "\n";

  result += "divisByNineMedian: ";
  result += getMedian(divisByNine, divisByNineLength);
  result += "\n";

  result += "otherNumsMedian: ";
  result += getMedian(otherNums, otherNumsLength);
  result += "\n\n";

  return result;
}

string getSum(int targetArr[], int targetArrLength){
  if(targetArrLength == 0){
    return "Array empty, no sum";

  } else{
    int targetArrSum = 0;

    for (int i = 0; i < targetArrLength; ++i){
      targetArrSum += targetArr[i];
    }

    return to_string(targetArrSum);
  }
}

string getAverage(int targetArr[], int targetArrLength){
  if(targetArrLength == 0){
    return "Array empty, no average";

  } else {
    double average = static_cast<double>(stod(getSum(targetArr, targetArrLength))) / targetArrLength;

    // Sets to 2 decimal points
    ostringstream stream;
    stream << fixed << setprecision(2) << average;
    return stream.str();
  }
}

string getMedian(int targetArr[], int targetArrLength){
  if(targetArrLength == 0){
    return "Array empty, no median";
  } 
  
  bubbleSort(targetArr, targetArrLength);

  if(targetArrLength % 2 == 0){
    double median = (static_cast<double>(targetArr[(targetArrLength - 1) / 2]) + static_cast<double>(targetArr[targetArrLength / 2])) / 2.0;
    
    // Sets to 2 decimal points
    ostringstream stream;
    stream << fixed << setprecision(2) << median;
    return stream.str();

  } else{ 
    return to_string(targetArr[targetArrLength / 2]);
  }
}

void bubbleSort(int targetArr[], int targetArrLength){
  if(targetArrLength == 0){
    cout << "Array empty, sort not processed.";
    
  } else {
    for (int i = 0; i < targetArrLength; ++i){
      for (int j = 0; j < targetArrLength - 1; ++j){
        if(targetArr[j] > targetArr[j + 1]){
        int temp = targetArr[j];
        targetArr[j] = targetArr[j + 1];
        targetArr[j + 1] = temp;
        }
      }
    }
  }
}

void switchGetStats(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength){
  cout << getStats(divisByFive, divisByNine, otherNums, divisByFiveLength, divisByNineLength, otherNumsLength);
  
  printMenuChoices();
}

void switchBubbleSort(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength){
  cout << "divisByFive: ";
  bubbleSort(divisByFive, divisByFiveLength);
  printArray(divisByFive, divisByFiveLength);

  cout << "\ndivisByNine: ";
  bubbleSort(divisByNine, divisByNineLength);
  printArray(divisByNine, divisByNineLength);

  cout << "\notherNums: ";
  bubbleSort(otherNums, otherNumsLength);
  printArray(otherNums, otherNumsLength);
  cout << "\n";

  printMenuChoices();
}

void quitAndOutputToFile(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveLength, int divisByNineLength, int otherNumsLength){
  ofstream outFile;

  outFile.open(OUT_FILE_NAME);

  outFile << getStats(divisByFive, divisByNine, otherNums, divisByFiveLength, divisByNineLength, otherNumsLength);
  cout << "Stats have been processed to " << OUT_FILE_NAME;

  outFile.close();
}

int validateInput(string input){
  if(input.length() != 1){
    // returns 4 in order to result in default in switch statement
    return 4; 
  } else{
    return stoi(input);
  }
}

void invalidInput(){
  cout << "- Invalid input, please try again. - \n";
 
  printMenuChoices();
}

void printMenuChoices(){
  cout << setfill('-') << setw(100) << " " << "\n Here are your choices (input the number for the corresponding action): \n 1. Print values stored in each array along with the average, median, and sum of the numbers stored in each array \n 2. Print values in each array sorted in ascending order \n 3. Quit and write arrays and their stats into an output file"
       << endl;
}

void printArray(int targetArr[], int arrayLength){
  for (int i = 0; i < arrayLength; i++) {
    cout << targetArr[i] << " ";
  }
}