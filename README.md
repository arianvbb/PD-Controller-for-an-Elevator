# ☑️ PD Controller Elevator Simulator
This program uses a PD Controller to control the movement of a simulated elevator and there's also multi-threading in the code which allows for elevator requests and constant updates to all happen simultaneously. 

## ❇️Features
- **Multithreading**: Multithreaded application protected with mutex to prevent data races and ensure every thread functions well with shared information. Allows me to execute multiple things at the same time.
- **PD Controller**: A version of the PID Controller that has a gain and derivative to ensure overshoot doesn't stall the program forever.
- **Queue**: I used a queue with the floor request generation integrated with the locks and condition variables to kill work when the queue is empty and the program has reached the floor to optimize CPU usage.

#### This project was made entirely in C++ with these following libraries: iostream, thread, algorithm, cmath, mutex, chrono, cstdlib, condition_variable, queue and random.

## 🤔The Process 

It was one of the first projects back after the exam period which lead me to make a simpler version compared to what I might have been able to do, I plan to add on this later and make it more advanced but it was a fun project which allowed me to use C++ to make something functional and interesting.

## 📚My takeaways

First time getting more deep with Mutex protection, specifically using lock_guard and unique_lock with condition variable. I see quite a lot of usage of this in the future and will include it in other projects.

It was also my first time modifying the PID Controller, which is something I didn't know you could do. Specifically tailoring the components needed for different applications.


## 🚀Running the project 

1. Install the ElevatorSim.cpp file alongside C++ on your code editor.
2. Run your code.

## 🍿Video
