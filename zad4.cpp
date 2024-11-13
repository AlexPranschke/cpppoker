#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

#define NumberOfPlayers 4
#define CASH 2000


using namespace std;

class Card;


bool IsStraightFlush(const vector<Card>& hand);
bool IsQuads(const vector<Card>& hand);
bool IsFullHouse(const vector<Card>& hand);
bool IsFlush(const vector<Card>& hand);
bool IsStraight(const vector<Card>& hand);
bool IsTriple(const vector<Card>& hand);
bool IsTwoPairs(const vector<Card>& hand);
bool IsPair(const vector<Card>& hand);
int CheckHighCard(const vector<Card>& hand);
int CheckCombination(const vector<Card>& hand);






enum class Color : uint8_t {
	Heart = 0 ,
	Diamond,
	Spade,
	Club,

	Number


};

enum class Combinations {
	None = 0,
	HighCard,
	Pair,
	TwoPairs,
	Triple,
	Straight,
	Flush,
	FullHouse,
	Quads,
	StraightFlush,
	RoyalFlush,

	Number

};

void Print(Color color) {
	switch (color) {
	case Color::Heart:
		cout << "heart"  ;
		break;
	case Color::Diamond:
		cout << "Diamond"  ;
		break;
	case Color::Spade:
		cout << "Spade"  ;
		break;
	case Color::Club:
		cout << "Club"  ;
		break;
	default:
		cout << "none"  ;

	}
}

enum class Value : uint8_t {
	Two = 0,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace,

	Number
};

void Print(Value value) {
	
	switch (value) {
	case Value::Two:
		cout << "Two" << endl;
		break;
	case Value::Three:
		cout << "Three" << endl;
		break;
	case Value::Four:
		cout << "Four" << endl;
		break;
	case Value::Five:
		cout << "Five" << endl;
		break;
	case Value::Six:
		cout << "Six" << endl;
		break;
	case Value::Seven:
		cout << "Seven" << endl;
		break;
	case Value::Eight:
		cout << "Eight" << endl;
		break;
	case Value::Nine:
		cout << "Nine" << endl;
		break;
	case Value::Ten:
		cout << "Ten" << endl;
		break;
	case Value::Jack:
		cout << "Jack" << endl;
		break;
	case Value::Queen:
		cout << "Queen" << endl;
		break;
	case Value::King:
		cout << "King" << endl;
		break;
	case Value::Ace:
		cout << "Ace" << endl;
		break;
	default:
		cout << "none" << endl;

	}
}

class Card {
	friend class Deck;
	
	Color m_color = Color::Heart;
	Value m_value = Value::Two;
public:
	Card() {

	}
	Card(Value value, Color color) {
		m_color =  color;
		m_value =  value;
	}
	
	void PrintCard() const{
		Print(m_color);
		cout << " ";
		Print(m_value);
	}
	Color GetColor() const {
		
		return m_color;
	}
	Value GetValue() const  {

		return m_value;
	}
	
};

class Deck {
	//init
private:
	int m_size = 0;
	Card m_cards[52];

public:

	Deck() {
		init();
		
	}

	void init() {
		int index = 0;
		for (int i = 0; i < (int)(Color::Number); ++i) {
			for (int j = 0; j < (int)(Value::Number); ++j) {
				m_cards[index].m_color = (Color)i;
				m_cards[index].m_value = (Value)j;
				
				index++;
				
			}
		}
		
		m_size = index;
		 
		
	}

	void PrintDeck() {
		
		for (int i = 0; i < m_size; i++) {
			m_cards[i].PrintCard();
		}
	}
	//shuffle
	void Shuffle(){
		srand(time(NULL));
		
		for (int i = 0; i < m_size; i++) {
			int index = rand() % m_size;
			swap(m_cards[i], m_cards[index]);
		}
	
	}

	Card Deal() {
		Card result = m_cards[m_size - 1];
		m_size--;
		return result;
	}
	//deal
	//GetSize()

	int GetSize(){
		return m_size;
	}

};

class Player {
public:

