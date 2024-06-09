/*                             .__    .__         .__                             __   
   ____   ____   ____   _____|  |__ |__| ____   |__| _____ ___________    _____/  |_ 
  / ___\_/ __ \ /    \ /  ___/  |  \|  |/    \  |  |/     \\____ \__  \ _/ ___\   __\
 / /_/  >  ___/|   |  \\___ \|   Y  \  |   |  \ |  |  Y Y  \  |_> > __ \\  \___|  |  
 \___  / \___  >___|  /____  >___|  /__|___|  / |__|__|_|  /   __(____  /\___  >__|  
/_____/      \/     \/     \/     \/        \/           \/|__|       \/     \/      
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stack>

using namespace std;

class Character {
public:
    string name;
    int hp;
    int attack;
    string city;

    Character(const string& name, int hp, int attack, const string& city)
        : name(name), hp(hp), attack(attack), city(city) {}
};

class Item {
public:
    string name;
    string stat;
    int value;

    Item(const string& name, const string& stat, int value) : name(name), stat(stat), value(value) {}
};

class NPC {
public:
    string name;
    string city;

    NPC(const string& name, const string& city) : name(name), city(city) {}

    virtual void printInfo() const = 0;
    virtual ~NPC() = default;
};

class Enemy : public NPC {
public:
    int hp;
    int attack;

    Enemy(const string& name, const string& city, int hp, int attack)
        : NPC(name, city), hp(hp), attack(attack) {}

    void printInfo() const override {
        cout << name << " (" << city << ")\n";
        cout << "HP: " << hp << "\tAttack: " << attack << endl;
    }
};

class Trader : public NPC {
public:
    vector<Item> items;

    Trader(const string& name, const string& city) : NPC(name, city) {}

    void addItem(const string& itemName, const string& stat, int value) {
        items.emplace_back(itemName, stat, value);
    }

    void printInfo() const override {
        cout << "NPC: " << name << " (" << city << ")\n";
        cout << "Barang Dijual:\n";
        for (const auto& item : items) {
            cout << item.name << "\nStat: " << item.stat << " (" << item.value << ")\n";
        }
    }
};

class NPCManager {
public:
    unordered_map<string, vector<NPC*>> cityNPCs;

    void addEnemy(const string& name, const string& city, int hp, int attack) {
        cityNPCs[city].push_back(new Enemy(name, city, hp, attack));
    }

    void addTrader(const string& name, const string& city, const vector<Item>& items) {
        Trader* trader = new Trader(name, city);
        for (const auto& item : items) {
            trader->addItem(item.name, item.stat, item.value);
        }
        cityNPCs[city].push_back(trader);
    }

    const vector<NPC*>& getNPCs(const string& city) const {
        auto it = cityNPCs.find(city);
        if (it != cityNPCs.end()) {
            return it->second;
        }
        static vector<NPC*> empty;
        return empty;
    }

    ~NPCManager() {
        for (auto& city : cityNPCs) {
            for (auto& npc : city.second) {
                delete npc;
            }
        }
    }
};

NPCManager manager;

// Normalizes city names to have the first letter of each word capitalized
string normalizeCityName(const string& name) {
    stringstream ss(name);
    string token, normalized;
    while (getline(ss, token, ' ')) {
        if (!token.empty()) {
            token[0] = toupper(token[0]);  // Capitalize the first letter
            for (size_t i = 1; i < token.length(); ++i) {
                token[i] = tolower(token[i]);  // Make other letters lowercase
            }
            if (!normalized.empty()) {
                normalized += " ";  // Add space before next word
            }
            normalized += token;
        }
    }
    return normalized;
}

// Abstraction - Base class for graphs
class BaseGraph {
protected:
    unordered_map<string, vector<pair<string, int>>> adjList;
    unordered_map<string, vector<Character>> cityCharacters;

public:
    virtual void addEdge(const string& city1, const string& city2, int distance) = 0;
    virtual void printGraph() const = 0;
    virtual void editEdge(const string& city1, const string& city2, int newDistance) = 0;
    virtual void deleteEdge(const string& city1, const string& city2) = 0;
    virtual void addCharacter(const string& city, const Character& character) = 0;

    // Getter for adjList
    const unordered_map<string, vector<pair<string, int>>>& getAdjList() const {
        return adjList;
    }

    const unordered_map<string, vector<Character>>& getCityCharacters() const {
        return cityCharacters;
    }

    virtual ~BaseGraph() = default;

    // DFS Function
    void dfs(Character& character) const {
        string nStartCity = normalizeCityName(character.city);
        unordered_map<string, bool> visited;
        stack<string> stack;
        stack.push(nStartCity);

        while (!stack.empty()) {
            string city = stack.top();
            stack.pop();

            if (!visited[city]) {
                visited[city] = true;

                cout << "Visiting " << city << endl;
                const auto& npcs = manager.getNPCs(city);
                for (const auto& npc : npcs) {
                    npc->printInfo();
                }

                // Check for enemies in the city
                for (const auto& npc : npcs) {
                    if (Enemy* enemy = dynamic_cast<Enemy*>(npc)) {
                        // Battle logic
                        while (enemy->hp > 0 && character.hp > 0) {
                            // Character attacks first
                            enemy->hp -= character.attack;
                            cout << character.name << " attacks " << enemy->name << " for " << character.attack << " damage." << endl;
                            if (enemy->hp > 0) {
                                // Enemy attacks back
                                character.hp -= enemy->attack;
                                cout << enemy->name << " attacks " << character.name << " for " << enemy->attack << " damage." << endl;
                                if (character.hp <= 0) {
                                    cout << "You died" << endl;
                                    return;
                                }
                            } else {
                                cout << enemy->name << " died" << endl;
                            }
                        }
                    }
                }

                // Buying items from traders
                for (const auto& npc : npcs) {
                    if (Trader* trader = dynamic_cast<Trader*>(npc)) {
                        cout << "Would you like to buy something from " << trader->name << "? (yes/no): ";
                        string response;
                        cin >> response;
                        if (response == "yes") {
                            for (size_t i = 0; i < trader->items.size(); ++i) {
                                cout << i + 1 << ". " << trader->items[i].name << " - " << trader->items[i].stat << " (" << trader->items[i].value << ")\n";
                            }
                            cout << "Enter the number of the item you want to buy: ";
                            size_t itemIndex;
                            cin >> itemIndex;
                            if (itemIndex > 0 && itemIndex <= trader->items.size()) {
                                Item& item = trader->items[itemIndex - 1];
                                if (item.stat.find("HP") != string::npos) {
                                    character.hp += item.value;
                                } else if (item.stat.find("ATK") != string::npos) {
                                    character.attack += item.value;
                                }
                                cout << "You bought " << item.name << " and your stats have been updated.\n";
                            } else {
                                cout << "Invalid selection.\n";
                            }
                        }else if (response == "no"){
                            cout << "Okeee!";
                        }else{
                            cout << "Apasih lu gaje WIBU!\n";
                        }
                    }
                }

                // Push neighboring cities to the stack
                if (adjList.find(city) != adjList.end()) {
                    for (const auto& neighbor : adjList.at(city)) {
                        if (!visited[neighbor.first]) {
                            stack.push(neighbor.first);
                        }
                    }
                } else {
                    cout << "City " << city << " \nTidak ada jalan darat untuk keluar pulau.\n";
                }
            }
        }
    }
};

// Concrete class for Road Graph
class RoadGraph : public BaseGraph {
public:
    void addEdge(const string& city1, const string& city2, int distance) override {
        string nCity1 = normalizeCityName(city1);
        string nCity2 = normalizeCityName(city2);
        adjList[nCity1].emplace_back(nCity2, distance);
        adjList[nCity2].emplace_back(nCity1, distance);
    }

    void editEdge(const string& city1, const string& city2, int newDistance) override {
        string nCity1 = normalizeCityName(city1);
        string nCity2 = normalizeCityName(city2);
        for (auto& neighbor : adjList[nCity1]) {
            if (neighbor.first == nCity2) {
                neighbor.second = newDistance;
                break;
            }
        }
        for (auto& neighbor : adjList[nCity2]) {
            if (neighbor.first == nCity1) {
                neighbor.second = newDistance;
                break;
            }
        }
    }

    void deleteEdge(const string& city1, const string& city2) override {
        string nCity1 = normalizeCityName(city1);
        string nCity2 = normalizeCityName(city2);
        adjList[nCity1].erase(remove_if(adjList[nCity1].begin(), adjList[nCity1].end(),
            [&nCity2](const pair<string, int>& neighbor) { return neighbor.first == nCity2; }),
            adjList[nCity1].end());
        
        adjList[nCity2].erase(remove_if(adjList[nCity2].begin(), adjList[nCity2].end(),
            [&nCity1](const pair<string, int>& neighbor) { return neighbor.first == nCity1; }),
            adjList[nCity2].end());
    }

    void addCharacter(const string& city, const Character& character) override {
        string nCity = normalizeCityName(city);
        cityCharacters[nCity].push_back(character);
    }

    void printGraph() const override {
        cout << "\nRoad Connections:\n";  // Added newline before Road Connections
        for (const auto& city : adjList) {
            cout << setw(15) << left << city.first << " -> ";
            for (const auto& neighbor : city.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << " km) ";
            }
            cout << endl;
        }
        cout << endl;  // Added newline after Road Connections
    }
};

// Concrete class for Sea Route Graph
class SeaRouteGraph : public BaseGraph {
public:
    void addEdge(const string& city1, const string& city2, int distance) override {
        string nCity1 = normalizeCityName(city1);
        string nCity2 = normalizeCityName(city2);
        adjList[nCity1].emplace_back(nCity2, distance);
        adjList[nCity2].emplace_back(nCity1, distance);
    }

    void editEdge(const string& city1, const string& city2, int newDistance) override {
        string nCity1 = normalizeCityName(city1);
        string nCity2 = normalizeCityName(city2);
        for (auto& neighbor : adjList[nCity1]) {
            if (neighbor.first == nCity2) {
                neighbor.second = newDistance;
                break;
            }
        }
        for (auto& neighbor : adjList[nCity2]) {
            if (neighbor.first == nCity1) {
                neighbor.second = newDistance;
                break;
            }
        }
    }

    void deleteEdge(const string& city1, const string& city2) override {
        string nCity1 = normalizeCityName(city1);
        string nCity2 = normalizeCityName(city2);
        adjList[nCity1].erase(remove_if(adjList[nCity1].begin(), adjList[nCity1].end(),
            [&nCity2](const pair<string, int>& neighbor) { return neighbor.first == nCity2; }),
            adjList[nCity1].end());
        
        adjList[nCity2].erase(remove_if(adjList[nCity2].begin(), adjList[nCity2].end(),
            [&nCity1](const pair<string, int>& neighbor) { return neighbor.first == nCity1; }),
            adjList[nCity2].end());
    }

    void addCharacter(const string& city, const Character& character) override {
        string nCity = normalizeCityName(city);
        cityCharacters[nCity].push_back(character);
    }

    void printGraph() const override {
        cout << "Sea Route Connections:\n";
        for (const auto& city : adjList) {
            cout << setw(15) << left << city.first << " -> ";
            for (const auto& neighbor : city.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << " km) ";
            }
            cout << endl;
        }
        cout << endl;  // Added newline after Sea Route Connections
    }
};

// Function to use Dijkstra's algorithm (common for both RoadGraph and SeaRouteGraph)
int dijkstra(const BaseGraph& graph, const string& src, const string& dest) {
    auto adjList = graph.getAdjList();
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, int> dist;

    string nSrc = normalizeCityName(src);
    string nDest = normalizeCityName(dest);

    for (const auto& city : adjList) {
        dist[city.first] = INT_MAX;
    }
    dist[nSrc] = 0;

    pq.emplace(0, nSrc);

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        if (u == nDest) {
            return dist[u];
        }

        for (const auto& neighbor : adjList[u]) {
            string v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    return INT_MAX;  // If there's no path between src and dest
}

void calculateDistanceBetweenCities(BaseGraph* roadGraph, BaseGraph* seaRouteGraph) {
    string src, dest, type;
    cout << "Masukkan kota asal: ";
    cin.ignore();
    getline(cin, src);
    cout << "Masukkan kota tujuan: ";
    getline(cin, dest);
    cout << "Masukkan jenis jalur (jalan atau laut): ";
    cin >> type;

    src = normalizeCityName(src);
    dest = normalizeCityName(dest);

    int distance;
    if (type == "jalan") {
        distance = dijkstra(*roadGraph, src, dest);
    } else if (type == "laut") {
        distance = dijkstra(*seaRouteGraph, src, dest);
    } else {
        cout << "Jenis jalur tidak dikenal!" << endl;
        return;
    }

    if (distance == INT_MAX) {
        cout << "Tidak ada jalur yang menghubungkan " << src << " dan " << dest << endl;
    } else {
        cout << "Jarak dari " << src << " ke " << dest << " adalah " << distance << " km" << endl;
    }
}

void TambahJalan(BaseGraph* roadGraph, BaseGraph* seaRouteGraph) {
    // Adding edges to road graph
    roadGraph->addEdge("Sumeru", "Mondstadt", 4);
    roadGraph->addEdge("Sumeru", "Liyue", 2);
    roadGraph->addEdge("Sumeru", "Fontaine", 3);
    roadGraph->addEdge("Sumeru", "Snezhnaya", 6);
    roadGraph->addEdge("Mondstadt", "Liyue", 2);
    roadGraph->addEdge("Mondstadt", "Fontaine", 4);
    roadGraph->addEdge("Mondstadt", "Snezhnaya", 5);
    roadGraph->addEdge("Liyue", "Fontaine", 3);
    roadGraph->addEdge("Liyue", "Snezhnaya", 5);
    roadGraph->addEdge("Fontaine", "Snezhnaya", 3);

    // Adding edges to sea route graph
    seaRouteGraph->addEdge("Sumeru", "Inazuma", 5);
    seaRouteGraph->addEdge("Mondstadt", "Inazuma", 7);
    seaRouteGraph->addEdge("Liyue", "Inazuma", 6);
    seaRouteGraph->addEdge("Inazuma", "Fontaine", 7.5);
    seaRouteGraph->addEdge("Inazuma", "Snezhnaya", 8);
}

void TambahKarakter(BaseGraph* roadGraph, BaseGraph* seaRouteGraph) {
    // Adding characters to cities
    roadGraph->addCharacter("Sumeru", Character("Nilou", 255, 3364, "Sumeru"));
    roadGraph->addCharacter("Sumeru", Character("Cyno", 658, 4608, "Sumeru"));
    roadGraph->addCharacter("Snezhnaya", Character("Tartaglia (Childe)", 206, 1857, "Snezhnaya"));
    roadGraph->addCharacter("Mondstadt", Character("Diluc", 594, 4178, "Mondstadt"));
    roadGraph->addCharacter("Mondstadt", Character("Fischl", 918, 7134, "Mondstadt"));
    roadGraph->addCharacter("Liyue", Character("Ningguang", 769, 9013, "Liyue"));
    roadGraph->addCharacter("Liyue", Character("Qiqi", 292, 4946, "Liyue"));
    seaRouteGraph->addCharacter("Inazuma", Character("Kujou Sara", 429, 1615, "Inazuma"));
    seaRouteGraph->addCharacter("Inazuma", Character("Raiden Shogun", 647, 1058, "Inazuma"));
    roadGraph->addCharacter("Fontaine", Character("Neuvillette", 294, 4395, "Fontaine"));
    roadGraph->addCharacter("Fontaine", Character("Wriothesley", 564, 7634, "Fontaine"));
}

void addEdgeFromUserInput(BaseGraph* roadGraph, BaseGraph* seaRouteGraph) {
    string city1, city2, type;
    int distance;

    cout << "Masukkan nama kota pertama: ";
    cin.ignore();
    getline(cin, city1);
    cout << "Masukkan nama kota kedua: ";
    getline(cin, city2);
    cout << "Masukkan jarak antara kedua kota: ";
    cin >> distance;
    cout << "Masukkan jenis jalan (jalan atau laut): ";
    cin >> type;

    city1 = normalizeCityName(city1);
    city2 = normalizeCityName(city2);

    if (type == "jalan") {
        roadGraph->addEdge(city1, city2, distance);
    } else if (type == "laut") {
        seaRouteGraph->addEdge(city1, city2, distance);
    } else {
        cout << "Jenis jalan tidak dikenal!" << endl;
    }
}

void editEdgeFromUserInput(BaseGraph* roadGraph, BaseGraph* seaRouteGraph) {
    string city1, city2, type;
    int newDistance;

    cout << "Masukkan nama kota pertama: ";
    cin.ignore();
    getline(cin, city1);
    cout << "Masukkan nama kota kedua: ";
    getline(cin, city2);
    cout << "Masukkan jarak baru antara kedua kota: ";
    cin >> newDistance;
    cout << "Masukkan jenis jalan (jalan atau laut): ";
    cin >> type;

    city1 = normalizeCityName(city1);
    city2 = normalizeCityName(city2);

    if (type == "jalan") {
        roadGraph->editEdge(city1, city2, newDistance);
    } else if (type == "laut") {
        seaRouteGraph->editEdge(city1, city2, newDistance);
    } else {
        cout << "Jenis jalan tidak dikenal!" << endl;
    }
}

void deleteEdgeFromUserInput(BaseGraph* roadGraph, BaseGraph* seaRouteGraph) {
    string city1, city2, type;

    cout << "Masukkan nama kota pertama: ";
    cin.ignore();
    getline(cin, city1);
    cout << "Masukkan nama kota kedua: ";
    getline(cin, city2);
    cout << "Masukkan jenis jalan (jalan atau laut): ";
    cin >> type;

    city1 = normalizeCityName(city1);
    city2 = normalizeCityName(city2);

    if (type == "jalan") {
        roadGraph->deleteEdge(city1, city2);
    } else if (type == "laut") {
        seaRouteGraph->deleteEdge(city1, city2);
    } else {
        cout << "Jenis jalan tidak dikenal!" << endl;
    }
}

void printCharacters(const BaseGraph& roadGraph, const BaseGraph& seaRouteGraph) {
    cout << "\nCharacters in Cities (Road Graph):\n";
    cout << setw(15) << left << "City" << setw(25) << "Character" << setw(10) << "HP" << setw(10) << "Attack" << endl;
    cout << "-----------------------------------------------------------------------------\n";
    for (const auto& city : roadGraph.getCityCharacters()) {
        for (const auto& character : city.second) {
            cout << setw(15) << left << city.first << setw(25) << character.name << setw(10) << character.hp << setw(10) << character.attack << endl;
        }
    }

    cout << "\nCharacters in Cities (Sea Route Graph):\n";
    cout << setw(15) << left << "City" << setw(25) << "Character" << setw(10) << "HP" << setw(10) << "Attack" << endl;
    cout << "-----------------------------------------------------------------------------\n";
    for (const auto& city : seaRouteGraph.getCityCharacters()) {
        for (const auto& character : city.second) {
            cout << setw(15) << left << city.first << setw(25) << character.name << setw(10) << character.hp << setw(10) << character.attack << endl;
        }
    }
    cout << "\n";
}

Character selectCharacter(const BaseGraph& roadGraph, const BaseGraph& seaRouteGraph) {
    cout << "Select a character from the list below:\n";
    vector<Character> allCharacters;

    for (const auto& city : roadGraph.getCityCharacters()) {
        for (const auto& character : city.second) {
            allCharacters.push_back(character);
        }
    }

    for (const auto& city : seaRouteGraph.getCityCharacters()) {
        for (const auto& character : city.second) {
            allCharacters.push_back(character);
        }
    }

    for (size_t i = 0; i < allCharacters.size(); ++i) {
        cout << i + 1 << ". " << allCharacters[i].name << " (City: " << allCharacters[i].city << ", HP: " << allCharacters[i].hp << ", Attack: " << allCharacters[i].attack << ")\n";
    }

    cout << "Enter the number of the character you want to select: ";
    size_t choice;
    cin >> choice;

    if (choice > 0 && choice <= allCharacters.size()) {
        return allCharacters[choice - 1];
    } else {
        cout << "Invalid choice, defaulting to first character.\n";
        return allCharacters[0];
    }
}

void exploreGraphWithDFS(BaseGraph* roadGraph, BaseGraph* seaRouteGraph) {
    Character character = selectCharacter(*roadGraph, *seaRouteGraph);
    string type;
    cout << "Masukkan jenis jalur (jalan atau laut): ";
    cin >> type;

    if (type == "jalan") {
        roadGraph->dfs(character);
    } else if (type == "laut") {
        seaRouteGraph->dfs(character);
    } else {
        cout << "Jenis jalur tidak dikenal!" << endl;
    }
}

void printNPCs() {
    cout << "\nNPCs in Cities:\n";
    for (const auto& city : manager.cityNPCs) {
        cout << setw(15) << left << city.first << " -> ";
        for (const auto& npc : city.second) {
            npc->printInfo();
            cout << "\n";
        }
    }
    cout << "\n";
}

void addNPC() {
    // Adding Enemies
    manager.addEnemy("Fatui Skirmisher (Cryogunner)", "Mondstadt", 10779, 1225);
    manager.addEnemy("Treasure Hoarder Crusher", "Liyue", 5390, 653);

    // Adding Traders with their items
    manager.addTrader("Sara (Good Hunter)", "Mondstadt", {{"Sweet Madame", "+20% HP", 20}, {"Teyvat Fried Egg", "+150 HP", 150}});
    manager.addTrader("Wagner (Blacksmith)", "Mondstadt", {{"Enhancement Ore", "+10 ATK", 10}, {"Fine Enhancement Ore", "+20 ATK", 20}, {"Mystic Enhancement Ore", "+50 ATK", 50}});
    manager.addTrader("Master Zhang (Blacksmith)", "Liyue", {{"White Iron Chunk", "+5 ATK", 5}, {"Crystal Chunk", "+15 ATK", 15}, {"Magical Crystal Chunk", "+25 ATK", 25}});
    manager.addTrader("Kiminami Anna (Kiminami Restaurant)", "Inazuma", {{"Onigiri", "+10% HP", 10}, {"Tricolor Dango", "+200 HP", 200}});
    manager.addTrader("Iwakura Doukei (Blacksmith)", "Inazuma", {{"Amethyst Lump", "+30 ATK", 30}, {"Electro Crystal", "+40 ATK", 40}, {"White Iron Greatsword", "+50 ATK", 50}});
}

int main() {
    BaseGraph* roadGraph = new RoadGraph();
    BaseGraph* seaRouteGraph = new SeaRouteGraph();
    
    int status = -1;
    
    // Add characters to database at the start
    TambahKarakter(roadGraph, seaRouteGraph);
    
    while (true) {
        cout << "Pilih 1 untuk memasukkan database\n";
        cout << "2 untuk menambahkan jalan\n";
        cout << "3 untuk mengedit jalan\n";
        cout << "4 untuk menghapus jalan\n";
        cout << "5 untuk menampilkan jalan yang ada\n";
        cout << "6 untuk mengetahui jarak antara 2 kota\n";
        cout << "7 untuk menampilkan karakter yang ada\n";
        cout << "8 untuk menampilkan NPC yang ada\n";
        cout << "9 untuk melakukan penjelajahan graf menggunakan DFS\n";
        cout << "Pilih 0 untuk mengakhiri program\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> status;

        if (status == 0) {
            break;
        }

        switch (status) {
            case 1:
                TambahJalan(roadGraph, seaRouteGraph);
                addNPC();
                break;
            case 2:
                addEdgeFromUserInput(roadGraph, seaRouteGraph);
                break;
            case 3:
                editEdgeFromUserInput(roadGraph, seaRouteGraph);
                break;
            case 4:
                deleteEdgeFromUserInput(roadGraph, seaRouteGraph);
                break;
            case 5:
                // Print both graphs
                roadGraph->printGraph();
                seaRouteGraph->printGraph();
                break;
            case 6:
                calculateDistanceBetweenCities(roadGraph, seaRouteGraph);
                break;
            case 7:
                printCharacters(*roadGraph, *seaRouteGraph);
                break;
            case 8:
                printNPCs();
                break;
            case 9:
                exploreGraphWithDFS(roadGraph, seaRouteGraph);
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    delete roadGraph;
    delete seaRouteGraph;

    return 0;
}
