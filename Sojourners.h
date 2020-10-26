/*
 * Sojourner.h
 *
 *  Created on: Oct 25, 2020
 *      Author: stevenpaster
 */

#ifndef SOJOURNER_H_
#define SOJOURNER_H_

#include <queue>
#include <iostream>

using namespace std;

// Sojourner object
struct Sojourner {
	Sojourner(string n, float s) : name(n), speed(s) { };
	string name;
	float  speed;
};

// A wrapper for the two fastest sojourners
struct fast:Sojourner {
	fast() : Sojourner("", 0) { }
	bool bank = false;
	void switchBank() { bank = !bank; }
	fast(Sojourner s) : Sojourner(s) { }
};


/*
 * A priority_queue that holds Sojourners.
 * This queue always pops() the slowest Sojourner present in the queue.
 */
class MinPriorityQueue {
	struct Compare {
		bool operator() (Sojourner x, Sojourner y) {
			return(x.speed > y.speed);
		}
	};
	priority_queue<Sojourner, vector<Sojourner>, Compare> pQ;
public:
	Sojourner top() { return(pQ.top()); }
	void push(const Sojourner x) { pQ.push(x); }
	void pop() { pQ.pop(); }
	bool empty() { return pQ.empty(); }
	int size() { return pQ.size(); }
};

class Sojourners {
	fast faster;         	// The second fastest sojourner
	fast fastest;			// The fastest sojourner
	int numSojourners = 0;
	double grandTotal = 0;  // cumulative total for all bridges
	MinPriorityQueue pq;	// a priority_queue that returns smallest values first
public:
	void addSojourner(const string name, const float speed);
	double cross(const float length);
};


#endif /* SOJOURNER_H_ */

