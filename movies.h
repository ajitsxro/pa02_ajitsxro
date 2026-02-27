#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>

struct Movie {
    std::string name;
    double rating;

    bool operator<(const Movie& other) const {
        return name < other.name;
    }
};

class MovieDatabase {
private:
    std::vector<Movie> movies;

public:
    MovieDatabase();
    ~MovieDatabase();

    void addMovie(const std::string& name, double rating);

    void sortAlphabetically();

    void printAllMovies() const;

    std::string processPrefix(const std::string& prefix) const;

    size_t size() const;
};

#endif 
