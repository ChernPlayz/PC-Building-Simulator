#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <map>

using namespace std;

bool isTutorial = false;
int tutorialMainSteps = 1;
int tutorialBuySteps = 1;

// Structs
struct Component{
  string name;
  double price;
};

struct PlrInv{
  string partType;
  string name;
  double price;
};

struct PlrBuilds{
  string name;
  vector<PlrInv> parts;
  double totalPrice;
};

// Component Lists
Component CPUList[] = {
  {"Intel i3-12100", 99.99},
  {"AMD Ryzen 3 4100", 109.75},
  {"Intel i5-12400", 179.50},
  {"AMD Ryzen 5 5600X", 199.95},
  {"Intel i7-12700K", 349.99},
  {"AMD Ryzen 7 5800X", 339.50},
  {"Intel i9-12900K", 589.99},
  {"AMD Ryzen 9 7950X", 649.99},
};

Component GPUList[] = {
  {"NVIDIA GTX 1650", 159.99},
  {"AMD RX 6500 XT", 179.50},
  {"NVIDIA RTX 3060", 329.99},
  {"AMD RX 6700 XT", 379.75},
  {"NVIDIA RTX 3070", 509.99},
  {"AMD RX 6800 XT", 649.99},
  {"NVIDIA RTX 4080", 1199.50},
  {"NVIDIA RTX 4090", 1599.99},
};

Component RAMList[] = {
  {"8GB DDR4 RAM", 44.99},
  {"16GB DDR4 RAM", 74.75},
  {"32GB DDR4 RAM", 139.99},
  {"16GB DDR5 RAM", 89.99},
  {"32GB DDR5 RAM", 159.50},
};

Component MoboList[] = {
  {"Budget Motherboard", 79.99},
  {"Mid-Range Motherboard", 149.75},
  {"High-End Motherboard", 299.99},
};

Component SSDList[] = {
  {"256GB SSD", 34.50},
  {"512GB SSD", 59.99},
  {"1TB SSD", 99.99},
  {"2TB SSD", 179.50},
};

Component PSUList[] = {
  {"400W PSU", 44.99},
  {"550W PSU", 69.50},
  {"750W PSU", 99.99},
  {"850W PSU", 129.99},
};

Component CaseList[] = {
  {"Budget ATX Case", 49.99},
  {"Mid-Range Mid-Tower Case", 89.50},
  {"Premium Full Tower Case", 179.99},
};

Component CoolerList[] = {
  {"Basic Air Cooler", 24.99},
  {"Mid-Range Air Cooler", 59.99},
  {"High-End Air Cooler", 119.50},
  {"240mm AIO Liquid Cooler", 149.99},
};

// Vectors
map<string, vector<PlrInv>> inventory;

vector<PlrBuilds> PlrBuild;
vector<string> partNames = {"CPU", "GPU", "RAM", "Mobo", "SSD", "PSU", "Case", "Cooler"};

// Currency
double cash;

// String Functions
int IntInputCheck(){
  int value;

  while (true){
    cin >> value;
    if (cin.fail()){
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid input! Please enter a number: ";
    } else {
      return value;
    }
  }
}

string hideStringASCII(const string &s) {
    string hidden = "";
    for (char c : s) {
        if (c == ' ') hidden += ' ';
        else hidden += '#';
    }
    return hidden;
}

void underline(){
  cout << "------------------------------\n";
}

