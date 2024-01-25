#ifndef CANNIBAL_H
#define CANNIBAL_H

#include "boat.h"
#include <QThread>
#include <QMutex>
#include <QSemaphore>

class Cannibal : public QThread
{
public:
    explicit Cannibal(QObject *parent = nullptr);
    explicit Cannibal(const int cannibalId,
                      int *lastTrip,
                      QSemaphore *freePlaces,
                      QSemaphore *consoleAvailable,
                      QSemaphore *usedBoat,
                      Boat *boat,
                      int *numMissionary,
                      int *numCannibals);

private:
    void cannibalArrive();

    int *numMissionary;
    int *numCannibals;

    int cannibalId;
    int *lastTrip;
    bool upBoat;
    QSemaphore *freePlaces;
    QSemaphore *consoleAvailable;
    QSemaphore *usedBoat;
    Boat *boat;

    // QThread interface
protected:
    void run();
};

#endif // CANNIBAL_H
