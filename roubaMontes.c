#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

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

typedef struct card
{
  int value;
  int suit;
  struct card *next;
} cardDataProps;

typedef struct deckOfCards
{
  cardDataProps *first;
  int quantity;
} deckOfCardsDataPros;

typedef struct player
{
  char name[10];
  deckOfCardsDataPros *deck;
  struct player *next;
} playerDataProps;

typedef struct PlayersList
{
  playerDataProps *first;
} playerListDataProps;

typedef struct discardList
{
  cardDataProps *first;
} discardListDataProps;

deckOfCardsDataPros *createDecks(int quantity); // cria o baralho;

cardDataProps *createNewCard(int value, int suit); // cria uma nova carta
cardDataProps *getCardFromDeck(deckOfCardsDataPros *deck); // pega uma carta do baralho;
cardDataProps *getCardFromDiscard(discardListDataProps *discard, int CardValue); // pega uma carta do discarte;

discardListDataProps *createDiscardList(); // cria a lista de discarte;

playerListDataProps *createAListOfPlayers(); // cria a lista de jogadores;
playerDataProps *verifyIfCardExistInOtherPalyersDeck(playerDataProps *player, int cardValue, int *result); // verifica se a carta existe no monte de outros jogsdores

int insertCardInDaeck(cardDataProps *card, deckOfCardsDataPros *deck); // insere uma nova carta no baralho;

int createNewPlayer(char name[], playerListDataProps *playersList); // cria um novo jogador;

int insertNewPlayerInList(playerDataProps *newPlayer, playerListDataProps *playersList); //insere um novo jogador na lista;

int shuffleDeck(deckOfCardsDataPros *deck, int quantity); // embaralha o baralho; 

int verifyCardExistInDiscard(cardDataProps *card, discardListDataProps *discard); // verifica se a carta retirada existe no discarte;

int insertCardInDiscard(cardDataProps *card, discardListDataProps *discard); // insere a carta no discarte

int insertCardInPalyerDeck(playerDataProps *player, cardDataProps *card); //insere a carta no monte do jogador;

int getDeckFromAnotherPlayer(playerDataProps *playerWhoWillRecive, playerDataProps *playerWhoWillDonate); // rouba o monte de outro jogador

int verifyIfCardExistInPlayerDeck(playerDataProps *player, int cardValue); // verifica se a carta existe no monte do jogador atual

void printCard(cardDataProps *card); // imptime a carta

void orderWinnerList(playerDataProps *winnerList, playerListDataProps *playersList, int quantity); // ordena o ranking de jogadores; 

void insertionSortWinnerPlayerCards(cardDataProps winnerCards[], int size); // ordena o vetor de cartas do vencedor

void inserStackOfCardsInWinnerRankingCardList(playerDataProps winnerPlayer, cardDataProps winnerRankingCardList[]); // insere as cartas do vencedor em um vetor;

void freePlayerList(playerListDataProps *playerList); // libera a lista e o monte dos jogadores

void freeDeckOfCards(deckOfCardsDataPros *deckOfCards); // libera o baralho;

void freeDiscardList(discardListDataProps *discardList);



