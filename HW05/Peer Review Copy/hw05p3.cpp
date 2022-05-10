/*
* FILE: main.cpp
* Author: Tushar Shrivastav
* Based on: Main, Savitch Data Structures and Other Objects Using C++ (4th Edition)
* Class: CSCI 61
*/
#include <iostream>
#include <cstdlib>
#include <queue>
#include <ctime>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <random>
#include <windows.h>
#include "office_hours.h"

using namespace std;
using u32 = uint_least32_t;
using engine = mt19937;

//global vars
int time_beyond_one_hr = 0;
double avg_wait = 0;
int avg_office_time = 0;
multimap<string, string> students;
map<string, int> number_of_times;

//PROTOTYPES
void simulate_office_hours(unsigned int office_time, double p, unsigned int total_time);
string get_topic();
string get_name();

int main() {
	
	for (int i = 0; i < 100; i++) {
		
		double arrival_prob = rand() % 101; //random number between 0-100
		unsigned int service_rate = rand() % 10 + 1; //time between 1 minute to 10 min
		simulate_office_hours(service_rate, arrival_prob / 100, 60);
	}


	cout << "average time student spends waiting: " << (avg_wait / 100) << " minutes" << endl;
	cout << "average time student spends with professor: " << (avg_office_time / 100) << " minutes" << endl;
	cout << "average time beyond 1 hr: " << (time_beyond_one_hr / 100) << " minutes" << endl;

	//generate report
	ofstream stream("student_data.txt");

	
	multimap<string, string>::iterator itr;
	for (const auto& i : number_of_times) {
		stream << i.first << " " << i.second << " ";
		string s = i.first;
		for (auto j = students.begin(); j != students.end(); j++) {
			if(s == j->first)
				stream << j->second << " ";
		}
		stream << endl;
	}
	

	stream.close();

	return 0;
}

string get_topic() {

	const string topic_arr[26] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t" ,"u", "v", "w", "x", "y", "z" };
	random_device os_seed;
	const u32 seed = os_seed();
	engine generator(seed);
	uniform_int_distribution< u32 > distribute(0, 19);
	return topic_arr[distribute(generator)];
}

string get_name() {
	const string student_arr[40] = { "Student1", "Student2", "Student3", "Student4", "Student5", "Student6", "Student7", "Student8", "Student9", "Student10", "Student11", "Student12", "Student13", "Student14", "Student15", "Student16","Student17", "Student18", "Student19", 
		"Student20", "Student21", "Student22", "Student23", "Student24", "Student25", "Student26", "Student27", "Student28", "Student29", "Student30" , "Student31" , "Student32" , "Student33" , "Student34" , "Student35", "Student36" , "Student37" , "Student38" , "Student39", 
		"Student40" };
	random_device os_seed;
	const u32 seed = os_seed();
	engine generator(seed);
	uniform_int_distribution< u32 > distribute(0, 39);
	return student_arr[distribute(generator)];
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
				//srand(time(0));
				int sp = ((rand() % 1000) + 1); //random student_priority 
				string str = get_name();
				string tpc = get_topic();
				Student k = Student(rand() % 10 + 1, current_second, sp, str, tpc);
				cout << k.get_name() << " " << k.get_topic() << endl;
				s.push(k);
			}
		}

		if (!office.is_busy() && !s.empty()) {
			Student temp = s.top();
			unsigned int tmpoftime = temp.get_office_time();
			next = temp.get_arrival_time();
			number_of_times[temp.get_name()]++;
			students.insert(make_pair(temp.get_name(), temp.get_topic()));
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