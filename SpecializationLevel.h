#pragma once
#include "Liberies.h"

enum class SpecializationLevel {
    Junior,
    Middle,
    Senior
};

string specializationLevelToString(SpecializationLevel level) {
    switch (level) {
    case SpecializationLevel::Junior: return "Junior";
    case SpecializationLevel::Middle: return "Middle";
    case SpecializationLevel::Senior: return "Senior";
    default: return "Unknown";
    }
}