File: README
Author: Stevenn Paster
-----------------------

Problem Statement
-----------------
A teamh of sojourners are hiking  through a forest at night. The team encounters a series of narrow bridges along the way.  At each bridge they may meet additional sojouners who need their help to cross the bridge. The narrow bridge can only hold two people at a time. They have one torch and because it's night, the torch has to be used when crossing the bridge. Each sojurner can cross the bridge at different speeds. When two sojourners cross the bridge together, they must move at the slower person's pace.

Determine the fastest time that the hikers can cross the each bridge and the total time for all crossings. The input to the program will be a yaml file that describes the speeds of each person, the bridges encountered, their length, and the additional hikers encountered along the way. Your solution should assume any number of people and bridges can be provided as inputs.


Notes on the solution
---------------------
This directory contains my solution to the bridges problem. Although there is a well known recursive solution, I elected to take 
a different route with the intention of printing out, in order, the names and direction of those sojourners that cross the bridge. 
Time prevented me from completing the task; however, the program does print out the required information.

Sample Output:

Crossing a bridge of length 100  with 4 people
   time:       17 minutes
   Cumulative: 17 minutes
------------------------------

Crossing a bridge of length 250  with 5 people
   time:       132.5 minutes
   Cumulative: 149.5 minutes
------------------------------

Crossing a bridge of length 150  with 7 people
   time:       95.5 minutes
   Cumulative: 245 minutes
------------------------------


The Algorithm
-------------
 Commpute the time it takes for all Sojourners to cross a bridge
 The two fastest sojourners are called guides.

 Repeat the following steps until all sojournes have crossed the bridge {
   1) if both guides are on the starting bank, then:
     1a) If there are only the two guides on the near bank, then we send both across to the far bank and we are done.
         time += time of slower guide.
     1b) Else, we send the two guides across to the farther bank and we use the faster guide to return the torch to the near bank.
         The time required = time needed for slower guide + time needed for faster guide
   2) If guides are on opposite banks:
     2a) if there are only one sojourners and a guide on the near bank, then we send them across.
         The time += time of the sojourner who is not the guide.
         And we are done -- all sojourners are across.
     2b) Else, we send the two slowest sojourners on the near bank across to the far bank.
         Next, the guide on the guide on the far bank, the slower guide, returns the torch to the near bank.
         time += time for slower guide to cross + time slowest sojourner to cross.
} 

Notice that, unless we are done, each step above end with the torch and the fastest guide on the near bank.


Building 
--------
The directory contans a Makefile. Go to the source code directory and enter "make". 
To run the file, go to the source code directory and run the command "bridges".


Debugging
---------
There are some debugging flags in the fie bridges.cpp. One is for debugging the yaml parser. The other is for calculating the time to cross bridges. Setting the flags to "true" turns them on.

Thera are also two test files.  By default, the bridge program reads and parses the fie, test.yaml. The directory also contains the file test_parse.yaml. It is a good aexample of what our minimal parser can do,  and it tests some edge cases of the bridge crossing algorithm as well. 

# Bridges
