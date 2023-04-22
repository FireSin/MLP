//
// Created by Rogelio Rast on 3/3/23.
//

#include "Worker.hpp"


Worker::Worker(NeuralNetworkManager *neuralNetwork, int epochs, std::string filepath, QThread* thread): network(neuralNetwork), epochs(epochs), path(filepath), curThread(thread) {}

Worker::~Worker() {
}

void Worker::run() {
    network->LoadTrainSet(path, 784, 26);
    network->CalculateMetricsForTestSet(network->trainingSet->validationInputs, network->trainingSet->validationTargets);
    emit accuracyChanged(network->getAccuracy());
    emit fileLoaded();
    for (int i = 0; i < epochs; ++i) {
        network->Train(1, 0.8);
        emit accuracyChanged(network->getAccuracy());
    }
}