// INVENTORY
void SaveInv(){
  ofstream invFile("Inventory.txt");
  if (!invFile.is_open()) {
    cout << "Inventory file not found!\n";
    return;
  }

  for (const auto &pair : inventory){
    const string &partType = pair.first;
    const vector<PlrInv> &items = pair.second;

    for (const auto &item : items) {
      invFile << partType << "," << item.name << "," << item.price << "\n";
    }
  }
  // for (int i = 0; i < InvCPU.size(); i++) {
  //     invFile << "CPU," << InvCPU[i].name << "," << InvCPU[i].price << '\n';
  // }
  // for (int i = 0; i < InvGPU.size(); i++) {
  //     invFile << "GPU," << InvGPU[i].name << "," << InvGPU[i].price << '\n';
  // }
  // for (int i = 0; i < InvRAM.size(); i++) {
  //     invFile << "RAM," << InvRAM[i].name << "," << InvRAM[i].price << '\n';
  // }
  // for (int i = 0; i < InvMobo.size(); i++) {
  //     invFile << "Mobo," << InvMobo[i].name << "," << InvMobo[i].price << '\n';
  // }
  // for (int i = 0; i < InvSSD.size(); i++) {
  //     invFile << "SSD," << InvSSD[i].name << "," << InvSSD[i].price << '\n';
  // }
  // for (int i = 0; i < InvPSU.size(); i++) {
  //     invFile << "PSU," << InvPSU[i].name << "," << InvPSU[i].price << '\n';
  // }
  // for (int i = 0; i < InvCase.size(); i++) {
  //     invFile << "Case," << InvCase[i].name << "," << InvCase[i].price << '\n';
  // }
  // for (int i = 0; i < InvCooler.size(); i++) {
  //     invFile << "Cooler," << InvCooler[i].name << "," << InvCooler[i].price << '\n';
  // }

  invFile.close();
  cout << "Inventory saved successfully!\n";
}

void LoadInv(){
  ifstream invFile("Inventory.txt");
  if (!invFile.is_open()) {
    cout << "Inventory file not found!\n";
    return;
  }

  inventory.clear();
  // InvCPU.clear();
  // InvGPU.clear();
  // InvRAM.clear();
  // InvMobo.clear();
  // InvSSD.clear();
  // InvPSU.clear();
  // InvCase.clear();
  // InvCooler.clear();

  string line;
  while (getline(invFile, line)) {
    stringstream ss(line);
    string partType, name, priceStr;

    getline(ss, partType, ',');
    getline(ss, name, ',');
    getline(ss, priceStr);

    if (partType.empty() || name.empty() || priceStr.empty()){
    continue;
    }

    double price = stod(priceStr);

    PlrInv item = {partType, name, price};

    inventory[partType].push_back(item);
    // if (partType == "CPU"){
    //   InvCPU.push_back(item);
    // } else if (partType == "GPU"){
    //   InvGPU.push_back(item);
    // } else if (partType == "RAM"){
    //   InvRAM.push_back(item);
    // } else if (partType == "Mobo"){
    //   InvMobo.push_back(item);
    // } else if (partType == "SSD"){
    //   InvSSD.push_back(item);
    // } else if (partType == "PSU"){
    //   InvPSU.push_back(item);
    // } else if (partType == "Case"){
    //   InvCase.push_back(item);
    // } else if (partType == "Cooler"){
    //   InvCooler.push_back(item);
    // }
  }

  invFile.close();
  cout << "Inventory loaded successfully!\n";
}

// BUILDS
void SaveBuilds(){
  ofstream buildFile("Builds.txt");
  if (!buildFile.is_open()) {
    cout << "Build file not found!\n";
    return;
  }

  for (auto &build: PlrBuild){
    buildFile << build.name << ",";
    for (int i=0; i<build.parts.size(); i++){
      buildFile << build.parts[i].partType << "|" << build.parts[i].name << "|" << build.parts[i].price;

      if (i != build.parts.size()-1){
        buildFile << ";";
      }
    }
    buildFile << "," << build.totalPrice << "\n";
  }

  buildFile.close();
  cout << "Builds saved successfully!\n";
}

void LoadBuilds(){
  ifstream buildFile("Builds.txt");
  if (!buildFile.is_open()) {
    cout << "Build file not found!\n";
    return;
  }

  PlrBuild.clear();

  string line;
  while (getline(buildFile, line)) {
    stringstream ss(line);
    string name, partsStr, totalPriceStr;

    getline(ss, name, ',');
    getline(ss, partsStr, ',');
    getline(ss, totalPriceStr);

    double totalPrice = stod(totalPriceStr);

    vector<PlrInv> parts;
    stringstream partsSS(partsStr);
    string p;
    while (getline(partsSS, p, ';')){
        stringstream ps(p);
        string type, pname, pprice;
        getline(ps, type, '|'); getline(ps, pname, '|'); getline(ps, pprice, '|');
        parts.push_back({type,pname,stod(pprice)});
    }

    PlrBuild.push_back({name, parts, totalPrice});
  }

  buildFile.close();
  cout << "Builds loaded successfully!\n";
}

