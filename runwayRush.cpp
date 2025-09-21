#include <iostream>
#include <fstream>
#include <random>

#define ROWS 10
#define COLS 10
#define MAP_FILE_NAME "map.txt"

void generateMap();
int findShortestPath(...);

int main() {
    generateMap();
    int minDistance = findShortestPath(...);

    std::cout << "Minimum traversal time: " << minDistance << std::endl;
}

//generate random map
void generateMap() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 9);

    std::ofstream mapFile(MAP_FILE_NAME);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 && j == 0) {
                mapFile << 0;
                continue;
            }

            if (j != 0) {
                mapFile << " ";
            }

            if (i != ROWS - 1 || j != COLS - 1) {
                mapFile << dist(gen);
            }
            else {
                mapFile << 0;
            }
        }

        mapFile << std::endl;
    }
}