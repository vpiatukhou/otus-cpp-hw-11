#include "CombinationTransformer.h"

std::string Homework::transformCombinationToString(const std::vector<Combination>& combinations) {
    std::string result;

    for (auto& combination : combinations) {
        result += std::to_string(combination.id);
        result += ',';
        result += combination.nameA;
        result += ',';
        result += combination.nameB;
        result += '\n';
    }

    return result;
}