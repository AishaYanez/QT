#include "missionary.h"
#include <iostream>

Missionary::Missionary(QObject *parent)
    : QThread{parent}
{}

Missionary::Missionary(const int missionaryId,
                       int *lastTrip,
                       QSemaphore *freePlaces,
                       QSemaphore *consoleAvailable,
                       QSemaphore *usedBoat,
                       Boat *boat,
                       int *numMissionary,
                       int *numCannibals)
{
    this->missionaryId = missionaryId;
    this->lastTrip = lastTrip;
    this->upBoat = false;
    this->freePlaces = freePlaces;
    this->consoleAvailable = consoleAvailable;
    this->usedBoat = usedBoat;
    this->boat = boat;
    this->numMissionary = numMissionary;
    this->numCannibals = numCannibals;
}

void Missionary::missionaryArrive(){
    while (!upBoat) {
        usedBoat->acquire();
        if((*numCannibals) == 0 ||
           (boat->getMisNum() == 0 ||  boat->getCanNum() == 0)){
            freePlaces->acquire();

            boat->plusMisNum();
            (*lastTrip)--;
            (*numMissionary)--;

            consoleAvailable->acquire();
            std::cout << "Misionero " << missionaryId + 1 << " se a subido al barco" << "\n";
            consoleAvailable->release(1);

            upBoat = true;

            if (freePlaces->available() == 0
                || (*lastTrip) == 0) {
                boat->crossTheRiver();
            }
        }
        usedBoat->release(1);
        QThread::msleep(1);
    }
}

void Missionary::run()
{
    missionaryArrive();
}