	Player() {
		++m_ID;
		playerID = m_ID;
		SetCash(CASH);
	}
	Player(int i) {
		++m_ID;
		playerID = m_ID;
		SetCash(CASH);
	}
	~Player() {

	}
	void GetCard(Deck & deck) {
		hand.push_back(deck.Deal());
	}
	int Check(int minBet) {

		m_check = true;
		m_bet = false;


		int missingCash = minBet - m_cashInvested;
		cout << "MISSINGCASH= " << missingCash << endl;

		if (m_cash - missingCash >= 0) {

			m_cashInvested += missingCash;
			m_cash -= missingCash;
			return missingCash;
		}
		else {
			cout << " ALL IN" << endl;
			m_cashInvested += m_cash;
			m_cash = 0;
			m_allIn = true;
			return m_cash;
		}

	}
	int Bet(int bet, int minBet) {

		int allin = 0;
		m_bet = true;
		m_check = false;

		if (bet < m_cash && m_cashInvested + bet >= minBet) {

			m_cashInvested += bet;
			m_cash -= bet;
			
			return m_cashInvested;
		}
		else {
			
			m_allIn = true;
			allin = m_cash;
			m_cashInvested += m_cash;
			m_cash = 0;
			m_allIn = true;
			
			return allin;
		}
	}
	void Fold() {
		m_fold = true;
	}
	bool GetFold() {
		return m_fold;
	}
	
	void SetCash(int cash) {
		m_cash = cash;
	}
	void AddCash(int cash) {
		m_cash += cash;
	}
	void ShowID() const {
		cout << "player" << playerID;
		cout << " Cash " << m_cash ;
		
	}
	void ShowCards() const {
		
		for (const auto& card : hand) {
			card.PrintCard();  // Modyfikuje ka¿dy element
		}
	}

	void ShowCashInvested() const {
		cout << "invested " << m_cashInvested;
	}
	
	void ShowCardsEnd() {
		m_showCardsEnd = true;
	}
	void SetCombination( Combinations x ) {
		m_bestCombination = x;
	}

	void SetAiPlayer(bool ai) {
		m_aiPlayer = ai;
	}

	string AiDecision(vector<Card> CardsOnTable, int minBet) {
		string move;

		if (m_allIn) {
			return "Check";
		}
		

		int combination;
		vector<Card> temp;

		temp.insert(temp.end(), CardsOnTable.begin(), CardsOnTable.end());
		temp.insert(temp.end(), hand.begin(), hand.end());

		combination = CheckCombination(temp);

		
		if (temp.size() < 3) {
			if (CheckHighCard(temp) < 7 && combination < 2) {
				move = "Fold";
			}
			else if ((CheckHighCard(temp) > 7 && CheckHighCard(temp) < 10) || combination == (int)Combinations::Pair) {
				move = "Check";
			}
			else {
				if (m_cash < minBet - m_cashInvested) {
					move = "Check";
				}
				else {
					move = "Bet";
				}
				
			}
		}
		else if (temp.size() > 3) {
			if (combination < 2) {
				move = "Fold";
			}
			else if ((CheckHighCard(temp) > 7 && CheckHighCard(temp) < 10) || combination == (int)Combinations::Pair) {
				move = "Check";
			}
			else {

				if (m_cash < minBet - m_cashInvested) {
					move = "Check";
				}
				else {
					move = "Bet";
				}
			}
		}
			return move;
	}


	int AiBet(int minBet) {
		int bet = 2 * minBet - m_cashInvested;

		if (m_cash > bet) {
			return bet;
		}
		else {
			m_allIn = true;
			return m_cash;
		}

	}


	Combinations GetCombination() {
		return m_bestCombination;
	}
	
	

	friend class Game;
private:

	bool m_aiPlayer = false;
	bool m_showCardsEnd = false;
	bool m_allIn = false;
	bool m_fold = false;
	bool m_check = false;
	bool m_bet = false;
	int m_cashInvested = 0;
	int m_cash = 0;
	int playerID;
	int m_lost = false;
	static int m_ID;
	vector<Card> hand;
	
	Combinations m_bestCombination = (Combinations)0;

};

int Player::m_ID = 0;

	

