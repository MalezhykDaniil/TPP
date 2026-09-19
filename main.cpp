#include <iostream>
#include <memory>
#include <iomanip>
#include "shared_types.h"

std::unique_ptr<Result> calculateC(std::shared_ptr<const InputData> data);

int main() {
    auto input = std::make_shared<const InputData>(InputData{
        .points = { {0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}, {3.0, 9.0}, {4.0, 16.0} },
        .x0 = 2.5
        });

    auto resC = calculateC(input);

    auto [valC, errC] = *resC;

    std::cout << "3. Студент С (Інтерполяція Ньютона):\n";
    std::cout << "   - Значення: " << valC << "\n";
    std::cout << "   - Оцінка похибки: " << errC << "\n\n";

    return 0;
}