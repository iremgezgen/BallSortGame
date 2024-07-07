// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "BallSort.h"
#include <cassert>

using namespace std;

enum TestColors
{
    Red = 1,
    Green = 2,
    Blue = 3,
    Yellow = 4,
    Purple = 5,
    Black = 6
};

void printSolution(vector<State*> solution)
{
    for (int i = 0; !solution.empty(); solution.pop_back(), i++) {
        cout << "***********************" << endl;
        if (i == 0) {
            cout << "Initial game:" << endl;
        }
        else {
            cout << "Step " << i << ": ";
            Motion m = solution.back()->getMotion();
            cout << "Moved ball from tube " << m.first + 1 << " to tube " << m.second + 1 << endl;
        }

        vector<Tube> tubes = solution.back()->getTubes();
        for (int t = 0; t < tubes.size(); t++) {
            cout << "Tube " << t + 1 << ": ";

            for (int b = 0; b < tubes[t].size(); b++) {
                cout << tubes[t].getBall(b) << "  ";
            }
            cout << endl;
        }
    }
}


BallSort* scenario1() {

    BallSort* retval = new BallSort(5, 3, 3);
    retval->setTube(0, 3, TestColors::Red, TestColors::Green, TestColors::Red);
    retval->setTube(1, 3, TestColors::Red, TestColors::Blue, TestColors::Green);
    retval->setTube(2, 3, TestColors::Green, TestColors::Blue, TestColors::Blue);

    return retval;
}

BallSort* scenario2() {

    BallSort* retval = new BallSort(6, 4, 4);
    retval->setTube(0, 4, TestColors::Red, TestColors::Green, TestColors::Red, TestColors::Yellow);
    retval->setTube(1, 4, TestColors::Red, TestColors::Yellow, TestColors::Blue, TestColors::Green);
    retval->setTube(2, 4, TestColors::Yellow, TestColors::Green, TestColors::Blue, TestColors::Red);
    retval->setTube(3, 4, TestColors::Blue, TestColors::Blue, TestColors::Yellow, TestColors::Green);

    return retval;
}


void runTest1_1(BallSort* test)
{
    assert(test->getState()->getTube(0).getBall(0) == TestColors::Red);
    assert(test->getState()->getTube(0).getBall(1) == TestColors::Green);
    assert(test->getState()->getTube(0).getBall(2) == TestColors::Red);
    assert(test->getState()->getTube(1).getBall(0) == TestColors::Red);
    assert(test->getState()->getTube(1).getBall(1) == TestColors::Blue);
    assert(test->getState()->getTube(1).getBall(2) == TestColors::Green);
    assert(test->getState()->getTube(2).getBall(0) == TestColors::Green);
    assert(test->getState()->getTube(2).getBall(1) == TestColors::Blue);
    assert(test->getState()->getTube(2).getBall(2) == TestColors::Blue);

    cout << "-----------------------------------Passed test 1-1" << endl;
}


void runTest1_2(BallSort* test)
{
    test->getState()->generateMotions();
    assert(test->getState()->isMotionInList(0, 3));
    assert(test->getState()->isMotionInList(1, 3));
    assert(test->getState()->isMotionInList(2, 3));
    assert(!test->getState()->isMotionInList(0, 4));

    cout << "-----------------------------------Passed test 1-2" << endl;
}


void runTest1_3(BallSort* test)
{
    vector<State*> solution = test->solve();
    assert(!solution.empty());

    printSolution(solution);
    cout << "-----------------------------------Passed test 1-3" << endl;
}


void runTest1()
{
    BallSort* test1 = scenario1();
    runTest1_1(test1);
    runTest1_2(test1);
    runTest1_3(test1);

    delete test1;
}


void runTest2_1(BallSort* test)
{
    assert(test->getState()->getTube(0).getBall(0) == TestColors::Red);
    assert(test->getState()->getTube(0).getBall(1) == TestColors::Green);
    assert(test->getState()->getTube(0).getBall(2) == TestColors::Red);
    assert(test->getState()->getTube(0).getBall(3) == TestColors::Yellow);

    assert(test->getState()->getTube(1).getBall(0) == TestColors::Red);
    assert(test->getState()->getTube(1).getBall(1) == TestColors::Yellow);
    assert(test->getState()->getTube(1).getBall(2) == TestColors::Blue);
    assert(test->getState()->getTube(1).getBall(3) == TestColors::Green);

    assert(test->getState()->getTube(2).getBall(0) == TestColors::Yellow);
    assert(test->getState()->getTube(2).getBall(1) == TestColors::Green);
    assert(test->getState()->getTube(2).getBall(2) == TestColors::Blue);
    assert(test->getState()->getTube(2).getBall(3) == TestColors::Red);

    assert(test->getState()->getTube(3).getBall(0) == TestColors::Blue);
    assert(test->getState()->getTube(3).getBall(1) == TestColors::Blue);
    assert(test->getState()->getTube(3).getBall(2) == TestColors::Yellow);
    assert(test->getState()->getTube(3).getBall(3) == TestColors::Green);

    cout << "-----------------------------------Passed test 2-1" << endl;
}


void runTest2_2(BallSort* test)
{
    test->getState()->generateMotions();
    assert(test->getState()->isMotionInList(0, 4));
    assert(test->getState()->isMotionInList(1, 4));
    assert(test->getState()->isMotionInList(2, 4));
    assert(test->getState()->isMotionInList(3, 4));
    assert(!test->getState()->isMotionInList(3, 5));

    cout << "-----------------------------------Passed test 2-2" << endl;
}


void runTest2_3(BallSort* test)
{
    vector<State*> solution = test->solve();
    assert(!solution.empty());

    printSolution(solution);
    cout << "-----------------------------------Passed test 2-3" << endl;
}

void runTest2()
{
    BallSort* test2 = scenario2();
    runTest2_1(test2);
    runTest2_2(test2);
    runTest2_3(test2);

    delete test2;
}


int main()
{
    runTest1();
    runTest2();
}
