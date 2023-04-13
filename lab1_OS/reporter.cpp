#include "employee.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
    std::ifstream fin(argv[1], std::ios::binary);
    std::ofstream fout(argv[2]);
    int salaryPerHour = atoi(argv[3]);

    fout<<"Result from "<< argv[1]<<"\n";

    int numOfEmployee;
	fin.read((char*)&numOfEmployee, sizeof(int));
    std::cout<<numOfEmployee;
    
    employee person;
    for(int i = 0; i < numOfEmployee; i++){
		fin.read((char *)&person, sizeof(employee));
        fout<<person.ID<<" "<<person.name<<" "<<person.hours<<" "<<person.hours*salaryPerHour<<"\n";
    }

    fin.close();
    fout.close();
}