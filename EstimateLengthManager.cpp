// EstimateLengthManager.cpp
#include "EstimateLengthManager.h"
#include "EstimateLengthResult.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include "SettingsManagerA.h"
#include "SettingsManagerB.h"
#include "GroupResult.h"
#include "CommonTypes.h"

EstimateLengthManager::EstimateLengthManager() {}



void EstimateLengthManager::performEstimation() {
    printPerSectionBreakdown();         // Step 1: Print per-section breakdown 
    groupAndOptimizeSections();         // Step 2: Group and optimize sections
}

void EstimateLengthManager::addWindowSections(const std::string& windowLabel, const SectionMap& sections) {
    windowSections[windowLabel] = sections;
}

// ✅ Paste removeWindow here
void EstimateLengthManager::removeWindow(const std::string& label) {
    // Remove the sections data for this window
    auto it = windowSections.find(label);
    if (it != windowSections.end()) {
        windowSections.erase(it);
    }

    // Optionally, also clear from combinedSections if you want immediate removal
    for (auto& [sectionName, items] : combinedSections) {
        items.erase(std::remove_if(items.begin(), items.end(),
                                   [&](const std::pair<std::string, double>& p) {
                                       return p.first.find(label) != std::string::npos;
                                   }),
                    items.end());
    }
}

///////////////////////// Print Per-Section Breakdown /////////////////////////

void EstimateLengthManager::printPerSectionBreakdown() const {
    combinedSections.clear();

    for (const auto& windowPair : windowSections) {
        const std::string& windowLabel = windowPair.first;
        const SectionMap& sections = windowPair.second;

        for (const auto& sectionPair : sections) {
            const std::string& sectionName = sectionPair.first;
            const std::vector<std::pair<double, std::string>>& values = sectionPair.second;

            for (const auto& valPair : values) {
                combinedSections[sectionName].emplace_back(valPair.second, valPair.first); 
            }
        }
    }

    std::cout << "\n================== 🧾 Section-wise Breakdown ==================\n";

    for (const auto& sectionEntry : combinedSections) {
        const std::string& sectionName = sectionEntry.first;
        const std::vector<std::pair<std::string, double>>& items = sectionEntry.second;

        // 📦 Copy and sort
        std::vector<std::pair<std::string, double>> sortedItems = items;

        std::sort(sortedItems.begin(), sortedItems.end(), [](const auto& a, const auto& b) {
            auto extractWindowNumber = [](const std::string& label) -> int {
                std::size_t pos = label.find("#");
                if (pos != std::string::npos) {
                    std::string numberPart;
                    for (size_t i = pos + 1; i < label.size(); ++i) {
                        if (isdigit(label[i]))
                            numberPart += label[i];
                        else
                            break;
                    }
                    return std::stoi(numberPart);
                }
                return 9999; // fallback if '#' not found
            };

            int winA = extractWindowNumber(a.first);
            int winB = extractWindowNumber(b.first);

            if (winA == winB)
                return a.first < b.first; // sort by label (e.g. HR < WT)
            return winA < winB;
        });

        std::cout << "\nSection " << sectionName << ":\n";
        for (const auto& [label, value] : sortedItems) {
            std::cout << "    " << std::fixed << std::setprecision(1)
                      << value << " ft   (" << label << ")\n";
        }
    }

    std::cout << "\n================================ Length Optimization =================================\n";
}



////////////////////// Group and Optimize Sections //////////////////////////


