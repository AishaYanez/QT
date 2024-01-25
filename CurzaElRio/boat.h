#ifndef BOAT_H
#define BOAT_H

#include <QThread>
#include <QMutex>
#include <QSemaphore>

class Boat {
public:
    Boat(QSemaphore *freePlaces,
         QSemaphore *consoleAvailable);

public:
    void crossTheRiver();
    void plusMisNum();
    void plusCanNum();

    int getMisNum() const;
    int getCanNum() const;

private:
    QSemaphore *freePlaces;
    QSemaphore *consoleAvailable;
    int numTrip;
    int misNum;
    int canNum;
};

#endif // BOAT_H
