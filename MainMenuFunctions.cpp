#include "MainMenuFunctions.h"

void printWindowsSummary(const vector<unique_ptr<FrameComponent>>& windows) {
    cout << "\n--- Entered Windows Summary ---\n";
    for (size_t i = 0; i < windows.size(); ++i) {
        const auto& w = windows[i];

        // Try casting to SlideWindow to access SlideWindow-specific methods
        if (auto sw = dynamic_cast<S_Win*>(w.get())) {
            cout << i + 1 << ": " << sw->getLabel()
                 << "Size: " << sw->getSize() << "  |  "
                 << "Height: " << sw->getHeight() << " i/f |  "
                 << "Width: " << sw->getWidth() << " i/f |  "
                 << "Collar: " << sw->getCollarType() << "  |  "
                 << "Area: " << sw->getAreaSqFt() << " ft \n";
        }
        else if (auto swm = dynamic_cast<SM_Win*>(w.get())) {
            cout << i + 1 << ": " << swm->getLabel()
                 << "Size: " << swm->getSize() << "  |  "
                 << "Height: " << swm->getHeight() << " i/f |  "
                 << "Width: " << swm->getWidth() << " i/f |  "
                 << "Collar: " << swm->getCollarType() << "  |  "
                 << "Area: " << swm->getAreaSqFt() << "ft \n";
        }
        else if (auto sg = dynamic_cast<SG_Win*>(w.get())) {
            cout << i + 1 << ": " << sg->getLabel()
                 << "Size: " << sg->getSize() << "  |  "
                 << "Height: " << sg->getHeight() << " i/f |  "
                 << "Width: " << sg->getWidth() << " i/f |  "
                 << "Collar: " << sg->getCollarType() << "  |  "
                 << "Area: " << sg->getAreaSqFt() << "ft \n";
        }
        else if (auto sgm = dynamic_cast<SGM_Win*>(w.get())) {
            cout << i + 1 << ": " << sgm->getLabel()
                 << "Size: " << sgm->getSize() << "  |  "
                 << "Height: " << sgm->getHeight() << " i/f |  "
                 << "Width: " << sgm->getWidth() << " i/f |  "
                 << "Collar: " << sgm->getCollarType() << "  |  "
                 << "Area: " << sgm->getAreaSqFt() << "ft \n";
        }
        else if (auto sc = dynamic_cast<SC_Win*>(w.get())) {
            cout << i + 1 << ": " << sc->getLabel()
                 << "Size: " << sc->getSize() << "  |  "
                 << "Height: " << sc->getHeight() << " i/f |  "
                 << "RightWidth: " << sc->getRightWidth() << " i/f |  "
                 << "LeftWidth: " << sc->getLeftWidth() << " i/f |  "
                 << "Collar: " << sc->getCollarType() << "  |  "
                 << "Area: " << sc->getAreaSqFt() << "ft \n";
        }
        else if (auto scm = dynamic_cast<SCM_Win*>(w.get())) {
            cout << i + 1 << ": " << scm->getLabel()
                 << "Size: " << scm->getSize() << "  |  "
                 << "Height: " << scm->getHeight() << " i/f |  "
                 << "RightWidth: " << scm->getRightWidth() << " i/f |  "
                 << "LeftWidth: " << scm->getLeftWidth() << " i/f |  "
                 << "Collar: " << scm->getCollarType() << "  |  "
                 << "Area: " << scm->getAreaSqFt() << "ft \n";
        }
        else if (auto fc = dynamic_cast<FC_Win*>(w.get())) {
            cout << i + 1 << ": " << fc->getLabel()
                 << "Size: " << fc->getSize() << "  |  "
                 << "Height: " << fc->getHeight() << " i/f |  "
                 << "RightWidth: " << fc->getRightWidth() << " i/f |  "
                 << "LeftWidth: " << fc->getLeftWidth() << " i/f |  "
                 << "Collar: " << fc->getCollarType() << "  |  "
                 << "Area: " << fc->getAreaSqFt() << "ft \n";
        }
        else if (auto f = dynamic_cast<F_Win*>(w.get())) {
            cout << i + 1 << ": " << f->getLabel()
                 << "Size: " << f->getSize() << "  |  "
                 << "Height: " << f->getHeight() << " i/f |  "
                 << "Width: " << f->getWidth() << " i/f |  "
                 << "Collar: " << f->getCollarType() << "  |  "
                 << "Area: " << f->getAreaSqFt() << "ft \n";
        }
        else if (auto o = dynamic_cast<O_Win*>(w.get())) {
            cout << i + 1 << ": " << o->getLabel()
                 << "Size: " << o->getSize() << "  |  "
                 << "Height: " << o->getHeight() << " i/f |  "
                 << "Width: " << o->getWidth() << " i/f |  "
                 << "Collar: " << o->getCollarType() << "  |  "
                 << "Area: " << o->getAreaSqFt() << "ft \n";
        }
        else if (auto d = dynamic_cast<D_Win*>(w.get())) {
            cout << i + 1 << ": " << d->getLabel()
                 << "Size: " << d->getSize() << "  |  "
                 << "Height: " << d->getHeight() << " i/f |  "
                 << "Width: " << d->getWidth() << " i/f |  "
                 << "Collar: " << d->getCollarType() << "  |  "
                 << "Area: " << d->getAreaSqFt() << "ft \n";
        }
        else if (auto ar = dynamic_cast<A_Win*>(w.get())) {
            cout << i + 1 << ": " << ar->getLabel()
                 << "Size: " << ar->getSize() << "  |  "
                 << "Height: " << ar->getHeight() << " i/f |  "
                 << "Width: " << ar->getWidth() << " i/f |  "
                 << "Arch: " << ar->getArch() << " i/f |  "
                 << "Collar: " << ar->getCollarType() << "  |  "
                 << "Area: " << ar->getAreaSqFt() << "ft \n";
        }
        else {
            cout << i + 1 << ": " << w->getLabel() << " (Unknown window type)\n";
        }

    }
    
}


