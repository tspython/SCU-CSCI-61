/*
* FILE: office_hours.h
* Author: Tushar Shrivastav
* Based on: Main, Savitch Data Structures and Other Objects Using C++ (4th Edition)
* Class: CSCI 61
*/

#ifndef OFFICE_HOURS_H
#define OFFICE_HOURS_H

#include <iostream>
#include <cstdlib>


class bool_source {
	public: 
		//constructors
		bool_source(double p = 0.5);

		//functions
		bool query() const;
	private:
		double probability; //Probability of query() returning true
};

class averager {
	public:
		//constructor
		averager();

		//functions
		void next_number(double value);
		std::size_t how_many_numbers() const {
			return count;
		}
		double average() const;
	private:
		std::size_t count;
		double sum;
};

class Student
{
	public:
		Student();
		Student(unsigned int ot, unsigned int at);
		int get_office_time() {
			return office_time;
		}
		int get_arrival_time() {
			return arrival_time;
		}
		void set_office_time(int of) {
			office_time = of;
		}
	private:
		int office_time;
		int arrival_time;
};


class office_hours {
	
	public:
		//constructors
		office_hours(unsigned int s = 60);
		
		//functions
		void one_second();
		void start_office_hours();
		bool is_busy() const {
			return (meeting_time_left > 0);
		}
	private:
		unsigned int seconds_for_meeting;
		unsigned int meeting_time_left;

};

#endif