#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <chrono>

int main() {
    // Ввод данных
    double avg_passenger_time, avg_bus_time;
    bool is_terminal_stop;
    int max_passengers;

    std::cout << "Введите среднее время между появлениями пассажиров: ";
    std::cin >> avg_passenger_time;
    std::cout << "Введите среднее время между появлениями маршруток: ";
    std::cin >> avg_bus_time;
    std::cout << "Введите тип остановки (0 - не конечная, 1 - конечная): ";
    std::cin >> is_terminal_stop;
    std::cout << "Введите максимальное количество пассажиров на остановке: ";
    std::cin >> max_passengers;

    // Генерация случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> passenger_dist(1.0 / avg_passenger_time);
    std::exponential_distribution<double> bus_dist(1.0 / avg_bus_time);
    std::uniform_int_distribution<int> capacity_dist(1, 20);

    // Моделирование
    std::queue<double> passengers;
    std::vector<int> bus_capacities;
    double time = 0.0;
    double total_wait_time = 0.0;
    int num_passengers = 0;

    while (time < 86400) { // 1 день = 86400 секунд
        // Появление пассажиров
        double passenger_arrival_time = time + passenger_dist(gen);
        passengers.push(passenger_arrival_time);
        num_passengers++;

        // Появление маршруток
        double bus_arrival_time = time + bus_dist(gen);
        int bus_capacity = capacity_dist(gen);
        bus_capacities.push_back(bus_capacity);

        // Обработка пассажиров
        while (!passengers.empty() && passengers.front() <= bus_arrival_time) {
            total_wait_time += bus_arrival_time - passengers.front();
            passengers.pop();
            num_passengers--;
        }

        // Обновление времени
        time = std::max(bus_arrival_time, time + 1.0);
    }

    // Вывод результатов
    std::cout << "Среднее время пребывания человека на остановке: " << total_wait_time / num_passengers << " секунд" << std::endl;
    std::cout << "Достаточный интервал времени между приходами маршруток: " << avg_bus_time << " секунд" << std::endl;
    std::cout << "Максимальное количество пассажиров на остановке: " << max_passengers << std::endl;

    return 0;
}
