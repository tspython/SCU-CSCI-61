/*
* FILE: office_hours.cpp
* Author: Tushar Shrivastav
* Based on: Main, Savitch Data Structures and Other Objects Using C++ (4th Edition)
* Class: CSCI 61
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "office_hours.h"


//bool_source implementation

bool_source::bool_source(double p) {
    assert(p >= 0);
    assert(p <= 1);
    probability = p;
}

bool bool_source::query() const {
    return (rand() < probability * RAND_MAX);
}

averager::averager() {
    count = 0;
    sum = 0;
}

void averager::next_number(double value) {
    ++count;
    sum += value;
}

double averager::average() const{
    assert(how_many_numbers() > 0);
    return sum / count;
}

Student::Student() {
    office_time = 0;
    arrival_time = 0;
}

Student::Student(unsigned int ot, unsigned int at) {
    office_time = ot;
    arrival_time = at;
}

office_hours::office_hours(unsigned int s) {
    seconds_for_meeting = s;
    meeting_time_left = 0;
}

void office_hours::one_second() {
    if (is_busy())
        meeting_time_left--;
}

void office_hours::start_office_hours() {
    assert(!is_busy());
    //reset to another random value between 1 and 10 minutes
    srand(time(0));
    meeting_time_left = rand() % 10 + 1;
    //std::cout << meeting_time_left << std::endl; | DEBUG STATEMENT
}

