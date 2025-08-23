#include "FC_Win.h"
#include "EstimateLengthManager.h"
#include "SettingsManagerA.h"
#include "CommonTypes.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

int FC_Win::windowCount = 0; 
void FC_Win::resetWindowCount() { windowCount = 0;}
FC_Win::FC_Win()
    : height(0.0), width(0.0), rightWidth(0.0), leftWidth(0.0),
      collarType(0), winType(0), inputInInches(false) {++windowCount;}

bool FC_Win::inputWindowData(bool isEditing) {
    if (!isEditing) {
        
        label = "FC_Win #" + std::to_string(windowCount) + " -> ";
    } else {
        std::cout << "\n--- Editing " << label << " ---\n";
    }

    if (!inputDetails()) return false;

    return true;
}

////////////////////////// Input Details Method //////////////////////////

bool FC_Win::inputDetails() {
    // 1. Unit choice
    while (true) {
        std::cout << "Enter size in (i)nches or (f)eet? [i/f] (0 = cancel): ";
        if (std::cin >> unitChoice) {
            if (unitChoice == '0') {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
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

    // 2. Collar type
    while (true) {
        std::cout << "Enter Collar Type (1 - 2, 0 = cancel): ";
        if (std::cin >> collarType) {
            if (collarType == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (collarType >= 1 && collarType <= 2) break;
        }
        std::cout << "❌ Please enter a number between 1 and 2.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 3. Height
    while (true) {
        std::cout << "Enter Height (0 = cancel): ";
        if (std::cin >> height) {
            if (height == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (height > 0) break;
        }
        std::cout << "❌ Height must be positive.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 4. Right Width
    while (true) {
        std::cout << "Enter Right Width (0 = cancel): ";
        if (std::cin >> rightWidth) {
            if (rightWidth == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (rightWidth > 0) break;
        }
        std::cout << "❌ Right Width must be positive.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 5. Left Width
    while (true) {
        std::cout << "Enter Left Width (0 = cancel): ";
        if (std::cin >> leftWidth) {
            if (leftWidth == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (leftWidth > 0) break;
        }
        std::cout << "❌ Left Width must be positive.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Convert inches to feet if needed
    if (inputInInches) {
        height     /= 12.0;
        rightWidth /= 12.0;
        leftWidth  /= 12.0;
    }

    // Set total width
    width = leftWidth + rightWidth;

    return true;
}


void FC_Win::calculateSections() {
    sectionMap.clear();

    double h = height;
    double wr = rightWidth;
    double wl = leftWidth;


    SettingsManagerA& settings = SettingsManagerA::getInstance();

    auto labelWith = [&](const std::string& prefix, double value) {
        return std::make_pair(label + prefix, value);
    };

    auto addSection = [&](const std::string& key, const std::vector<std::pair<std::string, double>>& values) {
        std::vector<std::pair<double, std::string>> converted;
        for (const auto& [lbl, val] : values) {
            converted.emplace_back(val, lbl);
        }
        sectionMap[settings.getSectionName(key)] = converted;
    };

    // Collar Type Sections
    if (collarType == 1) {
        addSection("D54F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25),
                               labelWith("WT_l", wl + 0.25), labelWith("WT_r", wr + 0.25),
                            labelWith("WB_l", wl + 0.25), labelWith("WB_r", wr + 0.25) });
    }
    else if (collarType == 2) {
        addSection("D54A", { labelWith("HL", h), labelWith("HL", h),
                               labelWith("WT_l", wl), labelWith("WT_r", wr),
                            labelWith("WB_l", wl), labelWith("WB_r", wr) });
    }

    // Inner Sections - Corner Window
    addSection("D41", { labelWith("HL", h), labelWith("HR", h),
                               labelWith("WT_l", wl), labelWith("WT_r", wr),
                            labelWith("WB_l", wl), labelWith("WB_r", wr) });
}

double FC_Win::getAreaSqFt() const {
    return height * width;
}

std::string FC_Win::getLabel() const {
    return label;
}

const SectionMap& FC_Win::getSectionMap() const {
    return sectionMap;
}


void FC_Win::sendToEstimator(EstimateLengthManager& estimator) {
    estimator.addWindowSections(label, sectionMap);
}

char FC_Win::getSize() const {return unitChoice;}   
double FC_Win::getHeight() const { if (inputInInches) {return height * 12.0;} return height;}
double FC_Win::getWidth() const {if (inputInInches){return width * 12.0;} return width;}
double FC_Win::getRightWidth() const { if (inputInInches) {return rightWidth * 12.0;} return rightWidth; }
double FC_Win::getLeftWidth() const { if (inputInInches) {return leftWidth * 12.0;} return leftWidth; }
int FC_Win::getCollarType() const { return collarType; }


void FC_Win::sendToEstimator() {
    std::cout << "[SlideWindow] Warning: No estimator provided in sendToEstimator().\n";
}


