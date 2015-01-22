//Author: Andres Garcia de Alba
//
//Implementation file for VLSMFunctions

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool askToContinue(){
	bool flag = false;

	do
	{
		char answer;
		cout << "\nContinue? [Y]/[N]: ";
		cin >> answer;
		if (flag = cin.fail() || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(numeric_limits<int>::max(), '\n');
			continue;
		}

		if (answer == 'Y' || answer == 'y')
		{
			//clear the '\n' from the user entering 'Y'
			cin.clear();
			cin.ignore(numeric_limits<int>::max(), '\n');
			
			//clear the screen
			system("CLS");
			
			return true;
		}
		else if (answer == 'N' || answer == 'n') return false;
		
		flag = true;

	} while (flag);
}//end of fn

void sortUsers(long int no_users[], int no_networks){

	bool trigger = 0; //trigger for outside loop

	do
	{
		trigger = false; //reset
		for (int j = 0; j < no_networks; j++)
		{
			int temp;
			if (no_users[j] < no_users[j + 1])
			{
				temp = no_users[j + 1];
				no_users[j + 1] = no_users[j];
				no_users[j] = temp;
				trigger = true;
			}
		} //end of for loop
	} while (trigger);

}//end of fn

int subMask(long int no_users){ 

	if (no_users <= 2) return 252;
	else if (no_users <= 6) return 248;
	else if (no_users <= 14) return 240;
	else if (no_users <= 30) return 224;
	else if (no_users <= 62) return 192;
	else if (no_users <= 126) return 128;
	else if (no_users <= 254) return 0;
	else if (no_users <= 510) return 254;
	else if (no_users <= 1022) return 252;
	else if (no_users <= 2046) return 248;
	else if (no_users <= 4094) return 240;
	else if (no_users <= 8190) return 224;
	else if (no_users <= 16382) return 192;
	else if (no_users <= 32766) return 128;
	else if (no_users <= 65534) return 0;
	else if (no_users <= 131070) return 254;
	else if (no_users <= 262142) return 252;
	else if (no_users <= 524288) return 248;
	else if (no_users <= 1048574) return 240;
	else if (no_users <= 2097150) return 224;
	else if (no_users <= 4194302) return 192;
	else if (no_users <= 8388608) return 128;
	else if (no_users <= 16777214) return 0;
	else if (no_users <= 33554430) return 254;
	else if (no_users <= 67108862) return 252;
	else if (no_users <= 134217726) return 248;
	else if (no_users <= 268435454) return 240;
	else if (no_users <= 536870910) return 224;
	else if (no_users <= 1073741822) return 192;
	else if (no_users <= 2147483646) return 128;
	else if (no_users <= 4294967294) return 0;
	else return 0; //to delete compiler warning C4715: "not all paths return a value"

}

int totalUsers(long int no_users){

	if (no_users <= 1) return 2;
	else if (no_users <= 2) return 2;
	else if (no_users <= 6)	 return 6;
	else if (no_users <= 14) return 14;
	else if (no_users <= 30) return 30;
	else if (no_users <= 64) return 62;
	else if (no_users <= 126) return 126;
	else if (no_users <= 254) return 254;
	else if (no_users <= 510) return 510;
	else if (no_users <= 1022) return 1022;
	else if (no_users <= 2046) return 2046;
	else if (no_users <= 4094) return 4094;
	else if (no_users <= 8190) return 8190;
	else if (no_users <= 16382) return 16382;
	else if (no_users <= 32766) return 32766;
	else if (no_users <= 65534) return 65534;
	else if (no_users <= 131070) return 131070;
	else if (no_users <= 262142) return 262142;
	else if (no_users <= 524288) return 524288;
	else if (no_users <= 1048574) return 1048574;
	else if (no_users <= 2097150) return 2097150;
	else if (no_users <= 4194302) return 4194302;
	else if (no_users <= 8388608) return 8388608;
	else if (no_users <= 16777214) return 16777214;
	else if (no_users <= 33554430) return 33554430;
	else if (no_users <= 67108862) return 67108862;
	else if (no_users <= 134217726) return 134217726;
	else if (no_users <= 268435454) return 268435454;
	else if (no_users <= 536870910) return 536870910;
	else if (no_users <= 1073741822) return 1073741822;
	else if (no_users <= 2147483646) return 2147483646;
	else if (no_users <= 4294967294) return 4294967294;
	else return 0; //to delete compiler warning C4715: "not all paths return a value"

}

