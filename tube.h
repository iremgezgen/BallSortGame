#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Tube {
private:
    vector<int> balls;
    int capacity;

public:
    // Constructor to initialize the tube with a given capacity
    Tube(int cap) : capacity(cap) {}
    Tube() : capacity(0) {}
    

    Tube(const Tube& t)
    {
        this->capacity = t.capacity;
        for (int b = 0; b < t.balls.size(); b++) {
            this->balls.push_back(t.balls[b]);
        }
    }

    // Function to check if the tube is full
    bool isFull() const 
    {
        return balls.size() == capacity;
    }

    // Function to return the last integer (top color)
    int topColor() const 
    {
        if (!balls.empty()) {
            return balls.back();
        }
        //throw out_of_range("Tube is empty");
        return -1;
    }

    // Function to check if all integers are equal
    bool allSame() const 
    {
        if (balls.empty()) {
            return false; // Consider an empty tube as not all same
        }
        return all_of(balls.begin(), balls.end(), [this](int val) { return val == balls[0]; });
    }

    // Function to pop the last integer
    int popColor() 
    {
        if (!balls.empty()) {
            int top = balls.back();
            balls.pop_back();
            return top;
        }
        //throw out_of_range("Tube is empty");
        return -1;
    }

    // Function to add an integer
    void pushColor(int color) 
    {
        if (!isFull()) {
            balls.push_back(color);
        }
        else {
            //throw overflow_error("Tube is full");
        }
    }

    // Function to get the current size of balls
    int size() const 
    {
        return (int) balls.size();
    }

    // Function to get the capacity of the tube
    int getCapacity() const 
    {
        return capacity;
    }

    // Function to check if the tube is empty
    bool isEmpty() const 
    {
        return balls.empty();
    }

    // -1: out of range, 0: no ball
    int getBall(int idx)
    {
        if (idx >= capacity) {
            return -1;
        }
        if (idx >= balls.size()) {
            return 0;
        }
        return balls[idx];
    }
};