void addOrEditWindowsLoop(
    std::vector<std::unique_ptr<FrameComponent>>& windows,
    std::map<int, std::pair<std::string, std::function<std::unique_ptr<FrameComponent>()>>>& windowTypes,
    EstimateLengthManager& estimator,
    SectionRatesManager& ratesManager,          // ✅ add this
    FinalSummaryManager& summaryManager,
    FinalCostCalculator& finalEstimator        // ✅ add this
) {
    while (true) {
        // Show window types
        std::cout << "\n------ Window Types ------\n";
        for (const auto& [id, pair] : windowTypes) {
            std::cout << pair.first << "   [" << id << "]\n";
        }
        std::cout << "0. 🔙 Back to Main Menu\n";

        int type;
        std::cout << "Select Type: ";
        if (!(std::cin >> type)) {
            std::cout << "❌ Invalid input! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (type == 0) {
            std::cout << "🔙 Returning to Main Menu...\n";
            break;
        }

        if (!windowTypes.count(type)) {
            std::cout << "❌ Invalid Type! Please try again.\n";
            continue;
        }

        int num = 0;
        while (true) {
            num++;
            std::cout << "\n------------- Window/Door/Arch no[" << num << "]-------------\n\n";
            auto window = windowTypes[type].second();
            bool success = window->inputWindowData();
            if (!success) {
                std::cout << "⚠ Window entry cancelled.\n";
                break;  // Cancel adding this window, back to window types menu
            }

            window->calculateSections();
            window->sendToEstimator(estimator);
            summaryManager.addWindow(window->getLabel(), window->getAreaSqFt());

            windows.push_back(std::move(window));
            std::cout << "✅ Window added successfully!\n";

            // Show current windows summary
            printWindowsSummary(windows);

            // Ask if user wants to add another of the same type
            std::cout << "Add another window of this type? (y/n): ";
            char cont;
            std::cin >> cont;
            if (cont != 'y' && cont != 'Y') break; // back to window types menu
        }
    }

    // --- After finishing adding windows, review/edit/delete loop ---
    while (true) {
        // Always show current summary
        printWindowsSummary(windows);

        std::cout << "\n➡ What do you want to do with Windows?\n";
        std::cout << "   [1] Add New Window\n";
        std::cout << "   [2] Edit a Window\n";
        std::cout << "   [3] Delete a Window\n";
        std::cout << "   [4] Next to Estimate\n";
        std::cout << "   [0] Back\n";
        std::cout << "Enter choice: ";

        int option;
        if (!(std::cin >> option)) {
            std::cout << "❌ Invalid input! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (option) {
            case 1: 
                addWindow(windows, estimator, summaryManager);                
                break;
            case 2: 
                 editWindow(windows, estimator, summaryManager); 
                break;
            case 3: 
                deleteWindow(windows, estimator, summaryManager); 
                break;
            case 4: 
                showFinalSummary(windows, estimator, ratesManager, summaryManager, finalEstimator);
                break;
            case 0: 
                std::cout << "🔙 Going back...\n"; 
                return;  // exit loop completely
            default: 
                std::cout << "❌ Invalid choice.\n"; 
                break;
        }
    }
}


