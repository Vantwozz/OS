#include "employee.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]){
    int employeeNum = atoi(argv[2]);
    std::ofstream fout(argv[1], std::ios::binary);
    std::vector<employee> list(employeeNum);

    for(int i = 0; i < employeeNum; i++){
        std::cout<<"Enter id of "<<i+1<<" employee:";
        std::cin>>list[i].ID;
        std::cout<<"Enter name of "<<i+1<<" employee:";
        std::cin>>list[i].name;
        std::cout<<"Enter hours for "<<i+1<<" employee:";
        std::cin>>list[i].hours;
    }

	fout.write((char*)&employeeNum, sizeof(int));
	for (int i = 0; i < employeeNum; i++) {
		fout.write((char*)&list[i], sizeof(employee));
	}

    fout.close();
}