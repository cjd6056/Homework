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

// Conor Dowdell
// AERSP 424 HW 2
// Questions 1 - 3


// Functions:

// Question 2 Function
const int NUM_ROBOTS = 5;
std::mutex toolMutex[NUM_ROBOTS];
std::mutex outputMutex;
int totalTime = 0;

void performTask(int robotId) 
{
    auto start = std::chrono::high_resolution_clock::now(); // Start time

    // Acquire tools
    toolMutex[robotId].lock();
    toolMutex[(robotId + 1) % NUM_ROBOTS].lock();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate 1-second delay for grabbing tools

    // Simulate collecting data
    outputMutex.lock();
    std::cout << "Robot " << robotId + 1 << " is collecting data." << std::endl;
    outputMutex.unlock();

    // Simulate grabbing tools
    outputMutex.lock();
    std::cout << "Robot " << robotId + 1 << " acquired tools and starts performing a task." << std::endl;
    outputMutex.unlock();

    // Simulate task execution/using tools
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Release tools
    toolMutex[robotId].unlock();
    toolMutex[(robotId + 1) % NUM_ROBOTS].unlock();

    // Simulate returning tools
    outputMutex.lock();
    std::cout << "Robot " << robotId + 1 << " finished the task and returning the tools." << std::endl;
    outputMutex.unlock();

    auto end = std::chrono::high_resolution_clock::now(); // End time

    // Calculate time taken by this robot
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    // Accumulate total time
    totalTime = std::max(totalTime, static_cast<int>(duration.count()));
}


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

    if (!atcTalking && aircraftInPattern < MAX_AIRCRAFT)
    {
        // If ATC is not talking and traffic pattern is not full, initiate communication
        atcTalking = true;
        std::cout << "Aircraft #" << id << " is cleared to land." << std::endl;
        cv.notify_one(); // Wake up ATC
    }
    else if (aircraftInPattern >= MAX_AIRCRAFT)
    {
        // If traffic pattern is full, divert to other airports
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport." << std::endl;
        std::cout << "Aircraft #" << id << " flying to another airport." << std::endl;
    }
    aircraftInPattern++;
}

void atc() // Air traffic control function
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::unique_lock<std::mutex> lck(mtx);
    while (aircraftLanded < TOTAL_AIRCRAFT)
    {
        cv.wait(lck, [] { return atcTalking || aircraftLanded >= TOTAL_AIRCRAFT; });
        if (aircraftLanded >= TOTAL_AIRCRAFT)
        {
            // All aircraft have landed, exit the loop
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(4)); // Simulating conversation
        std::cout << "Runway is now free." << std::endl;
        atcTalking = false;
        aircraftInPattern--;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Duration: " << duration.count() << " seconds." << std::endl;
}


int main()
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
                std::cout << "Gathering data from Position Sensor." << std::endl;
            }

            void processData() override
            {
                std::cout << "Processing data from Position Sensor." << std::endl;
            }
        };

        // Derived class for Pressure Sensor
        class VelocitySensor : public Sensor
        {
        public:
            void gatherData() override
            {
                std::cout << "Gathering data from Velocity Sensor." << std::endl;
            }

            void processData() override
            {
                std::cout << "Processing data from Velocity Sensor." << std::endl;
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
                if (sensorType == "Position")
                    return new PositionSensor();
                else if (sensorType == "Velocity")
                    return new VelocitySensor();
                else if (sensorType == "Altitude")
                    return new AltitudeSensor();
                else
                    return nullptr;
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

        private:
            std::vector<Sensor*> sensors;
        };

        // 1.5
        AerospaceControlSystem ctrlSys;

        // Add sensors
        ctrlSys.addSensor(SensorFactory::createSensor("Position"));
        ctrlSys.addSensor(SensorFactory::createSensor("Velocity"));
        ctrlSys.addSensor(SensorFactory::createSensor("Altitude"));

        // Monitor and adjust
        ctrlSys.monitorAndAdjust();

        std::cout << "------ End of Question 1 ------ \n" << std::endl;
    }

    // Question 2
    {
        std::cout << "------ Question 2 ------ \n" << std::endl;

        std::thread robots[NUM_ROBOTS];

        // Start threads for each robot
        for (int i = 0; i < NUM_ROBOTS; ++i) 
        {
            robots[i] = std::thread(performTask, i);
        }

        // Join threads
        for (int i = 0; i < NUM_ROBOTS; ++i) 
        {
            robots[i].join();
        }

        // Output total time
        std::cout << "Duration: " << totalTime << " seconds \n" << std::endl;

        std::cout << "------ End of Question 2 ------ \n" << std::endl;
    }

    // Question 3
    {
        std::cout << "------ Question 3 ------ \n" << std::endl;

        std::thread atcThread(atc);

        std::thread aircraftThreads[TOTAL_AIRCRAFT];
        for (int i = 0; i < TOTAL_AIRCRAFT; ++i)
        {
            aircraftThreads[i] = std::thread(pilot, i + 1);
        }

        for (int i = 0; i < TOTAL_AIRCRAFT; ++i)
        {
            aircraftThreads[i].join();
            aircraftLanded++;
        }

        cv.notify_one(); // Notify ATC to wake up and check if all aircraft have landed
        atcThread.join();

        std::cout << "\n------ End of Question 3 ------ \n" << std::endl;
    }

    // Question 4 in separate cpp file
}
