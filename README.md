# LTCG Calculator

This program calculates Long-term Capital Gains Tax (LTCG) for real estate investments in India using both the traditional and new taxation schemes.

## Building the Program

To build the program, make sure you have `g++` and `make` installed on your system. Then follow these steps:

1. Open a terminal in the directory containing the source code and Makefile.
2. Run the following command to build both debug and release versions:

   ```
   make
   ```

This will create two executables:
- `ltcg_calculator_debug`: Debug version
- `ltcg_calculator_release`: Optimized release version

## Running the Program

1. Ensure that the `price-inflatoin.tsv` file is in the same directory as the executable.
2. Run the program using one of the following commands:
   - For debug version: `./ltcg_calculator_debug`
   - For release version: `./ltcg_calculator_release`
3. Follow the prompts to enter the year of purchase, year of selling, and initial price.

## Input Format

- Year of purchase: Enter a year between 2010 and 2030.
- Year of selling: Enter a year between 2010 and 2030, must be after the year of purchase.
- Initial price: Enter the price in lakhs (e.g., 50 for 50 lakhs).

## Data File Format

The program reads data from a file named `price-inflation.tsv`. This file should be a tab-separated values (TSV) file with the following columns:
1. Year (in YYYY-MM-DD format)
2. Growth-Price (as a percentage)
3. Inflation (as a percentage)

Ensure that the TSV file includes data for all years from 2001 to 2030.

## Output

The program will display:
- Estimated selling price
- LTCG under the old taxation scheme
- LTCG under the new taxation scheme
- The difference between the two schemes
- Which scheme leads to higher taxes

## Note on External Code

No external code was used in this implementation. All code was written specifically for this assignment.