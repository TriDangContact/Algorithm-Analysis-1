///////////////////////////////////////////////////////////////////////////////
// project1.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

// Convenient typedef for a vector of strings.
typedef std::vector<std::string> string_vector;

// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or false on I/O error.
bool load_words(string_vector& words, const std::string& path) {
	words.clear();
	std::string line;
	std::ifstream input;
	input.open(path);
	if (input.is_open()) {
		while (input >> line) {
			words.push_back(line);
		}
		return true;
	}
	return false;
}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const std::string& string1, const std::string& string2) {
	int i = 0;
	int j = string2.length()-1;
	if ((string1 == string2) || (string1.length() != string2.length())) {
		return false;
	}
	while (i < string1.length()) {
		if (string1[i] == string2[j]) {
			i++;
			j--;
		}
		else {
			return false;
		}
	}
	return true;
};

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const std::string& alleged_substring,
	const std::string& alleged_superstring) {
	if (alleged_substring == "") {
		return true;
	}
	if (alleged_substring == alleged_superstring) {
		return false;
	}
	int maxindex = alleged_superstring.length() - alleged_substring.length();
	for (int supindex = 0; supindex <= maxindex; supindex++) {
		int subindex = 0;
		int tempsupindex = supindex;		//save the supindex so inner while loop doesn't change it
			while ((alleged_substring[subindex] == alleged_superstring[tempsupindex])) {
				if (subindex == alleged_substring.length()-1) {	//if the last char of substring is matched
					return true;								//then a substring is found
				}
				subindex++;					//increment to compare next char in substring
				tempsupindex++;				//increment to compare next char in superstring
			}
		}
	return false;
};

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
	unsigned int counts[256] = { 0 };		//create an array of size 256
	char c;
	for (const std::string& x : strings) {		//for each string in the string vector that is passed in
		for (const char& c : x) {			//for each char in those strings
			counts[c]++;					//increment the value at the same index as the char
		};
	};
	size_t arraysize = (sizeof counts / sizeof counts[0]);	//get the size of counts array
	int max = 0;
	for (int i = 1; i < arraysize; i++) {			//from i = 1 to end of counts array
		if (counts[i] > counts[max]) {				//get the max value in the counts array
			max = i;
		};
	};
	c = max;				//convert the index to char
	return c;
};

// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
std::string longest_mirrored_string(const string_vector& strings) {
	std::string best = "";
	for (const std::string& a : strings) {
		for (const std::string& b : strings) {
			if ((is_mirrored(a, b)) && (a.length() > best.length())) {
				best = a;
			};
		};
	};
	return best;
};

// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
	int best_length = 0;
	std::vector<std::string> trio (3,"");
	for (const std::string& a : strings) {
		for (const std::string& b : strings) {
			for (const std::string& c : strings) {
				int abc_length = a.length() + b.length() + c.length();
				if ((is_substring(a, b) && is_substring(b, c)) && (abc_length > best_length)) {
					best_length = abc_length;
					trio[0] = a;
					trio[1] = b;
					trio[2] = c;
				};
			};
		};
	};
	return trio;
};
