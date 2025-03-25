/// cpp
// IT-499 Code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// William Colon
// william.colon@snhu.edu
// CS-499
// Version 2.1  205/3/19


#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>
#include <fstream>
#include <sstream>

// Struct to represent an Appointment with relevant details
struct Appointment {
    std::string name;        
    std::string date;        
    std::string time;        
    std::string description; 
};

// The AppointmentService class manages a collection of appointments
class AppointmentService {
private:
    std::vector<Appointment> appointments; 
    const std::string filename = "appointment.csv"; 

    // Function to validate date input
    bool validateDate(const std::string& date) {
        return std::regex_match(date, std::regex(R"(\d{4}-\d{2}-\d{2})")); 
    }

    // Function to validate time input
    bool validateTime(const std::string& time) {
        return std::regex_match(time, std::regex(R"(\d{2}:\d{2})")); 
    }
    // Function to save appointments to CSV file
    void saveToCSV() {
        std::ofstream file(filename, std::ios::app); // Opens file in append mode
        for (const auto& appointment : appointments) {
            // Writes each appointment's details as a comma-separated line in the CSV file
            file << appointment.name << "," << appointment.date << "," << appointment.time << "," << appointment.description << "\n";
        }
    }

    // Function to load appointments from CSV file
    void loadFromCSV() {
        std::ifstream file(filename); /g
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream s(line);
            Appointment appointment;
            std::string field;

            std::getline(s, appointment.name, ','); 
            std::getline(s, appointment.date, ','); 
            std::getline(s, appointment.time, ','); 
            std::getline(s, appointment.description, ','); 

            appointments.push_back(appointment); 
        }
    }

public:
    AppointmentService() {
        loadFromCSV(); 
    }
    

    // Function to add a new appointment
    void addAppointment() {
        Appointment appointment; 

        std::cout << "Enter name: ";
        std::getline(std::cin, appointment.name); 

        
        std::string date;
        while (true) {
            std::cout << "Enter date (YYYY-MM-DD): ";
            std::getline(std::cin, date); 
            if (validateDate(date)) {
                appointment.date = date; 
                break; 
            }
            std::cout << "Invalid date format. Please try again.\n"; 
        }

        // Input validation for the appointment time
        std::string time;
        while (true) {
            std::cout << "Enter time (HH:MM): ";
            std::getline(std::cin, time); 
            if (validateTime(time)) {
                appointment.time = time; 
                break; 
            }
            std::cout << "Invalid time format. Please try again.\n"; 
        }

        std::cout << "Enter description: ";
        std::getline(std::cin, appointment.description); 

        appointments.push_back(appointment); 
        std::cout << "Appointment added successfully!\n"; 
    }

    // Function to display all scheduled appointments
    void displayAppointments() const {
        if (appointments.empty()) {
            std::cout << "No appointments scheduled.\n"; 
            return;
        }
        std::cout << "Scheduled Appointments:\n";
        for (const auto& appointment : appointments) {
            // Displays each appointment's details
            std::cout << "Name: " << appointment.name
                << ", Date: " << appointment.date
                << ", Time: " << appointment.time
                << ", Description: " << appointment.description << "\n";
        }
    }

    // Function to clear all appointments
    void clearAppointments() {
        appointments.clear(); 
        std::ofstream file(filename, std::ios::trunc); 
        std::cout << "All appointments cleared.\n"; 
    }

    // Function to delete a specific appointment by name
    void deleteAppointment() {
        std::string name;
        std::cout << "Enter the name of the appointment you wish to delete: ";
        std::getline(std::cin, name); // Reads the name of the appointment to delete

        // Removes the appointment from the vector based on the name
        auto it = std::remove_if(appointments.begin(), appointments.end(),
            [&name](const Appointment& app) { return app.name == name; });

        if (it != appointments.end()) {
            appointments.erase(it, appointments.end()); 
            std::ofstream file(filename, std::ios::trunc); 
                       std::cout << "Appointment deleted successfully.\n"; 
        }
        else {
            std::cout << "No appointment found for the name: " << name << "\n"; 
        }
    }
};

int main() {
    std::cout << "William Colon Scheduler\n"; 
    AppointmentService service; 
    int choice;
    do {
        // Display menu options for the user
        std::cout << "1. Add Appointment\n2. Display Appointments\n3. Clear Appointments\n4. Delete Appointment\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice; 
        std::cin.ignore(); 

        switch (choice) {
        case 1:
            service.addAppointment(); 
            break;
        case 2:
            service.displayAppointments(); 
            break;
        case 3:
            service.clearAppointments(); 
            break;
        case 4:
            service.deleteAppointment(); 
            break;
        case 5:
            std::cout << "Exiting the appointment service.\n"; 
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n"; 
    } while (choice != 5); 

    return 0; n
}