class Game {

public:
	Game() {
		initialize(NumberOfPlayers);
		m_startDeals = false;
		
	}
	~Game() {

	}
	void initialize(int x) {

		uint8_t m_NumberOfPlayer = x;
		for (int i = 0; i < NumberOfPlayers; i++) {
			Player player(i);
			player.m_fold = false;
			if (i > 0) {
				player.SetAiPlayer(true);
			}
			else {
				player.SetAiPlayer(false);
			}
			Players.push_back(player);
			
		}
		m_phases.assign(5, false);
		
	}

	void DrawBoard() {

		cout << "				PULA = " << m_sum << " minbet= " << m_minBet << " dealer: player "<< m_dealer+1;
		cout << endl;
		cout << endl;
		cout << endl;
		if (m_phase >= 1) {
			cout << "			";
			CardOnTables[0].PrintCard();
			cout << "			";
			CardOnTables[1].PrintCard();
			cout << "			";
			CardOnTables[2].PrintCard();
		}
		if (m_phase >= 2) {
			cout << "			";
			CardOnTables[3].PrintCard();
		}
		if (m_phase >= 3) {
			cout << "			";
			CardOnTables[4].PrintCard();
		}
		cout << endl;
		cout << endl;
		cout << endl;
		for (int j = 0; j < NumberOfPlayers; j++) {
			
			Players[j].ShowID();
			cout << "	";
			ShowMove(j);
			cout << "	";
			if (m_currentPlayer == j) {
				cout << " X ";
			}
			Players[j].ShowCashInvested();
			

			if (m_currentPlayer == j) {
				cout << " X ";
				
			}
			cout << endl;
			if (m_showPlayersCards == true && Players[j].m_fold == false) {
			
				Players[j].hand[0].PrintCard();
				Players[j].hand[1].PrintCard();

			}
			cout << endl;
			cout << endl;
			
		}
		cout << "your cards(player1)" << endl;
		Players[0].ShowCards();
		
	}
	
	void CheckPhase() {
		cout<< "LICZNIK = " << m_counter << endl;
		if (m_counter == 0 && m_phase<=4) {
			m_phase++;
			m_counter = NumberOfPlayers - m_NumberOfPlayersFold;
		}
	}

	void PutCardsOnTable(Deck &deck) {
		CheckPhase();
		if (m_phase == 0 && m_phases[0]== false) {
			m_counter = NumberOfPlayers - m_NumberOfPlayersFold -1;
			cout << "PHASE 0" << endl;
			m_phases[0] = true;
		}
		else if (m_phase == 1 && m_phases[1] == false) {
			cout << "PHASE 1" << endl;
			CardOnTables.push_back(deck.Deal());
			CardOnTables.push_back(deck.Deal());
			CardOnTables.push_back(deck.Deal());
			m_counter = NumberOfPlayers - m_NumberOfPlayersFold - 1;
			m_phases[1] = true;
		}
		else if (m_phase == 2 && m_phases[2] == false) {
			cout << "PHASE 2" << endl;
			CardOnTables.push_back(deck.Deal());
			m_counter = NumberOfPlayers - m_NumberOfPlayersFold - 1;
			m_phases[2] = true;
		}
		else if (m_phase == 3 && m_phases[3] == false) {
			cout << "PHASE 3" << endl;
			CardOnTables.push_back(deck.Deal());
			m_counter = NumberOfPlayers - m_NumberOfPlayersFold - 1;
			m_phases[3] = true;
		}
		else if (m_phase == 4 && m_phases[4] == false) {
			cout << "PHASE 4" << endl;
			m_counter = NumberOfPlayers - m_NumberOfPlayersFold - 1;
			m_phases[4] = true;
		}
		
	}

	void EndCheckCards(){
		if (m_NumberOfPlayersFold == 3) {
			CheckWinner();

		}
		else if (m_phase == 4  ) {
			m_showPlayersCards = true;
			for (int i = 0; i < NumberOfPlayers; i++) {
				if (!Players[i].m_fold) {
					for (int j = 0; j < 5; j++) {
						Players[i].hand.push_back(CardOnTables[j]);

					}

				}

			}
			CheckCombinations();
		}
	
	}

