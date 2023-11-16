# include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

deckOfCardsDataPros* createDecks(int quantity);
cardDataProps *createNewCard(int value, int suit);
int generateAChartValue();
int generateChartSuit();
int insertCardInDaeck(cardDataProps *card, deckOfCardsDataPros *deck);

int main(){
  deckOfCardsDataPros *deck;
  cardDataProps *aux;
  deck = createDecks(1);
  aux = deck->first;

  srand(time(NULL));

  while(aux != NULL){
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

  return 0;

};

deckOfCardsDataPros* createDecks(int quantity){
  int suit, value, success;
  cardDataProps *newCard;
  deckOfCardsDataPros *deck = (deckOfCardsDataPros *) malloc(sizeof(deckOfCardsDataPros));

  deck->first = NULL;

  for(int i = 1; i <= quantity; i++){
    for(int j = 1; j <= 10; j++){
      value = generateAChartValue();
      suit = generateChartSuit();
      newCard = createNewCard(value, suit);
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

