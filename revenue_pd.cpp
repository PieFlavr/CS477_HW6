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

#pragma region "Common Initializations"
//=========================================================================
// Common Initializations
//=========================================================================
enum Action { // 0 = REPAIR, 1 = CONSTRUCT, 2 = NONE
    REPAIR,
    CONSTRUCT,
    NONE
};

const int days = 4;
const int types = 3;

// Types enumerated as 3 despite table not giving a third type, as its an easy way to denote "no action". 
// Although, this is more a convention than a modification of the given table (i.e. easier to code/read)
// Row-Col notation, where Row = Day-1 (1-4) and Cols are enumerated as 0-2 (0 = REPAIR, 1 = CONSTRUCT, 2 = NONE)
int array2D[days][types] = { {1000, 500, 0}, 
                                {100, 5000, 0}, 
                                {1000, 500, 0}, 
                                {1000, 100, 0}};

#pragma endregion

int main(){
    std::cout << "Hello World!" << std::endl;
    return 0;
}