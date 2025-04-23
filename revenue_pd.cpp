/**
 * @file revenue_pd.cpp
 * @author Lucas Pinto
 * @brief Solution to HW6 problems from CS477. 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <string>

#pragma region "Includes"
//==========================================================================
// Includes
//==========================================================================
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#pragma endregion

#pragma region "Common Initializations"
//=========================================================================
// Common Initializations
//=========================================================================
enum Action { // 0 = REPAIR, 1 = CONSTRUCT
    REPAIR,
    CONSTRUCT,
    NONE,
    INVALID
};

// Must properly define these for the code to work properly
// (i.e. if you change the number of days, you must change the values array as well, so on so forth)
const int days = 4;
const int types = 3;

// Types enumerated as 2 since there are only two actions (REPAIR and CONSTRUCT). 
// Row-Col notation, where Row = Day-1 (1-4) and Cols are enumerated as 0-1 (0 = REPAIR, 1 = CONSTRUCT).
int values[days][types] = { {1000, 500}, 
                                {100, 5000}, 
                                {1000, 500}, 
                                {1000, 100}};

Action choice[days] = {INVALID, INVALID, INVALID, INVALID}; // Array to store the choices made for each day (initialized to NONE)
Action choice_cache[days] = {INVALID, INVALID, INVALID, INVALID}; // For sub-problem caching in file output

#pragma endregion

#pragma region "Functions"
//==========================================================================
// Functions
//==========================================================================
std::string action_to_string(int action);
void print_line(const std::string& day, const std::string& optimal_value, const std::string& choice, int category_length, std::ostream& output);

std::string action_to_string(int action) {
    switch (action) {
        case REPAIR: return "REPAIR";
        case CONSTRUCT: return "CONSTRUCT";
        case NONE: return "NONE";
        default: return "N/A";
    }
}


/**
 * @brief Prints a single formatted line for the given day to either console or file.
 * 
 * @param day The current day as a string.
 * @param category_length The length of the category column for formatting.
 * @param output The output stream to write to (e.g., std::cout or a file stream).
 */
void print_line(const std::string& day,  const std::string& choice, int category_length, std::ostream& output) {
    output << std::left << std::setw(category_length) << day << " | " 
        << std::left << std::setw(category_length) << choice << " | "
        << std::endl;
}

void reset_choice_cache(Action* choice) {
    for (int i = 0; i < days; ++i) {
        choice[i] = INVALID; // Reset all choices to INVALID
    }
}

#pragma endregion

#pragma region "Main Program"
//=========================================================================
// Main program
//=========================================================================
int main(){
    std::cout << "Hello World!" << std::endl;
    std::string file_name = "revenue_pd_out.txt";
    int category_width = 25;

    // File creation and validation
    std::ofstream output_file(file_name);
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not create or open the file " << file_name << "." << std::endl;
        return 1; // Exit with error code
    }

    std::cout << "File " << file_name << " created successfully." << std::endl;

    // Input file reading
    std::string input_file_name = "revenue_pc_out.txt";
    std::ifstream input_file(input_file_name);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open the input file " << input_file_name << "." << std::endl;
        return 1; // Exit with error code
    }

    // Read the input file and fill choice array
    int day = 0;
    std::string action_str;
    while (std::getline(input_file, action_str)) {
        if (action_str.find("REPAIR") != std::string::npos) {
            choice[day] = REPAIR;
        } else if (action_str.find("CONSTRUCT") != std::string::npos) {
            choice[day] = CONSTRUCT;
        } else if (action_str.find("NONE") != std::string::npos) {
            choice[day] = NONE;
        } else {
            choice[day] = INVALID;
        }
        if (choice[day] != INVALID) {
            ++day;
        }
    }

    input_file.close();

    std::ostream& output = output_file; //std::cout Change to output_file if you want to write to file
    
    print_line("Day",  "Choice", category_width, output);
    for(int i = 0; i < category_width * 3; ++i) {
        output << "-";
    }
    output << std::endl;

    for(int i = 0; i < days; ++i) { // Iterate through the days and prinoutt the choices made
        print_line(std::to_string(i), action_to_string(choice[i]), category_width, output);
    }
    
    int total_revenue = 0;
    for(int i = 0; i < days; ++i) { // Calculate the total revenue based on the choices made
        if (choice[i] == REPAIR) {
            total_revenue += values[i][REPAIR];
        } else if (choice[i] == CONSTRUCT) {
            total_revenue += values[i][CONSTRUCT];
        }
    }
    output << "Optimal Total Revenue: " <<  total_revenue << std::endl;

    return 0;
}
#pragma endregion 
