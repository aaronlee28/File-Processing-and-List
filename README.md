# File-Processing-and-List

The goal of this project is to design a system to keep track of employee data. The system should keep track of an employee’s name, ID, and hourly pay rate in a class called Employee. The data is stored in a file (user selectable) with the id number, hourly pay rate, and the employee’s full name (example): 

17 5.25 John Doe 
18 6.75 Jane Doe

The program will be able to print payroll information as well from data in a different file. The data is the employee’s id number and the number of hours that they worked (example): 

17 40 
18 20 
18 20 

The hours would be summed up based on the employee id. 

The first step of the project is to read in the frist file and store the data as objects in a linked list that were created (not part of the STL). After reading the first file, the second file will then be read, and finally print the payroll information basd on the hourly wage from the frist file multiplied by the number of times an employee worked in the second file.  

The final output is as follow: 

*********Payroll Information********
John Doe, $210
Jane Doe, $270
*********End payroll**************

This project highlights the use of files input and output, reading complex data from a file, linked list, and its implementations. 
