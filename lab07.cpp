#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>

using namespace std;

mutex mtx;

void threadFunction(const string& threadName, int n, double* arr1, double* arr2) {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(1.0, 10.0);

    for (int i = 0; i < n; ++i) {
        this_thread::sleep_for(chrono::milliseconds(10)); // Задержка 10 мс

        mtx.lock();
        cout << threadName << ": ";
        double operand1 = arr1[i];
        double operand2 = arr2[i];

        if (threadName == "thread1") {
            cout << operand1 << " * " << operand2 << " = " << operand1 * operand2 << endl;
        }
        else if (threadName == "thread2") {
            cout << operand1 << " + " << operand2 << " = " << operand1 + operand2 << endl;
        }
        else if (threadName == "thread3") {
            double randomValue = distribution(generator);
            cout << "Random value: " << randomValue << endl;
        }
        mtx.unlock();
    }
}

int main() {
    const int n1 = 20;
    const int n2 = 25;
    const int n3 = 30;

    double operands1[n1];
    double operands2[n1];

    default_random_engine generator;
    uniform_real_distribution<double> distribution(1.0, 10.0);

    for (int i = 0; i < n1; ++i) {
        operands1[i] = distribution(generator);
        operands2[i] = distribution(generator);
    }

    thread t1(threadFunction, "thread1", n1, operands1, operands2);
    thread t2(threadFunction, "thread2", n2, operands1, operands2);
    thread t3(threadFunction, "thread3", n3, operands1, operands2);

    t1.join();
    t2.join();
    t3.join();

    cout << "Main thread has finished execution." << endl;

    return 0;
}
