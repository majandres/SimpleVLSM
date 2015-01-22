//Author: Andres Garcia de Alba
//
//Specification file for the VLSMFunctions.

#ifndef VLSMFUNCTIONS_H
#define VLSMFUNCTIONS_H

bool askToContinue();

void sortUsers(long int no_users[], int no_networks);

int subMask(long int no_users);
	
int totalUsers(long int no_users);

int magicNumber(int subnet[], int i);

void updateNetwork(int network[], int subnet[]); 

void readIPAddress(int network[]);

void readSubnetMask(int subnet[]);

int readNumberofNetworks(int subnet[]);

void readUsersPerNet(long int no_users[], int no_networks, int subnet[], bool &while_loop);


#endif // !VLSMFUNCTIONS_H