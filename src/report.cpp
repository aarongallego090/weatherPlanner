#include "report.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <utility>
using namespace std;

static const string CITIES[] = {"Gainesville", "Orlando", "Tampa", "Miami", "NYC", "DC",
                                "Boston", "Chicago", "Houston", "Denver", "San Francisco", "Los Angeles"};
static const string ACTIVITIES[] = {"Running", "Tanning", "Swimming", "Picnic"};
static const string MONTHS[] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};

string cityName(int location) {
    if (location < 0 || location > 11) return "Unknown";
    return CITIES[location];
}

string activityName(int activity) {
    if (activity < 0 || activity > 3) return "Unknown";
    return ACTIVITIES[activity];
}

string formatDate(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
    if (month < 1 || month > 12) return "Invalid Date";
    return MONTHS[month - 1] + " " + to_string(day) + ", " + to_string(year);
}

vector<weatherNode> getAllNodes(Heap& weather) {
    Heap temp = weather;
    vector<weatherNode> nodes;
    while (!temp.empty()) {
        nodes.push_back(temp.top());
        temp.pop();
    }
    return nodes;
}

void printLocationReport(Heap& weather, int activity, int date, int location) {
    vector<weatherNode> all = getAllNodes(weather);

    // location -> date -> (sum of hourly scores, number of hours)
    map<int, map<int, pair<double, int>>> sums;
    for (weatherNode node : all) {
        if (node.hour < 6 || node.hour > 19) continue;
        if (location != -1 && node.loc != location) continue;

        node.score = 0;
        node.calculateScore(activity);

        pair<double, int>& entry = sums[node.loc][node.date];
        entry.first += node.score;
        entry.second++;
    }

    if (sums.empty()) {
        cout << "Weather Records Not Found" << endl;
        return;
    }

    int month = (date / 100) % 100;
    int year = date / 10000;
    string monthLabel = (month >= 1 && month <= 12) ? MONTHS[month - 1] + " " + to_string(year) : "Invalid Month";

    ios::fmtflags oldFlags = cout.flags();
    streamsize oldPrecision = cout.precision();
    cout << fixed << setprecision(2);

    for (auto& locEntry : sums) {
        int loc = locEntry.first;
        HashTable table;
        int dayCount = 0;
        double total = 0;
        double monthTotal = 0;
        int monthCount = 0;
        bool haveDate = false;
        double dateScore = 0;

        // Daily scores go into the hash table
        for (auto& dayEntry : locEntry.second) {
            double dayScore = dayEntry.second.first / dayEntry.second.second;
            weatherNode dayNode(dayEntry.first, 0, loc, 0, 0, 0, 0, dayScore);
            table.insert(dayNode);

            dayCount++;
            total += dayScore;

            if (dayEntry.first / 100 == date / 100) {
                monthTotal += dayScore;
                monthCount++;
            }
            if (dayEntry.first == date) {
                haveDate = true;
                dateScore = dayScore;
            }
        }

        // Retrieve every daily score back out of the hash table, then order by date
        vector<weatherNode> days = table.kLargest(dayCount);
        sort(days.begin(), days.end(), [](const weatherNode& a, const weatherNode& b) {
            return a.date < b.date;
        });
        // Exact best day (the hash table only separates scores to the nearest 0.1)
        const weatherNode* best = nullptr;
        for (const weatherNode& d : days) {
            if (best == nullptr || d.score > best->score) best = &d;
        }

        cout << endl << "========== " << cityName(loc) << " - " << activityName(activity) << " ==========" << endl;

        cout << "Score for " << formatDate(date) << ": ";
        if (haveDate) cout << dateScore << endl;
        else cout << "No Data Available" << endl;

        cout << "Score for the Month of " << monthLabel << " (Average): ";
        if (monthCount > 0) cout << monthTotal / monthCount << endl;
        else cout << "No Data Available" << endl;

        cout << "Score for Every Day:" << endl;
        for (const weatherNode& d : days) {
            cout << "  " << formatDate(d.date) << ": " << d.score << endl;
        }

        if (best != nullptr) {
            cout << "Best Day: " << formatDate(best->date) << " (Score: " << best->score << ")" << endl;
        }

        cout << "Average Score for " << cityName(loc) << ": " << total / dayCount << endl;
    }

    cout.flags(oldFlags);
    cout.precision(oldPrecision);
}

void runReport(Heap& weather) {
    int date, activity, location;

    cout << "Enter Date: YYYYMMDD" << endl;
    cin >> date;

    cout << "Choose an Activity:" << endl;
    cout << "0: Running, 1: Tanning, 2: Swimming, 3: Picnic" << endl;
    cin >> activity;
    while (activity < 0 || activity > 3) {
        cout << "Please Enter a Number From 0 to 3." << endl;
        cin >> activity;
    }

    cout << "Choose a City:" << endl;
    cout << "0: Gainesville, 1: Orlando, 2: Tampa, 3: Miami, 4: NYC, 5: DC, 6: Boston" << endl
         << "7: Chicago, 8: Houston, 9: Denver, 10: San Francisco, 11: Los Angeles, 12: All Cities" << endl;
    cin >> location;
    while (location < 0 || location > 12) {
        cout << "Please Enter a Number From 0 to 12." << endl;
        cin >> location;
    }
    if (location == 12) location = -1;

    printLocationReport(weather, activity, date, location);
}
