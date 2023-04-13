#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <numeric>
#include <unistd.h>
#include <chrono>

using namespace std;

void min_max(vector<int> vec, promise<int> promiseMin, promise<int> promiseMax)
{
    int max = 0;
    long int min = INT32_MAX;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] > max)
        {
            max = vec[i];
        }
        this_thread::sleep_for(chrono::milliseconds(7));
        if (vec[i] < min)
        {
            min = vec[i];
        }
        this_thread::sleep_for(chrono::milliseconds(7));
    }
    promiseMin.set_value(min);
    promiseMax.set_value(max);
    return;
}

void average(vector<int>::iterator first, vector<int>::iterator last, int n, promise<int> promise)
{
    int sum = accumulate(first, last, 0);
    sum /= n;
    this_thread::sleep_for(chrono::milliseconds(12*n));
    promise.set_value(sum);
    return;
}

int main()
{
    vector<int> vec;
    cout << "Input number of elements\n";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter " << i + 1 << " number:\n";
        int n;
        cin >> n;
        vec.push_back(n);
    }
    cout << "Your array:\n";
    for (int i = 0; i < n; i++)
    {
        cout << vec[i] << " ";
    }
    promise<int> prMin;
    future<int> futMin = prMin.get_future();
    promise<int> prMax;
    future<int> futMax = prMax.get_future();
    promise<int> prAverage;
    future<int> futAverage = prAverage.get_future();
    thread threadAverage(average, vec.begin(), vec.end(), n, move(prAverage));
    thread threadMin_Max(min_max, vec, move(prMin), move(prMax));
    futMin.wait();
    futMax.wait();
    futAverage.wait();
    int average = futAverage.get();
    int min = futMin.get();
    int max = futMax.get();
    threadAverage.join();
    threadMin_Max.join();
    for (int i = 0; i < n; i++)
    {
        if (vec[i] == min || vec[i] == max)
        {
            vec[i] = average;
        }
    }
    cout << "\nNew array:\n";
    for (int i = 0; i < n; i++)
    {
        cout << vec[i] << " ";
    }
    cout<<"\n";
    return 0;
}