// PLR DATA
void SaveData(){
  ofstream dataFile("Data.txt");
  if (!dataFile.is_open()) {
    cout << "Data file not found!\n";
    return;
  }

  dataFile << isTutorial << " " << tutorialMainSteps << " " << tutorialBuySteps << " "  << fixed << setprecision(2) << cash;

  dataFile.close();
  cout << "Data saved successfully!\n";
}

void LoadData(){
  ifstream dataFile("Data.txt");
  if (!dataFile.is_open()){
    cout << "Data file not found - Default settings applied\n";
    isTutorial = true;
    tutorialMainSteps = 1;
    tutorialBuySteps = 1;
    cash = 1000.00;
    return;
  }

  if (!(dataFile >> isTutorial >> tutorialMainSteps >> tutorialBuySteps >> cash)){
    cout << "Creating new data file - Default settings applied\n";
    isTutorial = true;
    tutorialMainSteps = 1;
    tutorialBuySteps = 1;
    cash = 1000.00;
    return;
  }

  dataFile.close();
  cout << "Data loaded successfully!\n";
}

// BUY MENU
int SelectBuyComponent(Component list[], int size, const string &part){
  int choice;

  while (true){
    cout << part << " LIST\n";
    underline();

    for (int i=0; i<size; i++){
      if (isTutorial){
        if (i==0){
          cout << i+1 << " " << list[i].name << " - $" << list[i].price << '\n';
        } else {
          cout << hideStringASCII(to_string(i+1) + " " + list[i].name + " - $" + to_string(list[i].price))<< '\n';
        }
      } else {
        cout << i+1 << " " << list[i].name << " - $" << list[i].price << '\n';
      }
    }
    
    if (isTutorial){
      cout << "Select a " << part << ": ";
    } else {
      cout << size+1 << " Back\n";
      cout << "Select a " << part << " (or Back): ";
    }
    choice = IntInputCheck();
    cout << '\n';
    
    if (isTutorial){
      if (choice!=1){
        cout << "Choose \"1\" to continue the tutorial\n\n";
        continue;
      } else {
        break;
      }
    } else {
      if (choice<1 || choice>size+1){
        cout << "Invalid choice! Input a number between 1-" << size+1 << "\n\n";
        continue;
      } else {
        break;
      }
    }
  }

  return choice;
}

void BuyComponent(Component list[], int size, const string &part){
  int BuyChoice = SelectBuyComponent(list, size, part);
  if (BuyChoice == 0) return;

  if (BuyChoice >= 1 && BuyChoice <= size){
    PlrInv boughtItem = {part, list[BuyChoice-1].name, list[BuyChoice-1].price};

    if (cash >= boughtItem.price){
      inventory[part].push_back(boughtItem);
      cout << "You bought " << boughtItem.name << '\n';
      cash -= boughtItem.price;
      cout << "Your total cash is now $" << cash << '\n';

      SaveInv();
      SaveData();
      cout << '\n';
    } else {
      cout << "Insufficient balance\n\n";
    }
  }
}

