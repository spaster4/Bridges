/*
 * Sojourner.cpp
 *
 *  Created on: Oct 25, 2020
 *      Author: Steven Paster
 */
#include "Sojourners.h"

extern bool debug;

/*
 * Commpute the time it takes for all Sojourners to cross a bridge
 * The two fastest sojourners are guides.
 *
 * We repeat the following steps until everyone is across:
 *   1) if both guides are on the starting bank, then
 *   	1a) If there are only the two guides on the near bank, then we send
 *   		both across to the far bank and we are done.
 *   		time += time of slower guide.
 *   	1b) Else, we send the two guides across to the farther bank and we use the
 *   		faster guide to return the torch to the near bank.
 *   		The time required = time needed for slower guide + time needed for faster guide
 *   2) If guides are on opposite banks:
 *   	2a) if there are only one sojourners and a guide on the near bank, then we send them across.
 *   		The time += time of the sojourner who is not the guide.
 *   		And we are done -- all sojourners are across.
 *   	2b) Else, we send the two slowest sojourners on the near bank across to the far bank.
 *   		Next, the guide on the guide on the far bank, the slower guide, returns the torch
 *   		to the near bank.
 *   		time += time for slower guide to cross + time slowest sojourner to cross.
 *
 * 	Notice that, unless we are done, each step above end with the torch and the
 * 	fastest guide on the near bank.
 */

double Sojourners::cross(const float length) {
	faster.bank = false;
	fastest.bank = false;
	double time=0;
	if(numSojourners == 1)
		cout << "Crossing a bridge of length " << length << "  with 1 person\n";
	else
		cout << "Crossing a bridge of length " << length << "  with " << numSojourners << " people\n";
	// We workmwith a copy of the priority queue to preserve the original
	MinPriorityQueue pq2 = pq;
	if(numSojourners == 0) return 0;
	while(pq2.size() > 0) {
		if(debug) cout << "size: " << pq2.size() << endl;
		if(!faster.bank && !fastest.bank) {
			// Both guides are on the near bank - send them across
			// Then send fastest Sojourner back with the torch
			faster.switchBank();
			time += (length/faster.speed + length/fastest.speed);
			if(debug) cout << "time1:" << time << endl;
		}
		else {
			// The guides are on opposite banks
			if(pq2.size() <= 1) {
				// We have guide and 1 person remaining - Send them across and we are done
				Sojourner slowest = pq2.top(); pq2.pop();
				time += length/slowest.speed;
				fastest.switchBank();
				if(debug) cout << "time3:" << time << endl;
				break;
			}

			// We have at least two sojourners in the queue -- send the two slowest across
			if(pq2.size() >= 2) {
				Sojourner slower = pq2.top(); pq2.pop();
				// need to pop off the next slowest too
				pq2.pop();
				time += length/slower.speed;
				// Need to send faster back to near bank
				time += length/faster.speed;
				faster.switchBank();
				if(debug) cout << "time2:" << time << endl;
			}
		}
	}
	// Either we are done or both guides are on near bank
	if(!faster.bank) {
		// Both guides are on near bank, send them across
		time += length/faster.speed;
		if(debug) cout << "time4:" << time << endl;
	}
	// print times
	cout << "   time:       " << time << " minutes\n";
	grandTotal += time;
	cout << "   Cumulative: " << grandTotal <<  " minutes\n";
	cout << "------------------------------\n\n";
	return time;
}

/*
 * Add a sojourner. We keep track of the two fastest sojourners. All other sojourners go into
 * the priority_queue, pq. We also keep track of the total number of sojourners, numSojourners.
*/
void Sojourners::addSojourner(string name, float speed) {
	Sojourner s(name, speed);
	do {
		if(numSojourners == 0) {
			faster = s;
			break;
		}
		if(numSojourners == 1) {
			if(faster.speed > s.speed) {
				fastest = faster;
				faster = s;
			}
			else {
				fastest = s;
			}
			break;
		}
		if(s.speed >= fastest.speed) {
			// We have a new fastest Sojourner - we need to change faster and fastest
			Sojourner tmp(faster.name, faster.speed);
			pq.push(tmp);
			faster = fastest;
			fastest = s;
			break;
		}
		if(s.speed > faster.speed) {
			// We have a new faster Sojourner - we displace the old one
			Sojourner tmp(faster.name, faster.speed);
			pq.push(tmp);
			faster = s;
			break;
		}
		// simply push the new Sojourner onto the queue
		pq.push(s);
	} while(0);
	numSojourners++;
	return;
}

