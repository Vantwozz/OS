#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

int average, minVal, maxVal, n;

DWORD WINAPI Min_Max(LPVOID v)
{
    int *vec = (int *)v;
    long int max = INT32_MIN;
    long int min = INT32_MAX;
    for (int i = 0; i < n; i++)
    {
        if (vec[i] > max)
        {
            max = vec[i];
        }
        Sleep(7);
        if (vec[i] < min)
        {
            min = vec[i];
        }
        Sleep(7);
    }
    minVal = min;
    maxVal = max;
    cout << "Min: " << min << "; Max: " << max << "\n";
    ExitThread(0);
}

DWORD WINAPI Average(LPVOID v)
{
    int *vec = (int *)v;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += vec[i];
        Sleep(12);
    }
    sum /= n;
    average = sum;
    cout << "Average: " << sum << "\n";
    ExitThread(0);
}

int main()
{
    cout << "Input number of elements\n";
    cin >> n;
    int *vec = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter " << i + 1 << " number:\n";
        int n;
        cin >> vec[i];
    }
    cout << "Your array:\n";
    for (int i = 0; i < n; i++)
    {
        cout << vec[i] << " ";
    }
    cout << "\n";
    HANDLE hThreads[2];
    hThreads[0] = CreateThread(NULL, 0, Min_Max, (void *)vec, 0, NULL);
    hThreads[1] = CreateThread(NULL, 0, Average, (void *)vec, 0, NULL);
    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
    for (int i = 0; i < n; i++)
    {
        if (vec[i] == minVal || vec[i] == maxVal)
        {
            vec[i] = average;
        }
    }
    cout << "New array:\n";
    for (int i = 0; i < n; i++)
    {
        cout << vec[i] << " ";
    }
    cout << "\n";
    return 0;
}