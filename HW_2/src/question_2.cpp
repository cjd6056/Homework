#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

const int NUM_ROBOTS = 5;
std::mutex tools[NUM_ROBOTS];  // Mutexes to protect the tools

// Simulate the task for each robot
void perform_task(int robot_id) {
    // Tools for the robot: tool 1 and tool 2 (circular)
    int tool1 = robot_id;
    int tool2 = (robot_id + 1) % NUM_ROBOTS;

    // Ensure we lock the mutexes in a consistent order (to avoid deadlock)
    if (tool1 < tool2) {
        tools[tool1].lock();
        tools[tool2].lock();
    } else {
        tools[tool2].lock();
        tools[tool1].lock();
    }

    // Simulate the time to grab the tools
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Robot " << robot_id << " grabbed tools " << tool1 << " and " << tool2 << "\n";

    // Simulate the task (5 seconds)
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Robot " << robot_id << " completed the task and returning tools\n";

    // Return the tools (unlock the mutexes)
    tools[tool1].unlock();
    tools[tool2].unlock();
}

int main() {
    std::thread robots[NUM_ROBOTS];

    // Start threads for each robot
    for (int i = 0; i < NUM_ROBOTS; i++) {
        robots[i] = std::thread(perform_task, i);
    }

    // Join threads to ensure all robots complete their tasks
    for (int i = 0; i < NUM_ROBOTS; i++) {
        robots[i].join();
    }

    return 0;
}
