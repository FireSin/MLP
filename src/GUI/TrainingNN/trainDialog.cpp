//
// Created by Rogelio Rast on 3/1/23.
//

#include "trainDialog.hpp"
#include <QFile>

trainDialog::~trainDialog() {
    delete series;
    delete chart;
    delete labelFilepath;
    delete chartView;
    delete gridLayout;
}

trainDialog::trainDialog(NeuralNetworkManager* web, std::vector<int>  topology, int epochs, std::string filepathData, QWidget *parent): QDialog(parent){
    network = new NeuralNetworkManager();
    network->LoadMatrixNN(topology);
    this->topology = topology;
    this->epochs = epochs;
    this->filepath = filepathData;
    curEpoch = 0;
    setupUI(this);
}

void trainDialog::setupUI(QWidget* win) {
    this->win = win;
    setWindow();
    setLabels();
    setChart();
    layoutElements();
    setProgress();
}

void trainDialog::setWindow() {
    this->setWindowTitle("Learning");
    gridLayout = new QGridLayout;
    this->setLayout(gridLayout);
}

void trainDialog::setProgress() {
    thread = new QThread(this);
    worker = new Worker(network, epochs, filepath, thread);
    worker->moveToThread(thread);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(this, &trainDialog::startWorker, worker, &Worker::run);
    connect(worker, &Worker::accuracyChanged, this, &trainDialog::onAccuracyChanged);
    connect(worker, &Worker::fileLoaded, this, &trainDialog::onFileLoaded);
    thread->start();
    emit startWorker();
}

void trainDialog::layoutElements() {
    gridLayout->addWidget(labelTopology, 0, 0);
    gridLayout->addWidget(labelFilepath, 1, 0);
    gridLayout->addWidget(chartView, 2, 0, 4, 4);
    this->setFixedSize(this->sizeHint());
}

void trainDialog::setChart() {
    series = new QSplineSeries();
    series->setName("spline");
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 1);
    chart->axes(Qt::Horizontal).first()->setRange(0, epochs);
    chart->axes(Qt::Vertical).first()->setTitleText("Accuracy");
    chart->axes(Qt::Horizontal).first()->setTitleText("Epochs");
    chart->setTitle("Load Training Set...");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 600);

}

void trainDialog::setLabels() {
    std::string tmp = "Epochs: " + std::to_string(epochs);
    tmp = "Tpology: ";
    std::ostringstream stream;
    std::copy(topology.begin(), topology.end() - 1, std::ostream_iterator<int>(stream, ", "));
    stream << topology.back();
    tmp += stream.str();
    labelTopology = new QLabel(QString::fromStdString(tmp));
    tmp = "Filepath of train set: " + filepath;
    labelFilepath = new QLabel(QString::fromStdString(tmp));
}

void trainDialog::onAccuracyChanged(double error) {
    series->append(curEpoch, error);
    ++curEpoch;
    chart->setTitle(QString::fromStdString("Learning... Epoch: " + std::to_string(curEpoch)));
}

void trainDialog::onFileLoaded() {
    chart->setTitle(QString::fromStdString("Learning... Epoch: " + std::to_string(curEpoch)));
}

