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
    case ProjectStatus::NotStarted: return "�� �����";
    case ProjectStatus::InProgress: return "� ���������";
    case ProjectStatus::Completed: return "��������";
    case ProjectStatus::OnHold: return "�� �����������";
    default: return "����������";
    }
}