int main()
{
  deckOfCardsDataPros *deck;

  playerListDataProps *playersList;

  playerDataProps *auxPlayer;
  playerDataProps *playerWhoWillDonateCards;
  playerDataProps *currentPlayer;
  playerDataProps *listOfWinners;

  discardListDataProps *discardList;
  cardDataProps *auxDiscardList;

  cardDataProps *card = (cardDataProps *)malloc(sizeof(playerDataProps));
  cardDataProps *cardFromDiscart;
  cardDataProps *winnerRankingCardList;

  int quantity, success, playerQuantity, cardExistInDicard, option, anotherPlayerHaveTheCard;
  char playerName[10];

  playersList = createAListOfPlayers();

  discardList = createDiscardList();

  printf("Bem vindo ao rouba montes");
  Sleep(3000);
  system("cls");

  do
  {
    printf("Digite a quantidade de jogadores: ");
    scanf("%d", &playerQuantity);

    if (playerQuantity < 2)
    {
      printf("O jogo deve conter no minimo 2 jogadores!");
      Sleep(2000);
    }

    system("cls");
  } while (playerQuantity < 2);


  for (int i = 1; i <= playerQuantity; i++)
  { 
    
    printf("Digite o nome do jogador: ");
    setbuf(stdin, NULL);
    gets(playerName);

    success = createNewPlayer(playerName, playersList);

    if(success == 1)
    {
      printf("Jogador %s criado com sucesso!\n", playerName);
      Sleep(1000);
      system("cls");
    }
    else
    {
      printf("erro!");
    }
  };

  do{
    printf("Digite a quantidade de baralhos: ");
    scanf("%d", &quantity);

    if(quantity < 1){
      printf("O jogo deve conter pelo menos um baralho!\n");
      Sleep(1000);
    }

    system("cls");
  }while(quantity < 1);

  deck = createDecks(quantity);

  for (int i = 0; i < 5; i++)
  {
    switch (i)
    {
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

  if (quantity == 1)
  {
    printf("BARALHO CRIADO COM SUCESSO!");
  }
  else
  {
    printf("BARALHOS CRIADOS COM SUCESSO!");
  }

  Sleep(2000);
  system("cls");

  currentPlayer = playersList->first;
  auxPlayer = playersList->first;
  playerWhoWillDonateCards = (playerDataProps *)malloc(sizeof(playerDataProps));

  while (deck->first != NULL)
  {
    card = getCardFromDeck(deck);

    printf("QUANTIDADE DE CARTAS NO BARALHO: %d\n", deck->quantity);

    printf("JOGADOR %s SUA CARTA E: \n", currentPlayer->name);

    if (success == 1) // verificar se e necessario
    {
      printCard(card);

      printf("VOCE TEM %d NO SEU MONTE\n", currentPlayer->deck->quantity); // MOSTRA A QUANTIDADE DE CARTAS O JOGADOR TEM NO SEU MONTE

      if (discardList->first != NULL) // IMPRIME A LISTA DE DISCARTE
      {
        auxDiscardList = discardList->first;

        printf("\nINICIO LISTA DE DISCARTE\n");

        while (auxDiscardList != NULL)
        {
          printCard(auxDiscardList);

          auxDiscardList = auxDiscardList->next;
        }

        printf("\n FIM DA LISTA DE DISCARTE\n");
      };

      if (currentPlayer->deck->first != NULL)
      { // IMPRIME A CARTA NO TOPO DO JOGADOR ATUAL
        printf("SUA CARTA NO TOPO: \n");
        printCard(currentPlayer->deck->first);
      }

      auxPlayer = currentPlayer->next;

      while (auxPlayer != currentPlayer)
      { // IMPRIME O TOPO DO MONTE DE CADA JOGADOR
        if (auxPlayer->deck->first != NULL)
        { // SO IMPRIME SE ESTIVER CARTA NO TOPO
          printf("TOPO DO MONTE DO JOGADOR %s", auxPlayer->name);
          printCard(auxPlayer->deck->first);
        }
        auxPlayer = auxPlayer->next;
      }

      cardExistInDicard = verifyCardExistInDiscard(card, discardList);
      playerWhoWillDonateCards = verifyIfCardExistInOtherPalyersDeck(currentPlayer, card->value, &anotherPlayerHaveTheCard);

      if (cardExistInDicard != 0)
      {
        do
        {
          printf("(1) pegar carta do discarte\n");
          printf("Selecione sua opcao: ");
          scanf("%d", &option);
        } while (option != 1);

        if (option == 1)
        {
          for (int i = 1; i <= cardExistInDicard; i++)
          {
            cardFromDiscart = getCardFromDiscard(discardList, card->value);
            success = insertCardInPalyerDeck(currentPlayer, cardFromDiscart);
            success = insertCardInPalyerDeck(currentPlayer, card);

            if (success == 1)
            {
              printf("Jogador %s carta adicionada ao seu monte\n", currentPlayer->name);
            }
          }
        }
      }
      else if (anotherPlayerHaveTheCard == 1)
      {
        do
        {
          printf("(1) pegar monte do jogador %s\n", playerWhoWillDonateCards->name);
          printf("Selecione sua opcao: ");
          scanf("%d", &option);
        } while (option != 1);

        if (option == 1)
        {
          success = getDeckFromAnotherPlayer(currentPlayer, playerWhoWillDonateCards);
          success = insertCardInPalyerDeck(currentPlayer, card);

          if (success == 1)
          {
            printf("MONTE DO JOGADOR %s roubado com sucesso\n", playerWhoWillDonateCards->name);
          }
        }
      }
      else if (verifyIfCardExistInPlayerDeck(currentPlayer, card->value))
      {
        do
        {
          printf("Sua carta do topo e igual a carta que voce tirou! \n");
          printf("(1) INSERIR CARTA NO SEU MONTE");
          printf("Selecione sua opcao: ");
          scanf("%d", &option);
        } while (option != 1);

        if (option == 1)
        {
          success = insertCardInPalyerDeck(currentPlayer, card);

          if (success == 1)
          {
            printf("CARTA INSERIDA COM SUCESSO!\n");
          }
        }
      }
      else
      {
        printf("Nao e possivel fazer nada com sua carta, ela foi inserida no discarte, pressione qualquer tecla para continuar o jogo!\n");
        scanf("%d", &option);
        insertCardInDiscard(card, discardList);
        currentPlayer = currentPlayer->next;
      }

      Sleep(2000);
      system("cls");
    };
  }

  listOfWinners = (playerDataProps *)malloc(playerQuantity * sizeof(playerDataProps));
  orderWinnerList(listOfWinners, playersList, playerQuantity);

  printf("Ranking de jodadores: \n");

  for (int i = 0; i < playerQuantity; i++)
  { // IMPRIME O RANKING DE JOGADORES
    printf("POSICAO %d: ", i + 1);
    printf("Nome : %s\n", listOfWinners[i].name);
    printf("Quantidade final de cartas: %d", listOfWinners[i].deck->quantity);

    printf("\n");
  }

  winnerRankingCardList = (cardDataProps *)malloc(listOfWinners[0].deck->quantity * sizeof(cardDataProps)); // aloca memoria para a quantidade de cartas do primeiro colocado do ranking

  for (int i = 0; i <= playerQuantity; i++)
  {
    if (listOfWinners[i].deck->quantity == listOfWinners[0].deck->quantity)
    {
      inserStackOfCardsInWinnerRankingCardList(listOfWinners[i], winnerRankingCardList); // ADICIONA AS CARTAS DO JOGADOR AO VETOR E LA DENTRO ORDENA AS CARTAS DE ACORDO COM SEU VALOR
      
      printf("CARTAS DO JOGADOR %s ORDENADAS: \n", listOfWinners[i].name);
      for (int j = 0; j < listOfWinners[i].deck->quantity; j++)
      {
        printCard(&winnerRankingCardList[j]);
      }

      printf("\n\n");
    }
  }

  freePlayerList(playersList);
  freeDeckOfCards(deck);
  freeDiscardList(discardList);
  free(listOfWinners);
  free(winnerRankingCardList);

  return 0;
};

deckOfCardsDataPros *createDecks(int quantity)
{
  int success;
  cardDataProps *newCard;
  deckOfCardsDataPros *deck = (deckOfCardsDataPros *)malloc(sizeof(deckOfCardsDataPros));
  deck->first = NULL;
  deck->quantity = 0;

  for (int h = 1; h <= quantity; h++)
  {
    for (int i = 1; i <= 4; i++)
    {
      for (int j = 1; j <= 13; j++)
      {
        newCard = createNewCard(j, i);
        success = insertCardInDaeck(newCard, deck);
      }
    }
  }

  if (success == 1)
  {
    success = shuffleDeck(deck, quantity);
  }

  return deck;
};

discardListDataProps *createDiscardList()
{
  discardListDataProps *newDiscrdList = (discardListDataProps *)malloc(sizeof(discardListDataProps));
  newDiscrdList->first = NULL;

  return newDiscrdList;
};

cardDataProps *createNewCard(int value, int suit)
{
  cardDataProps *newCard = (cardDataProps *)malloc(sizeof(cardDataProps));

  newCard->value = value;
  newCard->suit = suit;
  newCard->next = NULL;

  return newCard;
};

int insertCardInDaeck(cardDataProps *card, deckOfCardsDataPros *deck)
{

  card->next = deck->first;
  deck->first = card;

  deck->quantity++;

  return 1;
};

int createNewPlayer(char name[], playerListDataProps *playersList)
{
  int success;
  playerDataProps *newPlayer = (playerDataProps *)malloc(sizeof(playerDataProps));

  strcpy(newPlayer->name, name);

  newPlayer->deck = (deckOfCardsDataPros *)malloc(sizeof(deckOfCardsDataPros));

  newPlayer->deck->first = NULL;
  newPlayer->next = NULL;
  newPlayer->deck->quantity = 0;

  success = insertNewPlayerInList(newPlayer, playersList);

  return success;
};

playerListDataProps *createAListOfPlayers()
{
  playerListDataProps *newList = (playerListDataProps *)malloc(sizeof(playerListDataProps));

  newList->first = NULL;

  return newList;
};

int insertNewPlayerInList(playerDataProps *newPlayer, playerListDataProps *playersList)
{
  playerDataProps *aux = playersList->first;

  if (playersList->first != NULL)
  {
    while (aux->next != playersList->first)
    {
      aux = aux->next;
    }

    newPlayer->next = playersList->first;
    aux->next = newPlayer;
  }
  else
  {
    playersList->first = newPlayer;
    newPlayer->next = newPlayer;
  };

  return 1;
};

cardDataProps *getCardFromDeck(deckOfCardsDataPros *deck)
{
  cardDataProps *card;

  if (deck->first != NULL)
  {
    card = deck->first;
    deck->first = deck->first->next;
    card->next = NULL;
    deck->quantity--;
  }
  else
  {
    card = NULL;
  }

  return card;
};

int shuffleDeck(deckOfCardsDataPros *deck, int quantity)
{
  int size = 52 * quantity;
  int i, j;

  srand(time(NULL));

  cardDataProps *current = deck->first;
  cardDataProps *preview = deck->first;

  while (size > 1)
  {
    i = (rand() % (51 * quantity)) + (1 * quantity); // sorteia um numero aleatorio 

    current = deck->first;
    preview = deck->first;

    j = 1;
    while (j < i)
    {
      preview = current;
      current = current->next;
      j++;
    } // percorre a pilha ate achar a carta que esta na posicao sorteada 

    if (i > 1)
    {

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

int verifyCardExistInDiscard(cardDataProps *card, discardListDataProps *discard)
{
  int cardExistInDiscard = 0;
  cardDataProps *discardCard = discard->first;

  while (discardCard != NULL)
  {
    if (discardCard->value == card->value)
    {
      cardExistInDiscard++;
    };

    discardCard = discardCard->next;
  };

  return cardExistInDiscard;
};

int insertCardInDiscard(cardDataProps *card, discardListDataProps *discard)
{
  int success = 1;

  card->next = discard->first;
  discard->first = card;

  return success;
};

cardDataProps *getCardFromDiscard(discardListDataProps *discard, int cardValue)
{
  cardDataProps *current = discard->first;
  cardDataProps *prev = NULL;

  while (current != NULL && current->value != cardValue)
  {
    prev = current;
    current = current->next;
  }

  if (current != NULL)
  {
    // A carta foi encontrada

    if (prev == NULL)
    {
      // A carta está no início da lista
      discard->first = current->next;
    }
    else
    {
      prev->next = current->next;
    }

    current->next = NULL;
  }

  return current;
};

int insertCardInPalyerDeck(playerDataProps *player, cardDataProps *card)
{

  card->next = player->deck->first;
  player->deck->first = card;

  player->deck->quantity++;

  return 1;
};

playerDataProps *verifyIfCardExistInOtherPalyersDeck(playerDataProps *player, int cardValue, int *result)
{
  playerDataProps *currentPlayer = player->next;
  *result = 0;

  while (currentPlayer != player)
  {
    if (currentPlayer->deck->first != NULL)
    {
      if (currentPlayer->deck->first->value == cardValue)
      {
        *result = 1;
      }
    }
    if (*result == 1)
    {
      break;
    }
    else
    {
      currentPlayer = currentPlayer->next;
    }
  }

  return currentPlayer;
};

int getDeckFromAnotherPlayer(playerDataProps *playerWhoWillRecive, playerDataProps *playerWhoWillDonate)
{
  cardDataProps *aux = playerWhoWillDonate->deck->first;

  while (playerWhoWillDonate->deck->first != NULL)
  {
    playerWhoWillDonate->deck->first = aux->next; // topo de cartas de quem vai doar recebe o proximo

    aux->next = playerWhoWillRecive->deck->first; // aux proximo recebe o topo das cartas de quem ira receber
    playerWhoWillRecive->deck->first = aux;       // topo de quem do jogador que ira receber recebe o aux
    playerWhoWillRecive->deck->quantity++;

    aux = playerWhoWillDonate->deck->first; // aux recebe o topo das cartas do jogador que ira doar para que o processo se repita
  };

  playerWhoWillDonate->deck->quantity = 0;

  return 1;
};

void printCard(cardDataProps *card)
{
  printf("\n");
  printf("+-----+\n|");

  // Imprime o valor da carta
  switch (card->value)
  {
  case 1:
    printf("A    ");
    break;
  case 11:
    printf("J    ");
    break;
  case 12:
    printf("Q    ");
    break;
  case 13:
    printf("K    ");
    break;
  default:
    if (card->value == 10)
    {
      printf("%d   ", card->value);
    }
    else
    {
      printf("%d    ", card->value);
    }
    break;
  }

  printf("|\n| ");

  // Imprime o naipe da carta com estilo
  switch (card->suit)
  {
  case 1:
    printf(" P");
    break;
  case 2:
    printf(" O");
    break;
  case 3:
    printf(" C");
    break;
  case 4:
    printf(" E");
    break;
  default:
    break;
  };

  printf("  |\n|     |\n+-----+\n");
};

int verifyIfCardExistInPlayerDeck(playerDataProps *player, int cardValue)
{ // VERIFICA SE A CARTA NO TOPO DO MONTE DO JOGADOR E IGUAL A CARTA QUE ELE TIROU
  int cardExist;

  if (player->deck->first != NULL)
  {
    if (player->deck->first->value == cardValue)
    {
      cardExist = 1;
    }
    else
    {
      cardExist = 0;
    }
  }
  else
  {
    cardExist = 0;
  }

  return cardExist;
};

void insertionSortPlayersRanking(playerDataProps vector[], int size){
  playerDataProps aux; 
  int i, j;

  for (i = 1; i < size; i++) {  // Correção no loop
    aux = vector[i];
    j = i - 1;
    
    // Correção na condição do while
    while (j >= 0 && aux.deck->quantity > vector[j].deck->quantity) {
      vector[j + 1] = vector[j];
      j--;
    }

    vector[j + 1] = aux;
  }
}

void orderWinnerList(playerDataProps *winnerList, playerListDataProps *playersList, int quantity)
{
  playerDataProps *auxPlayer = playersList->first;

  for (int i = 0; i < quantity; i++)
  {
    winnerList[i] = *auxPlayer;
    auxPlayer = auxPlayer->next;
    winnerList[i].next = NULL;
  }

  insertionSortPlayersRanking(winnerList, quantity);
};

void insertionSortWinnerPlayerCards(cardDataProps winnerCards[], int size){
  cardDataProps aux;
  int i, j;

  for(i = 1; i < size; i++){  // Corrigido para i < size
    aux = winnerCards[i];
    j = i - 1;
    while(j >= 0 && aux.value < winnerCards[j].value){
      winnerCards[j + 1] = winnerCards[j];
      j--;
    }
    winnerCards[j + 1] = aux;
  }
}


void inserStackOfCardsInWinnerRankingCardList(playerDataProps winnerPlayer, cardDataProps winnerRankingCardList[]){
  cardDataProps *aux = winnerPlayer.deck->first;
  int i = 0;

  while (aux != NULL && i < winnerPlayer.deck->quantity) {
    winnerRankingCardList[i] = *aux;
    aux = aux->next;
    winnerRankingCardList[i].next = NULL; // Certifique-se de que o próximo seja nulo no vetor
    i++;
  }

  insertionSortWinnerPlayerCards(winnerRankingCardList, winnerPlayer.deck->quantity); // ORDENA O VETOR DE CARTAS DO JOGADOR VENCEDOR

};

void freePlayerList(playerListDataProps *playerList){
  playerDataProps *aux;

  while(playerList->first != NULL){
    aux = playerList->first;
    playerList->first = aux->next;

    freeDeckOfCards(aux->deck);

    aux->next = NULL;

    free(aux);
  };

  free(playerList);
};

void freeDeckOfCards(deckOfCardsDataPros *deckOfCards){
  cardDataProps *aux;

  while(deckOfCards->first != NULL){
    aux = deckOfCards->first;
    deckOfCards->first = aux->next;
    aux->next = NULL;
    free(aux);
  }
  free(deckOfCards);
};

void freeDiscardList(discardListDataProps *discardList){
  cardDataProps *aux;

  while(discardList->first != NULL){
    aux = discardList->first;
    discardList->first = aux->next;
    aux->next = NULL;
    free(aux);
  }
  free(discardList);
};
