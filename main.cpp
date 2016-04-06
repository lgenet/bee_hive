#include <iostream>
#include <limits>
#include <pthread.h>
#include <unistd.h>

using namespace std;

string pem;
string instances;
string results[4];

class beeClass{
public:
	string start = "bees -v";
	string end = "bees down";
	string attack = "bees report";
	int id = 0;

	beeClass(string a, int i){
		start = "bees up -s " + instances + " -g default -k " + pem;
		attack = a;
		id = i;
	}
	beeClass(){

	}
};


beeClass makeBee(int i){
	string attackCommand = "";
	cout << "Please enter the attack command: " << endl;
	getline(cin, attackCommand);

	beeClass c = *new beeClass(attackCommand, i);
	return c;
}
void clearCin(){
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
#define NUM_THREADS 4
void *PrintHello(void *arg)
{
   beeClass* myBee;
   myBee = (beeClass*)arg;
   usleep(rand()%1000+1);
   cout << "Hello World! Thread ID, " << myBee->id << endl;
   cout << "BEE " << myBee->id << " Start: " << myBee->start << " | Attack: " << myBee->attack << " | end: " << myBee->end << endl;
	results[myBee->id] = "Completed by Bee " + myBee->id;
   pthread_exit(NULL);
}
int runAssult (beeClass* beeList){
	pthread_t threads[NUM_THREADS];
   	int thread;
   	int i;
   	for( i=0; i < NUM_THREADS; i++ ){
      cout << "AssultFunction: creating thread, " << i << endl;
      thread = pthread_create(&threads[i], NULL, 
                          PrintHello, (void *)&beeList[i]);
      if (thread){
         cout << "AssultFunction Error:unable to create thread," << thread << endl;
         exit(-1);
      }
   }
   cout << "Threads are done in main" << endl;
   pthread_exit(NULL);
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
		beeList[i] = makeBee(i);
	}

	cout << "====================================" << endl;
	cout << "= These are the commands to be run =" << endl;
	cout << "====================================" << endl;
	for(int i = 0; i < arrayCount; i++){
		cout << "BEE " << i << " Start: " << beeList[i].start << " | Attack: " << beeList[i].attack << " | end: " << beeList[i].end << endl;
	}
	cout << "====================================" << endl;
	cout << "Do you wish to begin the assult? (y/n)" << endl;
	cout << "User > ";
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

