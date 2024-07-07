#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "tube.h"
#include <string>

using namespace std;

typedef pair<int, int> Motion;



class State {
private:
    int tube_count;
    int tube_capacity;
    vector<Tube>* tubes;
    vector<Motion> valid_motions;
    bool visited = false;

    Motion motion;
    State* previous_state;
    State* next_state;

public:

    ~State()
    {
        if (tubes) {
            tubes->clear();
            delete tubes;
            tubes = nullptr;
        }
        previous_state = nullptr;

        if (next_state) {
            delete next_state;
            next_state = nullptr;
        }
    }

    // Constructor to initialize state with a given number of tubes and capacity for each tube
    State(int tubeCount, int tube_capacity) : tube_count(tubeCount), previous_state(nullptr), tube_capacity(tube_capacity)
    {
        tubes = new vector<Tube>(tubeCount, Tube(tube_capacity));
    }

    void doMotion(Motion motion)
    {
        (*tubes)[motion.second].pushColor((*tubes)[motion.first].popColor());
    }

    Motion getMotion()
    {
        return motion;
    }

    State* getPreviousState()
    {
        return previous_state;
    }

    State(State* previous_state, Motion motion): previous_state(previous_state), motion(motion)
    {
        this->tube_count = previous_state->tube_count;
        tubes = new vector<Tube>();

        for (int i = 0; i < tube_count; i++) {
            tubes->push_back(previous_state->getTube(i));
        }
 
        doMotion(motion);
    }

    string encode()
    {
        string retval;

        for (Tube tube : *tubes) {
            for (int idx = 0; idx < tube.size(); idx++)
                retval += to_string(tube.getBall(idx)) + ',';
            retval += '|';
        }

        return retval;
    }

    void pritoritizeMotions()
    {
        // no priority change can be made with only 1 motion possibility
        if (valid_motions.size() <= 1)
            return;

        for (int idx = 0; idx < valid_motions.size() - 1; idx++) {
            Motion motion = valid_motions[idx];
            if (motion.second == this->getTubeWithMostHeightWithGivenColor(this->getTube(motion.first).topColor())) {
                valid_motions.erase(valid_motions.begin() + idx);
                valid_motions.push_back(motion);
                break;
            }
        }


    }

    State* generateNextState()
    {
        next_state = nullptr;
        if (!valid_motions.empty()) {
            pritoritizeMotions();
            next_state = new State(this, valid_motions.back()); 
        }
        return next_state;
    }

    void removeMotion()
    {
        valid_motions.pop_back();

        if (next_state) {
            delete next_state;
            next_state = nullptr;
        }
    }

    bool noMotionLeft() {
        return valid_motions.empty();
    }

    int getTubeWithMostHeightWithGivenColor(int color)
    {
        int result = -1;
        for (int i = 0; i < tube_count; i++) {
            if ((*tubes)[i].topColor() == color && (*tubes)[i].allSame()) {
                if (result == -1 || (*tubes)[i].size() > (*tubes)[result].size()) {
                    result = i;
                }
            }
        }
        return result;
    }

    int getFirstEmptyTube()
    {
        for (int i = 0; i < tube_count; i++) {
            if ((*tubes)[i].isEmpty()) {
                return i;
            }
        }
        return -1;
    }

    bool canMove(int from, int to) {
        // generic motion controls
        if ((from == to)
            || ((*tubes)[from].isEmpty())
            || ((*tubes)[to].isFull()) 
            || ( !(*tubes)[to].isEmpty() && ((*tubes)[from].topColor() != (*tubes)[to].topColor()) )
           ) 
            return false;

        // optimization controls

        // dont move from the same colored tube to an empty one
        if ((*tubes)[from].allSame() && (*tubes)[to].isEmpty()) return false; 

        // if from all same ise, daha az all same olan bir to ya koyma
        if ((*tubes)[from].allSame() && (*tubes)[to].allSame() && (*tubes)[from].size() > (*tubes)[to].size()) return false;

        // if there is more than one empty tube, choose the first one to avoid multiple moves
        if ((*tubes)[to].isEmpty() && to != getFirstEmptyTube()) return false;

        // if to is one colored (with most balls), then it is the only move
        // if there is a tube with only given color, you cant put it into an empty one
        if ((*tubes)[to].isEmpty() || (*tubes)[to].allSame()) {
            int heighestTubeWithColor = getTubeWithMostHeightWithGivenColor((*tubes)[from].topColor());

            if (heighestTubeWithColor != -1 && to != heighestTubeWithColor) return false;
        }

        // should not take the last motion back
        if ((motion.first == to) && (motion.second == from)) return false;

        // finally
        return true;
    }

    void generateMotions()
    {
        // motions can be generated only once
        if (!visited) {
            visited = true;
            for (int from = 0; from < tube_count; from++) {
                for (int to = 0; to < tube_count; to++) {
                    if (canMove(from, to)) {
                        valid_motions.push_back(make_pair(from, to));
                    }
                }
            }
        }
        
    }
   
    // Function to get the number of tubes
    int getCount() const {
        return tube_count;
    }

    // Function to get a reference to a specific tube by index
    Tube& getTube(int index) {
        if (index >= 0 && index < tube_count) {
            return (*tubes)[index];
        }
        //return &Tube();
        //throw out_of_range("Tube index out of range");
    }

  

    // Function to get the vector of all tubes
    const vector<Tube>& getTubes() const {
        return (*tubes);
    }

    // Function to add a ball to a specific tube by index
    void addBallToTube(int index, int color) {
        getTube(index).pushColor(color);
    }

    // Function to remove a ball from a specific tube by index
    int removeBallFromTube(int index) {
        return getTube(index).popColor();
    }

    // Function to check if all tubes are in a solved state (all balls in each tube are the same)
    bool isSolved() const {
        return all_of(tubes->begin(), tubes->end(), [](const Tube& tube) { return ((tube.allSame() && tube.isFull()) || tube.isEmpty()); });
    }

    // Only for unit testing
    bool isMotionInList(int from, int to)
    {
        for (auto motion : valid_motions) {
            if (motion.first == from && motion.second == to) return true;
        }

        return false;
    }


};
