# weatherPlanner

weatherPlanner helps you find the best hours of the day for an activity. You pick a city, a date and an activity, and the program uses past weather to show the best hours. It also compares a heap and a hash table to see which one is faster.

## How to run

You need a C++17 compiler and CMake. CLion already has both.

**In CLion:**
1. Clone the repository.
2. Go to File -> Open, select `CMakeLists.txt`, and choose Open as Project.
3. Build and run.

The data file is copied automatically, so you don't need to set anything up.

**In the terminal:**
```
cmake -S . -B build
cmake --build build
cd build
./weatherPlanner
```
On Windows, run `weatherPlanner.exe` instead.

## How to use

The program shows a menu:

1. **Find the best hours for an activity:** enter a date (YYYYMMDD), a city, an activity, and how many hours to show (1–14). The program shows the best hours between 6 AM and 7 PM from both the heap and the hash table, with the weather for each hour. Any date works, since it uses the same month and day from our data.
2. **Compare speed: Heap vs. Hash Table:** enter a date, an activity, and how many hours to find. The program times inserting and finding the top hours for both data structures, using a day, a week, a month and the full year of data (105,408 hours).
3. **Location Score Report:** enter a date, an activity, and a city (or all cities). The program shows the score for that date, the average for that month, the score for every day, the best day and the average score for the city. A day's score is the average of its hours from 6 AM to 7 PM.
4. **Exit**

For options 2 and 3, the date has to be in our data (September 30, 2025 to September 30, 2026).

## Data

We used hourly weather data from [Open-Meteo](https://open-meteo.com/en/docs/historical-weather-api) for 12 cities, from September 30, 2025 to September 30, 2026. It has 105,408 rows, with temperature, wind, rain, and cloud cover for each hour.

## Data structures

- **Heap:** keeps the highest score at the top.
- **Hash table:** groups the hours by score, so it can go from the highest score down.

## Team

- **Aaron:** heap, menu, loading the data, scoring
- **Samantha:** hash table, adding it to the menu, build setup, README
- **Scott:** speed test, location score report
