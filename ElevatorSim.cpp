#include <iostream>
#include <mutex>
#include <thread>
#include <random>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <cstdlib>

std::random_device rd;
std::mt19937 gen(rd());

std::queue<int> floorQueue;
std::mutex mtx;
std::condition_variable cv;

class Elevator{
public:
double position = 0.0;
double acceleration = 0.0;
double speed = 0.0;

void Engine(int floor){
    const double Kp = 1.5, Kd = 2.0, dt = 0.01;
    double prevError = floor - position;

    while(std::abs(floor - position) > 0.001 || std::abs(speed) > 0.001){
        double error = floor - position;
        double derivative = (error - prevError) / dt;
        prevError = error;

        acceleration = Kp * error + Kd * derivative;
        speed    += acceleration * dt;
        position += speed * dt;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    speed = acceleration = 0.0;
}
};

void FloorRequests(){
    std::uniform_int_distribution<int> Num(0,6);
    std::uniform_int_distribution<int> waitTime(0,10);
    while(true){
        if(waitTime(gen) >= 9){
            {
            std::lock_guard<std::mutex> lock(mtx);
            floorQueue.emplace(Num(gen));
            cv.notify_one();
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Updater(Elevator& Elevator){
    while(true){
        {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "**** UPDATER ****\n";
        std::cout << "Elevator Position: " << Elevator.position << '\n';
        std::cout << "Elevator Target: " << Elevator.position << '\n';
        std::cout << "Elevator Speed: " << Elevator.speed << '\n';
        std::cout << "Elevator Acceleration: " << Elevator.acceleration << '\n';
        std::cout << '\n';
        if(!floorQueue.empty()){
            std::cout << "Queue front: " << floorQueue.front() << '\n';
        }
        else{
            std::cout << "Queue front: empty\n";
        }
        std::cout << '\n';
        }
        std::this_thread::sleep_for(std::chrono::seconds(2)); // normally 3 sec / 5
        std::system("clear");
    }
}

int main(){
    
    Elevator Elevator;
    std::thread Floors(FloorRequests);
    std::thread updaterThread(Updater, std::ref(Elevator));


    // Processing requests from condition variable and sending to elevator logic.
    while(true){
        int targetFloor = 0;
        {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] {return !floorQueue.empty(); });
            targetFloor = floorQueue.front();
            floorQueue.pop();
        }
        Elevator.Engine(targetFloor);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        }


    Floors.join();
    updaterThread.join();

    return 0;
}