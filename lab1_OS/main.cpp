#include "employee.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <tlhelp32.h>
#include <stdbool.h>
#include <process.h>
#include <string>

bool isProcessRun(LPTSTR processName)
{
    HANDLE hSnap = NULL;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap!=NULL)
    {
        if (Process32First(hSnap, &pe32))
        {
            if (lstrcmp(pe32.szExeFile, processName) == 0)
                return TRUE;
            while (Process32Next(hSnap, &pe32))
                if (lstrcmp(pe32.szExeFile, processName) == 0)
                    return TRUE;
        }
    }
    CloseHandle(hSnap);
    return FALSE;
}

int main(){
    char arg[1000];
    std::string binaryFileName, outputFileName;
    int numOfEmployee, salaryPerHour;

    std::cout<<"Enter name of binary file:\n";
    std::cin>>binaryFileName;

    std::cout<<"Enter number of employees:\n";
    std::cin>>numOfEmployee;

    sprintf(arg, "%s %s %d", "start creator.exe", binaryFileName.c_str(), numOfEmployee);
    system(arg);
    while(isProcessRun(TEXT("creator.exe")));

    std::cout<<"Binary file:\n";
    std::ifstream fin(binaryFileName, std::ios::binary);

	fin.read((char*)&numOfEmployee, sizeof(int));
    employee person;

    for(int i = 0; i < numOfEmployee; i++){
		fin.read((char *)&person, sizeof(employee));
        std::cout<<person.ID<<" "<<person.name<<" "<<person.hours<<"\n";
    }
    fin.close();

    std::cout<<"Enter name of output file:\n";
    std::cin >> outputFileName;

    std::cout<<"Enter salary per hour:\n";
    std::cin>>salaryPerHour;

    sprintf(arg, "%s %s %s %d", "reporter.exe", binaryFileName.c_str(), outputFileName.c_str(), salaryPerHour);
    system(arg);
    while(isProcessRun(TEXT("reporter.exe")));

    std::ifstream finReport(outputFileName);
    std::string line;
    for(int i = 0; i<=numOfEmployee; i++)
    {
      std::getline(finReport,line);
      std::cout<<line<<"\n";
    }
    finReport.close();
}