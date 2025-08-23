#include "F_Win.h"
#include "EstimateLengthManager.h"
#include "SettingsManagerA.h"
#include "CommonTypes.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>


int F_Win::windowCount = 0; 
void F_Win::resetWindowCount() { windowCount = 0;}
F_Win::F_Win() {
    height = 0.0;
    width = 0.0;
    collarType = 0;
    inputInInches = false;
    ++windowCount;
}

// Returns true if data entered successfully, false if cancelled
bool F_Win::inputWindowData(bool isEditing) {
    if (!isEditing) {
        
        label = "F_Win #" + std::to_string(windowCount) + " -> ";
    } else {
        std::cout << "\n--- Editing " << label << " ---\n";
    }

    // Unit choice
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



void F_Win::calculateSections() {
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
            addSection("D54F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25), labelWith("WT", w + 0.25), labelWith("WB", w + 0.25) });
            break;
        case 2:
            addSection("D54A", { labelWith("HL", h), labelWith("HR", h), labelWith("WT", w), labelWith("WB", w) });
            break;
        case 3:
            addSection("D54F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25), labelWith("WB", w + 0.25) });
            addSection("D54A", { labelWith("WT", w) });
            break;
        case 4:
            addSection("D54F", { labelWith("HL", h + 0.25), labelWith("WT", w + 0.25), labelWith("WB", w + 0.25) });
            addSection("D54A", { labelWith("HR", h) });
            break;
        case 5:
            addSection("D54F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25), labelWith("WT", w + 0.25) });
            addSection("D54A", { labelWith("WB", w) });
            break;
        case 6:
            addSection("D54F", { labelWith("HR", h + 0.25), labelWith("WT", w + 0.25), labelWith("WB", w + 0.25) });
            addSection("D54A", { labelWith("HL", h) });
            break;
        case 7:
            addSection("D54F", { labelWith("HR", h + 0.25), labelWith("WB", w + 0.25) });
            addSection("D54A", { labelWith("HL", h), labelWith("WT", w) });
            break;
        case 8:
            addSection("D54F", { labelWith("HL", h + 0.25), labelWith("WT", w + 0.25) });
            addSection("D54A", { labelWith("HR", h), labelWith("WB", w) });
            break;
        case 9:
            addSection("D54F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25) });
            addSection("D54A", { labelWith("WB", w), labelWith("WT", w) });
            break;
        case 10:           
            addSection("D54F", { labelWith("WT", w + 0.25), labelWith("WB", w + 0.25) });
            addSection("D54A", { labelWith("HL", h), labelWith("HR", h) });
            break;
        case 11:
            addSection("D54F", { labelWith("WT", w + 0.25) });
            addSection("D54A", { labelWith("HL", h), labelWith("HR", h), labelWith("WB", w) });
            break;
        case 12:
            addSection("D54F", { labelWith("HR", h + 0.25) });
            addSection("D54A", { labelWith("HL", h), labelWith("WT", w), labelWith("WB", w) });
            break;
        case 13:
            addSection("D54F", { labelWith("WB", w + 0.25) });
            addSection("D54A", { labelWith("HL", h), labelWith("HR", h), labelWith("WT", w) });     
            break;
        case 14:
            addSection("D54F", { labelWith("HL", h + 0.25) });
            addSection("D54A", { labelWith("HR", h), labelWith("WT", w), labelWith("WB", w) });        
            break;
    }


    // Inner Sections
    addSection("D41", { labelWith("HL", h), labelWith("HR", h ), labelWith("WT", w ), labelWith("WB", w ) });
}

double F_Win::getAreaSqFt() const {
    return height * width;
}

std::string F_Win::getLabel() const {
    return label;
}

const SectionMap& F_Win::getSectionMap() const {
    return sectionMap;
}


void F_Win::sendToEstimator(EstimateLengthManager& estimator) {
    estimator.addWindowSections(label, sectionMap);
}

char F_Win::getSize() const {return unitChoice;}   
double F_Win::getHeight() const { if (inputInInches) {return height * 12.0;} return height;}
double F_Win::getWidth() const {if (inputInInches){return width * 12.0;} return width;}
int F_Win::getCollarType() const { return collarType; }


void F_Win::sendToEstimator() {
    std::cout << "[F_Win] Warning: No estimator provided in sendToEstimator().\n";
}
