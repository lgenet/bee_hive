#include <iostream>
#include <limits>
#include <pthread.h>

using namespace std;

string pem;
string instances;
class beeClass{
public:
	string start = "bees -v";
	string end = "bees down";
	string attack = "bees report";

	beeClass(string a){
		start = "bees up -s " + instances + " -g default -k " + pem;
		attack = a;
	}
	beeClass(){

	}
};


beeClass makeBee(){
	string attackCommand = "";
	cout << "Please enter the attack command: " << endl;
	getline(cin, attackCommand);

	beeClass c = *new beeClass(attackCommand);
	return c;
}
void clearCin(){
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int main(){
	int arrayCount	;
	char response;

	cout << "How many attacking bees do you want?";
	cin >> arrayCount;

	cout << "Please enter your pem file: ";
	cin >> pem;

	cout << "Please enter the number of instances to use: ";
	cin >> instances;

	clearCin();

	beeClass* beeList = new beeClass[arrayCount];
	for(int i = 0; i < arrayCount; i++){
		beeList[i] = makeBee();
	}

	cout << "====================================" << endl;
	cout << "= These are the commands to be run ="
	cout << "====================================" << endl;
	for(int i = 0; i < arrayCount; i++){
		cout << "BEE " << i << " Start: " << beeList[i].start << " | Attack: " << beeList[i].attack << " | end: " << beeList[i].end << endl;
	}
	cout << "====================================" << endl;
	cout << "Do you wish to begin the assult? (y/n)" << endl;
	cout >> "User > ";
	cin >> response;

	if(response == 'y' || response == 'Y'){
		cout << "Sit back, the assult will begin shortly." << endl;
		runAssult(beeList);
	}
	else{
		cout << "We will dismiss the assembled swarms." << endl;
	}

	cout << "====================================" << endl;
	cout << "====================================" << endl;
	cout << "====================================" << endl;
	cout << "Terminating Execution..." << endl;

	delete[] beeList;
	return 0;
}

