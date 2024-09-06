#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

class YearlyRates {
public:
    int year;
    double growthPrice;
    double inflation;
    
    YearlyRates(int y, double g, double i) : year(y), growthPrice(g), inflation(i) {}
};

class TaxCalculator {
private:
    std::vector<YearlyRates> rates;
    
    double roundToTwoDecimals(double value) const {
        return std::round(value * 100.0) / 100.0;
    }

    double getInflationRate(int year) const {
        auto it = std::find_if(rates.begin(), rates.end(),
                               [year](const YearlyRates& r) { return r.year == year; });
        if (it != rates.end()) {
            return it->inflation;
        }
        throw std::runtime_error("No inflation data available for year " + std::to_string(year));
    }

public:
    void loadRatesFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        std::string line;
        // Skip the header
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string yearStr, growthStr, inflationStr;

            if (std::getline(iss, yearStr, '\t') &&
                std::getline(iss, growthStr, '\t') &&
                std::getline(iss, inflationStr)) {
                
                int year = std::stoi(yearStr.substr(0, 4));
                double growth = std::stod(growthStr);
                double inflation = std::stod(inflationStr);

                rates.emplace_back(year, growth, inflation);
            }
        }
        
        std::cout << "Loaded " << rates.size() << " records from file." << std::endl;
    }

    double calculateSellingPrice(int buyYear, int sellYear, double initialPrice) const {
        if (buyYear < 2002 || sellYear > 2030 || buyYear >= sellYear) {
            throw std::invalid_argument("Invalid buy or sell year");
        }

        double price = initialPrice;
        std::cout << "Initial price: " << price << std::endl;
        for (int year = buyYear; year < sellYear; ++year) {
            auto it = std::find_if(rates.begin(), rates.end(),
                                   [year](const YearlyRates& r) { return r.year == year; });
            if (it != rates.end()) {
                price *= (1 + it->growthPrice / 100.0);
                std::cout << "Year " << year << ": Price = " << price << ", Growth = " << it->growthPrice << "%" << std::endl;
            } else {
                std::cout << "No data found for year " << year << std::endl;
            }
        }
        return roundToTwoDecimals(price);
    }

    double calculateLTCG(double buyPrice, double sellPrice, int buyYear, int sellYear) const {
        double indexedCost = buyPrice;
        for (int year = buyYear; year < sellYear; ++year) {
            double inflationRate = getInflationRate(year);
            indexedCost *= (1 + inflationRate / 100.0);
        }
        double profit = sellPrice - indexedCost;
        std::cout << "Buy price: " << buyPrice << ", Indexed cost: " << indexedCost << ", Sell price: " << sellPrice << ", Profit: " << profit << std::endl;
        return profit > 0 ? roundToTwoDecimals(profit * 0.20) : 0.0;
    }
};

int main() {
    TaxCalculator calculator;

    try {
        calculator.loadRatesFromFile("price-inflation.tsv");

        int buyYear, sellYear;
        double initialPrice;

        while (true) {
            std::cout << "Enter the year of purchase (2002-2030): ";
            if (!(std::cin >> buyYear) || buyYear < 2002 || buyYear > 2030) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a year between 2002 and 2030.\n";
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter the year of selling (2002-2030): ";
            if (!(std::cin >> sellYear) || sellYear < 2002 || sellYear > 2030 || sellYear <= buyYear) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a year between " << (buyYear + 1) << " and 2030.\n";
                continue;
            }
            break;
        }

        while (true) {
            std::cout << "Enter the initial price (in lakhs): ";
            if (!(std::cin >> initialPrice) || initialPrice <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a positive number.\n";
                continue;
            }
            break;
        }

        double sellingPrice = calculator.calculateSellingPrice(buyYear, sellYear, initialPrice);
        double ltcg = calculator.calculateLTCG(initialPrice, sellingPrice, buyYear, sellYear);

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Estimated selling price: Rs. " << sellingPrice << " lakhs" << std::endl;
        std::cout << "LTCG (with indexation): Rs. " << ltcg << " lakhs" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
