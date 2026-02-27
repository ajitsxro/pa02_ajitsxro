#include "movies.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

MovieDatabase::MovieDatabase() {}

MovieDatabase::~MovieDatabase() {}

void MovieDatabase::addMovie(const std::string& name, double rating) {
    movies.push_back({name, rating});
}

void MovieDatabase::sortAlphabetically() {
    std::sort(movies.begin(), movies.end());
}

void MovieDatabase::printAllMovies() const {
    for (const auto& movie : movies) {
        std::cout << movie.name << ", " << std::fixed << std::setprecision(1) << movie.rating << std::endl;
    }
}

std::string MovieDatabase::processPrefix(const std::string& prefix) const {
    Movie start_movie = {prefix, 0.0};
    auto lower = std::lower_bound(movies.begin(), movies.end(), start_movie);
    
    std::vector<Movie> matches;
    auto current = lower;
    
    while (current != movies.end() && current->name.substr(0, prefix.size()) == prefix) {
        matches.push_back(*current);
        ++current;
    }
    
    if (matches.empty()) {
        std::cout << "No movies found with prefix " << prefix << std::endl;
        return "";
    }
    
    std::sort(matches.begin(), matches.end(), [](const Movie& a, const Movie& b) {
        if (a.rating != b.rating) {
            return a.rating > b.rating; 
        }
        return a.name < b.name;         
    });
    
    for (const auto& movie : matches) {
        std::cout << movie.name << ", " << std::fixed << std::setprecision(1) << movie.rating << std::endl;
    }
    std::cout << std::endl;  // Blank line after each prefix's movies
    
    std::ostringstream best;
    best << "Best movie with prefix " << prefix << " is: " << matches[0].name 
         << " with rating " << std::fixed << std::setprecision(1) << matches[0].rating;
    return best.str();
}

size_t MovieDatabase::size() const {
    return movies.size();
}