	void CheckCombinations() {
		
		for (int i = 0; i < NumberOfPlayers; i++) {
			bool temp = false;
			if (!Players[i].m_fold) {

				
				temp = IsStraightFlush(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::StraightFlush);
					continue;
				}
				temp = IsQuads(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::Quads);
					continue;
				}
				temp = IsFullHouse(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::FullHouse);
					continue;
				}
				temp = IsFlush(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::Flush);
					continue;
				}
				temp = IsStraight(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::Straight);
					continue;
				}
				temp = IsTriple(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::Triple);
					continue;
				}
				temp = IsTwoPairs(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::TwoPairs);
					continue;
				}
				temp = IsPair(Players[i].hand);
				if (temp == true) {
					Players[i].SetCombination(Combinations::StraightFlush);
					continue;
				}
				if (temp == false) {
					Players[i].SetCombination(Combinations::HighCard);
				}
				
			}

		}
		CheckWinner();
		for (int i = 0; i < 4; i++) {
			cout << m_winner[i];
		}
	}

	void CheckWinner() {
		int Highcard = 0;
		int BestCombination = 0;
		int PlayerId = 0;
		int tab[NumberOfPlayers] = { 0,0,0,0 };   // Tablica na kombinacje graczy
		int tab2[NumberOfPlayers] = { 0,0,0,0 };  // Tablica na najwy¿sze karty graczy
		int m_winner[NumberOfPlayers] = { 0,0,0,0 }; // Tablica wyników, pocz¹tkowo wszyscy przegrani

		// Uzupe³niamy tablice `tab` i `tab2` kombinacjami i wysokimi kartami graczy
		for (int i = 0; i < NumberOfPlayers; i++) {
			if (!Players[i].GetFold()) {
				tab[i] = (int)Players[i].GetCombination();
				tab2[i] = CheckHighCard(Players[i].hand);
			}
		}

		// Przechodzimy przez tablice, aby znaleŸæ najlepsz¹ kombinacjê i najwy¿sz¹ kartê
		for (int i = 0; i < NumberOfPlayers; i++) {
			if (!Players[i].GetFold()) {
				if (tab[i] > BestCombination) {
					BestCombination = tab[i];
					Highcard = tab2[i];
				}
				else if (tab[i] == BestCombination) {
					if (tab2[i] > Highcard) {
						Highcard = tab2[i];
					}
				}
			}
		}

		// Przypisujemy wynik `1` dla ka¿dego gracza, który ma najlepsz¹ kombinacjê oraz najwy¿sz¹ kartê
		for (int i = 0; i < NumberOfPlayers; i++) {
			if (tab[i] == BestCombination && tab2[i] == Highcard) {
				m_winner[i] = 1; // Gracz jest zwyciêzc¹
			}
		}

		// Wyœwietlamy zwyciêzców 
		for (int i = 0; i < NumberOfPlayers; i++) {
			std::cout << "Player " << i << " Winner: " << m_winner[i] << std::endl;
		}
	

		int temp = 0;
		for (int i = 0; i < NumberOfPlayers; i++) {
			temp += m_winner[i];
		}
		
			for (int i = 0; i < NumberOfPlayers; i++) {
				if (m_winner[i] == 1) {
					Players[i].AddCash(m_sum/temp);
					m_sum = 0;
					
					
				}

			}
			m_newRound = true;

		
	}

	void NewRound(Deck & deck) {
		if (m_newRound == true) {
			m_NumberOfPlayersFold = 0;
			m_sum = 0;
			for (int i = 0; i < NumberOfPlayers; i++) {
				if (Players[i].m_cash > 0) {
					Players[i].m_fold = false;
					Players[i].m_check = false;
					Players[i].m_bet = false;
					Players[i].hand.clear();
					Players[i].m_cashInvested = 0;
					m_winner[i] = 0;
					Players[i].m_allIn = false;
				}
				else
				{	
					m_NumberOfPlayersFold++;
					Players[i].m_lost = true;
					Players[i].m_allIn = true;
					Players[i].m_cashInvested = 0;
					Players[i].m_fold = true;
					Players[i].m_allIn = false;
					Players[i].hand.clear();
				}
			}
			
			m_showPlayersCards = false;
			m_phase = 0;
			m_newRound = false;
			m_startDeals = false;
			m_minBet = 200;
			deck.init();
			m_dealer = (m_dealer + 1) % 4;
		}
		
	}

	bool CheckNewRound() {
			
		return m_newRound;
	}

	void CheckPlayers() const {  
		for (int i = 0; i < NumberOfPlayers; i++) {
			Players[i].ShowID();
			Players[i].ShowCards();
			cout << endl;
		}
	}

	void GiveCards(Deck & deck) {
		for (int i = 0; i < NumberOfPlayers; i++) {
			if (!Players[i].m_lost) {
				Players[i].GetCard(deck);
				Players[i].GetCard(deck);
			}
		}
	}

	void ShowMove(int i) {
		if(Players[i].m_lost == true) {
			cout << "LOST";
		}
		else if(Players[i].m_fold == true){
			cout << "FOLD";
		}
		else if (Players[i].m_check == true) {
			cout << "CHECK";
		}
		else if (Players[i].m_bet == true) {
			cout << "BET";
		}
		else {
			cout << "WAITING";
		}
	}

	int NextPlayer() {
		int i = 1;
		int temp = (m_currentPlayer + i) % NumberOfPlayers;
		while (Players[temp].m_lost) {
			i++;
			temp = (m_currentPlayer + i) % NumberOfPlayers;
			
		}
		return m_currentPlayer = (m_currentPlayer + 1) % (int)NumberOfPlayers;
		
	}

	void FirstDeals() {
		m_currentPlayer = m_dealer;

		if (m_startDeals == false) {
			cout << "small deal from player " << m_currentPlayer + 1 % 4 << endl;
			Players[m_currentPlayer].Bet(m_deal, m_deal);
			m_sum += m_deal;
			NextPlayer();
			cout << "big deal from player " << m_currentPlayer + 1 % 4 << endl;
			Players[m_currentPlayer].Bet(m_deal * 2, m_deal * 2);
			m_sum += m_deal *2;
			m_minBet = m_deal * 2;
			m_startDeals = true;
			NextPlayer();
			m_counter = NumberOfPlayers-1-m_NumberOfPlayersFold;
			
			
			
		}
	}

	void PlayerMove() {
		
		
		if (!Players[m_currentPlayer].m_fold) {

			if (m_phase == 4) {
				cout << endl;
				Players[m_currentPlayer].ShowCardsEnd();
				
			}
			else {



				string move;



				cout << "Player " << m_currentPlayer + 1 % 4 << " Check, Fold, Bet ?";
				
				if (Players[m_currentPlayer].m_aiPlayer == false) {
					if (Players[m_currentPlayer].m_allIn) {
						move = "Check";
					}
					else {
						cin >> move;
					}
				}
				else {


					move = Players[m_currentPlayer].AiDecision(CardOnTables, m_minBet);
				}

				if (move == "Check") {
					m_sum += Players[m_currentPlayer].Check(m_minBet);
					cout << "Player " << m_currentPlayer + 1 << " chose to Check." << endl;
					m_counter--;
					NextPlayer();

				}
				else if (move == "Fold") {
					cout << "Player " << m_currentPlayer + 1 << " chose to Fold." << endl;
					Players[m_currentPlayer].Fold();
					m_counter--;
					m_NumberOfPlayersFold++;
					NextPlayer();

				}
				else if (move == "Bet") {
					m_bet = 0;
					cout << "Player " << m_currentPlayer + 1 << " chose to Bet." << endl;




					if (Players[m_currentPlayer].m_aiPlayer == false) {
						if (m_minBet + Players[m_currentPlayer].m_cashInvested <= Players[m_currentPlayer].m_cash) {
							while (m_bet + Players[m_currentPlayer].m_cashInvested < m_minBet) {
								cout << "How much do you want to bet ?";
								cin >> m_bet;
								if (cin.fail()) {
									cin.clear(); // Resetowanie stanu b³êdu
									cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuniêcie niepoprawnych danych z bufora
									cout << "Invalid input. Please enter a valid integer.\n";
								}

							}
							m_sum += Players[m_currentPlayer].Bet(m_bet, m_minBet);
						}
						else if (m_minBet + Players[m_currentPlayer].m_cashInvested > Players[m_currentPlayer].m_cash) {
							cout << "ALL IN" << endl;
							m_sum += Players[m_currentPlayer].Bet(Players[m_currentPlayer].m_cash, m_minBet);
						}
					}
					else {
							m_bet = Players[m_currentPlayer].AiBet(m_minBet);
							m_sum += Players[m_currentPlayer].Bet(m_bet, m_minBet);
					}


					cout << "PULA = " << m_sum << " minbet= " << m_minBet << endl;



					if (Players[m_currentPlayer].m_cashInvested > m_minBet) {
						m_minBet = Players[m_currentPlayer].m_cashInvested;

					}
					m_counter = NumberOfPlayers - m_NumberOfPlayersFold -1;

					NextPlayer();

				}
				else {
					cout << "Invalid move! Please enter Check, Fold, or Bet." << endl;
					// Powrót do pocz¹tku pêtli, aby spróbowaæ ponownie
				}
			}
		}
		else
			NextPlayer();


		
		
	}