void BuyMenu(){
  int BuyChoice;
  
  while (true){
    cout << "Buy Menu\n";
    underline();
    for (int i=0; i<partNames.size(); i++){
      if (!isTutorial){
        cout << i+1 << " " << partNames[i] << '\n';
      } else {
        if (i+1 <= tutorialBuySteps){
          cout << i+1 << " " << partNames[i] << '\n';
        } else {
          cout << i+1 << " " << hideStringASCII(partNames[i]) << '\n';
        }
      }
    }

    if (!isTutorial){
      cout << partNames.size()+1 << " Back\n";
    }

    cout << "Choose 1 of the following above: ";
    BuyChoice = IntInputCheck();
    cout << '\n';

    if (isTutorial){
      if (BuyChoice != tutorialBuySteps){
        cout << "Choose \"" << tutorialBuySteps << "\" to continue the tutorial\n\n";
        continue;
      }
    }  

    switch (BuyChoice){
      case 1: BuyComponent(CPUList, sizeof(CPUList)/sizeof(CPUList[0]), "CPU"); break;
      case 2: BuyComponent(GPUList, sizeof(GPUList)/sizeof(GPUList[0]), "GPU"); break;
      case 3: BuyComponent(RAMList, sizeof(RAMList)/sizeof(RAMList[0]), "RAM"); break;
      case 4: BuyComponent(MoboList, sizeof(MoboList)/sizeof(MoboList[0]), "Mobo"); break;
      case 5: BuyComponent(SSDList, sizeof(SSDList)/sizeof(SSDList[0]), "SSD"); break;
      case 6: BuyComponent(PSUList, sizeof(PSUList)/sizeof(PSUList[0]), "PSU"); break;
      case 7: BuyComponent(CaseList, sizeof(CaseList)/sizeof(CaseList[0]), "Case"); break;
      case 8: BuyComponent(CoolerList, sizeof(CoolerList)/sizeof(CoolerList[0]), "Cooler"); break;
      case 9: return;
      default: cout << "Invalid choice! Input a number between 1-9!\n\n"; break;
    }

    if (isTutorial && BuyChoice == tutorialBuySteps) {  
      tutorialBuySteps++;
      SaveData();
      cout << "\n";
    }

    if (isTutorial && tutorialBuySteps == 9){
      cout << "Great job! Now that you gathered all the parts, you can start building your very first own PC!\n";
      return;
    }
  }
}

// BUILD MENU
int SelectBuildComponent(const string &part){
  if (inventory[part].empty()){
    cout << "No " << part << " is in your inventory\n";
    cout << "Go buy more " << part << " to continue building\n\n";
    return -1;
  }

  while (true){
    cout << part << " LIST\n";
    underline();
    
    for (int i=0; i<inventory[part].size(); i++){
      cout << i+1 << " " << inventory[part][i].name << " - $" << inventory[part][i].price << '\n';
    }

    int choice;
    if (isTutorial){
      cout << "Select a " << part << ": ";
    } else {
      cout << inventory[part].size()+1 << " Back\n";
      cout << "Select a " << part << " (or Back): ";
    }
    choice = IntInputCheck();
    cout << '\n';

    if (!isTutorial && choice == inventory[part].size() + 1){
      return 0;
    }

    if (choice >= 1 && choice <= inventory[part].size()){
      return choice;
    }

    if (isTutorial){
      cout << "Choose \"1\" to continue the tutorial";
    } else {
      cout << "Invalid choice! Input a number between 1-" << inventory[part].size()+1;
    }
    cout << "\n\n";
  }
}

void BuildMenu(){
  vector<PlrInv> selectedParts;
  int currentPart = 0;

  cout << "Build Menu\n";
  underline();

  while (currentPart < partNames.size()){
    int choice = SelectBuildComponent(partNames[currentPart]);

    if (choice == -1){
      return;
    }

    if (choice == 0){
      if (currentPart == 0){
        return;
      }

      currentPart --;
      selectedParts.pop_back();
      continue;
    }

    selectedParts.push_back(inventory[partNames[currentPart]][choice-1]);
    currentPart ++;
  }

  // All parts selected
  string buildName;
  cout << "Name your build: ";
  cin.ignore();
  getline(cin, buildName);
  cout << '\n';

  double totalPrice = 0.00;

  for (auto &part : selectedParts){
    totalPrice += part.price;
  }

  PlrBuilds newBuild = {buildName, selectedParts, totalPrice};
  PlrBuild.push_back(newBuild);

  for (auto &part : selectedParts){
    auto &inv = inventory[part.partType];

    for (int i=0; i<inv.size(); i++){
      if (inv[i].name == part.name){
        inv.erase(inv.begin() + i);
        break;
      }
    }
  }

  SaveInv();
  SaveBuilds();
  cout << '\n';

  cout << "Build created successfully!\n";
  cout << "Build Name: " << buildName << '\n';
  for (auto &part : selectedParts) {
    cout << part.partType << ": " << part.name << " - $" << part.price << '\n';
  }
  cout << "Total Price: $" << totalPrice << '\n';

  if (isTutorial && tutorialMainSteps == 2){
    cout << '\n';
    cout << "Great job! You build your 1st PC, now sell it :D\n";
    return;
  }

  cout << '\n';
}