///////////////////////////////////// Show Final Summary /////////////////////////////////////

void showFinalSummary(
    vector<unique_ptr<FrameComponent>>& windows,
    EstimateLengthManager& estimator,
    SectionRatesManager& ratesManager,
    FinalSummaryManager& summaryManager,
    FinalCostCalculator& finalEstimator
) {
    if (windows.empty()) {
        cout << "⚠️ No windows added yet!\n";
        return;
    }

    try {
        cout << "\n🔍 Performing Final Estimation...\n";

        // 1. Estimation chalao
        estimator.performEstimation();

        // 2. Section rates input lo
        ratesManager.inputRatesFromUser();
        ratesManager.editRateByLineNumber();     // optional correction
        double grandTotal = ratesManager.computeAndStoreTotals();
        ratesManager.printFinalSummaryTable();

        // 3. Aluminium total ko summary manager me store karo
        summaryManager.setAluminiumTotal(grandTotal);

        // 4. Baaki general rates input lo
        finalEstimator.inputRates();

        // 5. Loop for re-estimation / re-entering rates
        while (true) {
            int choice = finalEstimator.displayFinalSummary();
        
            if (choice == 1) {
                cout << "\n🆕 Generating a NEW Bill (without re-calculating sections)...\n";
        
                // Sirf rates re-enter karna hai
                ratesManager.inputRatesFromUser();
                ratesManager.editRateByLineNumber();

                grandTotal = ratesManager.computeAndStoreTotals();
                ratesManager.printFinalSummaryTable();

                summaryManager.setAluminiumTotal(grandTotal);

                finalEstimator.inputRates();
                // 🚫 Yahan dobara displayFinalSummary() call nahi karna
                // Loop apne aap next iteration me fir se summary dikhayega
            }
                    else if (choice == 2) {
                cout << "\n-- Re-entering Other Rates...\n";
                finalEstimator.inputRates();
                // Loop automatic summary fir se show karega
            }
            else if (choice == 0) {
                cout << "\n-- Going back to Home Menu...\n";
                break;  // return ki jagah break, taake loop se nikal jaye
            }
            else {
                cout << "⚠️ Invalid choice! Please enter 1, 2, or 0.\n";
            }
        }

            }
            catch (const std::exception& ex) {
        cerr << "❌ Error during final summary: " << ex.what() << "\n";
            }
            catch (...) {
        cerr << "❌ Unknown error occurred during final summary!\n";
            }
}




////////////////////////////////////////////////////////////////////////////////

