#include "S_Win.h"
#include "EstimateLengthManager.h"
#include "SettingsManagerA.h"
#include "CommonTypes.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>


int S_Win::windowCount = 0; 
void S_Win::resetWindowCount() { windowCount = 0;}
S_Win::S_Win() {
    height = 0.0;
    width = 0.0;
    collarType = 0;
    inputInInches = false;
    ++windowCount;
}


// Returns true if data entered successfully, false if cancelled
bool S_Win::inputWindowData(bool isEditing) {
    if (!isEditing) {  
        label = "S_Win #" + std::to_string(windowCount) + " -> ";
    } else {
        std::cout << "\n--- Editing " << label << " ---\n";
    }

    
    while (true) {
        std::cout << "Enter size in (i)nches or (f)eet? [i/f] (0 = cancel): ";
        if (std::cin >> unitChoice) {
            if (unitChoice == '0') {
                std::cout << "⚠ Entry cancelled!\n";
                return false; // cancelled
            }
            if (unitChoice == 'i' || unitChoice == 'I' || unitChoice == 'f' || unitChoice == 'F') {
                inputInInches = (unitChoice == 'i' || unitChoice == 'I');
                break;
            }
        }
        std::cout << "❌ Invalid input! Please enter 'i' or 'f'.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Collar type
    while (true) {
        std::cout << "Enter Collar Type (1 - 14, 0 = cancel): ";
        if (std::cin >> collarType) {
            if (collarType == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (collarType >= 1 && collarType <= 14) break;
        }
        std::cout << "❌ Please enter a number between 1 and 14.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Height
    while (true) {
        std::cout << "Enter Height (0 = cancel): ";
        if (std::cin >> height) {
            if (height == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (height > 0) break;
        }
        std::cout << "❌ Height must be a positive number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Width
    while (true) {
        std::cout << "Enter Width (0 = cancel): ";
        if (std::cin >> width) {
            if (width == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (width > 0) break;
        }
        std::cout << "❌ Width must be a positive number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (inputInInches) {
        height /= 12.0;
        width  /= 12.0;
    }
    return true;
}



void S_Win::calculateSections() {
    sectionMap.clear();

    double h = height;
    double w = width;
    SettingsManagerA& settings = SettingsManagerA::getInstance();

    auto labelWith = [&](const std::string& prefix, double value) {
        return std::make_pair(label + prefix, value);
    };

    auto addSection = [&](const std::string& key, const std::vector<std::pair<std::string, double>>& values) {
        std::vector<std::pair<double, std::string>> converted;
        for (const auto& [label, val] : values) {
            converted.emplace_back(val, label);
        }
        sectionMap[settings.getSectionName(key)] = converted;
    };

    switch (collarType) {
        case 1:
            addSection("DC30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25), labelWith("WT", w + 0.25) });
            addSection("DC26F", { labelWith("WB", w + 0.25) });
            break;
        case 2:
            addSection("DC30C", { labelWith("HL", h), labelWith("HR", h), labelWith("WT", w) });
            addSection("DC26C", { labelWith("WB", w) });
            break;
        case 3:
            addSection("DC30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25) });
            addSection("DC30C", { labelWith("WT", w) });
            addSection("DC26F", { labelWith("WB", w + 0.25) });
            break;
        case 4:
            addSection("DC30F", { labelWith("HL", h + 0.25), labelWith("WT", w + 0.25) });
            addSection("DC30C", { labelWith("HR", h) });
            addSection("DC26F", { labelWith("WB", w + 0.25) }); 
            break;
        case 5:
            addSection("DC30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25), labelWith("WT", w + 0.25) });
            addSection("DC26C", { labelWith("WB", w) });
            break;
        case 6:
            addSection("DC30C", { labelWith("HL", h) });
            addSection("DC30F", { labelWith("HR", h + 0.25), labelWith("WT", w + 0.25) });
            addSection("DC26F", { labelWith("WB", w + 0.25) });
            break;
        case 7:
            addSection("DC30C", { labelWith("HL", h), labelWith("WT", w) });
            addSection("DC30F", { labelWith("HR", h + 0.25) });
            addSection("DC26F", { labelWith("WB", w + 0.25) });
            break;
        case 8:
            addSection("DC30C", { labelWith("HR", h) });
            addSection("DC30F", { labelWith("HL", h + 0.25), labelWith("WT", w + 0.25) });
            addSection("DC26C", { labelWith("WB", w) });
            break;
        case 9:
            addSection("DC30C", { labelWith("WT", w) });
            addSection("DC30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25) });
            addSection("DC26C", { labelWith("WB", w) });
            break;
        case 10:
            addSection("DC30C", { labelWith("HL", h), labelWith("HR", h) });
            addSection("DC30F", { labelWith("WT", w + 0.25) });
            addSection("DC26F", { labelWith("WB", w + 0.25) });
            break;
        case 11:
            addSection("DC30C", { labelWith("HL", h), labelWith("HR", h) });
            addSection("DC30F", { labelWith("WT", w + 0.25) });
            addSection("DC26C", { labelWith("WB", w) });
            break;
        case 12:
            addSection("DC30C", { labelWith("HL", h), labelWith("WT", w) });
            addSection("DC30F", { labelWith("HR", h + 0.25) });
            addSection("DC26C", { labelWith("WB", w) });
            break;
        case 13:
            addSection("DC30C", { labelWith("HL", h), labelWith("HR", h), labelWith("WT", w) });
            addSection("DC26F", { labelWith("WB", w + 0.25) });
            break;
        case 14:
            addSection("DC30C", { labelWith("HR", h), labelWith("WT", w) });
            addSection("DC30F", { labelWith("HL", h + 0.25) });
            addSection("DC26C", { labelWith("WB", w) });
            break;
    }

    // Inner Sections
    addSection("M23", { labelWith("H", h), labelWith("H", h) });
    addSection("M28", { labelWith("H", h), labelWith("H", h) });
    addSection("M24", {
        labelWith("W1", w / 2), labelWith("W2", w / 2),
        labelWith("W3", w / 2), labelWith("W4", w / 2)
    });
    addSection("D29", {
        labelWith("HL", h), labelWith("HR", h),
        labelWith("WT", w / 2), labelWith("WB", w / 2)
    });
}

double S_Win::getAreaSqFt() const {
    return height * width;
}

std::string S_Win::getLabel() const {
    return label;
}

const SectionMap& S_Win::getSectionMap() const {
    return sectionMap;
}


void S_Win::sendToEstimator(EstimateLengthManager& estimator) {
    estimator.addWindowSections(label, sectionMap);
}


char S_Win::getSize() const { return unitChoice; }
double S_Win::getHeight() const { if (inputInInches) {return height * 12.0;} return height;}
double S_Win::getWidth() const {if (inputInInches){return width * 12.0;} return width;}
int S_Win::getCollarType() const { return collarType; }


void S_Win::sendToEstimator() {
    std::cout << "[S_Win] Warning: No estimator provided in sendToEstimator().\n";
}
