# Walmart-Movie-Theater-Challenge
Algorithm to implement seating arrangement in a movie theatre to maximize both customer satisfaction and theater utilization.

## Summary: 

This algorithm arranges the seats for the customer such that the customer sattisfaction is received by allocating majority seats of the reservation together and maximising theater utilisation taking Covid situation in consideration. 

## Description:

Given a theatre with seating capacity of 20 seats in each of the 10 rows (200 seats), the algorithm needs to assign seats to the customers to maximize theatre utilization and gurantees customer sattisfaction.

## Input: 

An input file which would contain one line of input for each reservation request. The order of the lines in the file reflects the order in which the reservation requests were received. Each line in the file will be comprised of a reservation identifier, followed by a space, and then the number of seats requested. The reservation identifier will have the format: R####.

### Sample Input Example: 
R001 2 
R002 4 
R003 4 
R004 3

## Output:

The output should be a file containing the seating assignments for each request. Each row in the file should include the reservation number followed by a space, and then a comma-delimited list of the assigned seats.

### Sample Output Example: 
R001 I1,I2
R002 F16,F17,F18,F19 
R003 A1,A2,A3,A4 
R004 J4,J5,J6

## Assumptions
- Row A is closest to Screen and later alphabets are farther away from screen.
- Cost of all seats are same.
- Seats will be reserved on FCFS basis.
- First comer gets better seat than a person who reserves seat later. i.e. seats will be filled starting from last rows that is row J in this case.
- The system will try to allocate seats with entire reservation in single row if possible.
- Once it is not possible to allocate seats in single row, the system will book the remaining seats in different rows.
- If two reservationIds are same, then the earlier one will be considered and the rest will be ignored.

## Future Work/Improvements
- Increase customer satisfaction by allocating seats starting from center of the row.
- Covid condition? (Maybe allocate seats in alternating fashion)
- Cancel Tickets functionality

## Code Discussion/Approach:
- There are mainly two classes - Row and MovieTheater
- Row represents one single row in a movie theater and stores info like rowId, numberOfUnreservedSeats, seatAllocation, etc.
- MovieTheater represents an array of rows and has methods like bookReservation which helps to allocate the seats according to the reservation.
- The method uses Greedy approach, wherein it first tries to fit entire reservation in single row if possible.
- If not possible, then allocates the best seats in different rows.

## Steps to Compile and Run:
- Requirements: g++ compiler to compile C++ code.
- Open terminal, navigate to folder where Theater_Seat_Allocation.cpp is stored. Put InputFile_1.txt in same folder at same level.
- Compile code using command: g++ Theater_Seat_Allocation.cpp -o Theater_Seat_Allocation
- Execute using command: ./Theater_Seat_Allocation
- Enter number of rows and number of seats per row. After that, the Output.txt file will be generated in the current working directory.