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
int createNewPlayer(char name[], playerListDataProps *playersList);
playerListDataProps* createAListOfPlayers();
int insertNewPlayerInList(playerDataProps *newPlayer, playerListDataProps *playersList);
cardDataProps* getCardFromDeck(deckOfCardsDataPros *deck);
int shuffleDeck(deckOfCardsDataPros *deck, int quantity);

int main(){
  deckOfCardsDataPros *deck;
  playerListDataProps *playersList;
  cardDataProps *card = (cardDataProps*) malloc(sizeof(playerDataProps));
  int quantity, success;
  char playerName[10];

  playersList = createAListOfPlayers();


    
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

  printf("Digite a quantidade de baralhos: ");
  scanf("%d", &quantity);

  deck = createDecks(quantity);




  /* if(success == 1){
    printf("\n");
    printf("CARTA RESGATADA: \n");
    switch(card->suit){
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

    switch(card->value){
      case 11:
        printf("Valor: Valete\n");
        break;
      case 12:
        printf("Valor: Dama\n");
        break; 
      case 13:
        printf("Valor: Rei\n");
        break; 
      default:
        printf("Valor: %d\n", card->value);
        break;
    };
  } */

  return 0;

};

deckOfCardsDataPros* createDecks(int quantity){
  int success;
  cardDataProps *newCard;
  deckOfCardsDataPros *deck = (deckOfCardsDataPros *) malloc(sizeof(deckOfCardsDataPros));
  deck->first = NULL;

  for(int i = 1; i <= 4; i++){
    for(int j = 1; j <= 13; j++){
      newCard = createNewCard(j, i);
      success = insertCardInDaeck(newCard, deck);
    }
  }


  if(success == 1){
    success = shuffleDeck(deck, quantity);
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


int createNewPlayer(char name[], playerListDataProps *playersList){
    int success;
    playerDataProps *newPlayer = (playerDataProps*) malloc(sizeof(playerDataProps));

    
    strcpy(newPlayer->name, name);




    newPlayer->deck = (deckOfCardsDataPros*) malloc(sizeof(deckOfCardsDataPros));

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

cardDataProps* getCardFromDeck(deckOfCardsDataPros *deck){
  cardDataProps *card;

  if(deck->first != NULL){
    card = deck->first;
    deck->first = deck->first->next;
    card->next = NULL;

    printf("CARD VALUE => %d\n",card->value);
  
  } else {
    card = NULL;
  }

  
 return card;


};


int shuffleDeck(deckOfCardsDataPros *deck, int quantity) {
 int size = 52 * quantity;
 int i, j;

 srand(time(NULL));

 cardDataProps *current = deck->first;
 cardDataProps *preview = deck->first;

 while (size > 1) {
    i = (rand() % (51 * quantity)) + (1 * quantity);

    current = deck->first;
    preview = deck->first;

    j = 1;
    while (j < i) {
      preview = current;
      current = current->next;
      j++;
    } 


    if(i > 1){

      // Desvincula o elemento atual do resto da fila
      preview->next = current->next;

      // Insere o elemento atual no início da fila
      current->next = deck->first;
      deck->first = current;
    }

    size--;
 }

 return 1;
}
