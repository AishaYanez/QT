#include "cannibal.h"
#include <QDebug>
#include <iostream>

Cannibal::Cannibal(QObject *parent)
    : QThread{parent}
{}

Cannibal::Cannibal(const int cannibalId,
                   int *lastTrip,
                   QSemaphore *freePlaces,
                   QSemaphore *consoleAvailable,
                   QSemaphore *usedBoat,
                   Boat *boat,
                   int *numMissionary,
                   int *numCannibals)
{
    this->cannibalId = cannibalId;
    this->lastTrip = lastTrip;
    this->upBoat = false;
    this->freePlaces = freePlaces;
    this->consoleAvailable = consoleAvailable;
    this->usedBoat = usedBoat;
    this->boat = boat;
    this->numMissionary = numMissionary;
    this->numCannibals = numCannibals;
}

void Cannibal::cannibalArrive(){
    while (!upBoat) {
        usedBoat->acquire();
        if(boat->getMisNum() < 2  || (*numMissionary) == 0){
            freePlaces->acquire();

            boat->plusCanNum();
            (*lastTrip)--;
            (*numCannibals)--;

            consoleAvailable->acquire();
            std::cout << "Canibal3 " << cannibalId + 1 << " se a subido al barco" << "\n";
            consoleAvailable->release(1);

            upBoat = true;

            if (freePlaces->available() == 0
                || (*lastTrip) == 0) {
                boat->crossTheRiver();
            }
        }

        usedBoat->release(1);

        QThread::msleep(10);
    }
}

void Cannibal::run()
{
    cannibalArrive();
}
