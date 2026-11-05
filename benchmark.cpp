#include "benchmark.h"
#include "hashtable.h"
#include "report.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Keeps the compiler from optimizing the timed work away
static volatile size_t sink = 0;

// Days since 1970-01-01 for a YYYYMMDD date (used to find the 7-day window)
static long dayNumber(int date) {
    long y = date / 10000;
    long m = (date / 100) % 100;
    long d = date % 100;
    y -= (m <= 2) ? 1 : 0;
    long era = (y >= 0 ? y : y - 399) / 400;
    long yoe = y - era * 400;
    long doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    long doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + doe - 719468;
}

struct BenchResult {
    string label;
    size_t hours;
    int runs;
    double heapInsert;
    double heapTopK;
    double hashInsert;
    double hashTopK;
};

// Times insert and top k separately for both structures, averaged over several runs
static BenchResult timeCase(const string& label, const vector<weatherNode>& nodes, int k, int runs) {
    BenchResult result{label, nodes.size(), runs, 0, 0, 0, 0};
    if (nodes.empty()) return result;

    int topK = min(k, (int)nodes.size());
    using clock = chrono::steady_clock;

    for (int r = 0; r < runs; r++) {
        // Heap insert
        auto t0 = clock::now();
        Heap heap(true);
        for (const weatherNode& node : nodes) heap.insert(node);
        auto t1 = clock::now();

        // Heap top k
        for (int i = 0; i < topK && !heap.empty(); i++) {
            sink += heap.top().hour;
            heap.pop();
        }
        auto t2 = clock::now();

        // Hash Table insert
        HashTable table;
        for (const weatherNode& node : nodes) table.insert(node);
        auto t3 = clock::now();

        // Hash Table top k
        vector<weatherNode> best = table.kLargest(topK);
        sink += best.size();
        auto t4 = clock::now();

        result.heapInsert += chrono::duration<double, micro>(t1 - t0).count();
        result.heapTopK += chrono::duration<double, micro>(t2 - t1).count();
        result.hashInsert += chrono::duration<double, micro>(t3 - t2).count();
        result.hashTopK += chrono::duration<double, micro>(t4 - t3).count();
    }

    result.heapInsert /= runs;
    result.heapTopK /= runs;
    result.hashInsert /= runs;
    result.hashTopK /= runs;
    return result;
}

void runBenchmark(Heap& weather) {
    int date, activity, k;

    cout << "Enter Date: YYYYMMDD" << endl;
    cin >> date;

    cout << "Choose an Activity:" << endl;
    cout << "0: Running, 1: Tanning, 2: Swimming, 3: Picnic" << endl;
    cin >> activity;
    while (activity < 0 || activity > 3) {
        cout << "Please Enter a Number From 0 to 3." << endl;
        cin >> activity;
    }

    cout << "How Many Hours to Show? (1-16)" << endl;
    cin >> k;
    while (k < 1 || k > 16) {
        cout << "Please Enter a Number From 1 to 16." << endl;
        cin >> k;
    }

    // Collect scored hours (6:00 to 19:00) for all 12 cities, grouped by time span
    vector<weatherNode> all = getAllNodes(weather);
    vector<weatherNode> dayNodes, weekNodes, monthNodes, yearNodes;
    long startDay = dayNumber(date);

    for (weatherNode node : all) {
        if (node.hour < 6 || node.hour > 19) continue;
        node.score = 0;
        node.calculateScore(activity);

        yearNodes.push_back(node);
        if (node.date / 100 == date / 100) monthNodes.push_back(node);

        long nodeDay = dayNumber(node.date);
        if (nodeDay >= startDay && nodeDay < startDay + 7) weekNodes.push_back(node);
        if (node.date == date) dayNodes.push_back(node);
    }

    if (dayNodes.empty()) {
        int firstDate = all.empty() ? 0 : all[0].date;
        int lastDate = firstDate;
        for (const weatherNode& node : all) {
            firstDate = min(firstDate, node.date);
            lastDate = max(lastDate, node.date);
        }
        cout << endl << "No Weather Records Found for " << formatDate(date) << "." << endl;
        cout << "Available Dates: " << formatDate(firstDate) << " to " << formatDate(lastDate) << endl;
        return;
    }

    cout << endl << "Speed Comparison: Heap vs. Hash Table" << endl;
    cout << "Activity: " << activityName(activity) << ", All 12 Cities, Top " << k << " Hours" << endl;
    cout << "Day: " << formatDate(date) << endl;
    cout << "Week: 7 Days Starting " << formatDate(date) << endl;
    cout << "Month: The Calendar Month of " << formatDate(date) << endl;
    cout << "Full Year: Every Day in the Data" << endl;
    cout << "Running (This May Take a Few Seconds)..." << endl;

    vector<BenchResult> results;
    results.push_back(timeCase("Day", dayNodes, k, 200));
    results.push_back(timeCase("Week", weekNodes, k, 50));
    results.push_back(timeCase("Month", monthNodes, k, 10));
    results.push_back(timeCase("Full Year", yearNodes, k, 3));

    ios::fmtflags oldFlags = cout.flags();
    streamsize oldPrecision = cout.precision();

    cout << endl << "All Times Are Averages in Microseconds" << endl;
    cout << left << setw(12) << "Size" << right << setw(10) << "Hours"
         << setw(7) << "Runs" << setw(15) << "Heap Insert" << setw(15) << "Heap Top K"
         << setw(15) << "Hash Insert" << setw(15) << "Hash Top K" << endl;
    cout << string(89, '-') << endl;

    cout << fixed << setprecision(1);
    for (const BenchResult& r : results) {
        cout << left << setw(12) << r.label << right << setw(10) << r.hours;
        if (r.hours == 0) {
            cout << "  No Data Available" << endl;
            continue;
        }
        cout << setw(7) << r.runs << setw(15) << r.heapInsert << setw(15) << r.heapTopK
             << setw(15) << r.hashInsert << setw(15) << r.hashTopK << endl;
    }

    cout.flags(oldFlags);
    cout.precision(oldPrecision);
}
