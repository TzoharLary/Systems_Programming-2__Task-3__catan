#include "Player.hpp"
#include "Board.hpp"
#include "Validator.hpp"


Player::Player(const string &name) : name(name), points(0), Citys(0) {
    for (int i = WOOD; i <= ORE; ++i) {
        resources[static_cast<ResourceType>(i)] = 0;
    }
}

void Player::Buy(BuyType type) {
    // There is no problem creating a map with each call
    // to the function because the local object cost is created
    // on the stack and automatically deleted at the end of the function.
    map<ResourceType, int> cost;

    switch (type) {
        case ROAD:
            cost = {{WOOD, 1}, {BRICK, 1}};
            break;
        case SETTLEMENT:
            cost = {{WOOD, 1}, {BRICK, 1}, {SHEEP, 1}, {WHEAT, 1}};
            break;
        case CITY:
            cost = {{WHEAT, 2}, {ORE, 3}};
            break;
        case DEVELOPMENT_CARD:
            cost = {{ORE, 1}, {WHEAT, 1}, {SHEEP, 1}};
            break;
        default:
            cout << "Unknown purchase type." << endl;
            return;
    }

    if (checkResources(cost)) {
        // Deduct resources using removeResource
        try {
            for (const auto& item : cost) {
                removeResource(item.first, item.second);
            }
            cout << "Purchase successful!" << endl;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }
    else {
        cout << "Not enough resources to complete the purchase." << endl;

    }
}

bool Player::checkResources(const map<ResourceType, int>& cost) {
    bool hasAllResources = true;
    for (const auto& item : cost) {
        if (resources[item.first] < item.second) {
            hasAllResources = false;
            cout << "Resource: " << resourceTypeToString(item.first) 
                      << ", Required: " << item.second 
                      << ", Available: " << resources[item.first] << endl;
        }
    }

    return hasAllResources;
}

string Player::resourceTypeToString(ResourceType type) {
    switch(type) {
        case WOOD: return "Wood";
        case BRICK: return "Brick";
        case SHEEP: return "Sheep";
        case WHEAT: return "Wheat";
        case ORE: return "Ore";
        default: return "Unknown";
    }
}

void Player::placeSettlement(int vertexIndex, Board& board) {
    
    Validator validator("Player", "placeSettlement", this, vertexIndex, board);
    if (!validator.isValid()) {
        return;
    }   
    // Get the vertex object from the map
    Vertex& vertex = board.vertices.at(vertexIndex); // Using at() instead of []

    if(this->getPoints() > 2){
         Buy(Player::BuyType::SETTLEMENT);
    }
    else{
        // Get the tiles that are associated with the vertex that we built the settlement on
        vector<Tile*> tilesForThisVertex = board.getTilesForVertex(vertexIndex);
        // Iterate over the tiles and add the resources to the player
        for (Tile* tile : tilesForThisVertex) {
            addResource(tile->getResource(), 1);
        }
    }

    // CHECK IF I CAN REMOVE THIS LINES
    // vertex.occupied = true; // From now the vertex will be occupied by the player
    // vertex.player = this; // Save the pointer to the player


    vertex.setPlayer(this); // Set the player of the vertex to the current player
    vertex.setType(Vertex::VertexType::SETTLEMENT); // Set the type of the vertex to a settlement
    this->settlements.push_back(vertexIndex); // Add the settlement to the player's list of settlements
    points += 1; // Settlement is worth 1 point
    cout << name << " placed a settlement on vertex " << vertexIndex << endl;
}

void Player::placeRoad(int roadIndex, Board& board) { 
    Validator validator("Player", "placeRoad", this, roadIndex, board);
    if (!validator.isValid()) {
        return;
    }   
    Road& road = board.roads.at(roadIndex);
    if(this->getPoints() > 2){
        Buy(Player::BuyType::ROAD);
    }
    road.setPlayer(this); // Set the player of the road to the current player
    cout << name << " placed a road on road " << roadIndex << endl;
}

void Player::upgradeSettlementToCity(int vertexIndex, Board& board) {
    Validator validator("Player", "upgradeSettlementToCity", this, vertexIndex, board);
    if (!validator.isValid()) {
        return;
    }  
    // Access the vertex by index, assuming existence is already verified
    // because vertex is alias so we will get to the method with . and not ->
    Vertex& vertex = board.vertices.at(vertexIndex);
    // try to buy
    this->Buy(Player::BuyType::CITY);
    // Change the vertex type to CITY, indicating an upgrade
    vertex.setType(Vertex::VertexType::CITY);
    // Increment points by 1. This assumes a settlement is worth 1 point and upgrading to a city makes it worth 2 points in total
    this->incrementNumOfCity();
    this->incrementPoints();
    // Output a message indicating the player has upgraded a settlement to a city at the specified vertex
    std::cout << "Player " << name << " upgraded a settlement to a city on vertex " << vertexIndex << std::endl;
}

void Player::addResource(ResourceType resource, int amount) {
    resources[resource] += amount; 
}

void Player::removeResource(ResourceType resource, int amount) {
    if (resources[resource] >= amount) {
        resources[resource] -= amount;
        if (resources[resource] == 0) {
            resources.erase(resource);
        }
    } else {
        throw std::runtime_error("Not enough resources");
    }
}

string Player::getName() const {
    return name;
}

int Player::getPoints() const {
    return points;
}

int Player::getNumOfCity() const {
    return Citys;
}

void Player::incrementNumOfCity() {
    Citys++;
}

void Player::incrementPoints() {
    points++;
}
