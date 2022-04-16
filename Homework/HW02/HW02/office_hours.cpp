#include <iostream>
#include <cassert>
#include <cstdlib>
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
    meeting_time_left = seconds_for_meeting;
}

