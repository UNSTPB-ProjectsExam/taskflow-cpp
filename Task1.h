#ifndef TASK_H
#define TASK_H

#include <string>

struct Task {
    int id;
    std::string description;
    int priority;

    Task() : id(0), description(""), priority(0) {}
    Task(int i, std::string d, int p) : id(i), description(d), priority(p) {}
};

#endif