// SELL & MY BUILDS MENU
void SellBuild(int index){
  PlrBuilds selectedBuild = PlrBuild[index];
  double sellPrice = selectedBuild.totalPrice/2;
  cash += sellPrice;
  cout << "You sold \"" << selectedBuild.name << "\" for $" << sellPrice << '\n';
  cout << "You're total cash is now $" << cash << '\n';

  PlrBuild.erase(PlrBuild.begin() + index);
  
  SaveBuilds();
  SaveData();
  cout << '\n';
}

void SellPart(vector<PlrInv> &partList, int index){
  PlrInv selectedPart = partList[index];
  double sellPrice = selectedPart.price/2;
  cash += sellPrice;
  cout << "You sold \"" << selectedPart.name << "\" for $" << sellPrice << '\n';
  cout << "You're total cash is now $" << cash << '\n';

  partList.erase(partList.begin() + index);
  
  SaveInv();
  SaveData();
  cout << '\n';
}

void SelectSellPart(const string &partType){
  vector<PlrInv> &partList = inventory[partType];

  if (partList.empty()) {
    cout << "No " << partType << " is found in your inventory.\n\n";
    return;
  }

  while (true){
    cout << "MY " << partType << " (s)\n";
    underline();

    for (int i=0; i<partList.size(); i++) {
      cout << i+1 << " " << partList[i].name << " - $" << partList[i].price << '\n';
    }
    cout << partList.size()+1 << " Back\n";

    cout << "Select a part to sell (or Back): ";
    int choice = IntInputCheck();
    cout << '\n';

    if (choice == partList.size()+1){
      break;
    }

    if (choice < 1 || choice > partList.size()){
      cout << "Invalid choice! Input a number between 1-" << partList.size()+1 << "\n\n";
      continue;
    }

    SellPart(partList, choice-1);

    if (partList.empty()){
      cout << "No more " << partType << " left.\n\n";
      break;
    }
  }
}

void SellPartsMenu(){
  bool empty = true;

  for (auto &pair : inventory){
    if (!pair.second.empty()){
      empty = false;
      break;
    }
  }

  if (empty){
    cout << "No parts are found in your inventory\n";
    cout << "Go buy more parts\n\n";
    return;
  }

  while (true){
    cout << "SELL PARTS\n";
    underline();

    for (int i=0; i<partNames.size(); i++){
      cout << i+1 << " " << partNames[i] << '\n';
    }

    cout << "9 Back\n";
    cout << "Select an option (or Back): ";
    int choice = IntInputCheck();
    cout << '\n';

    if (choice == partNames.size()+1){
      return;
    }

    if (choice < 1 || choice > partNames.size()){
      cout << "Invalid choice! Input a number between 1-" << partNames.size()+1 << "\n\n";
      continue;
    }

    SelectSellPart(partNames[choice-1]);
  }
}

void ViewBuildParts(int index, bool sellOnly){
  int choice;

  cout << "Parts in \"" << PlrBuild[index].name << "\":\n";
  underline();
  for (auto &part : PlrBuild[index].parts){
    cout << part.partType << ": " << part.name << " - $" << part.price << '\n';
  }
  cout << "Total Value: $" << PlrBuild[index].totalPrice << '\n';
  cout << "Sell Price: $" << PlrBuild[index].totalPrice / 2 << "\n\n";

  if (!sellOnly){
    cout << "Type any number to go back: ";
    choice = IntInputCheck();
    cout << '\n';
  }
}

void RenameBuild(int index){
  cout << "Current build name: " << PlrBuild[index].name << '\n';
  cout << "Enter new name for your build: ";
  cin.ignore();
  string newName;
  getline(cin, newName);

  if(newName.empty()){
    cout << "Name cannot be empty! Build name unchanged\n\n";
    return;
  }

  PlrBuild[index].name = newName;
  SaveBuilds();

  cout << "Build renamed successfully! New name: " << PlrBuild[index].name << "\n\n";
}

