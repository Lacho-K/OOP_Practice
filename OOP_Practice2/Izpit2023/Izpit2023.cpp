#include <iostream>
#include "Sequence.hpp"
#include "CompositeTask.h"
#include "SimpleTask.h"

int even(int x)
{
    return x + 2;
}

int main()
{
    Sequence<int> seq(0, 10, even);

    for (int el : seq)
    {
        std::cout << el << " ";
    }

    std::cout << std::endl;

    Task** baseTasks = new Task * [3];

    Task** comp1SubTasks = new Task * [3];
    comp1SubTasks[0] = new SimpleTask("Login Page", 3);
    comp1SubTasks[1] = new SimpleTask("Crate Contact page", 2);
    comp1SubTasks[2] = new SimpleTask("Contacts list", 4);

    Task** comp2SubTasks = new Task * [2];
    comp2SubTasks[0] = new SimpleTask("Create AWS account", 1);
    comp2SubTasks[1] = new SimpleTask("Run deployment", 1);

    baseTasks[0] = new CompositeTask("WriteCode", comp1SubTasks, 3, 6);
    baseTasks[1] = new SimpleTask("Test app", 2);
    baseTasks[2] = new CompositeTask("Deploy", comp2SubTasks, 2, 4);

    

    CompositeTask task("Create My Contacts App", baseTasks, 3, 6);

    std::cout << task.totalTime() << std::endl;
    task.printPlan();

    for (int i = 0; i < 3; i++) 
        delete baseTasks[i];
    for (int i = 0; i < 3; i++) 
        delete comp1SubTasks[i];
    for (int i = 0; i < 2; i++) 
        delete comp2SubTasks[i];

    delete[] baseTasks;
    delete[] comp1SubTasks;
    delete[] comp2SubTasks;
}