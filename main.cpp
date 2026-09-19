#include <iostream>
#include <memory>
#include <iomanip>
#include "shared_types.h"

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);

int main() {
    auto input = std::make_shared<const InputData>(InputData{
        .points = { {0.0, 0.0}, {1.0, 1.0}, {2.0, 4.0}, {3.0, 9.0}, {4.0, 16.0} },
        .x0 = 2.5
        });

    auto resB = calculateB(input);
    auto [valB, errB] = *resB;

    std::cout << "2. Студент Б (Кубічний сплайн):\n";
    std::cout << "   - Значення: " << valB << "\n";
    std::cout << "   - Оцінка похибки: " << errB << "\n\n";

    return 0;
}