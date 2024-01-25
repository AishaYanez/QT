#include "boat.h"
#include <iostream>

Boat::Boat(QSemaphore *freePlaces,
           QSemaphore *consoleAvailable)
{
    this->freePlaces = freePlaces;
    this->consoleAvailable = consoleAvailable;
    this->numTrip = 0;
    this->canNum = 0;
    this->misNum = 0;
}

void Boat::crossTheRiver(){
    numTrip++;
    consoleAvailable->acquire();
    std::cout << "Viaje numero " << numTrip << "\n";
    consoleAvailable->release(1);
    misNum = 0;
    canNum = 0;
    freePlaces->release(3);
}

int Boat::getMisNum() const
{
    return misNum;
}

int Boat::getCanNum() const
{
    return canNum;
}

void Boat::plusMisNum()
{
    misNum++;
}

void Boat::plusCanNum()
{
    canNum++;
}
