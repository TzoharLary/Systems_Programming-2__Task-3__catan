#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include "Tile.hpp" 
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include "Validator.hpp"
using std::string;
using std::map;
using std::vector;
using std::runtime_error;
using std::cout;
using std::endl;
using std::find;
using std::out_of_range;
using std::unique_ptr;

class Board;
class DevelopmentCard;

class Player {

private:
 
    // we create a field that hold the development cards of the player
    vector<unique_ptr<DevelopmentCard>> developmentCards;
    int knightCount;
    int victoryPoints;
    Board& board;
    string name;
    int points;
    map<ResourceType, int> resources; 
    vector<int> settlements; // List of settlement vertex indices
    int Citys; // List of Citys vertex indices
    bool usingRoadBuildingCard = false;
    enum BuyType { ROAD, SETTLEMENT, CITY, DEVELOPMENT_CARD };
    void Buy(BuyType type);

    /* Resource functions with explanations:
    *  removeResource: Remove resources from the player
    *  checkResources: Helper function to check if the player has enough resources to buy something
    *  resourceTypeToString: Helper function to convert a ResourceType to a string
    *  stringToResourceType: Helper function to convert a string to a ResourceType
    *  addResource: Add resources to the player
    */ 
    void removeResource(ResourceType resource, int amount); // Remove resources from the player
    bool checkResources(const map<ResourceType, int>& cost);// Helper function to check if the player has enough resources to buy something
    string resourceTypeToString(ResourceType type) const;
    ResourceType stringToResourceType(const std::string& str) const; 
   
    /* Increment and decrement functions with explanations:
    *  decrementNumOfSettlements: Decrease the number of settlements the player has
    *  incrementNumOfCity: Increase the number of cities the player has
    *  incrementVictoryPoints: Increase the number of victory points the player has
    *  incrementKnightCount: Increase the number of knights the player has
    *  incrementPoints: Increase the number of points the player has
    */
    void decrementNumOfSettlements(int vertexIndex);
    void incrementNumOfCity();
    void incrementVictoryPoints();
    void incrementKnightCount();
    void incrementPoints();   

    /* Development card functions with explanations:
    *  addDevelopmentCard: Add a development card to the player's hand
    *  setUsingRoadBuildingCard: bool value to determine if the player is using a road building card or not
    *  getUsingRoadBuildingCard: Get the player's road building card usage status 
    *  to determine if the player is using a road building card or not int the placeRoad function
    *  getDevelopmentCards: Get the player's development cards
    */
    void addDevelopmentCard(std::unique_ptr<DevelopmentCard> card);
    void setUsingRoadBuildingCard(bool value);
    bool getUsingRoadBuildingCard() const;
    const std::vector<std::unique_ptr<DevelopmentCard>>& getDevelopmentCards() const;

    /*  Friend classes with explanations why they are friends:
    *  KnightCard: The KnightCard class needs to access to methods: incrementKnightCount, incrementPoints, and getKnightCount.
    *  VictoryPointCard: The VictoryPointCard class needs to access to methods: incrementPoints and incrementVictoryPoints.
    *  DevelopmentCard: The DevelopmentCard class needs to access to methods: addDevelopmentCard, getDevelopmentCards, and setUsingRoadBuildingCard.
    
    */
    friend class KnightCard;
    friend class VictoryPointCard;
    // friend class DevelopmentCard;
    friend class Vertex;
    friend void Validator::validatePlayer();

public:

    /* Constructor, Trade, and status functions with explanations:
    *  Player: Constructor for the Player class
    *  Trade: Trade resources with another player
    *  status: Print the player's status
    */ 
    Player(const string& name, Board& board); // constructor 
    void Trade(Player& player, ResourceType give, int giveAmount, ResourceType take, int takeAmount);  
    void status() const;

    /* Place functions with explanations:
    *  placeSettlement: Place a settlement on the board
    *  placeRoad: Place a road on the board
    *  upgradeSettlementToCity: Upgrade a settlement to a city
    */
    void placeSettlement(int vertexIndex); 
    void placeRoad(int roadIndex); 
    void upgradeSettlementToCity(int vertexIndex); // this function will upgrade a settlement to a city
    

    /* Development card functions with explanations:
    *  buyDevelopmentCard: Buy a development card
    *  useDevelopmentCard: Use a development card
    */
    void buyDevelopmentCard();
    void useDevelopmentCard(const std::string& command); 

    /* Getter functions with explanations:
    *  getResources: Get the player's resources map
    *  getKnightCount: Get the player's knight amount
    *  getName: Get the player's name
    *  getPoints: Get the player's points
    *  getNumOfCity: Get the player's number of cities
    *  getNumOfRoads: Get the player's number of roads
    *  getNumOfSettlements: Get the player's number of settlements
    */
    map<ResourceType, int> getResources() const;
    int getKnightCount() const;
    string getName() const;
    int getPoints() const;
    int getNumOfCity() const;
    int getNumOfRoads() const;
    int getNumOfSettlements() const;

    // i leave for now this function in public for test myself in the main
    void addResource(ResourceType resource, int amount); 
};

#endif // PLAYER_HPP
