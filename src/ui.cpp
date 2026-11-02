#include "ui.h"
#include "heap.h"
#include "hashtable.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void menu(Heap& weather, Heap& scores, HashTable& hashScores){
    // Read the CSV into the weather heap (105,408 rows)
    readData(weather, 0);

    // Names for printing
    string cities[] = {"Gainesville", "Orlando", "Tampa", "Miami", "NYC", "DC",
                       "Boston", "Chicago", "Houston", "Denver", "San Francisco", "Los Angeles"};
    string activities[] = {"Running", "Tanning", "Swimming", "Picnic"};
    string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // First menu print
    cout << "---------- weatherPlanner ----------" << endl;
    cout << "1: Find the best hours for an activity" << endl;
    cout << "2: Compare speed: Heap vs. Hash Table" << endl;
    cout << "3: Exit" << endl;
    int x = 0;
    cin >> x;

    while(x != 3){
        if(x == 1){
            // Get date, location, activity, fill heap and hash table with scores
            int date;
            int location;
            int activity;
            int k;
            getDay(date, location, activity, k);
            vector <weatherNode> dayNodes = getDayNodes(date, location, activity, weather);
            if(dayNodes.empty()){
                cout << "Weather Records Not Found" << endl;
            }
            else {
                fillHeap(dayNodes, scores);
                fillHashTable(dayNodes, hashScores);

                // Header
                int month = (date / 100) % 100;
                int day = date % 100;
                cout << endl << activities[activity] << " in " << cities[location]
                     << " on " << months[month - 1] << " " << day << endl;

                // PRINT RESULTS
                cout << endl << "Best " << k << " Hours for activity (Heap):" << endl;

                for(int i = 0; i < k; i++){
                    if(scores.empty()) break;
                    printResult(i + 1, scores.top());
                    scores.pop();
                }

                cout << endl << "Best " << k << " Hours for activity (Hash Table):" << endl;
                vector<weatherNode> hashResults = hashScores.kLargest(k);
                for(int i = 0; i < hashResults.size(); i++){
                    printResult(i + 1, hashResults[i]);
                }

                cout << endl << "Based on past weather for this date." << endl;
            }
        }

        cout << endl << "---------- weatherPlanner ----------" << endl;
        cout << "1: Find the best hours for an activity" << endl;
        cout << "2: Compare speed: Heap vs. Hash Table" << endl;
        cout << "3: Exit" << endl;

        cin >> x;
    }
}

// Reads every row of the CSV into weather heap
void readData(Heap& weather, int method){
    ifstream file("projectData.csv");
    vector<weatherNode> nodes;

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
        precipitation = stod(field);

        getline(stream, field, ',');
        cloudCover = stoi(field);

        // Insert into a vector
        if(method == 0){
            weatherNode newNode = weatherNode(date, hour, id, temp, wind, precipitation, cloudCover, score);
            nodes.push_back(newNode);
        }
    }

    // Build heap
    if(method == 0) weather.buildHeap(nodes);
    file.close();
}

void getDay(int& date, int& location, int& activity, int& k){
    cout << "Enter Date: YYYYMMDD" << endl;
    cin >> date;

    cout << "Choose a city:" << endl;
    cout << "0: Gainesville, 1: Orlando, 2: Tampa, 3: Miami, 4: NYC, 5: DC, 6: Boston" << endl <<
            "7: Chicago, 8: Houston, 9: Denver, 10: San Francisco, 11: Los Angeles" << endl;
    cin >> location;

    cout << "Choose an activity:" << endl;
    cout << "0: Running, 1: Tanning, 2: Swimming, 3: Picnic" << endl;
    cin >> activity;

    cout << "How many hours to show? (1-14)" << endl;
    cin >> k;
    while (k<1 || k>14) {
        cout << "Please enter a number from 1 to 14." << endl;
        cin >> k;
    }
}

// Finds the hours for the chosen date and city, scores them for the activity
vector<weatherNode> getDayNodes(int date, int location, int activity, Heap &weather) {
    Heap temp = weather;
    vector<weatherNode> result;

    while (!temp.empty()) {
        weatherNode node = temp.top();
        temp.pop();

        if ((node.date % 10000 == date % 10000) && node.loc == location && (node.hour >=6 && node.hour <= 19)) {
            node.score = 0;
            node.calculateScore(activity);
            result.push_back(node);
        }
    }
    return result;
}

// Fills heap: clears, then inserts each node
void fillHeap(const vector<weatherNode>& dayNodes, Heap& scores){
    scores.clear();
    for (const auto& node : dayNodes) {
        scores.insert(node);
    }
}

// Fills hash table: clears, then inserts each node
void fillHashTable(const vector<weatherNode>& dayNodes, HashTable& hashScores) {
    hashScores.clear();
    for (const auto& node : dayNodes) {
        hashScores.insert(node);
    }
}

// Prints one result line (rank, hour, score and the weather for that hour)
void printResult(int rank, const weatherNode& node) {
    cout << rank << ": " << node.hour << ":00, Score: " << node.score;
    cout << "  (" << node.temp << " C, wind " << node.wind << " km/h, clouds " << node.cloudCover << "%, ";
    if (node.precip == 0) {
        cout << "dry)";
    }
    else {
        cout << "rain)";
    }
    cout << endl;
}