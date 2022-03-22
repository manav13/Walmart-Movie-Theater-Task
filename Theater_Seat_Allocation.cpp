#include<bits/stdc++.h>
using namespace std;

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

class Row {
    string id;
    int numOfUnreservedSeats;
    vector<int> seatAllocation;

    public:

    Row () {}

    Row(string ID, int seatsAvailable) {
        id = ID;
        numOfUnreservedSeats = seatsAvailable;
        vector<int> temp(seatsAvailable, 0);
        seatAllocation = temp;
    }

    void reserveSeats(int numOfSeats, string reservationId, map<string, string> &output) {
        if(numOfSeats <= numOfUnreservedSeats) {
            int i=0;
            while(seatAllocation[i] != 0) {
                i++;
            }
            // Buffer of 3 seats - Functionality Incomplete
            // if(i!=0) {
            //     for(int j=0; j<3; j++) {
            //         seatAllocation[j+i] = 1;
            //     }
            //     i+=3;
            //     numOfUnreservedSeats -= 3;
            // }
            string seatNumber = "";
            for(int j=i; j<i+numOfSeats; j++) {
                seatAllocation[j] = 1;
                seatNumber += id + to_string(j+1) + ",";
            }
            output[reservationId] += seatNumber;
            numOfUnreservedSeats -= numOfSeats;
        }
        return;
    }

    int getNumOfUnreservedSeats() {
        return numOfUnreservedSeats;
    }
};

class MovieTheater {

    int totalSeatsAvailable, rows, seatsPerRow;
    vector<Row> theater;

    public:

    MovieTheater(int nrows, int seats) {
        totalSeatsAvailable = nrows * seats;
        rows = nrows;
        seatsPerRow = seats;
        string ch = "A";

        // Adding rows to theater
        for(int i=0; i<rows; i++) {
            theater.push_back(Row(ch, seats));
            ch[0]++;
        }
        return;
    }

    void bookReservation(string reservationId, string numOfSeatsString, map<string, string> &output) {
        if(!is_digits(numOfSeatsString)) {
            output[reservationId] = "Invalid Output";
            return;
        }
        int numOfSeats = stoi(numOfSeatsString);
        if(numOfSeats <= 0) {
            output[reservationId] = "Number of tickets are less than or equal to 0";
            return;
        }
        if(numOfSeats > totalSeatsAvailable) {
            output[reservationId] = "Insufficient tickets";
            return;
        }
        totalSeatsAvailable -= numOfSeats;
        if(numOfSeats <= seatsPerRow) {
            // Check if all the seats can be booked in single row
            for(int i=rows-1; i>=0; i--) {
                if(numOfSeats <= theater[i].getNumOfUnreservedSeats()) {
                    theater[i].reserveSeats(numOfSeats, reservationId, output);
                    return;
                }
            }

            // Split the reservations to different rows
            for(int i=rows-1; i>=0; i--) {
                if(numOfSeats == 0) break;
                if(numOfSeats > theater[i].getNumOfUnreservedSeats()) {
                    numOfSeats -= theater[i].getNumOfUnreservedSeats();
                    theater[i].reserveSeats(theater[i].getNumOfUnreservedSeats(), reservationId, output);
                }
                else {
                    theater[i].reserveSeats(numOfSeats, reservationId, output);
                    numOfSeats = 0;
                }
            }
            return;
        }
        else {
            // Split the reservations to different rows
            for(int i=rows-1; i>=0; i--) {
                if(numOfSeats == 0) break;
                if(numOfSeats > theater[i].getNumOfUnreservedSeats()) {
                    numOfSeats -= theater[i].getNumOfUnreservedSeats();
                    theater[i].reserveSeats(theater[i].getNumOfUnreservedSeats(), reservationId, output);
                }
                else {
                    theater[i].reserveSeats(numOfSeats, reservationId, output);
                    numOfSeats = 0;
                }
            }
            return;
        }
        return;
    }

};

void parseInputFile(string fileName, vector<pair<string, string>> &reservations) {
    ifstream infile(fileName);
    string reservationId;
    string numOfSeats;

    // Hashmap for checking the duplicate reservation ids
    unordered_map<string, int> hash;

    while(infile >> reservationId >> numOfSeats) {
        if(hash.find(reservationId) == hash.end()) {
            reservations.push_back({reservationId, numOfSeats});
            hash[reservationId]++;
        }
        
    }
    infile.close();
    return;
}

void writeOutputFile(map<string, string> output) {
    ofstream outFile("Output.txt");
    for(auto res : output) {
        string st = res.first + " " + res.second + "\n";
        outFile << st;
    }
    outFile.close();
    return;
}

int main() {
    // Default rows and seatPerRows
    int rows=10, seatsPerRow=20;

    // Get number of rows and seats per row
    // cout << "Enter number of rows: ";
    // cin >> rows;
    // cout << "Enter nummber of seats per row: ";
    // cin >> seatsPerRow;

    // Parse reservation input from text file
    vector<pair<string, string>> reservations;
    parseInputFile("InputFile.txt", reservations);

    // Output Variable
    map<string, string> output;
    MovieTheater th(rows, seatsPerRow);

    // Iterating through every reservation
    for(auto res : reservations) {
        th.bookReservation(res.first, res.second, output);
    }

    writeOutputFile(output);
    return 0;
}