int magicNumber(int subnet[], int i){
	//returns the number to increment the next net
	switch (subnet[i])
	{
	case 255:
		return 1;
	case 254:
		return 2;
	case 252:
		return 4;
	case 248:
		return 8;
	case 240:
		return 16;
	case 224:
		return 32;
	case 192:
		return 64;
	case 128:
		return 128;
	default:
		break;
	}//end switch
}//end of fn

void updateNetwork(int network[], int subnet[]){

	//run loop 4 times to check each subnet[] octet
	for (int a = 0; a < 4; a++){
		//flag will be true to indicate the octet that we're working with
		bool flag = false;
		//if subnet octet is 0, that is the octet we will work with
		if (subnet[a] == 0)
		{
			network[a - 1] += 1;
			flag = true;
		}
		//else if subnet octet is less than 255, that is the octet we will work with
		else if (subnet[a] < 255)
		{
				flag = true;
				//increment by the "magic number"
				int temp;
				temp = magicNumber(subnet, a);
				//update the current network[] in the octet specified earlier
				network[a] += temp;

				//if new network is set past the allowalbe range
				if (network[a] > 252)
				{
					network[a - 1] += 1;
					network[a] = 0;
				}
		}//end of if

		//flag being true indicates that we have found the subnet[] octet that we will be incrementing by and break out of this loop
		if (flag == true)
			break;
	}//end of for loop

}//end of fn

void readIPAddress(int network[]){
	string temp[4];
	bool trigger;

	do
	{
		//set to false to avoid an infinite loop
		trigger = false;

		cout << "Enter the network address to VLSM: ";

		//read ip address from user as a string
		for (int i = 0; i < 4; i++){
			char delim = '.';

			if (i > 2) { delim = '\n'; }

			getline(cin, temp[i], delim);
		}
	
		//verify that the input contains only numbers
		char *ctemp;
		for (int i = 0; i < 4; i++)
		{
			//var for strcpy_s argument
			int size = temp[i].length() + 1;
			//create a char array in the heap the length of the temp[] + null char
			ctemp = new char[temp[i].length() + 1];
			//copy the converted ctring to the char array
			strcpy_s(ctemp, size, temp[i].c_str());


			//check the char array to make sure that the characters fall between ASCII code 48 & 57
			for (int j = 0; j < temp[i].length(); j++)
			{
				if (*(ctemp + j) < 48 || *(ctemp + j) > 57)
				{
					//causes readIPAddress() to run again.
					trigger = true;
				} //end of if
			}//end of for loop

			//delete the memory that the pointer variable is utilizing and set pointer to NULL
				delete ctemp;
				ctemp = NULL;
	
		}//end of for loop

		

		//convert ip address to an int and store in network[] of type int
		for (int i = 0; i < 4; i++){
			//Parses the C-string, interpreting its content as an integral number, which is returned as a value of type int.
			network[i] = atoi(temp[i].c_str());		
		}

		//validate the ip address entered
		if (network[0] < 0 || network[0] > 223) readIPAddress((network));

		for (int i = 1; i < 4; i++){
			if (network[i] < 0 || network[i] > 255) readIPAddress((network));
		}

	} while (trigger);
	
}//end of fn 

