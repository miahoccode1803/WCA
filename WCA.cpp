#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Cấu trúc đại diện cho một cá thể
struct Individual {
    double x; // Vị trí x
    double fitness; // Giá trị hàm mục tiêu
};

// Hàm mục tiêu f(x) = x^2
double objectiveFunction(double x) {
    return x * x;
}

// Hàm khởi tạo quần thể ngẫu nhiên
void initializePopulation(vector<Individual> &population, int size, double lowerBound, double upperBound) {
    for (int i = 0; i < size; ++i) {
        double x = lowerBound + (upperBound - lowerBound) * ((double)rand() / RAND_MAX);
        population.push_back({x, objectiveFunction(x)});
    }
}

// Cập nhật vị trí của cá thể dựa trên dòng chảy
void updatePosition(Individual &stream, const Individual &target, double C) {
    double randFactor = (double)rand() / RAND_MAX;
    stream.x = stream.x + randFactor * C * (target.x - stream.x);
    stream.fitness = objectiveFunction(stream.x);
}

// Tạo giọt mưa mới ngẫu nhiên
void createNewRaindrop(Individual &stream, double lowerBound, double upperBound) {
    stream.x = lowerBound + (upperBound - lowerBound) * ((double)rand() / RAND_MAX);
    stream.fitness = objectiveFunction(stream.x);
}

int main() {
    srand(time(0));

    // Tham số thuật toán
    const int populationSize = 20;
    const int maxIterations = 50;
    const double lowerBound = -10.0;
    const double upperBound = 10.0;
    const double C = 2.0; // Hệ số điều chỉnh dòng chảy

    // Khởi tạo quần thể
    vector<Individual> population;
    initializePopulation(population, populationSize, lowerBound, upperBound);

    // Phân loại biển, sông và suối
    sort(population.begin(), population.end(), [](const Individual &a, const Individual &b) {
        return a.fitness < b.fitness;
    });
    Individual sea = population[0];
    vector<Individual> rivers(population.begin() + 1, population.begin() + 4); // 3 sông
    vector<Individual> streams(population.begin() + 4, population.end());      // Suối

    // Vòng lặp tối ưu hóa
    for (int iter = 0; iter < maxIterations; ++iter) {
        // Cập nhật vị trí của suối về sông
        for (auto &stream : streams) {
            const Individual &target = rivers[rand() % rivers.size()];
            updatePosition(stream, target, C);
        }

        // Cập nhật vị trí của sông về biển
        for (auto &river : rivers) {
            updatePosition(river, sea, C);
        }

        // Kiểm tra và hoán đổi nếu cần
        for (auto &river : rivers) {
            if (river.fitness < sea.fitness) {
                swap(river, sea);
            }
        }
        for (auto &stream : streams) {
            for (auto &river : rivers) {
                if (stream.fitness < river.fitness) {
                    swap(stream, river);
                }
            }
        }

        // Tạo giọt mưa mới nếu cần
        for (auto &stream : streams) {
            if (stream.fitness > sea.fitness) {
                createNewRaindrop(stream, lowerBound, upperBound);
            }
        }

        // Cập nhật cá thể tốt nhất (biển)
        sort(population.begin(), population.end(), [](const Individual &a, const Individual &b) {
            return a.fitness < b.fitness;
        });
        sea = population[0];

        // Hiển thị thông tin
        cout << "Iteration " << iter + 1 << ": Best Fitness = " << sea.fitness << endl;
    }

    // Kết quả cuối cùng
    cout << "\nOptimal Solution: x = " << sea.x << ", f(x) = " << sea.fitness << endl;

    return 0;
}
