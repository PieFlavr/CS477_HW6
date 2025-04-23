/**
 * @file revenue_pc.cpp
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
int get_choice_cache(const int& i, const int& max_days, Action* choice);
int total_max_revenue_pb(const int& i, int values[days][types], const int& max_days, Action* choice);

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
 * @param optimal_value The optimal revenue value as a string.
 * @param category_length The length of the category column for formatting.
 * @param output The output stream to write to (e.g., std::cout or a file stream).
 */
void print_line(const std::string& day, const std::string& optimal_value, const std::string& choice, int category_length, std::ostream& output) {
    output << std::left << std::setw(category_length) << day << " | " 
        << std::left << std::setw(category_length) << optimal_value << " | " 
        << std::left << std::setw(category_length) << choice << " | "
        << std::endl;
}

/**
 * @brief  Checks the choice cache for a given day and calculates the maximum revenue if not already calculated.
 * 
 * @param i  The current day.
 * @param max_days  The maximum number of days to consider.
 * @return int  The maximum revenue for the given day.
 */
int get_choice_cache(const int& i, const int& max_days, Action* choice){
    if (i < 0) {
        return 0;
    } else if (i > max_days){
        return 0;
    } else {
        if(choice[i] == INVALID) { // Check if the choice for the current day is invalid/not calculated
            return total_max_revenue_pb(i, values, max_days, choice); // Call the function to calculate the value and store choice
        } else if (choice[i] == NONE){ // Check if the choice is NONE
            return 0; // Return 0 as no revenue is generated
        } else { // If the choice is valid, return the corresponding value
            // std::cout << "Retrieving cache for day " << i <<  " with choice " << choice[i] <<  " value " << values[i][choice[i]] << std::endl;
            return values[i][choice[i]]; // Return the value for the chosen action
        }
    }
}

/**
 * @brief Calculates the maximum possible revenue using a recursive approach.
 * 
 * @param i The current day.
 * @param values A 2D array containing revenue values for each action on each day (predefined dimensions)
 * @param max_days The maximum number of days to consider.
 * @return int The maximum possible revenue up to the given day.
 */
int total_max_revenue_pb(const int& i, int values[days][types], const int& max_days, Action* choice) {
// Base case: if day is 0, return 0 (no revenue)
int return_value = 0;
if (i < 0) {
    return_value = 0;
} else if (i > max_days) { // Invalid Case: if day is greater than max_days, use maximum possible total return at max_days
    int i_1_revenue = get_choice_cache(i - 1, max_days, choice);
    return_value = i_1_revenue;
} else if (choice[i] != INVALID) { // Check if the choice for the current day is already calculated
    return_value = get_choice_cache(i, max_days, choice) + total_max_revenue_pb(i - 1, values, max_days, choice); // Get cached choice and then recurse

} else {
    // Recursive case: calculate the maximum possible revenue for the current day using the previous two possible days
    int i_1_revenue = get_choice_cache(i - 1, max_days, choice);
    int i_2_revenue = get_choice_cache(i - 2, max_days, choice);

    int repair_revenue = values[i][REPAIR] + i_1_revenue;
    int construct_revenue = values[i][CONSTRUCT] + i_2_revenue;
    int none_revenue = i_1_revenue;


        if (repair_revenue >= construct_revenue && repair_revenue >= none_revenue) {
            choice[i] = REPAIR;
            return_value = repair_revenue;
        } else if (construct_revenue >= repair_revenue && construct_revenue >= none_revenue) {
            if(i - 1 >= 0) {
                choice[i - 1] = NONE; 
            }
            choice[i] = CONSTRUCT;
            return_value = construct_revenue;
        } else {
            choice[i] = NONE;
            return_value = none_revenue;
        }

}
return return_value;
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
    std::string file_name = "revenue_pc_out.txt";
    int category_width = 25;

    // File creation and validation
    std::ofstream output_file(file_name);
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not create or open the file " << file_name << "." << std::endl;
        return 1; // Exit with error code
    }

    total_max_revenue_pb(days-1, values, days, choice); // Pre-calculate everything to avoid printing garbage

    std::cout << "File " << file_name << " created successfully." << std::endl;

    std::ostream& output = output_file; //std::cout Change to output_file if you want to write to file

    print_line("Day", "Optimal Overall Value", "Cached Choice", category_width, output);
    for(int i = 0; i < category_width * 5; ++i) {
        output << "-";
    }
    output << std::endl;

    // The "optimal choice" at each sub-problem is not necessarily the optimal choice for the entire problem
    // If a choice is calculated calculated in the original problem, then it is not necessarily the optimal choice for the particular sub-problem
    // That is to say, this is NOT a GREEDY ALGORITHM, hence why the cached choice for DAY 1 does not match the "pure" recursively calculated choice for DAY 1 in B)
    print_line("0", "0 (base case)", "N/A", category_width, output);
    print_line("1", std::to_string(total_max_revenue_pb(0, values, days, choice)), action_to_string(choice[0]), category_width, output);
    print_line("2", std::to_string(total_max_revenue_pb(1, values, days, choice)), action_to_string(choice[1]), category_width, output);
    print_line("3", std::to_string(total_max_revenue_pb(2, values, days, choice)), action_to_string(choice[2]), category_width, output);
    print_line("4", std::to_string(total_max_revenue_pb(3, values, days, choice)), action_to_string(choice[3]), category_width, output);
    output << "Optimal Total Revenue: " << total_max_revenue_pb(days-1, values, days, choice) << std::endl;

    return 0;
}
#pragma endregion 
