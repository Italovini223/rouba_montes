# include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/*
  SUit:
  1: Paus;
  2: Ouros;
  3: Copas;
  4: Espadas;

*/

/*
  value {
    12: Valete;
    13: Dama;
    14: Rei;
  }
*/

typedef struct card {
  int value;
  int suit;
  struct card *next;
} cardDataProps;

typedef struct deckOfCards {
   cardDataProps *first;
} deckOfCardsDataPros;

typedef struct player {
   char name[10];
    deckOfCardsDataPros *deck;
    struct player *next;
} playerDataProps;

typedef struct PlayersList {
    playerDataProps *first;
} playerListDataProps;

deckOfCardsDataPros* createDecks(int quantity);
cardDataProps* createNewCard(int value, int suit);
int generateAChartValue();
int generateChartSuit();
int insertCardInDaeck(cardDataProps *card, deckOfCardsDataPros *deck);
int cardAlreadyExistInDeck(deckOfCardsDataPros *deck, cardDataProps *newCard, int quantity);
int createNewPlayer(char name[], playerListDataProps *playersList);
playerListDataProps* createAListOfPlayers();
int insertNewPlayerInList(playerDataProps *newPlayer, playerListDataProps *playersList);

int main(){
  deckOfCardsDataPros *deck;
  playerListDataProps *playersList;
  cardDataProps *aux;
  int quantity, success;
  char playerName[10];

  deck = createDecks(1);
  playersList = createAListOfPlayers();

    
  aux = deck->first;

  srand(time(NULL));

  printf("Digite a quantidade de jogadores: ");
  scanf("%d", &quantity);

  for(int i = 1; i <= quantity; i++){
    printf("Digite o nome do jogador: ");
    setbuf(stdin, NULL);
    gets(playerName);
    
    success = createNewPlayer(playerName, playersList);

    if(success ==  1){
        printf("Jogador %s criado com sucesso!\n", playerName);
    } else {
        printf("erro!");
    }
  };

  /* while(aux != NULL){
    switch(aux->suit){
      case 1:
        printf("Naipe: Paus\n");
        break;
      case 2:
        printf("Naipe: Ouros\n");
        break;
      case 3:
        printf("Naipe: Copas\n");
        break;
      case 4:
        printf("Naipe: Espada\n");
      default:
        break;
    };

    switch(aux->value){
      case 12:
        printf("Valor: Valete\n");
        break;
      case 13:
        printf("Valor: Dama\n");
        break; 
      case 14:
        printf("Valor: Rei\n");
        break; 
      default:
        printf("Valor: %d\n", aux->value);
        break;
    };

    printf("\n");

    aux = aux->next;
  };

  */

  return 0;

};

deckOfCardsDataPros* createDecks(int quantity){
  int suit, value, success, cardAlreadyExist;
  cardDataProps *newCard;
  deckOfCardsDataPros *deck = (deckOfCardsDataPros *) malloc(sizeof(deckOfCardsDataPros));

  deck->first = NULL;

  for(int i = 1; i <= quantity; i++){
    
    for(int j = 1; j <= 10; j++){
      do{
        value = generateAChartValue();
        suit = generateChartSuit();
        newCard = createNewCard(value, suit);
        cardAlreadyExist = cardAlreadyExistInDeck(deck, newCard, quantity);
      }while(cardAlreadyExist == 1);
      success = insertCardInDaeck(newCard, deck);
    }
  }

  if(success == 1){
    printf("Baralho criado com sucesso!\n");
  }

  return deck;
};

int generateAChartValue(){
  int value;
  value = (rand()%12) + 1;

  return value;
};

int generateChartSuit(){
  int value;
  
  value = (rand()%3) + 1;

  return value;
};

cardDataProps *createNewCard(int value, int suit){
  cardDataProps *newCard = (cardDataProps*) malloc(sizeof(cardDataProps));

  newCard->value = value;
  newCard->suit = suit;
  newCard->next = NULL;

  return newCard;  
};

int insertCardInDaeck(cardDataProps *card, deckOfCardsDataPros *deck){
  
  card->next = deck->first;
  deck->first = card;

  return 1;
};

int cardAlreadyExistInDeck(deckOfCardsDataPros *deck, cardDataProps *newCard, int quantity){
  cardDataProps *aux = deck->first;
  int numberOfCards = 0;
  int cardAlreadyExist;

  while(aux != NULL){
    if(aux->value == newCard->value && aux->suit == newCard->suit){
      numberOfCards++;
    };


    aux = aux->next;
  }

  if(numberOfCards >= quantity){
    cardAlreadyExist = 1;
  } else {
    cardAlreadyExist = 0;
  }

  return cardAlreadyExist;
  
};

int createNewPlayer(char name[], playerListDataProps *playersList){
    int success;
    playerDataProps *newPlayer = (playerDataProps*) malloc(sizeof(playerDataProps));
    
    strcpy(newPlayer->name, name);

    newPlayer->deck->first = NULL;
    newPlayer->next = NULL;

    success = insertNewPlayerInList(newPlayer, playersList);

    return success;
};

playerListDataProps* createAListOfPlayers(){
    playerListDataProps *newList = (playerListDataProps*) malloc(sizeof(playerListDataProps));

    newList->first = NULL;

    return newList;
};

int insertNewPlayerInList(playerDataProps *newPlayer, playerListDataProps *playersList){
    playerDataProps *aux = playersList->first;

    if(playersList->first != NULL){
        while(aux->next != playersList->first){
            aux = aux->next;
        }

        newPlayer->next = playersList->first;
        aux->next = newPlayer;

    } else {
        playersList->first = newPlayer;
        newPlayer->next = newPlayer;
    };

    return 1;
};
