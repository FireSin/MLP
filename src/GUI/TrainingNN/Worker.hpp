//
// Created by Rogelio Rast on 3/3/23.
//

#ifndef MLP_WORKER_HPP
#define MLP_WORKER_HPP

#include <QObject>
#include <QThread>
#include "../../NeuralNetworkCPP/NeuralNetworkManager.h"

class Worker: public QObject {
Q_OBJECT
private:
    NeuralNetworkManager *network;
    int epochs;
    std::string path;
    QThread* curThread;

public:
    Worker(NeuralNetworkManager *neuralNetwork, int epochs, std::string filepath, QThread* thread);
    ~Worker();

    void run();

signals:
    void accuracyChanged(double accuracy);
    void fileLoaded();

};

#endif //MLP_WORKER_HPP
