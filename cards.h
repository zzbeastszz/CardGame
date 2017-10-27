// A deck is comprised of 1 of every suit, and 1 of each number within the suit.

//TODO: Multiplayer and serialising data. Player dealing, overarching game class and differnt games;
//Create seperate h(pp) files for each class.?
char suitNames[4][8] = {"Clubs", "Spades", "Diamond", "Hearts"};
char rankNames[13][3] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};

std::mt19937 mt_engine = std::mt19937(std::random_device()());

class Card {
public:
  Card(int desired_suit, int desired_rank);
  int GetSuit();
  int GetRank();
  char *GetSuitName();
  char *GetRankName();
private:
  int suit;
  int rank;
};

class Deck {
public:
  Deck();
  std::vector<Card>& GetCards();
  void Shuffle();
private:
  std::vector<Card> cards;
};

class CardHolder {
public:
    void AddCard(Card &new_card);
    std::vector<Card>& GetCards();
protected:
    std::vector<Card> cards;
};

class Player : public CardHolder{
public:
  Player(std::string name, float start_balance);
  float GetBalance();
  std::string GetName();
private:
  std::string player_name;
  float balance;
};

class Table : public CardHolder
{
public:
  float GetPot();
private:
  float pot;
};

class Game { 
public:
  void AddPlayer(std::string name, float start_balance);
  void ClearGame();
  void DealCard();
  void DealTable();
  Deck& GetDeck();
  Table& GetTable();
  std::vector<Player>& GetPlayers();
private:
  std::vector<Player> players;
  Deck deck;
  Table table;
};

Card::Card(int desired_suit, int desired_rank) { 
  this->suit = desired_suit; 
  this->rank = desired_rank;
}

int Card::GetSuit() {
  return this->suit;
}

int Card::GetRank() {
  return this->rank;
}

char *Card::GetSuitName() { 
  return suitNames[this->suit]; 
}

char *Card::GetRankName() { 
  return rankNames[this->rank]; 
}

Deck::Deck() { 
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 13; ++j) {
     this->cards.push_back(Card(i,j));
    }
  }
}

std::vector<Card>& Deck::GetCards() { 
  return this->cards; 
}

void Deck::Shuffle() { 
  std::shuffle(cards.begin(), cards.end(), mt_engine); 
}

void CardHolder::AddCard(Card &new_card) { 
  this->cards.push_back(new_card); 
}

std::vector<Card>& CardHolder::GetCards() { 
  return this->cards; 
}

Player::Player(std::string name, float start_balance = 10000) {
  this->player_name = name;
  this->balance = start_balance;
}

float Player::GetBalance() { 
  return this->balance; 
}

std::string Player::GetName() { 
  return this->player_name; 
}

float Table::GetPot() {
  return this->pot;
}

void Game::AddPlayer(std::string name, float start_balance = 10000) {
  Player new_player = Player(name,start_balance);
  this->players.push_back(new_player);
}

void Game::ClearGame() {
  for(std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
    it->GetCards().clear();
  } 
  table.GetCards().clear();
  this->deck = Deck();
  this->deck.Shuffle();
}

void Game::DealCard() {
  for(std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
    it->AddCard(this->deck.GetCards().back());
    this->deck.GetCards().pop_back();
  }
}

void Game::DealTable() {
  table.AddCard(this->deck.GetCards().back());
  this->deck.GetCards().pop_back();
}

Deck& Game::GetDeck() {
  return this->deck;
}

Table& Game::GetTable() {
  return this->table;
}

std::vector<Player>& Game::GetPlayers() { 
  return this->players; 
}
