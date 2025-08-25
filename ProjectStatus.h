#pragma once
#include "Liberies.h"

enum class ProjectStatus {
    NotStarted,
    InProgress,
    Completed,
    OnHold,
    Error
};

string projectStatusToString(ProjectStatus status) {
    switch (status) {
    case ProjectStatus::NotStarted: return "Не начат";
    case ProjectStatus::InProgress: return "В прогрессе";
    case ProjectStatus::Completed: return "Выполнен";
    case ProjectStatus::OnHold: return "На удерживании";
    default: return "Неизвестно";
    }
}