EstimateLengthResult EstimateLengthManager::groupAndOptimizeSections() {
    EstimateLengthResult result;
    std::unordered_map<std::string, std::vector<LengthGroup>> groupedResults;

    // 🟢 Clear old summaries before generating new ones
    sectionSummaries.clear();

    SettingsManagerA& settings = SettingsManagerA::getInstance(); // ✅ old manager
    SettingsManagerB& generalSettings = SettingsManagerB::getInstance(); // ✅ new one for red zone & extra pieces

    groupedResults.clear();

    if (combinedSections.empty()) {
        std::cout << "No sections available to group and optimize.\n";
        return result;
    }

    for (const auto& sectionEntry : combinedSections) {
        const std::string& sectionName = sectionEntry.first;
        const auto& pieces = sectionEntry.second;

        std::vector<double> allowedLengths = settings.getAllowedLengthsForSection(sectionName);
        std::sort(allowedLengths.begin(), allowedLengths.end(), std::greater<>());

        std::vector<std::pair<double, std::vector<std::string>>> bestFitGroupings;
        std::vector<bool> used(pieces.size(), false);

        while (true) {
            double bestWastage = 999;
            double chosenLength = -1;
            std::vector<int> bestIndices;

            for (float length : allowedLengths) {
                std::vector<int> currentIndices;
               double sum = 0.0f;

                for (size_t i = 0; i < pieces.size(); ++i) {
                    if (used[i]) continue;
                   double pieceLength = pieces[i].second;

                    if (sum + pieceLength <= length) {
                        currentIndices.push_back(i);
                        sum += pieceLength;
                        if (length - sum < 0.0001) break;
                    }
                }

               double currentWastage = length - sum;

                if (!currentIndices.empty() && currentWastage <= 1.75f && currentWastage < bestWastage) {
                    bestWastage = currentWastage;
                    chosenLength = length;
                    bestIndices = currentIndices;
                }
            }

            if (bestIndices.empty()) break;

           double total = 0.0f;
            std::vector<std::string> labelDetails;
            for (int idx : bestIndices) {
                used[idx] = true;
                total += pieces[idx].second;
                labelDetails.push_back(pieces[idx].first + "(" + std::to_string(pieces[idx].second) + ")");
            }

            bestFitGroupings.emplace_back(chosenLength, labelDetails);
        }

        // Smart handling of leftover small pieces
        std::vector<std::pair<std::string, double>> leftovers;
        for (size_t i = 0; i < pieces.size(); ++i) {
            if (!used[i]) leftovers.push_back(pieces[i]);
        }

       double leftoverSum = 0.0f;
        std::vector<std::string> leftoverLabels;
        for (const auto& [label, len] : leftovers) {
            leftoverSum += len;
            leftoverLabels.push_back(label + "(" + std::to_string(len) + ")");
        }

        if (!leftoverLabels.empty()) {
            double finalLength = leftoverSum;

            // 🎯 Get the red zone value dynamically
            double redZone = settings.isGroup1(sectionName) ? generalSettings.getRedZone1() : generalSettings.getRedZone2();

            if (leftoverSum >= redZone) {
                for (double len : allowedLengths) {
                    if (len >= leftoverSum) {
                        finalLength = len;
                        break;
                    }
                }
            }

            bestFitGroupings.emplace_back(finalLength, leftoverLabels);
        }

        // Output & summary (unchanged)
        double totalLength = 0.0f;
        std::vector<double> usedLengths;

        std::cout << "\n" << sectionName << ":\n";
        for (const auto& group : bestFitGroupings) {
            double len = group.first;
            const auto& labels = group.second;

            double usedLength = 0.0f;
            std::string joined;
            for (const auto& lbl : labels) {
                size_t pos1 = lbl.find("(");
                size_t pos2 = lbl.find(")");
                if (pos1 != std::string::npos && pos2 != std::string::npos) {
                    usedLength += std::stof(lbl.substr(pos1 + 1, pos2 - pos1 - 1));
                }
                joined += lbl + " + ";
            }
            if (!joined.empty()) joined.erase(joined.size() - 3);

            double wastage = len - usedLength;

            std::cout << "  " << len << "ft = " << joined << " | Wastage: " << wastage << "ft\n";
            totalLength += len;
            usedLengths.push_back(len);
        }

        std::cout << "Total Length for " << sectionName << ": ";
        for (size_t i = 0; i < usedLengths.size(); ++i) {
            std::cout << usedLengths[i];
            if (i < usedLengths.size() - 1) std::cout << " + ";
        }
        std::cout << " = " << totalLength << "ft\n";

        SectionSummary summary;
        summary.sectionName = sectionName;
        summary.usedLengths = usedLengths;
        summary.totalLength = totalLength;
        sectionSummaries.push_back(summary);
    }

    return result;
}


///////////////////////////// Clear All Data ////////////////////////////

void EstimateLengthManager::clearAllData() {
    windowSections.clear();
    allSections.clear();
    groupResults.clear();
    optimizedSectionSummary.clear();
    sectionSizes.clear();
    combinedSections.clear();
    sectionSummaries.clear();

    // Reset grouped section summaries
    groupedSectionSummaries = EstimateLengthResult();

    // 🟢 Reset the window counter here
    //windowCounter = 0;

    std::cout << "🔄 EstimateLengthManager memory cleared!\n";
}

// --- at the end ---

const std::vector<SectionSummary>& EstimateLengthManager::getSummaries() const {
    return sectionSummaries;
}

std::vector<SectionSummary>& EstimateLengthManager::getSummaries() {
    return sectionSummaries;
}



 