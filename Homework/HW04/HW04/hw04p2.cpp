/*
/*
* FILE: main.cpp
* Author: Tushar Shrivastav
* Based on: Main, Savitch Data Structures and Other Objects Using C++ (4th Edition)
* Class: CSCI 61


#include <iostream>
#include <cstdlib>
#include <queue>
#include <ctime>
#include "office_hours.h"

using namespace std;

//global vars
int time_beyond_one_hr = 0;
double avg_wait = 0;
int avg_office_time = 0;

//PROTOTYPES
void simulate_office_hours(unsigned int office_time, double p, unsigned int total_time);

int main() {

	//TO DO: ASK USER INPUTS
	//		RANDOMIZE OFFICE_TIME FOR EACH STUDENT

	//run program 100 times

	//need to print 
	//The average time a student spends waiting during an office hour visit
	//The average time a student spends with the professor during an office hour visit
	//The average time a Professor spends at an office hour beyond the 1 hour he intended to

	srand(time(0));
	for (int i = 0; i < 100; i++) {
		//ranndom arrival prob
		double arrival_prob = rand() % 101; //random number between 0-100
		//random service_rate
		unsigned int service_rate = rand() % 10 + 1; //time between 1 minute to 10 min
		simulate_office_hours(service_rate, arrival_prob / 100, 60);
		//get values from queue
	}


	cout << "average time student spends waiting: " << (avg_wait / 100) << " minutes" << endl;
	cout << "average time student spends with professor: " << (avg_office_time / 100) << " minutes" << endl;
	cout << "average time beyond 1 hr: " << (time_beyond_one_hr / 100) << " minutes" << endl;


	return 0;
}

void simulate_office_hours(unsigned int office_time, double p, unsigned int total_time) {
	priority_queue<Student> s;
	unsigned int next;
	bool_source arrival(p);
	office_hours office(office_time);
	averager wait_times;
	unsigned int current_second = 0;
	int total_time_spent = 0;

	while (current_second <= 60 || !s.empty()) {
		//check for new student //need to make sure we have not hit total_time too
		if (current_second < 60) {
			if (arrival.query()) {
				srand(time(0));
				int sp = ((rand() % 1000) + 1); //random student_priority 
				Student k = Student(rand() % 10 + 1, current_second, sp);
				s.push(k);
			}
		}

		if (!office.is_busy() && !s.empty()) {
			Student temp = s.top();
			unsigned int tmpoftime = temp.get_office_time();
			next = temp.get_arrival_time();
			s.pop();
			wait_times.next_number(current_second - next);
			office.start_office_hours(tmpoftime);
			total_time_spent += office.get_meeting_time_left();
		}
		office.one_second();
		current_second++;
	}

	if (wait_times.how_many_numbers() > 0) {
		avg_wait += wait_times.average();
		avg_office_time += (total_time_spent / (wait_times.how_many_numbers()));
		time_beyond_one_hr += (current_second - 60);
	}
}
*/