private:
	bool m_newRound = false;
	bool m_startDeals = false;
	bool m_playersPassed[NumberOfPlayers];
	bool m_showPlayersCards = false;
	int m_counter = NumberOfPlayers ;
	int m_deal = 200;
	int m_check = 200;
	int m_sum = 0;
	int m_allSum = 0;
	int m_dealer = 0;
	int m_bet = 0;
	int m_minBet = 0;
	int m_currentPlayer = 0;
	int m_NumberOfPlayer = 0;
	int m_NumberOfPlayersFold = 0;
	int m_phase = 0;
	int m_winner[4] = { 0,0,0,0 };
	vector<bool> m_phases;
	vector<Card> CardOnTables;
	vector<Player> Players;
	vector<Card> AllCards;
};





int main() {
	
	Deck deck;
	Game game;
	
	
	
	
	
	while (true) {
		deck.Shuffle();
		game.GiveCards(deck);
		game.FirstDeals();
		game.DrawBoard();
		system("PAUSE");
		while (true) {
			
			game.PlayerMove();
			game.PutCardsOnTable(deck);
			game.EndCheckCards();
			game.DrawBoard();
			system("PAUSE");
			cout << endl;
			
			if (game.CheckNewRound()) {
				
				system("PAUSE");
				game.NewRound(deck);
				
				break;
			}
		}
		
	}

	return 0;
}


