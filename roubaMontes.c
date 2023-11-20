# include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>

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

typedef struct discardList {
  cardDataProps *first;
} discardListDataProps;

deckOfCardsDataPros* createDecks(int quantity);
cardDataProps* createNewCard(int value, int suit);
discardListDataProps * createDiscardList();
cardDataProps * getCardFromDiscard(discardListDataProps * discard, int CardValue);
int generateAChartValue();
int generateChartSuit();
int insertCardInDaeck(cardDataProps *card, deckOfCardsDataPros *deck);
int createNewPlayer(char name[], playerListDataProps *playersList);
playerListDataProps* createAListOfPlayers();
int insertNewPlayerInList(playerDataProps *newPlayer, playerListDataProps *playersList);
cardDataProps* getCardFromDeck(deckOfCardsDataPros *deck);
int shuffleDeck(deckOfCardsDataPros *deck, int quantity);
int verifyCardExistInDiscard(cardDataProps *card, discardListDataProps *discard);
int insertCardInDiscard(cardDataProps *card, discardListDataProps *discard);
int insertCardInPalyerDeck(playerDataProps *player, cardDataProps *card);
int verifyIfCardExistInPalyersDeck(playerDataProps *player, int cardValue, playerDataProps *playerWhoWillDonate);
int getDeckFromAnotherPlayer(playerDataProps *playerWhoWillRecive, playerDataProps *playerWhoWillDonate);

int main(){
  deckOfCardsDataPros *deck;

  playerListDataProps *playersList;
  playerDataProps *auxPlayer;
  playerDataProps *currentPlayer;

  discardListDataProps *discardList;
  cardDataProps *auxDiscardList;

  cardDataProps *card = (cardDataProps*) malloc(sizeof(playerDataProps));
  cardDataProps *cardFromDiscart;


  int quantity, success, playerQuantity, i =1, cardExistInDicard, option, anotherPlayerHaveTheCard;
  char playerName[10];

  playersList = createAListOfPlayers();
  discardList = createDiscardList();

  printf("Bem vindo ao rouba montes");
  Sleep(3000);
  system("cls");

  do {
    printf("Digite a quantidade de jogadores: ");
    scanf("%d", &playerQuantity);

    if(playerQuantity < 1){
      printf("Digite uma quantidade valida!");
      Sleep(2000);
      system("cls");
    }
  }while(playerQuantity < 1);
    
  system("cls");

  for(int i = 1; i <= playerQuantity; i++){
    printf("Digite o nome do jogador: ");
    setbuf(stdin, NULL);
    gets(playerName);
    
    success = createNewPlayer(playerName, playersList);

    if(success ==  1){
        printf("Jogador %s criado com sucesso!\n", playerName);
        Sleep(1000);
        system("cls");
    } else {
        printf("erro!");
    }
  };

  printf("Digite a quantidade de baralhos: ");
  scanf("%d", &quantity);

  system("cls");

  deck = createDecks(quantity);

  for(int i = 0; i < 5; i++){
    switch(i){
      case 1:
        printf("CARREGANDO BARALHO.");
        break;
      case 2:
        printf("CARREGANDO BARALHO..");
        break;
      case 3:
        printf("CARREGANDO BARALHO...");
        break;
      case 4:
        printf("CARREGANDO BARALHO....");
        break;
      case 5:
        printf("CARREGANDO BARALHO.....");
        break;
      default:
        break;
    };
    

    Sleep(1000);
    system("cls");
  }

  if(quantity == 1){
    printf("BARALHO CRIADO COM SUCESSO!");
  } else {
    printf("BARALHOS CRIADOS COM SUCESSO!");
  }

  Sleep(2000);
  system("cls");

  currentPlayer = playersList->first;
  auxPlayer = playersList->first;

  while(deck->first != NULL){
    card = getCardFromDeck(deck);

    printf("JOGADOR %s SUA CARTA E: \n", currentPlayer->name);

    if(success == 1){
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
          printf("Valor: Valete\n\n");
          break;
        case 12:
          printf("Valor: Dama\n\n");
          break; 
        case 13:
          printf("Valor: Rei\n\n");
          break; 
        default:
          printf("Valor: %d\n\n", card->value);
          break;
      };

      if(discardList->first != NULL){
        auxDiscardList = discardList->first;

        printf("\nINICIO LISTA DE DISCARTE\n");

        while(auxDiscardList != NULL){
          switch(auxDiscardList->suit){
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

          switch(auxDiscardList->value){
            case 11:
              printf("Valor: Valete\n\n");
            break;
            case 12:
              printf("Valor: Dama\n\n");
             break; 
            case 13:
              printf("Valor: Rei\n\n");
            break; 
            default:
              printf("Valor: %d\n\n", auxDiscardList->value);
            break;
          };

          auxDiscardList = auxDiscardList->next;
        }

        printf("\n FIM DA LISTA DE DISCARTE\n");
      };


      
      cardExistInDicard = verifyCardExistInDiscard(card, discardList);
      anotherPlayerHaveTheCard = verifyIfCardExistInPalyersDeck(currentPlayer, card->value, auxPlayer);

      if(anotherPlayerHaveTheCard == 1){
        do{
          printf("(1) pegar monte do jogador %s\n", auxPlayer->name);
          printf("Selecione sua opcao: ");
          scanf("%d", &option);
        }while(option !=1);

        if(option == 1){
          success = getDeckFromAnotherPlayer(currentPlayer, auxPlayer);

          if(success == 1){
            printf("MONTE DO JOGADOR %s roubado com sucesso\n", auxPlayer->name);
            Sleep(2000);
            system("cls");
          }
        }
      }

      

      if(cardExistInDicard == 0 && anotherPlayerHaveTheCard == 0){
        success = insertCardInDiscard(card, discardList);
      } else {
        do{
          printf("(1) pegar carta do discarte\n");
          printf("Selecione sua opcao: ");
          scanf("%d", &option);
        }while(option != 1);

        if(option == 1){
         for(int i = 1; i<= cardExistInDicard; i++){
          cardFromDiscart = getCardFromDiscard(discardList, card->value);
          success = insertCardInPalyerDeck(currentPlayer, cardFromDiscart);

          if(success == 1){
            printf("Jogador %s carta adicionada ao seu monte\n", currentPlayer->name);
          }
         }
        }
      }

      Sleep(8000);
      system("cls");

      i++;
    };

    currentPlayer = currentPlayer->next;
  }



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

  for(int h = 1; h <= quantity; h++){
    for(int i = 1; i <= 4; i++){
      for(int j = 1; j <= 13; j++){
        newCard = createNewCard(j, i);
        success = insertCardInDaeck(newCard, deck);
      }
    }
  }



  if(success == 1){
    success = shuffleDeck(deck, quantity);
  }

  return deck;
};

