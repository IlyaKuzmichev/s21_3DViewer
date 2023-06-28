#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "ObjectParameters.h"

extern "C" {
#include "../backend/3d_viewer.h"
}

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent, object_t& initial_state, object_t& new_state);

signals:
    void workerReady();

private slots:
    void Calculate(ObjectParameters *params, int id, int total);

private:
    object_t& initial_state_;
    object_t& new_state_;
};

#endif // WORKER_H
