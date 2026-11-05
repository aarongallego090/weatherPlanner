#pragma once
#include <string>
#include <vector>
#include "heap.h"
#include "hashtable.h"

// Name helpers (properly capitalized for output)
std::string cityName(int location);
std::string activityName(int activity);

// Turns 20260101 into "January 1, 2026"
std::string formatDate(int date);

// Returns every node in the weather heap (works on a copy, original is untouched)
std::vector<weatherNode> getAllNodes(Heap& weather);

// Prints, for each location (or only one if location != -1):
//   - the score for the given date
//   - the score for the month of the given date
//   - the score for every day (retrieved from a HashTable)
//   - the average score for the location
// A day's score is the average of its hourly scores from 6:00 to 19:00.
void printLocationReport(Heap& weather, int activity, int date, int location = -1);

// Prompts the user for a date, activity and city, then prints the report
void runReport(Heap& weather);