void addWindowForFabrication() {
    cout << "🛠 Add Window for Fabrication feature is coming soon!\n";
}

void getCuttingSize() {
    cout << "📏 Get Cutting Size feature is coming soon!\n";
}

//////////////////////////// ⚙️ Section Settings Menu //////////////////////////

void settingsMenu() {
    int option;
    auto& manager = SettingsManagerA::getInstance();     // Old system (A)
    auto& managerB = SettingsManagerB::getInstance();   // New system (B)

    do {
        cout << "\n🔧 === Section Settings Menu ===\n"
             << "1. Show All Sections\n"
             << "2. Update Section Lengths\n"
             << "3. Rename a Section\n"
             << "4. Set maxExtraPieces\n"
             << "5. Set redZone1 & redZone2\n"
             << "0. 🔙 Back to Main Menu\n"
             << "Choose option: ";
        cin >> option;
        cin.ignore();

switch (option) {
case 1:
                manager.displayAllSettings();
                break;

case 2: {
    string section;
    int count;

    cout << "Enter section name (e.g. DC30F) or 0 to go back: ";
    cin >> section;
    if (section == "0") break; // Back to settings menu

    cout << "How many lengths to enter? (0 to go back): ";
    cin >> count;
    if (count == 0) break; // Back

    if (count < 0) {
        cout << "❌ Count can't be negative!\n";
        break;
    }

    vector<int> lengths(count);
    for (int i = 0; i < count; ++i) {
        cout << "Enter length #" << (i + 1) << ": ";
        cin >> lengths[i];
    }

    manager.setSectionLengths(section, lengths);
    manager.saveToFile("section_settings.txt");
    cout << "✅ Lengths updated and saved!\n";
    break;
                    }


case 3: {
    string oldName, newName;
    cout << "Enter current section name (0 to cancel): ";
    cin >> oldName;
    if (oldName == "0") {
        cout << "↩️ Cancelled. Returning to settings menu...\n";
        break;
    }

    cout << "Enter new section name (0 to cancel): ";
    cin >> newName;
    if (newName == "0") {
        cout << "↩️ Cancelled. Returning to settings menu...\n";
        break;
    }

    manager.renameSection(oldName, newName);
    manager.saveToFile("section_settings.txt");
    cout << "✅ Section renamed and saved!\n";
    break;
}


case 4: {
    int value;
    cout << "Enter new value for maxExtraPieces (0 to cancel): ";
    cin >> value;

    if (value == 0) {
        cout << "↩️ Cancelled. Returning to settings menu...\n";
        break;
    }

    if (value < 0) {
        cout << "❌ Invalid: maxExtraPieces can't be negative!\n";
    } else {
        managerB.setMaxExtraPieces(value);
        managerB.saveSettings("general_settings.txt");
        cout << "✅ maxExtraPieces updated and saved!\n";
    }
    break;
}

case 5: {
    double rz1, rz2;
    cout << "Enter redZone1 value (0 to cancel): ";
    cin >> rz1;
    if (rz1 == 0) {
        cout << "↩️ Cancelled. Returning to settings menu...\n";
        break;
    }

    cout << "Enter redZone2 value (0 to cancel): ";
    cin >> rz2;
    if (rz2 == 0) {
        cout << "↩️ Cancelled. Returning to settings menu...\n";
        break;
    }

    if (rz1 <= 0 ||  rz2 <= 0) {
        cout << "❌ Error: Values must be greater than 0.\n";
    } else {
        managerB.setRedZone1(rz1);
        managerB.setRedZone2(rz2);
        managerB.saveSettings("general_settings.txt");
        cout << "✅ redZone1 and redZone2 updated and saved!\n";
    }
    break;
}


            case 0:
                cout << "👋 Returning to Main Menu...\n";
                break;

            default:
                cout << "❌ Invalid option. Try again.\n";
        }
    } while (option != 0);
}