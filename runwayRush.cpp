#include <iostream>
#include <fstream>
#include <random>

#define MAP_FILE_NAME "map.txt"

void generateMap(int rows, int cols);
int findShortestPath(...);

int main() {
    int minDistance;
    int rows, cols;

    std::cout << "Test case 1" << std::endl;
    rows = 10;
    cols = 10;
    generateMap(rows, cols);
    minDistance = findShortestPath(...);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 2" << std::endl;
    rows = 20;
    cols = 5;
    generateMap(rows, cols);
    minDistance = findShortestPath(...);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 3" << std::endl;
    rows = 5;
    cols = 20;
    generateMap(rows, cols);
    minDistance = findShortestPath(...);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 4" << std::endl;
    rows = 20;
    cols = 1;
    generateMap(rows, cols);
    minDistance = findShortestPath(...);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 5" << std::endl;
    rows = 1;
    cols = 20;
    generateMap(rows, cols);
    minDistance = findShortestPath(...);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 6" << std::endl;
    rows = 100;
    cols = 100;
    generateMap(rows, cols);
    minDistance = findShortestPath(...);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;
}

//generate random map
void generateMap(int rows, int cols) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 9);

    std::ofstream mapFile(MAP_FILE_NAME);

    if(!mapFile.is_open()) {
        std::cout << "Error writing map.txt file, check write privileges " << std::endl;
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 && j == 0) {
                mapFile << 0;
                continue;
            }

            if (j != 0) {
                mapFile << " ";
            }

            if (i != rows - 1 || j != cols - 1) {
                mapFile << dist(gen);
            }
            else {
                mapFile << 0;
            }
        }

        mapFile << std::endl;
    }
}