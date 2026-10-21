#include "ui.h"
#include "heap.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void menu(Heap& weather, Heap& scores){
    // First menu print

    cout << "---------- weatherPlanner ----------" << endl;
    cout << "1: Find the best hours for an activity" << endl;
    cout << "2: Compare speed: Heap vs. hash map" << endl;
    cout << "3: Exit" << endl;
    int x = 0;
    cin >> x;

    while(x != 3){
        if(x == 1){
            // TODO: add hash table option

            // Read csv and build data structure. 0 = heap, 1 = hash table
            readData(weather, 0);

            // Get date, location, activity
            int date;
            int location;
            int activity;
            getDay(date, location, activity);

            // Create day data structure, score them
            fillDayHeap(date, location, activity, weather, scores);
            cout << "Score at top: " << scores.top().score << ", Temperature: " << scores.top().temp << endl;
        }

        cout << endl << "---------- weatherPlanner ----------" << endl;
        cout << "1: Find the best hours for an activity" << endl;
        cout << "2: Compare speed: Heap vs. hash map" << endl;
        cout << "3: Exit" << endl;

        cin >> x;
    }
}

void readData(Heap& weather, int method){
    ifstream file("projectData.csv");

    if (!file.is_open()) {
        cerr << "Failed to open CSV file" << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream stream(line);
        string field;

        int id;
        int date;
        int hour;
        double temp, wind, precipitation;
        int cloudCover;
        int score = 0;

        // Location
        getline(stream, field, ',');
        id = stoi(field);

        // Date and time
        string datetime;
        getline(stream, datetime, ',');

        size_t space = datetime.find(' ');

        string dateString = datetime.substr(0, space);
        string timeString = datetime.substr(space + 1);

        // Convert YYYY-MM-DD to YYYYMMDD
        date = stoi(
                dateString.substr(0, 4) +
                dateString.substr(5, 2) +
                dateString.substr(8, 2)
        );

        // Convert HH:MM to hour
        hour = stoi(timeString.substr(0, timeString.find(':')));

        // Weather Vars
        getline(stream, field, ',');
        temp = stod(field);

        getline(stream, field, ',');
        wind = stod(field);

        getline(stream, field, ',');
        precipitation = stoi(field);

        getline(stream, field, ',');
        cloudCover = stoi(field);

        // Insert
        if(method == 0){
            weather.insert(date, hour, id, temp, wind, precipitation, cloudCover, score);
        }
    }
    file.close();
}

void getDay(int& date, int& location, int& activity){
    cout << "Enter Date: YYYYMMDD" << endl;
    cin >> date;

    cout << "Choose a city:" << endl;
    cout << "0: Gainesville, 1: Orlando, 2: Tampa, 3: Miami,"
            "4: NYC, 5: DC, 6: Boston, 7: Chicago, "
            "8: Houston, 9: Denver, 10: San Francisco, 11: Los Angeles" << endl;
    cin >> location;

    cout << "Choose an activity:" << endl;
    cout << "0: Running, 1: Tanning, 2: Swimming. 3: Picnic" << endl;
    cin >> activity;
}

bool fillDayHeap(int& date, int& location, int& activity, Heap& weather, Heap& scores){
    Heap temp = weather;

    while (!temp.empty() && temp.top().date <= date) {
        auto node = temp.top();
        temp.pop();

        if (node.date == date && node.loc == location) {
            // HELP
            node.calculateScore(activity);
            scores.insert(node);
        }
    }

    if(scores.empty()){
        cout << "Weather Records Not Found" << endl;
        return false;
    }
    return true;
}