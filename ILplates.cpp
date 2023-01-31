/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// Adrian Aguada
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>

#include "ILplates.h"

using namespace std;

bool correctCharacters(string plate) {
	for(size_t i = 0; i < plate.size(); ++i) { // has a character that's not a letter/digit (excluding including spaces)
		if((((!isdigit(plate[i])) && (plate[i] != ' '))) && ((!isalpha(plate[i])) && (plate[i] != ' '))) {
			return false;
		}
	}
	return true;
}

bool correctSpaces(string plate) {
	int size = plate.size();
	
	if(plate[0] == ' ' || plate[size - 1] == ' ') { // space in front or back
		return false;
	}
	
	int spaceCounter = 0;
	for(int i = 0; i < size; ++i) {
		if(plate[i] == ' ') {
			spaceCounter++;
		}
	}
	
	if(spaceCounter > 1) { // more than 1 space
		return false;
	}
	return true;
}

bool noLowercase(string plate) {
	for(size_t i = 0; i < plate.size(); ++i) {
		if(islower(plate[i])) { // lowercase letter found
			return false;
		}
	}
	return true;
}

bool personalized(string plate) {
	string firstPlate;
	string secondPlate;
	
	/* split plate between the space */
	for(size_t i = 0; i < plate.size(); ++i) {
		if(plate[i] == ' ') {
			firstPlate = plate.substr(0, i);
			secondPlate = plate.substr(i + 1, plate.length() - (i + 1));
			break;
		}
	}

	/* check if firstPlate has any digits */
	for(size_t i = 0; i < firstPlate.size(); ++i) {
		if(isdigit(firstPlate[i])) {
			return false;
		}
	}
	
	/* check if secondPlate has any letters */
	for(size_t i = 0; i < secondPlate.size(); ++i) {
		if(isalpha(secondPlate[i])) {
			return false;
		}
	}
	
	if(firstPlate.size() > 6) { // check if firstPlate is too big
		return false;
	}
	
	if(firstPlate.size() <= 5) { 
		if(secondPlate.size() > 2) { // check if second plate is too big based on first plate
			return false;
		}
	}
	else { //firstPlate size is 6
		if(secondPlate.size() > 1) { // check if second plate is too big based on first plate
			return false;
		}
	}
	return true;
}

/* overloaded: returns firstPlate and secondPlate for strcat */
bool personalized(string plate, string &firstPlate, string &secondPlate) {
	/* count spaces and if does not equal 1, return false */
	int spaceCounter = 0;
	for(size_t i = 0; i < plate.size(); ++i) {
		if(plate[i] == ' ') {
			spaceCounter++;
		}
	}
	if(spaceCounter != 1) {
		return false;
	}
	
	/* split plate between the space */
	for(size_t i = 0; i < plate.size(); ++i) {
		if(plate[i] == ' ') {
			firstPlate = plate.substr(0, i);
			secondPlate = plate.substr(i + 1, plate.length() - (i + 1));
			break;
		}
	}

	/* check if firstPlate has any digits */
	for(size_t i = 0; i < firstPlate.size(); ++i) {
		if(isdigit(firstPlate[i])) {
			return false;
		}
	}
	
	/* check if secondPlate has any letters */
	for(size_t i = 0; i < secondPlate.size(); ++i) {
		if(isalpha(secondPlate[i])) {
			return false;
		}
	}
	
	if(firstPlate.size() > 6) { // check if firstPlate is too big
		return false;
	}
	
	if(firstPlate.size() <= 5) { 
		if(secondPlate.size() > 2) { // check if second plate is too big based on first plate
			return false;
		}
	}
	else { //firstPlate size is 6
		if(secondPlate.size() > 1) { // check if second plate is too big based on first plate
			return false;
		}
	}
	return true;
}

bool vanity(string plate) {
	int size = plate.size();
	int numCounter = 0;
	int charCounter = 0;
	
	/* check if plate has a space */
	for(int i = 0; i < size; ++i) {
		if(plate[i] == ' ') {
			return false;
		}
	}
	
	/* count number of digits/letters */
	for(int i = 0; i < size; ++i){
		if(isdigit(plate[i])){
			++numCounter;
		}
		else if(isalpha(plate[i])){
			++charCounter;
		}
	}
	
	if(size <= 3 && charCounter == 0 && numCounter <= 3) {
		return true;
	}
	else if(size <= 7 && charCounter <= 7 && numCounter == 0) {
		return true;
	}
	return false;
}

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int Hash(string plate)
{
	unsigned long long int index = -1;

	if(!noLowercase(plate) || !correctSpaces(plate) || !correctCharacters(plate)) {
		return index;
	}
	
	string plate1;
	string plate2;
	
	/* checks if plate is personalized, if not, then checks if it's vanity. if neither, returns -1 */
	if(!personalized(plate, plate1, plate2)) {
		if(!vanity(plate)) {
			return index;
		}
	}
	
	if(personalized(plate)) {
		string strcat = plate1 + plate2;
		for(size_t i = 0; i < strcat.size(); ++i) {
			index += (strcat[i] * pow(36, i));
		}
	}
	else if(vanity(plate)) {
		for(size_t i = 0; i < plate.size(); ++i) {
			index += (plate[i] * pow(36, i));
		}
	}
	
	return index % HT.Size();
}

//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int Search(string plate)
{
	int bucket = Hash(plate);
	int bucketsProbed = 0;
	bool empty;
	string key;
	int value;
	
	HT.Get(bucket, empty, key, value);
	
	while((!empty) && (bucketsProbed < HT.Size())) {
		if(key == plate) {
			return value;
		}
		
		++bucket;
		++bucketsProbed;
		HT.Get(bucket, empty, key, value);
	}
	return -1;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void Insert(string plate, int newValue)
{
	int bucket = Hash(plate);
	int bucketsProbed = 0;
	bool empty;
	string key;
	int value;
	
	HT.Get(bucket, empty, key, value);
	
	while(bucketsProbed < HT.Size()) {
		if(empty || key == plate) {
			HT.Set(bucket, plate, newValue);
			break;
		}
		
		++bucket;
		++bucketsProbed;
		
		HT.Get(bucket, empty, key, value);
	}
}