int CheckCombination(const vector<Card>& hand) {
	if (IsStraightFlush(hand)) {
		return static_cast<int>(Combinations::StraightFlush);
	}
	else if (IsQuads(hand)) {
		return static_cast<int>(Combinations::Quads);
	}
	else if (IsFullHouse(hand)) {
		return static_cast<int>(Combinations::FullHouse);
	}
	else if (IsFlush(hand)) {
		return static_cast<int>(Combinations::Flush);
	}
	else if (IsStraight(hand)) {
		return static_cast<int>(Combinations::Straight);
	}
	else if (IsTriple(hand)) {
		return static_cast<int>(Combinations::Triple);
	}
	else if (IsTwoPairs(hand)) {
		return static_cast<int>(Combinations::TwoPairs);
	}
	else if (IsPair(hand)) {
		return static_cast<int>(Combinations::Pair);
	}
	else {
		
		return static_cast<int>(Combinations::HighCard);
	}
}


int CheckHighCard(const vector<Card>& hand) {
	int HighCard = 0;
	for (auto& card : hand) {
		if (HighCard < static_cast<int>(card.GetValue())) {
			HighCard = static_cast<int>(card.GetValue());
		}
	}
	return HighCard;
}

bool IsFlush(const vector<Card>& hand) {
	// Mapa do przechowywania liczby kart ka¿dego koloru
	unordered_map<Color, int> ColorCount;

	// Iterujemy przez wszystkie karty w rêce gracza
	for (const auto& card : hand) {
		// Zwiêkszamy licznik dla koloru tej karty
		ColorCount[card.GetColor()]++;
	}

	// Sprawdzamy, czy którykolwiek kolor wystêpuje co najmniej 5 razy
	for (const auto& entry : ColorCount) {
		if (entry.second >= 5) return true;  // Znaleziono flush
	}

	return false;  // Nie znaleziono flush
}

bool IsPair(const std::vector<Card>& hand) {
	std::unordered_map<Value, int> valueCount;

	for (const auto& card : hand) {
		valueCount[card.GetValue()]++;
	}

	for (const auto& entry : valueCount) {
		if (entry.second == 2) return true;  // Znaleziono parê
	}
	return false;  // Brak pary
}

