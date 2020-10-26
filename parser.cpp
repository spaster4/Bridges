/*
 * Parser.cpp
 *
 *  Created on: Oct 25, 2020
 *      Author: Steven Paster
 *
 *
 *  Simple and incomplete yaml parser. See the file test_parser.yaml
 *  for examples of situations this parse will handle.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Sojourners.h"

using namespace std;

extern bool debugParser;

// Remove comments fro1m a string as well as
// 	 leading and trailing whitespace.
void trim(string& s) {
	string s2="";
	int i=0;
	// remove leading whitespace
	while(i<s.length() && isspace(s[i])) i++;
	// remove any comments
	while(i<s.length() && s[i] != '#') s2 += s[i++];
	i = s2.length()-1;
	// remove trailing whitespace
	while(isspace(s[i] && i>=0)) i--;
	if(isspace(s2[s2.size()-1])) s = s2.substr(0,i);
	else s = s2.substr(0,i+1);
	return;
}

// Parse out the tag from a line from a yaml file
// returns "" if no tag is found
string parseTag(string& line) {
	trim(line);
	int pos = line.find(":", 0);
	if(pos == string::npos) return "";
	string tag = line.substr(0, pos);
	trim(tag);
	line = line.substr(pos+1, line.length());
	return(tag);
}


// Parse out the value from a line of a yaml file.
// I present, remove quotation marks.
string parseValue(string &line) {
	int i=0;
	string value = "";
	trim(line);
	if(line[i] == '"') {
		i++;
		while(i<line.length() && line[i] != '"') i++;
		if(line[i] != '"' ) line = "";
		else value = line.substr(1, i-1);
	}
	else {
		value = line.substr(0, line.length());
	}
	return value;
}


// Convert a string to a float.
// If an exception occurs, return 0.
float string2Float(string s) {
	float f;
	try {
		f = stof(s);
	}
	catch(exception& e) {
		cout << "An exception occurred in str2Float(): " << e.what() << '\n';
		f = 0;
	}
	return f;
}

// We mayhave parsed out a command to cross a bridge
// Check the tag, and parse out the bridge length.
void doBridgeCmd(Sojourners& s, string& line) {
	string tag = parseTag(line);
	if(tag != "bridge") return;
	string value = parseValue(line);
	float length = string2Float(value);
	if(length == 0) {
		cout << "Ignoring a bridge of length 0\n";
		cout << "-----------------------------\n\n";
	}
	else s.cross(length);
	return;
}

// We have parsed out an add sojourner command
// We still need to parse out the name and the speed,
// then add the new sojourner
void doAddPersonCmd(Sojourners& s, string& line, fstream& file) {
	string tag = parseTag(line);
	if(tag != "add") return;
	string value="";
	bool gotSpeed = false;
	bool gotName = false;
	float speed = 0;
	string name="";
	while(getline(file, line)) {
		trim(line);
		if(line[0] == '-') {
			line = line.substr(1,line.length());
			trim(line);
		}
		if(line.substr(0,5) == "speed") {
			tag = parseTag(line);
			if(tag != "speed") continue;
			value = parseValue(line);
			speed =  string2Float(value);
			gotSpeed = true;
		}
		else if(line.substr(0,4) == "name") {
			tag = parseTag(line);
			trim(tag);
			if(tag != "name") continue;
			name = parseValue(line);
			gotName = true;
		}
		if(gotSpeed && gotName) {
			if(debugParser)
				cout << "adding " << name << "  speed " << speed << endl;
			s.addSojourner(name, speed);
			return;
		}
	}
	// We have run out of file
	return;
}

//Read from a file
int parseFile(Sojourners& s, string fname) {
	int retval=0;
	fstream file;
	file.open(fname, ios::in);
	if(file.is_open()) {
		string line;
		while(getline(file, line)) {
			if(debugParser) cout << "--> " << line << endl;
			if(line.substr(0,6) == "bridge") {
				doBridgeCmd(s, line);
			}
			else if(line.substr(0,3) == "add") {
				doAddPersonCmd(s, line, file);
			}
		}
		file.close(); //close the file object.
	}
	else {
		cout << "Failed to open file " << fname << " for reading\n";
		retval = 1;
	}
	return retval;
}


int test(string fname) {
	Sojourners s;
	int retval = parseFile(s, fname);
	return retval;
}




