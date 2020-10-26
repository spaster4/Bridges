//============================================================================
// Name        : bridges.cpp
// Author      : sbp
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

extern void test(string);
bool debug = false;
bool debugParser = false;  // Debugging flag for the parser

// Entrypoint for the bridges problem
int main() {
   cout << endl;
	test("test.yaml");
	return 0;
}