void readSubnetMask(int subnet[]){
	string temp[4];
	bool trigger;

	do
	{
		//set to false to avoid an infinite loop
		trigger = false;

		cout << "Enter the subnet address: ";

		//read subnet mask from user as a string
		for (int i = 0; i < 4; i++){
			char delim = '.';
			if (i > 2) { delim = '\n'; }
			getline(cin, temp[i], delim);
		}

		//verify that the input contains only numbers
		char *ctemp;
		for (int i = 0; i < 4; i++)
		{
			//var for strcpy_s argument
			int size = temp[i].length() + 1;
			//create a char array in the heap the length of the temp[] + null char
			ctemp = new char[temp[i].length() + 1];
			//copy the converted ctring to the char array
			strcpy_s(ctemp, size, temp[i].c_str());


			//check the char array to make sure that the characters fall between ASCII code 48 & 57
			for (int j = 0; j < temp[i].length(); j++)
			{
				if (*(ctemp + j) < 48 || *(ctemp + j) > 57)
				{
					//causes readSubnetMask to run again.
					trigger = true;
				} //end of if
			}//end of for loop

		}//end of for loop

		//delete the memory that the pointer variable is utilizing and set pointer to NULL
		delete ctemp;
		ctemp = NULL;

		//convert subnet address to an int and store in subnet[] of type int
		for (int i = 0; i < 4; i++){
			subnet[i] = atoi(temp[i].c_str());
		}

		//validate the subnet address entered
		for (int i = 0; i < 4; i++){

			switch (subnet[i])
			{
			case 0:
			case 128:
			case 192:
			case 224:
			case 240:
			case 248:
			case 252:
			case 254:
			case 255:
				break;
			default: readSubnetMask(subnet);
				break;
			}//end of switch

			//if < 255 is entered, then the rest of the octets must be 0
			if (i > 0 && subnet[i - 1] != 255 && subnet[i] != 0)
			{
				readSubnetMask(subnet);
			}
		}//end of for loop
	} while (trigger);
}

int readNumberofNetworks(int subnet[]){
	int sum = 0;
	for (int i = 0; i < 4; i++){
		
		switch (subnet[i])
		{
		case 255:
			sum += 8; break;
		case 254:
			sum += 7; break;
		case 252:
			sum += 6; break;
		case 248:
			sum += 5; break;
		case 240:
			sum += 4; break;
		case 224:
			sum += 3; break;
		case 192:
			sum += 2; break;
		case 128:
			sum += 1; break;
		default:
			sum += 0; break;
		}//end switch
	}//end of for loop
	int max_no_networks = static_cast <int> (pow(2, sum));
	
	int no_networks;
	bool flag;
	do
	{
		flag = false;
		cout << "Enter the total number of networks: ";
		cin >> no_networks;

		//cin.fail returns 1 if input entered does not match the value defined in the variable
		//or if there are any other characters after an integer that are not the newline character
		if (flag = cin.fail() || cin.peek() != '\n')
		{
			cin.clear(); //repairs the input stream
			cin.ignore(numeric_limits<int>::max(), '\n'); //clears the buffer
		}

		if (no_networks > max_no_networks){
			//if flag is true, then the user has entered too many networks. While loop continues
			flag = true;
		}

	} while (flag);

	return no_networks;
}

void readUsersPerNet(long int no_users[], int no_networks, int subnet[], bool &while_loop){
	
	int sum = 0;
	for (int i = 0; i < 4; i++){

		switch (subnet[i])
		{
		case 255:
			sum += 0; break;
		case 254:
			sum += 1; break;
		case 252:
			sum += 2; break;
		case 248:
			sum += 3; break;
		case 240:
			sum += 4; break;
		case 224:
			sum += 5; break;
		case 192:
			sum += 6; break;
		case 128:
			sum += 7; break;
		default:
			sum += 8; break;
		}//end switch
	}//end of for loop
	//pow() return a double value
	int max_no_users = static_cast<int>(pow(2, sum) - 2);

	bool flag = false;
	do
	{
		for (int i = 0; i < no_networks; i++){
			bool flag1 = false;
			do
			{
				flag1 = false;
				cout << "How many users in network " << i + 1 << ": ";
				cin >> no_users[i];

				//cin.fail returns 1 if input entered does not match the value defined in the variable
				//or if there are any other characters after an integer that are not the newline character
				if (flag = cin.fail() || cin.peek() != '\n')
				{
					cin.clear(); //repairs the input stream
					cin.ignore(numeric_limits<int>::max(), '\n'); //clears the buffer
					flag1 = true;
				}

			} while (flag1);

			//reduce the number of available users
			max_no_users = max_no_users - 2 - totalUsers(no_users[i]);
		}//end of for loop

		//check if no_users entered surpasses the max_no_users
		if (max_no_users < -3){
			cout << "\n\nSUBNETTING FAILED, TOO MANY USERS...\n\n";
			//if true, program will prompt the user to continue
			while_loop = true;
			continue;
		}
		
	} while (flag);

}//end of fn
