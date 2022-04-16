#include <iostream>
#include <cstdlib>
#include <queue>
#include "office_hours.h"

using namespace std;

 //global vars
int time_beyond_one_hr = 0;
int avg_wait = 0;
int avg_office_time = 0;

//PROTOTYPES
void simulate_office_hours(unsigned int office_time, double p, unsigned int total_time);

int main() {
    //run program 100 times

	//need to print 
	//The average time a student spends waiting during an office hour visit
	//The average time a student spends with the professor during an office hour visit
	//The average time a Professor spends at an office hour beyond the 1 hour he intended to

	for (int i = 0; i < 100; i++) {
		//ranndom arrival prob
		double random_service_rate = rand()% 15 + 15;
		//random service_rate
		unsigned int totaltimerandom = rand()% 15 + 1;
		simulate_office_hours(totaltimerandom, random_service_rate/100 , 60);
	}

	cout<< "average time student spends waiting: " << (avg_wait/100) << endl;
	cout<< "average time student spends with professor: " << (avg_office_time/100) << endl;
	cout<< "average time beyond 1 hr: " << (time_beyond_one_hr/100) << endl;

	return 0;
}

void simulate_office_hours(unsigned int office_time, double p, unsigned int total_time) {
	queue<unsigned int> arrival_times;
	unsigned int next;

	bool_source arrival(p);
	office_hours office(office_time);
	averager wait_times;
	unsigned int current_second = 0;

	while (current_second <= 60 || !arrival_times.empty()) {

		if (current_second < 60) {
			if (arrival.query()) 
				arrival_times.push(current_second);
		}

		if (!office.is_busy() && !arrival_times.empty()) {
			next = arrival_times.front();
			arrival_times.pop();
			wait_times.next_number(current_second - next);
			office.start_office_hours();
		}
		office.one_second();
		current_second++;

	}

	time_beyond_one_hr += (current_second - 60);
	avg_wait += wait_times.average();
	avg_office_time += office_time;

}
