#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include "Validator.hpp"
#include "Board.hpp"
// #include "catan.hpp"
// #include "DevelopmentCard.hpp"

/* Explanation of includes in Player.hpp and not in Player.cpp:
*  We include the Validator.hpp because we want that the validatePlayer method
   be a friend of the Player for using private methods of the Player class.
*  We include the Board.hpp because we want that the distributeResources method
   be a friend of the Player for using private methods of the Player class.
*  We include the DevelopmentCard.hpp because we want that the YearOfPlentyCard, KnightCard, and VictoryPointCard classes
   be a friend of the Player for using private methods of the Player class.

*/

using std::string;
using std::istringstream;
using std::map;
using std::vector;
using std::runtime_error;
using std::cout;
using std::endl;
using std::find;
using std::out_of_range;
using std::unique_ptr;

// class Catan;

class Player {

private:
    /* Fields:
    *  developmentCards: The development cards of the player
    *  knightCount: The number of knights the player has
    *  victoryPoints: The number of victory points the player has
    *  board: The board object
    *  name: The name of the player
    *  points: The number of points the player has
    *  resources: Map that holds the player's resources and the amount of each resource
    *  settlements: The index of the settlements the player has
    *  Citys: The number of cities the player has
    *  Comment:  The reason that we have a vector of settlements and not a number
    *            is that we need to use it for remove the settlement to built their a city
    *            and that's why we need only the number of the city.
    *  usingRoadBuildingCard: A bool value to determine if the player is using a road building card or not
    */
    enum BuyType { ROAD, SETTLEMENT, CITY, DEVELOPMENT_CARD };
    vector<unique_ptr<DevelopmentCard>> developmentCards;   
    map<string, int> cardCounts;
    int knightCount;
    int victoryPoints;
    Board& board;
    string name;
    int points;
    map<ResourceType, int> resources; 
    vector<int> settlements; 
    int Citys; 
    bool usingRoadBuildingCard = false;
    bool isMyTurn = false;
    bool parchaseDevelopmentCardThisTurn = false; 
    vector<bool> purchaseYOPThisTurn = {false, false};
    vector<bool> roundStatus = {false, false, false};
    void setisMyTurn(bool value);
    void setPurchaseDevelopmentCardThisTurn(bool value);
    void setPurchaseYOPThisTurn(const vector<bool>& value);
    void setRoundStatus(const vector<bool>& newStatus);
    void Buy(BuyType type);
    void handleError(const std::exception& e);
    /* Resource functions with explanations:
    *  removeResource: Remove resources from the player
    *  checkResources: Helper function to check if the player has enough resources to buy something
    *  resourceTypeToString: Helper function to convert a ResourceType to a string
    *  stringToResourceType: Helper function to convert a string to a ResourceType
    *  addResource: Add resources to the player
    */ 
    void addResource(ResourceType resource, int amount); 
    void removeResource(ResourceType resource, int amount); // Remove resources from the player
    bool checkResources(const map<ResourceType, int>& cost);// Helper function to check if the player has enough resources to buy something
    string resourceTypeToString(ResourceType type) const;
    ResourceType stringToResourceType(const string& str) const; 
   
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
    *  printDevelopmentCards: Print the development cards the player has
    */
    void addDevelopmentCard(unique_ptr<DevelopmentCard> card);
    void setUsingRoadBuildingCard(bool value);
    bool getUsingRoadBuildingCard() const;
    void printDevelopmentCards() const;
    /*  Friend classes with explanations why they are friends:
    *   KnightCard: The KnightCard class needs to access to methods: incrementKnightCount, incrementPoints, and getKnightCount.
    *   VictoryPointCard: The VictoryPointCard class needs to access to methods: incrementPoints and incrementVictoryPoints.
    *   Validator: The validatePlayer method in the Validator class needs to access to methods: getNumOfSettlements, and getNumOfCity.
    */
    // friend class DevelopmentCard;
    friend class KnightCard;
    friend class VictoryPointCard;
    friend class YearOfPlentyCard;
    friend class Catan;
    friend void Validator::validatePlayer();
    // friend void Board::distributeResources(int rolledNumber);

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
    void useDevelopmentCard(const string& command); 

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
    vector<int> getSettlements() const;
    vector<bool> getRoundStatus();
    int getNumOfDevelopmentCards() const;
    int getNumOfVictoryPoints() const;
    // declaration of get method that return the development cards that the player has
    const vector<unique_ptr<DevelopmentCard>>& getDevelopmentCards() const;
    vector<bool> getPurchaseYOPThisTurn() const;


};

#endif // PLAYER_HPP
