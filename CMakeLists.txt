cmake_minimum_required(VERSION 3.22)

project(MLP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/firesin/Qt/6.4.1/gcc_64/lib/cmake")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

add_executable(MLP src/App/main.cpp src/GUI/window.hpp src/GUI/window.cpp src/App/main.hpp src/GUI/paintScene.cpp src/GUI/paintScene.hpp src/GUI/trainPreferensWebWidget.cpp src/GUI/trainPreferensWebWidget.hpp
        src/NeuralNetworkCPP/MatrixNeuralNetwork.cpp src/NeuralNetworkCPP/MatrixNeuralNetwork.h src/NeuralNetworkCPP/DataSet.cpp
        src/NeuralNetworkCPP/DataSet.h src/NeuralNetworkCPP/StopWatch.cpp src/NeuralNetworkCPP/NeuralNetworkBase.h
        src/NeuralNetworkCPP/NeuralNetworkManager.cpp src/NeuralNetworkCPP/NeuralNetworkManager.h src/NeuralNetworkCPP/NeuralNetworkBase.cpp src/GUI/TrainingNN/trainDialog.cpp src/GUI/TrainingNN/trainDialog.hpp src/GUI/TrainingNN/Worker.cpp src/GUI/TrainingNN/Worker.hpp)
target_link_libraries(MLP
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        )

