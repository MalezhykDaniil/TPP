#include <iostream>
#include <memory>
#include <iomanip>
#include "shared_types.h"

std::unique_ptr<Result> calculateC(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);

int main() {
    auto input = std::make_shared<const InputData>(InputData{
        .points = { {0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}, {3.0, 9.0}, {4.0, 16.0} },
        .x0 = 2.5
        });

    auto resA = calculateA(input);
    auto resB = calculateB(input);
    auto resC = calculateC(input);

    auto [valA, errA] = *resA;
    auto [valB, errB] = *resB;
    auto [valC, errC] = *resC;

    std::cout << "1. Студент А (Поліном Лагранжа):\n";
    std::cout << "   - Значення: " << valA << "\n";
    std::cout << "   - Оцінка похибки: " << errA << "\n\n";

    std::cout << "2. Студент Б (Кубічний сплайн):\n";
    std::cout << "   - Значення: " << valB << "\n";
    std::cout << "   - Оцінка похибки: " << errB << "\n\n";

    std::cout << "3. Студент С (Інтерполяція Ньютона):\n";
    std::cout << "   - Значення: " << valC << "\n";
    std::cout << "   - Оцінка похибки: " << errC << "\n\n";


    return 0;
}