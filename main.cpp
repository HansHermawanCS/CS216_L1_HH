#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// Const variables, please place path for filenames
const string fileName = "";
const string outFileName = "";
const int maxSize = 15;

void bubbleSort(int targetArr[], int targetArrLength);
string getAverageMedianSum(int divisByFiveArr[], int divisByNineArr[], int otherNumsArr[], int divisByFiveArrLength, int divisByNineArrLength, int otherNumsArrLength);
string getAverage(int targetArr[], int targetArrLength);
void getData();
string getMedian(int targetArr[], int targetArrLength);
string getSum(int targetArr[], int targetArrLength);
void invalidProcedure(int divisByFiveArr[], int divisByNineArr[], int otherNumsArr[], int divisByFiveArrLength, int divisByNineArrLength, int otherNumsArrLength);
void printChoices();
void quitAndOutputToFile(int divisByFiveArr[], int divisByNineArr[], int otherNumsArr[], int divisByFiveArrLength, int divisByNineArrLength, int otherNumsArrLength);
void switchStatement(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveTracker, int divisByNineTracker, int otherNumsTracker);

int main() {
  getData();

  return 0;
}

void getData(){
  // Array variables
  int divisByFive[20];
  int divisByNine[20];
  int otherNums[20];

  // Array num tracker
  int divisByFiveTracker = 0;
  int divisByNineTracker = 0;
  int otherNumsTracker = 0;

  // Track amount of numbers processed
  int count = 0;

  ifstream inFile; 
  ofstream outFile;

  // Open input file
  inFile.open(fileName); 

  // Checking if inFile is properly read
  if(!inFile){
    cout << "Failed reading input file. Terminating program\n";

    exit(1);
  }

  outFile.open(outFileName);

  // Checking if outFile is properly read
  if(!outFile){
    cout << "Failed reading output file. Terminating program\n";

    exit(1);
  }

  outFile.close();

  int i_fromFile = 0;
  while((count < maxSize) && (inFile >> i_fromFile)){ // While there are still int to read from inFile place each one in i_fromFile
    count++; // Increase count by 1
    bool isDivisibleByFive = (i_fromFile % 5 == 0);
    bool isDivisibleByNine = (i_fromFile % 9 == 0);

    if(i_fromFile == 0){ // Since 0 is unique we have to make an edge case for it
      otherNums[otherNumsTracker] = (i_fromFile);
      otherNumsTracker++;

    } else if(isDivisibleByFive && isDivisibleByNine){ // If the number is divisble by both 5&9 e.g. 45
      divisByFive[divisByFiveTracker] = i_fromFile;
      divisByFiveTracker++;

      divisByNine[divisByNineTracker] = (i_fromFile);
      divisByNineTracker++;
    
    } else if(isDivisibleByFive){
      divisByFive[divisByFiveTracker] = i_fromFile;
      divisByFiveTracker++;

    } else if(isDivisibleByNine){
      divisByNine[divisByNineTracker] = (i_fromFile);
      divisByNineTracker++;

    } else{
      otherNums[otherNumsTracker] = (i_fromFile);
      otherNumsTracker++;

    }

    if(count >= maxSize){
      cout << "Not all numbers have been processed. Only the first " << count << " numbers were processed." << endl;
    }
  }

  if((divisByFiveTracker == 0) && (divisByNineTracker == 0) && (otherNumsTracker == 0)){
    cout << "File empty please have numbers inside input";
  } else{
    cout << "divisByFive: ";
    bubbleSort(divisByFive, divisByFiveTracker);

    cout << "divisByNine: ";
    bubbleSort(divisByNine, divisByNineTracker);

    cout << "otherNums: ";
    bubbleSort(otherNums, otherNumsTracker);

    printChoices();
    switchStatement(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
  }

  inFile.close();
}

void switchStatement(int divisByFive[], int divisByNine[], int otherNums[], int divisByFiveTracker, int divisByNineTracker, int otherNumsTracker){
  int userInput;

  // Propmts user to input value
  cin >> userInput;
  cout << "\n";

  switch(userInput){
    case (1):
      cout << getAverageMedianSum(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
      
      printChoices();
      switchStatement(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
      break;

    case (2):
      cout << "divisByFive: ";
      bubbleSort(divisByFive, divisByFiveTracker);

      cout << "divisByNine: ";
      bubbleSort(divisByNine, divisByNineTracker);

      cout << "otherNums: ";
      bubbleSort(otherNums, otherNumsTracker);
      printChoices();
      switchStatement(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);

      break;

    case (3):
      quitAndOutputToFile(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
      return;

    default:
      cin.clear();
      cin.ignore();  
      invalidProcedure(divisByFive, divisByNine, otherNums, divisByFiveTracker, divisByNineTracker, otherNumsTracker);
      break;
    }
}

string getAverageMedianSum(int divisByFiveArr[], int divisByNineArr[], int otherNumsArr[], int divisByFiveArrLength, int divisByNineArrLength, int otherNumsArrLength){
  string result;

  result += "--Sum--\n";
  result += "divisByFiveSum: ";
  result += getSum(divisByFiveArr, divisByFiveArrLength);
  result += "\n";

  result += "divisByNineSum: ";
  result += getSum(divisByNineArr, divisByNineArrLength);
  result += "\n";

  result += "otherNumsSum: ";
  result += getSum(otherNumsArr, otherNumsArrLength);
  result += "\n";

  result += "\n--Average--\n";
  result += "divisByFiveAverage: ";
  result += getAverage(divisByFiveArr, divisByFiveArrLength);
  result += "\n";

  result += "divisByNineAverage: ";
  result +=  getAverage(divisByNineArr, divisByNineArrLength);
  result += "\n";

  result += "otherNumsAverage: ";
  result += getAverage(otherNumsArr, otherNumsArrLength);
  result += "\n";
  
  result += "\n--Median--\n";
  result += "divisByFiveMedian: ";
  result += getMedian(divisByFiveArr, divisByFiveArrLength);
  result += "\n";

  result += "divisByNineMedian: ";
  result += getMedian(divisByNineArr, divisByNineArrLength);
  result += "\n";

  result += "otherNumsMedian: ";
  result += getMedian(otherNumsArr, otherNumsArrLength);
  result += "\n\n";

  return result;
}

string getSum(int targetArr[], int targetArrLength){
  if(targetArrLength == 0){
    // When array is empty
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
    // When array is empty
    return "Array empty, no average";

  } else {
    return to_string(stoi(getSum(targetArr, targetArrLength)) / targetArrLength);
  }
  
}

string getMedian(int targetArr[], int targetArrLength){
  if(targetArrLength == 0){
    // When array is empty
    return "Array empty, no median";

  } else if(targetArrLength % 2 == 0){ 
    // When array length is even
    return to_string(((targetArr[(targetArrLength - 1) / 2] + targetArr[targetArrLength / 2]) / 2));

  } else{ 
    // When array length is odd
    return to_string(targetArr[targetArrLength / 2]);

  }
}

void bubbleSort(int targetArr[], int targetArrLength){
  if(targetArrLength == 0){
    // If array is empty
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
    for (int i = 0; i < targetArrLength; i++) {
      cout << targetArr[i] << " ";
    }
  }
  
  cout << "\n";
}

void quitAndOutputToFile(int divisByFiveArr[], int divisByNineArr[], int otherNumsArr[], int divisByFiveArrLength, int divisByNineArrLength, int otherNumsArrLength){
  ofstream outFile;

  outFile.open(outFileName);

  // Processes stats to outFile
  outFile << getAverageMedianSum(divisByFiveArr, divisByNineArr, otherNumsArr, divisByFiveArrLength, divisByNineArrLength, otherNumsArrLength);

  cout << "Stats have been processed to " << outFileName;

  return;
}

void invalidProcedure(int divisByFiveArr[], int divisByNineArr[], int otherNumsArr[], int divisByFiveArrLength, int divisByNineArrLength, int otherNumsArrLength){
  cout << "--- Invalid input, please try again. --- \n";
 
  printChoices();

  switchStatement(divisByFiveArr, divisByNineArr, otherNumsArr, divisByFiveArrLength, divisByNineArrLength, otherNumsArrLength);
}

void printChoices(){
  cout << "------------------------------------------\n" 
       << "Here are your choices (input the number for the corresponding action): \n"
       << "1. Print values stored in each array along with the average, median, and sum of the numbers stored in each array \n"
       << "2. Print values in each array sorted in ascending order \n"
       << "3. Quit and write arrays and their stats into an output file" 
       << endl;
}