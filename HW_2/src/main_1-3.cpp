/*
AERSP 424 HW 2: Questions 1 - 3
Authors: Conor & Gabrielle Dowdell

*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <queue>
#include <cmath>
#include <memory>
#include <utility>


// Functions:

const int NUM_ROBOTS = 5;
std::mutex tools[NUM_ROBOTS];  // Mutexes to protect the tools
std::mutex outputMutex;         // Mutex to protect the output (std::cout)

int totalTime = 0;  // Variable to track the total time taken by all robots

// Simulate the task for each robot
void perform_task(int robot_id) {
    auto start = std::chrono::high_resolution_clock::now(); // Start time

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

    // Lock the output mutex to prevent race conditions in printing
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Robot " << robot_id << " grabbed tools " << tool1 << " and " << tool2 << "\n";
    }

    // Simulate the task (5 seconds)
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Lock the output mutex to prevent race conditions in printing
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Robot " << robot_id << " completed the task and returning tools\n";
    }

    // Return the tools (unlock the mutexes)
    tools[tool1].unlock();
    tools[tool2].unlock();

    auto end = std::chrono::high_resolution_clock::now(); // End time

    // Calculate the time taken by this robot
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    // Accumulate the maximum time taken by any robot
    totalTime = std::max(totalTime, static_cast<int>(duration.count()));
}


// Question 3 Functions
// Question 3 Functions
const int MAX_AIRCRAFT = 3;
const int TOTAL_AIRCRAFT = 10;

std::mutex mtx;
std::condition_variable cv;
bool atcTalking = false;
int aircraftInPattern = 0;
int aircraftLanded = 0;

void pilot(int id) // Function for landing aircraft
{
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating landing process
    std::unique_lock<std::mutex> lck(mtx);
    std::cout << "Aircraft #" << id << " requesting landing." << std::endl;

    if (aircraftInPattern < MAX_AIRCRAFT)
    {
        // If traffic pattern is not full, initiate communication
        std::cout << "Aircraft #" << id << " is cleared to land." << std::endl;
        aircraftInPattern++;
        cv.notify_one(); // Wake up ATC after landing clearance
    }
    else
    {
        // If traffic pattern is full, divert to another airport
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport." << std::endl;
        std::cout << "Aircraft #" << id << " flying to another airport." << std::endl;
    }
}

void atc() // Air traffic control function
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::unique_lock<std::mutex> lck(mtx);
    
    while (aircraftLanded < TOTAL_AIRCRAFT)
    {
        cv.wait(lck, [] { return aircraftInPattern > 0 || aircraftLanded >= TOTAL_AIRCRAFT; });

        if (aircraftLanded >= TOTAL_AIRCRAFT)
        {
            break; // All aircraft have landed, exit the loop
        }

        std::this_thread::sleep_for(std::chrono::seconds(4)); // Simulating conversation time
        std::cout << "Runway is now free." << std::endl;
        aircraftInPattern--;
        aircraftLanded++;

        // Notify if all aircraft have landed to stop ATC
        if (aircraftLanded == TOTAL_AIRCRAFT)
        {
            break;
        }
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Duration: " << duration.count() << " seconds." << std::endl;
}

int main1()
{
    // Question 1
    {
        std::cout << "------ Question 1 ------ \n" << std::endl;
        // 1.1
        // Abstract base class for sensors
        class Sensor 
        {
        public:
            virtual ~Sensor() {}
            virtual void gatherData() = 0;
            virtual void processData() = 0;
        };

        // 1.2
        // Derived class for Temperature Sensor
        class PositionSensor : public Sensor 
        {
        public:
            void gatherData() override
            {
                std::cout << "\nGathering data from Position Sensor." << std::endl;
            }

            void processData() override
            {
                std::cout << "Processing data from Position Sensor." << std::endl;
            }
        };

        // Derived class for Pressure Sensor
        class AirspeedSensor : public Sensor
        {
        public:
            void gatherData() override
            {
                std::cout << "Gathering data from Airspeed Sensor." << std::endl;
            }

            void processData() override
            {
                std::cout << "Processing data from Airspeed Sensor." << std::endl;
            }
        };

        // Derived class for Position Sensor
        class AltitudeSensor : public Sensor
        {
        public:
            void gatherData() override
            {
                std::cout << "Gathering data from Altitude Sensor." << std::endl;
            }

            void processData() override
            {
                std::cout << "Processing data from Altitude Sensor." << std::endl;
            }
        };

        // 1.3
        // Factory class for creating sensors
        class SensorFactory
        {
        public:
            static Sensor* createSensor(const std::string& sensorType)
            {
                Sensor* sensor = nullptr;

                if (sensorType == "Position") {
                    sensor = new PositionSensor();
                }
                else if (sensorType == "Airspeed") {
                    sensor = new AirspeedSensor();
                }
                else if (sensorType == "Altitude") {
                    sensor = new AltitudeSensor();
                }

                // Print memory address when the sensor is created
                if (sensor) {
                    std::cout << "Sensor created " << sensor << " of type \"" << sensorType << "\"" << std::endl;
                }
                
                return sensor;
            }

            // Static function to delete a sensor
            static void deleteSensor(Sensor* sensor, const std::string& sensorType)
            {
                // Print memory address when the sensor is deleted
                std::cout << "Sensor deleted " << sensor << " of type \"" << sensorType << "\"" << std::endl;
                delete sensor;
            }
        };

        // 1.4
        // Aerospace Control System class
        class AerospaceControlSystem
        {
        public:
            void addSensor(Sensor* sensor)
            {
                sensors.push_back(sensor);
            }

            void monitorAndAdjust()
            {
                for (Sensor* sensor : sensors)
                {
                    sensor->gatherData();
                    sensor->processData();
                    std::cout << "Adjusting controls based on sensor data. \n" << std::endl;
                }
            }

            ~AerospaceControlSystem()
            {
                // Delete the sensors
                for (Sensor* sensor : sensors)
                {
                    if (dynamic_cast<PositionSensor*>(sensor)) {
                        SensorFactory::deleteSensor(sensor, "Position");
                    }
                    else if (dynamic_cast<AirspeedSensor*>(sensor)) {
                        SensorFactory::deleteSensor(sensor, "Airspeed");
                    }
                    else if (dynamic_cast<AltitudeSensor*>(sensor)) {
                        SensorFactory::deleteSensor(sensor, "Altitude");
                    }
                }
            }

        private:
            std::vector<Sensor*> sensors;
        };

        // 1.5
        AerospaceControlSystem ctrlSys;

        // Add sensors
        ctrlSys.addSensor(SensorFactory::createSensor("Position"));
        ctrlSys.addSensor(SensorFactory::createSensor("Airspeed"));
        ctrlSys.addSensor(SensorFactory::createSensor("Altitude"));

        // Monitor and adjust
        ctrlSys.monitorAndAdjust();

        
    }

    // Question 2
    {
        // Delete sensors at the end of Q1
        std::cout << "\n------ End of Question 1 ------ \n" << std::endl;
        
        std::cout << "\n------ Question 2 ------ \n" << std::endl;

        std::thread robots[NUM_ROBOTS];

        // Start threads for each robot
        for (int i = 0; i < NUM_ROBOTS; i++) {
            robots[i] = std::thread(perform_task, i);
        }

        // Join threads to ensure all robots complete their tasks
        for (int i = 0; i < NUM_ROBOTS; i++) {
            robots[i].join();
        }

        // Output total time
        std::cout << "Duration: " << totalTime << " seconds \n" << std::endl;

        std::cout << "------ End of Question 2 ------ \n" << std::endl;
    }

    // Question 3
    {
        std::cout << "\n------ Question 3 ------ \n" << std::endl;

        std::thread atcThread(atc);

        std::thread aircraftThreads[TOTAL_AIRCRAFT];
        for (int i = 0; i < TOTAL_AIRCRAFT; ++i)
        {
            aircraftThreads[i] = std::thread(pilot, i + 1);
        }

        for (int i = 0; i < TOTAL_AIRCRAFT; ++i)
        {
            aircraftThreads[i].join(); // Join each aircraft thread
        }

        // Ensure ATC knows that all aircraft have been processed
        cv.notify_one(); // Notify ATC to process landings and finalize

        // Join the ATC thread once all aircraft have landed
        atcThread.join();

        std::cout << "\n------ End of Question 3 ------ \n" << std::endl;
    }

    return 0;
}
