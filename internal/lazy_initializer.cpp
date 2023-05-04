#pragma once
#include "common.cpp"
namespace dalt {
Vec<Func<void(void)>> delay_tasks;
void AddDelayTask(const Func<void(void)> &task) {
  delay_tasks.push_back(task);
}
}