bool IsTwoPairs(const std::vector<Card>& hand) {
	std::unordered_map<Value, int> valueCount;
	int pairs = 0;

	for (const auto& card : hand) {
		valueCount[card.GetValue()]++;
	}

	for (const auto& entry : valueCount) {
		if (entry.second == 2) pairs++;
	}

	return pairs >= 2;  // Musi byæ co najmniej 2 pary
}

bool IsTriple(const std::vector<Card>& hand) {
	std::unordered_map<Value, int> valueCount;

	for (const auto& card : hand) {
		valueCount[card.GetValue()]++;
	}

	for (const auto& entry : valueCount) {
		if (entry.second == 3) return true;  // Znaleziono trójkê
	}
	return false;  // Brak trójki
}

bool IsFullHouse(const std::vector<Card>& hand) {
	std::unordered_map<Value, int> valueCount;
	bool hasTriple = false;
	bool hasPair = false;

	for (const auto& card : hand) {
		valueCount[card.GetValue()]++;
	}

	for (const auto& entry : valueCount) {
		if (entry.second == 3) hasTriple = true;
		if (entry.second == 2) hasPair = true;
	}

	return hasTriple && hasPair;  // Musi byæ trójka i para
}

bool IsQuads(const std::vector<Card>& hand) {
	std::unordered_map<Value, int> valueCount;

	for (const auto& card : hand) {
		valueCount[card.GetValue()]++;
	}

	for (const auto& entry : valueCount) {
		if (entry.second == 4) return true;  // Znaleziono czwórkê
	}
	return false;  // Brak czwórki
}

bool IsStraight(const std::vector<Card>& hand) {
	std::unordered_map<int, bool> valueExists;

	// Ustawiamy wartoœci kart, które istniej¹ w rêce
	for (const auto& card : hand) {
		// Rzutujemy wartoœæ enum (np. CardValue) na int
		valueExists[static_cast<int>(card.GetValue())] = true;
	}

	// Sprawdzamy strita od dowolnej wartoœci od 0 do 8 (dla strita 5-kartowego)
	for (int start = 0; start <= 8; ++start) {
		int consecutiveCount = 0;
		for (int i = start; i < start + 5; ++i) {  // Sprawdzamy kolejne 5 kart
			if (valueExists[i]) {
				consecutiveCount++;
			}
			else {
				break;  // Brak kolejnej wartoœci, przerywamy
			}
		}
		if (consecutiveCount == 5) return true;  // Znaleziono strita
	}

	// Sprawdzanie specjalnego strita A-2-3-4-5 (As jako 12 i 0)
	if (valueExists[12] && valueExists[0] && valueExists[1] && valueExists[2] && valueExists[3]) {
		return true;  // Znaleziono strita A-2-3-4-5
	}

	return false;  // Brak strita
}

bool IsStraightFlush(const std::vector<Card>& hand) {
	// Mapa, aby przechowaæ karty wed³ug koloru
	std::unordered_map<Color, std::vector<int>> colorToValues;

	// Przechodzimy przez karty w rêce i grupujemy je wed³ug koloru
	for (const auto& card : hand) {
		colorToValues[card.GetColor()].push_back(static_cast<int>(card.GetValue()));
	}

	// Dla ka¿dego koloru sprawdzamy, czy mamy 5 kolejnych kart
	for (auto& entry : colorToValues) {
		// Posortuj wartoœci kart w danym kolorze
		sort(entry.second.begin(), entry.second.end());

		// Zmienna do zliczania kolejnych kart
		int consecutiveCount = 1;

		// Sprawdzamy kolejnoœæ kart w tym kolorze
		for (size_t i = 1; i < entry.second.size(); ++i) {
			if (entry.second[i] == entry.second[i - 1] + 1) {
				consecutiveCount++;
				if (consecutiveCount == 5) {
					return true;  // Znaleziono Straight Flush
				}
			}
			else if (entry.second[i] != entry.second[i - 1]) {
				consecutiveCount = 1;  // Resetujemy liczbê kolejnych kart
			}
		}
	}

	return false;  // Brak Straight Flush
}