void SelectBuild(int index, bool sellOnly){
  while (true){
    if (sellOnly){
      ViewBuildParts(index, true);
      if (isTutorial){
        cout << "1 Sell Build\n";
        cout << "Select an option: ";
      } else {
        cout << "1 Sell Build\n";
        cout << "2 Back\n";
        cout << "Select an option (or Back): ";
      }
    } else {
      cout << PlrBuild[index].name << '\n';
      underline();
      cout << "1 View Parts\n";
      cout << "2 Rename Build\n";
      cout << "3 Sell Build\n";
      cout << "4 Back\n";
      cout << "Select an option (or Back): ";
    }

    int choice = IntInputCheck();
    cout << '\n';

    if (isTutorial && choice!= 1){
      cout << "Choose \"1\" to continue the tutorial\n\n";
      continue;
    }

    if (sellOnly){
      if (choice==1){
        SellBuild(index);
        if (isTutorial && tutorialMainSteps == 3){
          cout << "Great job! You sold your first PC!\n";
          cout << "Now you can earn money by working or gambling!\n\n";
        }
        return;
      } else if (choice==2){
        return;
      } else {
        cout << "Invalid choice! Input a number between 1-2\n\n";
      }
    } else {
      if (choice==1){
        ViewBuildParts(index, false);
      } else if (choice==2){
        RenameBuild(index);
      } else if (choice==3){
        SellBuild(index);
        return;
      } else if (choice==4){
        return;
      } else {
        cout << "Invalid choice! Input a number between 1-4\n\n";
      }
    }
  }
}

int MyBuildsMenu(bool sellOnly){
  while (true){
    if (PlrBuild.empty()){
      cout << "No builds are found in your inventory\n";
      cout << "Go build more PCs by buying parts\n\n";
      return 0;
    }
    
    cout << "MY BUILDS\n";
    underline();

    for (int i=0; i<PlrBuild.size(); i++){
      cout << i+1 << " " << PlrBuild[i].name << " - $" << PlrBuild[i].totalPrice << '\n';
    }

    int choice;
    if (isTutorial){
      cout << "Select a build to view: ";
    } else {
      cout << PlrBuild.size()+1 << " Back\n";
      cout << "Select a build to view (or Back): ";
    }
    choice = IntInputCheck();
    cout << '\n';

    if (isTutorial && choice!= 1){
      cout << "Choose \"1\" to continue the tutorial\n\n";
      continue;
    }

    if (!isTutorial && choice == PlrBuild.size() + 1){
      return 0;
    }

    if (choice >= 1 && choice <= PlrBuild.size()){
      if (sellOnly){
        SelectBuild(choice-1, true);
        if (isTutorial & tutorialMainSteps == 3){
          return 0;
        }
      } else {
        SelectBuild(choice-1, false);
      }
    } else {
      cout << "Invalid choice! Input a number between 1-" << PlrBuild.size()+1 << "\n\n";
    }
  }
}

void SellMenu(){
  while (true){
    cout << "Sell Menu\n";
    underline();
    cout << "1 Sell Builds\n";

    if (isTutorial){
      cout << hideStringASCII("2 Sell Parts") << '\n';
      cout << hideStringASCII("3 Back") << '\n';
      cout << "Select an option: ";
    } else {
      cout << "2 Sell Parts\n";
      cout << "3 Back\n";
      cout << "Select an option (or Back): ";
    }

    int choice = IntInputCheck();
    cout << '\n';

    if (isTutorial && choice!= 1){
      cout << "Choose \"1\" to continue the tutorial\n\n";
      continue;
    }

    if (choice==1){
      MyBuildsMenu(true);
      if (isTutorial & tutorialMainSteps == 3){
        return;
      }
    } else if (!isTutorial && choice==2){
      SellPartsMenu();
    } else if (!isTutorial && choice==3){
      return;
    } else {
      cout << "Invalid choice! Input a number between 1-3\n\n";
    }
  }
}

// EARN MONEY MENU
double Work(){
  int randNum = (rand() % 100) + 1;
  return randNum;
}

double Gamble(){
  int randNum = (rand() % 100) + 1;
  int randSymbol = (rand() % 3) + 1;
  int num;

  if (randSymbol == 1){
    num = randNum;
  } else if (randSymbol == 2){
    num = -randNum;
  } else if (randSymbol == 3){
    num = 0;
  }

  return num;
}

