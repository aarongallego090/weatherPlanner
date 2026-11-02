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

1. **Find the best hours for an activity:** enter a date (YYYYMMDD), a city, an activity, and how many hours to show (1–14). The program shows the best hours between 6 AM and 7 PM, with the weather for each hour. 
2. **Compare speed: Heap vs. Hash Table:** times both data structures and shows which one is faster.
3. **Exit**

## Data

We used hourly weather data from [Open-Meteo](https://open-meteo.com/en/docs/historical-weather-api) for 12 cities, from September 30, 2025 to September 30, 2026. It has 105,408 rows, with temperature, wind, rain, and cloud cover for each hour.

## Data structures

- **Heap:** keeps the highest score at the top.
- **Hash table:** groups the hours by score, so it can go from the highest score down.

## Team

- **Aaron:** heap, menu, loading the data, scoring
- **Samantha:** hash table, adding it to the menu, build setup
- **Scott:** speed test
