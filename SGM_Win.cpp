#include "SGM_Win.h"
#include "EstimateLengthManager.h"
#include "SettingsManagerA.h"
#include "CommonTypes.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>


void SGM_Win::resetWindowCount() { windowCount = 0;} 
int SGM_Win::windowCount = 0; 
SGM_Win::SGM_Win() {
    height = 0.0;
    width = 0.0;
    collarType = 0;
    inputInInches = false;
    ++windowCount;
}

// Returns true if data entered successfully, false if cancelled
bool SGM_Win::inputWindowData(bool isEditing) {
    if (!isEditing) {
        
        label = "SGM_Win #" + std::to_string(windowCount) + " -> ";
    } else {
        std::cout << "\n--- Editing " << label << " ---\n";
    }

    if (!selectGlassOption()) return false;
    if (!inputSizeAndCollar()) return false;

    return true;
}

bool SGM_Win::selectGlassOption() {
    while (true) {
        std::cout << "\n| |   | | Center Fix              (1) ";
        std::cout << "\n| | | | | Center Slide            (2) ";
        std::cout << "\n | | | |  Equal three glass part  (3) ";
        std::cout << "\n Select Option or 0 to cancel: ";

        if (std::cin >> glassOption) {
            if (glassOption == 0) {
                std::cout << "⚠ Entry cancelled!\n";
                return false;
            }
            if (glassOption >= 1 && glassOption <= 3) break;
        }
        std::cout << "❌ Invalid input! Please enter 1, 2, or 3.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return true;
}

bool SGM_Win::inputSizeAndCollar() {
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
        std::cout << "❌ Height must be a positive number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 4. Width
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

    // Convert inches to feet if needed
    if (inputInInches) {
        height /= 12.0;
        width  /= 12.0;
    }

    return true;
}


void SGM_Win::calculateSections() {
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
        addSection("M30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25), labelWith("WT", w + 0.25) });
        addSection("M26F", { labelWith("WB", w + 0.25) });
        break;
    case 2:
        addSection("M30", { labelWith("HL", h), labelWith("HR", h), labelWith("WT", w) });
        addSection("M26", { labelWith("WB", w) });
        break;
    case 3:
        addSection("M30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25) });
        addSection("M30", { labelWith("WT", w) });
        addSection("M26F", { labelWith("WB", w + 0.25) });
        break;
    case 4:
        addSection("M30F", { labelWith("HL", h + 0.25), labelWith("WT", w + 0.25) });
        addSection("M30", { labelWith("HR", h) });
        addSection("M26F", { labelWith("WB", w + 0.25) }); 
        break;
    case 5:
        addSection("M30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25), labelWith("WT", w + 0.25) });
        addSection("M26", { labelWith("WB", w) });
        break;
    case 6:
        addSection("M30", { labelWith("HL", h) });
        addSection("M30F", { labelWith("HR", h + 0.25), labelWith("WT", w + 0.25) });
        addSection("M26F", { labelWith("WB", w + 0.25) });
        break;
    case 7:
        addSection("M30", { labelWith("HL", h), labelWith("WT", w) });
        addSection("M30F", { labelWith("HR", h + 0.25) });
        addSection("M26F", { labelWith("WB", w + 0.25) });
        break;
    case 8:
        addSection("M30", { labelWith("HR", h) });
        addSection("M30F", { labelWith("HL", h + 0.25), labelWith("WT", w + 0.25) });
        addSection("M26", { labelWith("WB", w) });
        break;
    case 9:
        addSection("M30", { labelWith("WT", w) });
        addSection("M30F", { labelWith("HL", h + 0.25), labelWith("HR", h + 0.25) });
        addSection("M26", { labelWith("WB", w) });
        break;
    case 10:
        addSection("M30", { labelWith("HL", h), labelWith("HR", h) });
        addSection("M30F", { labelWith("WT", w + 0.25) });
        addSection("M26F", { labelWith("WB", w + 0.25) });
        break;
    case 11:
        addSection("M30", { labelWith("HL", h), labelWith("HR", h) });
        addSection("M30F", { labelWith("WT", w + 0.25) });
        addSection("M26", { labelWith("WB", w) });
        break;
    case 12:
        addSection("M30", { labelWith("HL", h), labelWith("WT", w) });
        addSection("M30F", { labelWith("HR", h + 0.25) });
        addSection("M26", { labelWith("WB", w) });
        break;
    case 13:
        addSection("M30", { labelWith("HL", h), labelWith("HR", h), labelWith("WT", w) });
        addSection("M26F", { labelWith("WB", w + 0.25) });
        break;
    case 14:
        addSection("M30", { labelWith("HR", h), labelWith("WT", w) });
        addSection("M30F", { labelWith("HL", h + 0.25) });
        addSection("M26", { labelWith("WB", w) });
        break;
    }


    // Inner Sections
   if (glassOption == 1) {
        addSection("M23", { labelWith("H", h), labelWith("H", h) });
        addSection("M28", { labelWith("H", h), labelWith("H", h), labelWith("H", h), labelWith("H", h) });
        addSection("M24", { labelWith("W1", w/4), labelWith("W2", w/4), labelWith("W3", w/4), labelWith("W4", w/4),
                             labelWith("W5", w/2), labelWith("W6", w/2) });
        //addSection("D29", { labelWith("W1", w/4), labelWith("W2", w/4), labelWith("W3", w/4), labelWith("W4", w/4),
         //                    labelWith("H1", h), labelWith("H2", h), labelWith("H3", h), labelWith("H4", h) });
    }
    else if (glassOption == 2) {
        addSection("M23", { labelWith("H1", h), labelWith("H2", h), labelWith("H3", h), labelWith("H4", h) });
        addSection("M28", { labelWith("H", h), labelWith("H", h), labelWith("H", h), labelWith("H", h) });
        addSection("M24", { labelWith("W1", w/4), labelWith("W2", w/4), labelWith("W3", w/4), labelWith("W4", w/4),
                             labelWith("W5", w/4), labelWith("W6", w/4), labelWith("W7", w/4), labelWith("W8", w/4) });
        //addSection("D29", { labelWith("W1", w/4), labelWith("W2", w/4), labelWith("W3", w/4), labelWith("W4", w/4),
        //                     labelWith("H1", h), labelWith("H2", h), labelWith("H3", h), labelWith("H4", h) });
        addSection("D32A", { labelWith("H", h) });
    }
    else if (glassOption == 3) {
        addSection("M23", { labelWith("H", h), labelWith("H", h) });
        addSection("M28", { labelWith("H", h), labelWith("H", h), labelWith("H", h), labelWith("H", h) });
        addSection("M28", { labelWith("W1", w/3), labelWith("W2", w/3), labelWith("W3", w/3),
                             labelWith("W4", w/3), labelWith("W5", w/3), labelWith("W6", w/3) });
        //addSection("D29", { labelWith("W1", w/3), labelWith("W2", w/3), labelWith("H1", h), labelWith("H2", h) });
    }
}

double SGM_Win::getAreaSqFt() const {
    return height * width;
}

std::string SGM_Win::getLabel() const {
    return label;
}

const SectionMap& SGM_Win::getSectionMap() const {
    return sectionMap;
}


void SGM_Win::sendToEstimator(EstimateLengthManager& estimator) {
    estimator.addWindowSections(label, sectionMap);
}

char SGM_Win::getSize() const {return unitChoice;}
double SGM_Win::getHeight() const { if (inputInInches) {return height * 12.0;} return height;}
double SGM_Win::getWidth() const {if (inputInInches){return width * 12.0;} return width;}
int SGM_Win::getCollarType() const { return collarType; }


void SGM_Win::sendToEstimator() {
    std::cout << "[SlideWindow] Warning: No estimator provided in sendToEstimator().\n";
}
