#include <QCoreApplication>
#include <QSemaphore>
#include "cannibal.h"
#include "missionary.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    qSetMessagePattern("[%{type}] %{message}");

    int numCannibals = 5;
    int numMissionaries = 41;
    int lastTrip = numMissionaries + numCannibals;

    QSemaphore freePlaces(3);
    QSemaphore consoleAvailable(1);
    QSemaphore usedBoat(1);

    Boat* boat = new Boat(&freePlaces, &consoleAvailable);

    Cannibal* cannibals[numCannibals];
    Missionary* missionaries[numMissionaries];



    for (int i = 0; i < numCannibals; ++i) {
        cannibals[i] = new Cannibal(i, &lastTrip, &freePlaces, &consoleAvailable, &usedBoat, boat, &numMissionaries, &numCannibals);
        cannibals[i]->start();
    }

    for (int i = 0; i < numMissionaries; ++i) {
        missionaries[i] = new Missionary(i, &lastTrip, &freePlaces, &consoleAvailable, &usedBoat, boat, &numMissionaries, &numCannibals);
        missionaries[i]->start();
    }

    for (int i = 0; i < numCannibals; ++i) {
        cannibals[i]->wait();
    }

    for (int i = 0; i < numMissionaries; ++i) {
        missionaries[i]->wait();
    }

    return 0;
}
