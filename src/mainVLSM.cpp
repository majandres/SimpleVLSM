//SimpleVLSM -  will divide an IP address space into a hierarchy of subnets of different sizes
// Copyright (C) 2015  Andres Garcia de Alba

//This program is free software : you can redistribute it and / or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <string>
#include <iomanip>
#include "VLSMfunctions.h"
#include "Network.h"


using namespace std;

int main(){
	int network[4] = { 0 };
	int subnet[4] = { 0 };
	bool while_loop;

	cout << "SimpleVLSM Copyright(C) 2015  Andres Garcia de Alba\n";
	cout << "This program comes with ABSOLUTELY NO WARRANTY\n";
	cout << "This is free software, and you are welcome to redistribute it\n";
	cout << "under certain conditions\n";
	cout << "Visit: http://www.gnu.org/licenses/gpl.html for more details\n\n\n";

	do 
	{
		//reset while_loop
		while_loop = false;

		//read the IP address and store in network[]	
		readIPAddress(network);
		cout << "\n\n";

		//read the subnet into subnet[]
		readSubnetMask(subnet);
		cout << "\n\n";

		//prompt and receive the number of networks that are needed
		int no_networks = readNumberofNetworks(subnet);
		cout << "\n\n";

		//create dynamic array for no_users based on no_networks entered. pointer variable created
		long int *no_users;

		//allocate memory and returns a value of type pointer which is assigned to no_users
		no_users = new long int[no_networks];

		//read the number of users per network and store in no_users[]
		readUsersPerNet(no_users, no_networks, subnet, while_loop);
		if (while_loop == true)
		{
			//if subnetting fails, prompt user to continue or not. askToContinue() returns true or false
			while_loop = askToContinue();
			continue;
		}


		//sort users in descending order (ex. 100, 50, 20, etc...)
		sortUsers(no_users, no_networks);


		//create array of Networks based on toal number of networks entered by user
		Network *net;
		net = new Network[no_networks];

		//initialize each network object with correct network address's and subnet masks
		for (int i = 0; i < no_networks; i++){
			if (i == 0) 
			{ 
				//set the network address of the FIRST network
				net[i].setAddress(network, subnet);
			}
			else
			{
				//update network[], since the rest of the networks will be basing their information from it
				updateNetwork(network, subnet);
				//set the network address for the REST of the networks
				net[i].setAddress(network, subnet);
			}
			net[i].setMask(no_users, subnet, i);
			net[i].setFirstAddress(network);
			net[i].setLastAddress(network, no_users, subnet, i);
			net[i].setBroadcastAddress();
		}//end of for loop

		//print each network object and their corresponding network addresses and subnet masks
		cout << "\n\n";
		cout << setw(16) << left << "Network" << setw(16) << left << "First Address" << setw(16) << left << "Last Address" << setw(16) << left << "Broadcast" << setw(16) << left << "Subnet Address";
		cout << setw(79) << setfill('=') << "" << endl << setfill(' ');
		for (int i = 0; i < no_networks; i++){
			cout << left << setw(16); net[i].printNet();
			cout << left << setw(16); net[i].printFirst();
			cout << left << setw(16); net[i].printLast();
			cout << left << setw(16); net[i].printBroadcast();
			cout << left << setw(16); net[i].printMask(); cout << "\n";
		}

		//delete the memory that pointer variable is utilizing and set pointer to NULL
		delete no_users;
		no_users = NULL;

		//prompt user to continue or quit
		while_loop = askToContinue();
		
	} while (while_loop);
	

	return 0;
}