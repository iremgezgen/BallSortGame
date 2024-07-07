#pragma once

#include <cstdarg>
#include <vector>
#include "State.h"
#include <set>
#include <string>

class BallSort
{
	int tube_count;
    int tube_capacity;
	int color_count;
    State *initial_state = nullptr;

public:
    BallSort(int tube_count, int tube_capacity, int color_count) : tube_count(tube_count), tube_capacity(tube_capacity), color_count(color_count) 
    {
        initial_state = new State(tube_count, tube_capacity);
    }

    ~BallSort()
    {
        if (!initial_state) {
            delete initial_state;
            initial_state = nullptr;
        }
    }
    
    State* getState()
    {
        return initial_state;
    }

	void setTube(int tube_id, int ball_count, ...) 
    {
        va_list list;

        // Initialize position of va_list 
        va_start(list, ball_count);

        // Iterate through every argument 
        for (int i = 0; i < ball_count; i++) {
            initial_state->addBallToTube(tube_id, static_cast<int>(va_arg(list, int)));
        }

        // Ends the use of va_list 
        va_end(list);
	}


	vector<State*> solve()
    {
        set<string> visitedStates;
        vector<State*> solution;
        if (!initial_state) return vector<State*>();

        State* current = initial_state;
 
        for (current->generateMotions(); !current->isSolved(); current->generateMotions()) {
            // go one level up
            if (current->noMotionLeft()) {
                current = current->getPreviousState();
                if (!current) {
                    return vector<State*>(); // No solution found
                }
                // remove the motion of dead end
                current->removeMotion();
            }
            else {
                State *next = current->generateNextState();
                string code = next->encode();

                if (visitedStates.find(code) != visitedStates.end()) {
                    // remove the motion of dead end
                    // delete next - remove motion deletes next state;
                    current->removeMotion();
                }
                else {
                    visitedStates.insert(code);
                    current = next;
                }
            }
        }

        // return the state path
        while (current) {
            solution.push_back(current);
            current = current->getPreviousState(); 
        }

        return solution;
    }
};