void EarnMoneyMenu(){
  int choice;
  double cashEarned;

  while (true){
    cout << "Earn Money Menu\n";
    underline();
    cout << "1 Work\n";
    cout << "2 Gamble\n";
    if (isTutorial){
      cout << "Choose 1 of the following above: ";
    } else {
      cout << "3 Back\n";
      cout << "Choose 1 of the following above (or Back): ";
    }
    choice = IntInputCheck();
    cout << '\n';

    if (isTutorial){
      if (choice!=1 && choice!=2){
        cout << "Choose \"1\" or \"2\" to continue the tutorial\n\n";
        continue;
      }
    }

    switch (choice){
      case 1: cashEarned = Work(); break;
      case 2: cashEarned = Gamble(); break;
      case 3: if(!isTutorial){return;} break;
      default: cout << "Invalid choice! Input a number between 1-3!\n\n"; continue; break;
    }

    if (cashEarned > 0){
      cout << "You earned $" << cashEarned << '\n';
    } else if (cashEarned < 0){
      cout << "You lost $" << abs(cashEarned) << '\n';
    } else {
      cout << "You earned nothing" << '\n';
    }

    cash += cashEarned;
    cout << "You're total cash is now $" << cash << '\n';
    SaveData();
    cout << '\n';

    if (isTutorial){
      if (choice==1){
        cout << "Great job! You earned your first cash!\n\n";
      } else if(choice==2){
        if (cashEarned>0){
          cout << "You gambled and won? Damn risk taker!\n\n";
        } else if (cashEarned<0){
          cout << "You gambled? See, you lost money :<\n\n";
        } else if (cashEarned==0){
          cout << "You gambled? You're lucky it's 0 this time\n\n";
        }
      }
      return;
    }
  }
}

// VIEW MENU
void ViewInvParts(string partType){
  while (true){
    vector<PlrInv> &partList = inventory[partType];

    if (partList.empty()){
      cout << "You don't own any " << partType << "\n\n";
      return;
    }

    cout << partType << " LIST\n";
    underline();

    for (int i = 0; i < partList.size(); i++){
      cout << i+1 << " " << partList[i].name << " - $" << partList[i].price << '\n';
    }

    cout << partList.size()+1 << " Back\n";
    cout << "Select a part to view (or Back): ";
    int choice = IntInputCheck();
    cout << '\n';

    if (choice == partList.size()+1){
      return;
    }

    if (choice < 1 || choice > partList.size()){
      cout << "Invalid choice! Please input a number between 1-" << partList.size()+1 << "\n\n";
      continue;
    }

    while (true){
      PlrInv &selectedPart = partList[choice-1];

      cout << "Type: " << selectedPart.partType << '\n';
      cout << "Name: " << selectedPart.name << '\n';
      cout << "Value: $" << selectedPart.price << '\n';
      cout << "Sell Price: $" << selectedPart.price/2 << "\n\n";

      cout << "1 Sell Part\n";
      cout << "2 Back\n";
      cout << "Select an option (or Back): ";
      int choice2 = IntInputCheck();
      cout << '\n';

      switch (choice2){
        case 1: SellPart(partList, choice-1); goto back_to_list; break;
        case 2: goto back_to_list; break;
        default: cout << "Invalid choice! Please input a number between 1-2\n\n"; continue; break;
      }
    }

    back_to_list:;
  }
}

void MyPartsMenu(){
  while (true){
    bool empty = true;

    for (auto &pair : inventory){
      if (!pair.second.empty()){
        empty = false;
        break;
      }
    }

    if (empty){
      cout << "No parts are found in your inventory\n";
      cout << "Go buy more parts\n\n";
      return;
    }

    cout << "MY PARTS\n";
    underline();

    for (int i=0; i<partNames.size(); i++){
      cout << i+1 << " " << partNames[i] << '\n';
    }

    cout << "9 Back\n";
    cout << "Select a part to view (or Back): ";
    int choice = IntInputCheck();
    cout << '\n';

    if (choice == partNames.size()+1){
      return;
    }

    if (choice < 1 || choice > partNames.size()){
      cout << "Invalid choice! Input a number between 1-" << partNames.size()+1 << "\n\n";
      continue;
    }

    ViewInvParts(partNames[choice-1]);
  }
}

