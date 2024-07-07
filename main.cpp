// zort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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


// unit test for initialization
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

    cout << "Ballzy test 1_1" << endl;
}


void runTest1_2(BallSort* test)
{
    test->getState()->generateMotions();
    assert(test->getState()->isMotionInList(0, 3));
    assert(test->getState()->isMotionInList(1, 3));
    assert(test->getState()->isMotionInList(2, 3));
    assert(!test->getState()->isMotionInList(0, 4));

    cout << "Ballzy test 1_2" << endl;
}


// unit test for god knows what
void runTest1_3(BallSort* test)
{
    vector<State*> solution = test->solve();
    assert(!solution.empty());

    printSolution(solution);
    cout << "Ballzy test 1_3" << endl;
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
}


void runTest2_2(BallSort* test)
{

}


void runTest2_3(BallSort* test)
{
    vector<State*> solution = test->solve();
    assert(!solution.empty());

    printSolution(solution);
    cout << "Ballzy test 2_3" << endl;
}

void runTest2()
{
    BallSort* test2 = scenario2();
    runTest2_1(test2);
    runTest2_2(test2);
    runTest2_3(test2);

    delete test2;
}



void runTestRun()
{
//    runTest1();
    runTest2();

}


int main()
{
    cout << "help!\n";
    runTestRun();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