discardListDataProps * createDiscardList(){
  discardListDataProps * newDiscrdList = (discardListDataProps *)malloc(sizeof(discardListDataProps));
  newDiscrdList->first = NULL;

  return newDiscrdList;
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
};

int verifyCardExistInDiscard(cardDataProps *card, discardListDataProps *discard){
  int cardExistInDiscard = 0; 
  cardDataProps *discardCard = discard->first;

  while(discardCard != NULL){
    if(discardCard->value == card->value){
      cardExistInDiscard++;
    };

    discardCard = discardCard->next;
  };

  return cardExistInDiscard;
};

int insertCardInDiscard(cardDataProps *card, discardListDataProps *discard) {
  int success = 1;

  card->next = NULL;

  if (discard->first == NULL) {
    discard->first = card;
  } else {
    cardDataProps *aux = discard->first;
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = card;
  }

  return success;
};

cardDataProps* getCardFromDiscard(discardListDataProps* discard, int cardValue) {
  cardDataProps* current = discard->first;
  cardDataProps* prev = NULL;

  while (current != NULL && current->value != cardValue) {
    prev = current;
    current = current->next;
  }

  if (current != NULL) {
    // A carta foi encontrada

    if (prev == NULL) {
      // A carta está no início da lista
      discard->first = current->next;
    } else {
      prev->next = current->next;
    }

    current->next = NULL;
  }

  return current;
};


int insertCardInPalyerDeck(playerDataProps *player, cardDataProps *card){
  
  card->next = player->deck->first;
  player->deck->first = card;

  return 1;

};

int verifyIfCardExistInPalyersDeck(playerDataProps *player,int cardValue, playerDataProps *playerWhoWillDonate){
  playerDataProps *currentPlayer =  player->next;
  int playerHaveTheCard = 0;

  while(currentPlayer != player){
    if(currentPlayer->deck->first != NULL){
      if(currentPlayer->deck->first->value == cardValue){
        printf("\n VALOR TOPO JOGADOR => %d\n",currentPlayer->deck->first->value);
        printf("VALOR CARTA %d\n", cardValue);
        playerHaveTheCard = 1;
        break;
      } 
    }

    currentPlayer = currentPlayer->next;

  }

  if(playerHaveTheCard == 1){
    playerWhoWillDonate = currentPlayer;
  };

  return playerHaveTheCard;
};


int getDeckFromAnotherPlayer(playerDataProps *playerWhoWillRecive, playerDataProps *playerWhoWillDonate){
  cardDataProps *aux = playerWhoWillDonate->deck->first;

  while(playerWhoWillDonate->deck->first != NULL){
    playerWhoWillDonate->deck->first = aux->next;

    aux->next = playerWhoWillRecive->deck->first;
    playerWhoWillRecive->deck->first = aux;

    aux = playerWhoWillDonate->deck->first;
  };

  return 1;
};