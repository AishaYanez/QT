#ifndef MISSIONARY_H
#define MISSIONARY_H

#include "boat.h"
#include <QMutex>
#include <QThread>
#include <QSemaphore>

class Missionary : public QThread
{
public:
    explicit Missionary(QObject *parent = nullptr);
    explicit Missionary(const int missionarylId,
                        int *lastTrip,
                        QSemaphore *freePlaces,
                        QSemaphore *consoleAvailable,
                        QSemaphore *usedBoat,
                        Boat *boat,
                        int *numMissionary,
                        int *numCannibals);

private:
    void missionaryArrive();

    int *numMissionary;
    int *numCannibals;

    int missionaryId;
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

#endif // MISSIONARY_H