void ViewMenu(){
  while (true){
    cout << "View Menu\n";
    underline();

    cout << "1 View Builds\n";
    cout << "2 View Parts\n";
    cout << "3 Back\n";
    cout << "Choose an option (or Back): ";
    int choice = IntInputCheck();
    cout << '\n';

    switch (choice){
      case 1: MyBuildsMenu(false); break;
      case 2: MyPartsMenu(); break;
      case 3: return; break;
      default: cout << "Invalid choice! Input a number between 1-3!\n\n"; continue; break;
    }
  }
}

// MAIN MENU
void MainMenu(){
  int MainMenuChoice;
  bool isRunning = true;

  while (isRunning){
    cout << "PC Building Simulator\n";
    underline();
    cout << "1 Buy\n";
    cout << "2 Build\n";
    cout << "3 Sell\n";
    cout << "4 View\n";
    cout << "5 Earn Money\n";
    cout << "6 Exit\n";
    cout << "Total Cash: $" << cash << '\n';
    cout << "Choose 1 of the following above: ";
    MainMenuChoice = IntInputCheck();
    cout << '\n';

    switch (MainMenuChoice){
      case 1: BuyMenu(); break;
      case 2: BuildMenu(); break;
      case 3: SellMenu(); break;
      case 4: ViewMenu(); break;
      case 5: EarnMoneyMenu(); break;
      case 6: SaveData(); isRunning = false; break;
      default: cout << "Invalid choice! \n\n"; break;
    }
  }
}

// TUTORIAL //
void Tutorial(){
  isTutorial = true;
  SaveData();
  cout << "\n";

  int choice;

  cout << "Welcome to PC Building Simulator!\n";
  cout << "This tutorial will guide you on how to play the game\n\n";

  // Step 1: Buy
  while (isTutorial && tutorialMainSteps <= 4){
    cout << "Step " << tutorialMainSteps << ": ";

    switch (tutorialMainSteps) {
      case 1: cout << "Buy A Part\n"; break;
      case 2: cout << "Build Your 1st PC\n"; break;
      case 3: cout << "Sell Your PC\n"; break;
      case 4: cout << "Earn Money\n"; break;
    }

    underline();

    cout << "1 Buy\n";
    cout << (tutorialMainSteps >= 2 ? "2 Build\n" : hideStringASCII("2 Build") + "\n");
    cout << (tutorialMainSteps >= 3 ? "3 Sell\n" : hideStringASCII("3 Sell") + "\n");
    cout << (tutorialMainSteps >= 4 ? "4 Earn Money\n" : hideStringASCII("4 Earn Money") + "\n");
    cout << "5 Exit\n";
    cout << "6 Skip Tutorial\n";
    cout << "Total Cash: $" << cash << '\n';
    cout << "Choose 1 of the following above: ";
    choice = IntInputCheck();
    cout << '\n';

    if (choice == 5){
      SaveData();
      exit(0);
    }

    if (choice == 6){
      isTutorial = false;
      SaveData();
      cout << '\n'; 
      MainMenu();
      return;
    }

    if (choice == tutorialMainSteps) {
      switch (choice) {
        case 1: BuyMenu(); break;
        case 2: BuildMenu(); break;
        case 3: SellMenu(); break;
        case 4: EarnMoneyMenu(); break;
      }

      tutorialMainSteps++;
      SaveData();
      cout << "\n";
    } else {
      cout << "Choose \"" << tutorialMainSteps << "\" to continue the tutorial\n\n";
    }
  }

  // Step 5: FINISH
  if (tutorialMainSteps == 5){
    cout << "Tutorial complete! Enjoy the game :D\n";
    isTutorial = false;
    SaveData();
    cout << '\n';
    MainMenu();
  }
}

// MAIN //
int main(){
  srand(time(NULL));
  cout << fixed << setprecision(2);

  inventory["CPU"];
  inventory["GPU"];
  inventory["RAM"];
  inventory["Mobo"];
  inventory["SSD"];
  inventory["PSU"];
  inventory["Case"];
  inventory["Cooler"];

  cout << "Loading game...\n";
  LoadInv();
  LoadBuilds();
  LoadData();

  if (isTutorial == true){
    Tutorial();
  } else {
    cout << '\n';
    MainMenu();
  }
}