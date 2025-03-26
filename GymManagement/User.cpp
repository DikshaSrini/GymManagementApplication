#include "User.h"
#include <fstream>
#include <sstream>
#include <conio.h>

std::string getPassword() {
    std::string password;
    char ch;

    while ((ch = _getch()) != '\r') { // Stop when Enter (Carriage Return) is pressed
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*'; // Show * instead of actual characters
        }
    }
    std::cout << std::endl;
    return password;
}

// Define the static member variable
std::string User::loggedInUsername = "";

// User data structure to store user information from CSV
struct UserData {
    std::string username;
    std::string password;
    Role role;
    std::string name;
    int age;
    std::string gender;
    // For members
    double height;
    double weight;
    std::string dietPreference;
    std::string activityLevel;
    // For trainers
    int yearsOfExperience;
};

// Load users from CSV file
std::unordered_map<std::string, UserData> loadUsers() {
    std::unordered_map<std::string, UserData> users;
    std::ifstream file("users.csv");

    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open users.csv" << std::endl;
        return users;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        UserData user;
        std::string roleStr;

        std::getline(ss, user.username, ',');
        std::getline(ss, user.password, ',');
        std::getline(ss, roleStr, ',');

        if (roleStr == "ADMIN") user.role = ADMIN;
        else if (roleStr == "TRAINER") user.role = TRAINER;
        else if (roleStr == "MEMBER") user.role = MEMBER;
        else user.role = NONE;

        std::getline(ss, user.name, ',');
        ss >> user.age;
        ss.ignore();
        std::getline(ss, user.gender, ',');

        if (user.role == MEMBER) {
            ss >> user.height;
            ss.ignore();
            ss >> user.weight;
            ss.ignore();
            std::getline(ss, user.dietPreference, ',');
            std::getline(ss, user.activityLevel, ',');
        }
        else if (user.role == TRAINER) {
            ss >> user.yearsOfExperience;
        }

        users[user.username] = user;
    }

    file.close();
    return users;
}


// Save users to CSV file
void saveUsers(const std::unordered_map<std::string, UserData>& users) {
    std::ofstream file("users.csv");

    // Write header
    file << "username,password,role,name,age,gender,height,weight,dietPreference,activityLevel,yearsOfExperience\n";

    for (const auto& pair : users) {
        const UserData& user = pair.second;
        file << user.username << ","
            << user.password << ",";

        if (user.role == ADMIN) file << "ADMIN,";
        else if (user.role == TRAINER) file << "TRAINER,";
        else if (user.role == MEMBER) file << "MEMBER,";

        file << user.name << ","
            << user.age << ","
            << user.gender << ",";

        if (user.role == MEMBER) {
            file << user.height << ","
                << user.weight << ","
                << user.dietPreference << ","
                << user.activityLevel << ",";
        }
        else if (user.role == TRAINER) {
            file << "0,0,NA,NA," << user.yearsOfExperience << "\n";
        }

        file << "\n";
    }

    file.close();
}

// Function to register a new user
void User::registerUser() {
    auto users = loadUsers();
    UserData newUser;

    std::cout << "=== REGISTRATION ===\n";
    std::cout << "Create Username: ";
    std::cin >> newUser.username;

    // Check if username already exists
    if (users.find(newUser.username) != users.end()) {
        std::cout << "Username already exists! Please try again.\n";
        return;
    }

    std::cout << "Create Password: ";
    newUser.password = getPassword();

    int roleChoice;
    std::cout << "Select Role:\n";
    std::cout << "1. Member\n";
    std::cout << "2. Trainer\n";
    std::cout << "Choice: ";
    std::cin >> roleChoice;

    if (roleChoice == 1) newUser.role = MEMBER;
    else if (roleChoice == 2) newUser.role = TRAINER;
    else {
        std::cout << "Invalid choice! Registration failed.\n";
        return;
    }

    std::cin.ignore(); // Clear input buffer

    std::cout << "Enter Full Name: ";
    std::getline(std::cin, newUser.name);

    std::cout << "Enter Age: ";
    std::cin >> newUser.age;

    std::cin.ignore(); // Clear input buffer

    std::cout << "Enter Gender (Male/Female/Other): ";
    std::getline(std::cin, newUser.gender);

    if (newUser.role == MEMBER) {
        std::cout << "Enter Height (m): ";
        std::cin >> newUser.height;

        std::cout << "Enter Weight (kg): ";
        std::cin >> newUser.weight;

        std::cin.ignore(); // Clear input buffer

        std::cout << "Diet Preference (Vegetarian/Vegan/Non-Vegetarian/Pescetarian/Ketogenic): ";
        std::getline(std::cin, newUser.dietPreference);

        std::cout << "Activity Level (Sedentary/Lightly Active/Moderately Active/Very Active/Super Active): ";
        std::getline(std::cin, newUser.activityLevel);
    }
    else if (newUser.role == TRAINER) {
        std::cout << "Years of Experience: ";
        std::cin >> newUser.yearsOfExperience;
    }

    // Add user to map and save to file
    users[newUser.username] = newUser;
    saveUsers(users);

    std::cout << "Registration successful! Please login.\n\n";
}

Role User::login() {
    std::cout << "\n=== LOGIN ===\n";
    std::string usernameInput, passwordInput;
    std::cout << "Enter Username: ";
    std::cin >> usernameInput;
    std::cout << "Enter Password: ";
    passwordInput = getPassword();

    try {
        auto users = loadUsers();

        std::cout << "Login Successful!\n";
        loggedInUsername = usernameInput;
        return users[usernameInput].role;
    }
    catch (const std::exception& e) {
        std::cerr << "EXCEPTION during login: " << e.what() << std::endl;
        return NONE;
    }
    catch (...) {
        std::cerr << "UNKNOWN EXCEPTION during login" << std::endl;
        return NONE;
    }
}

bool User::verifyCredentials(const std::string& username, const std::string& password) {
    auto users = loadUsers();

    if (users.count(username) && users[username].password == password) {
        loggedInUsername = username;
        return true;
    }

    return false;
}

Role User::getUserRole(const std::string& username) {
    auto users = loadUsers();

    if (users.count(username)) {
        return users[username].role;
    }

    return NONE;
}

std::string User::getUsername() {
    return loggedInUsername;
}