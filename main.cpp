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
	beeClass(){}
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
void *attackWithBee(void *arg)
{
   beeClass* myBee;
   myBee = (beeClass*)arg;
   usleep(rand()%1000+1);
   cout << "Bee " << myBee->id << " is spining up "<< endl;
	// system(myBee->start.c_str());
	cout << "Bee " << myBee->id << " is starting its asult!" << endl;
	// system(myBee->attack.c_str());
	results[myBee->id] = "Assulted Completed by Bee " + to_string(myBee->id);
   pthread_exit(NULL);
}
int runAssult (beeClass* beeList){
	pthread_t threads[NUM_THREADS];
   	int thread;
   	int i;

   	pthread_attr_t attr;
   	void *status;

   	// Initialize and set thread joinable
   	pthread_attr_init(&attr);
   	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   	for(i = 0; i < NUM_THREADS; i++){
      	cout << "Hive: Bee swarm " << i <<  " is locked, loaded, and ready to go! " << endl;
      	thread = pthread_create(&threads[i], NULL, 
                          attackWithBee, (void *)&beeList[i]);
      	if (thread){
        	cout << "Hive: Massive failure!  We failed to ready Bee " << thread << "!" 
        		 << "Hive: Self destruction... initiated..." << endl;
        	exit(-1);
      	}
   	}
   	// free attribute and wait for the other threads
   	pthread_attr_destroy(&attr);
   	for(i = 0; i < NUM_THREADS; i++){
      	thread = pthread_join(threads[i], &status);
      	if (thread){
        	cout << "Hive: We have lost contact with swarm " << thread << "!" << endl;
        	cout << "Hive: They have refused to rejoin the hive!" << endl;
        	cout << "Hive: Self destruction... initiated..." << endl;
        	exit(-1);
      	}
      	cout << "Hive: Bee Swarm " << i << " has returned to the hive!";
      	cout << "  ariving with status :" << status << endl;
   	}

   	for(i = 0; i < NUM_THREADS; i++){
   		cout << "Hive: " << results[i] << endl;
   		// system(beeList[i].end.c_str());
   	}
   	cout << "Hive: Mission complete!  Shuting down..." << endl;
   	pthread_exit(NULL);
}

int main(){
	int arrayCount;
	char response;

	cout << "Hive: How many attacking bees do you want?";
	cin >> arrayCount;

	cout << "Hive: Please enter your pem file: ";
	cin >> pem;

	cout << "Hive: Please enter the number of instances to use: ";
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
	cout << "Hive: Do you wish to begin the assult? (y/n)" << endl;
	cout << "User > ";
	cin >> response;

	if(response == 'y' || response == 'Y'){
		cout << "Hive: Sit back, the assult will begin shortly." << endl;
		 runAssult(beeList);
	}
	else{
		cout << "Hive: We will dismiss the assembled swarms." << endl;
	}

	cout << "====================================" << endl;
	cout << "====================================" << endl;
	cout << "====================================" << endl;
	cout << "Hive: Shutting down..." << endl;

	delete[] beeList;
	return 0;
}