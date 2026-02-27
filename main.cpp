// Winter'24
// Instructor: Diba Mirza
// Student name: Ajit Saravanan
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    MovieDatabase db;

    string line, movieName;
    double movieRating;
    
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        // Use std::string movieName and double movieRating
        // to construct your Movie objects and insert them
        db.addMovie(movieName, movieRating);
    }

    movieFile.close();
    
    // Sort movies alphabetically immediately after loading them
    db.sortAlphabetically();

    if (argc == 2){
        // print all the movies in ascending alphabetical order of movie names
        db.printAllMovies();
        return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        // Strip trailing carriage return if running on Windows files
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    // Process all prefixes and store the string outputs for the "best movies"
    vector<string> bestMovies;
    for (const string& prefix : prefixes) {
        string best = db.processPrefix(prefix);
        if (!best.empty()) {
            bestMovies.push_back(best);
        }
    }
    
    // Print the highest rated movies at the very end
    for (const string& best : bestMovies) {
        cout << best << endl;
    }

    return 0;
}

/* 
Time Complexity Analysis
------------------------
Let `n` be the number of movies.
Let `m` be the number of prefixes.
Let `k` be the maximum number of matches for a single prefix.
Let `l` be the maximum length of a movie name.

Algorithm Steps and Time Complexity:
1. `std::lower_bound` takes O(l * log n) to find the first movie starting with the prefix.
2. Iterating through the matching movies takes O(k * l) time to collect the matches.
3. Sorting the `k` matches by rating takes O(k * log k * l) time.
4. Doing this for `m` prefixes repeats this process `m` times.

Total Time Complexity: O(m * l * (log n + k * log k))

Space Complexity Analysis
-------------------------
1. The `std::vector` stores `n` movies, taking O(n * l) space.
2. For each prefix, we create a temporary vector of up to `k` matches, taking O(k * l) space.
3. The array of `m` prefixes takes O(m * l) space.

Total Space Complexity: O(n * l + m * l + k * l) = O((n + m + k) * l)

Tradeoffs between Time/Space Complexity
---------------------------------------
Did you design your algorithm for a low time complexity, a low space complexity, or both? 
I designed my algorithm for a low space complexity while maintaining a highly competitive time complexity using STL algorithms. My target space complexity was O(n * l) and target time complexity was O(m * l * (log n + k * log k)).

Were you able to achieve a low time complexity as well? Why or why not? 
Yes, the time complexity is extremely fast in practice. By keeping the database sorted as a contiguous vector and using binary search (std::lower_bound), I avoided the massive memory footprint of a Trie. This array-based approach improves cache locality, allowing sequential memory accesses which offsets the theoretical O(m * l) time savings of a Trie lookup.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
