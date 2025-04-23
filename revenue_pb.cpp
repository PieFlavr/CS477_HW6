/**
 * @file revenue_pb.cpp
 * @author Lucas Pinto
 * @brief Solution to HW6 problems from CS477. 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

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
    NONE
};

// Must properly define these for the code to work properly
// (i.e. if you change the number of days, you must change the values array as well, so on so forth)
const int days = 4;
const int types = 2;

// Types enumerated as 2 since there are only two actions (REPAIR and CONSTRUCT). 
// Row-Col notation, where Row = Day-1 (1-4) and Cols are enumerated as 0-1 (0 = REPAIR, 1 = CONSTRUCT).
int values[days][types] = { {1000, 500}, 
                                {100, 5000}, 
                                {1000, 500}, 
                                {1000, 100}};

#pragma endregion

#pragma region "Functions"
//==========================================================================
// Functions
//==========================================================================
/**
 * @brief Prints a single formatted line for the given day to either console or file.
 * 
 * @param day The current day as a string.
 * @param optimal_value The optimal revenue value as a string.
 * @param category_length The length of the category column for formatting.
 * @param output The output stream to write to (e.g., std::cout or a file stream).
 */
void print_line(const std::string& day, const std::string& optimal_value, int category_length, std::ostream& output) {
    output << std::left << std::setw(category_length) << day << " | " 
           << std::left << std::setw(category_length) << optimal_value << " | " 
           << std::endl;
}

/**
 * @brief Calculates the maximum possible revenue using a recursive approach.
 * 
 * @param i The current day.
 * @param values A 2D array containing revenue values for each action on each day (predefined dimensions)
 * @param max_days The maximum number of days to consider.
 * @return int The maximum possible revenue up to the given day.
 */
int total_max_revenue_pb(const int& i, int values[days][types], const int& max_days){
    // Base case: if day is 0, return 0 (no revenue)
    int return_value = 0;
    if (i < 0) {
        return_value = 0;
    } else if (i > max_days){ // Invalid Case: if day is greater than max_days, use maximm possible total return at max_days
        return_value = total_max_revenue_pb(i - 1, values, max_days);
    } else {
        // Recursive case: calculate the maximum possible revenue for the current day using the previous two possible days
        return_value =  std::max<int>(
            values[i][REPAIR] + total_max_revenue_pb(i - 1, values, max_days), // Repair, r_i + T_(i-1)
            std::max<int>(
                values[i][CONSTRUCT] + total_max_revenue_pb(i - 2, values, max_days), // Construct, c_i + T_(i-2)
                total_max_revenue_pb(i - 1, values, max_days) // None, T_(i-1)
            )
        );
    }
    return return_value;
}

#pragma endregion

#pragma region "Main Program"
//=========================================================================
// Main program
//=========================================================================
int main(){
    std::cout << "Hello World!" << std::endl;
    std::string file_name = "revenue_pb_out.txt";
    int category_width = 25;

    // File creation and validation
    std::ofstream output_file(file_name);
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not create or open the file " << file_name << "." << std::endl;
        return 1; // Exit with error code
    }
    std::cout << "File " << file_name << " created successfully." << std::endl;

    std::ostream& output = output_file; //std::cout Change to output_file if you want to write to file

    print_line("Day", "Optimal Sub-Value (up-to-day)", category_width, output);
    for(int i = 0; i < category_width * 3; ++i) {
        output << "-";
    }
    output << std::endl;
    print_line("0", "0 (base case)", category_width, output);
    print_line("1", std::to_string(total_max_revenue_pb(0, values, days)) + " (ends up unused)", category_width, output);
    print_line("2", std::to_string(total_max_revenue_pb(1, values, days)), category_width, output);
    print_line("3", std::to_string(total_max_revenue_pb(2, values, days)), category_width, output);
    print_line("4", std::to_string(total_max_revenue_pb(3, values, days)), category_width, output);

    output << "Optimal Total Revenue: " << total_max_revenue_pb(days-1, values, days) << std::endl;

    return 0;
}
#pragma endregion
