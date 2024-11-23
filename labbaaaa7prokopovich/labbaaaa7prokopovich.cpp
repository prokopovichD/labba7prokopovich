#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <deque>
#include <set>

using namespace std;
using namespace chrono;

class LogDuration {
public:
    explicit LogDuration(const string& msg = "") : message(msg + ": "), start(high_resolution_clock::now()) {}
    ~LogDuration() {
        auto finish = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(finish - start);
        cerr << message << duration.count() << " ms" << endl;
    }
private:
    string message;
    high_resolution_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
    LogDuration UNIQ_ID(__LINE__){message};


int main() {
    setlocale(LC_ALL, "ru");
    deque<int> deq;
    {
        LOG_DURATION("Add in deq 100000");
        for (int i = 0; i < 100000; ++i) {
            deq.push_front(rand() % 1000);
        }
    }

    deque<int> deqt;
    set<int> sett;
    cout << "--------------------" << endl;
    {
        LOG_DURATION("Add in deqt 100000");
        for (int i = 0; i < 100000; ++i) {
            deqt.push_front(deq[i]);
        }
        cout << "complexity is O(1)" << endl;
    }

    {
        LOG_DURATION("Search in deqt 100000");
        for (int i = 0; i < 100000; ++i) {
            find(deqt.begin(), deqt.end(), deq[i]);
        }
    }
    cout << "complexity is Sorted:= O(log(n))/ Other:=O(n)" << endl;

    {
        LOG_DURATION("Delete in deqt 100000");
        for (int i = 0; i < 100000; ++i) {
            deqt.pop_back();
        }
        cout << "complexity is O(1)" << endl;
    }

    cout << "--------------------" << endl;
    {
        LOG_DURATION("Add in set 100000");
        for (int i = 0; i < 100000; ++i) {
            sett.insert(rand() % 1000);
        }
        cout << "complexity is O(log(n))" << endl;
    }
    {
        LOG_DURATION("Search in set 100000");
        for (int i = 0; i < 100000; ++i) {
            sett.find(i);
        }
        cout << "complexity is O(log(n))" << endl;
    }
    {
        LOG_DURATION("Delete in set 100000");
        for (int i = 0; i < 100000; ++i) {
            sett.erase(i);
        }
        cout << "complexity is O(log(n))" << endl;
    }
    cout << "Добавление элементов в deq быстрее чем в set" << endl;
    cout << "Поиск элементов в deq медленне чем в set" << endl;
    cout << "Удаление элементов в deq быстрее чем в set" << endl;
    return 0;
}

