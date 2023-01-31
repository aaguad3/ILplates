/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     Adrian Aguada
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"
#include "ILplates.cpp"

using namespace std;

/* two overloaded swap functions, one for int vectors and another for string vectors */
void swapElem(vector<string> &vec, int i) {
	string temp = vec[i];
	vec[i] = vec[i + 1];
	vec[i + 1] = temp;
}

void swapElem(vector<int> &vec, int i) {
	int temp = vec[i];
	vec[i] = vec[i + 1];
	vec[i + 1] = temp;
}

void bubbleSort(vector<string> &vec, vector<int> &vec2) {
	int size = vec.size();
	for(int i = 0; i < size - 1; ++i) {
		for(int j = size - 2; j >= i; --j) {
			if(vec[j] > vec[j + 1]) {
				swapElem(vec, j);
				swapElem(vec2, j);
			}
		}
	}
}

//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

//     cout << fine << endl;
//     cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hasHTable size> ";
  cin >> N;

  hashtable<string, int>  HT(N);
  ILplates                hashplates(HT);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = HT.Keys();
  vector<int> amounts = HT.Values();
	
  cout << "Sorting...\n";	
  bubbleSort(plates, amounts);
	
  string outfilename = basename + "-output.txt";
  ofstream outfile(outfilename);
	
  cout << "Writing " << "'" << outfilename << "'...\n";
  
  int size = plates.size();
  for(int i = 0; i < size; ++i) {
	  outfile << "\"" << plates[i] << "\"" << " $" << amounts[i] << endl;
  }

  //
  // done:
  //
  return 0;
}