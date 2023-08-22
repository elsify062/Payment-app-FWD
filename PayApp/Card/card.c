#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "card.h"

#define MAXNAME 24
#define MINNAME 20
#define EXPIRE  5
#define MINPAN 16
#define MAXPAN 19

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t name[35];
    printf("please enter name:");
	fflush(stdin);
	fgets(name, 34, stdin);
    if (strlen(name) < MINNAME || (name) == NULL || strlen(name)> MAXNAME ) {

        printf("WRONG_NAME\n");
        return  WRONG_NAME;
    }
	else {
		strcpy(cardData->cardHolderName, name);
		return CARD_OK;
	}
}

void getCardHolderNameTest(void) {
	ST_cardData_t cardData = {"","",""};
   
	printf("Tester Name: Ahmed Mahmoud\n");
	printf("Function Name: getCardHolderName\n");


	printf("\nTest Case 1: NULL \n");
	printf("Input Data: \n");
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n", cardData.cardHolderName);

	printf("\nTest Case 2: less than 20 characters \n");
	printf("Input Data: AHMED\n");
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n",cardData.cardHolderName);


	printf("\nTest Case 3: more than 24 characters \n");
	printf("Input Data: AHMED MAHMOUD ABDRABBOU ELSAIFY\n");
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n",cardData.cardHolderName);

	printf("\nTest Case 4: correct form \n");
	printf("Input Data:AHMED MAHMOUD ABDRABBOU \n");
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n", cardData.cardHolderName);

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t buff[10];

	
	printf("Enter card Expiry Date in format MM/YY: ");
	fflush(stdin);
	fgets(buff,9, stdin);
	buff[strcspn(buff, "\n")] = 0;
	if (strlen(buff) != EXPIRE ||
		(buff) == NULL || !isdigit(buff[0]) ||
		(buff[2]) != '/' || !isdigit(buff[1]) || !isdigit(buff[3]) || !isdigit(buff[4]))
	{
		printf("Wrong Date\n");
		return WRONG_EXP_DATE;
	}
		
	strcpy(((*cardData).cardExpirationDate),buff);
	return CARD_OK ;
}

void getCardExpiryDateTest(void) {

	ST_cardData_t cardData = { "","","" };
	printf("\n\nTester Name: Ahmed Mahmoud\n");
	printf("Function Name: getCardExpiryDate\n");

	printf("\nTest Case 1: NULL \n");
	printf("Input Data: \n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n", cardData.cardExpirationDate);

	printf("\nTest Case 2: less than 5 characters \n");
	printf("Input Data: 8/22\n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n", cardData.cardExpirationDate);

	printf("\nTest Case 3: more than 5 characters \n");
	printf("Input Data: 12/2024 \n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n", cardData.cardExpirationDate);


	printf("\nTest Case 4: wrong format \n");
	printf("Input Data: 04-25\n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n", cardData.cardExpirationDate);

	printf("\nTest Case 5: correct form \n");
	printf("Input Data: 04/24\n");
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n", cardData.cardExpirationDate);
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t PAN[30];
	printf("Please enter the Card PAN: ");
	fflush(stdin);
	fgets(PAN, 25, stdin);
	PAN[strcspn(PAN, "\n")] = 0;
	// Check Card PAN format

	if (strlen(PAN) < MINPAN || (PAN) == NULL || strlen(PAN) > MAXPAN)
	{
		printf("Wrong PAN\n");
		return WRONG_PAN;
	}
	else
	{
		strcpy(((*cardData).primaryAccountNumber), PAN);
		return CARD_OK;
	}
}

void getCardPANTest(void) {

	ST_cardData_t cardData = { "","","" };
	printf("\n\nTester Name: Ahmed Mahmoud\n");
	printf("Function Name: getCardPAN\n");

	printf("\nTest Case 1: NULL \n");
	printf("Input Data: \n");
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n", cardData.primaryAccountNumber);

	printf("\nTest Case 2: less than 16 characters \n");
	printf("Input Data: 12345\n");
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n", cardData.primaryAccountNumber);


	printf("\nTest Case 3: more than 19 characters \n");
	printf("Input Data: 1234567890123456789525 \n");
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n", cardData.primaryAccountNumber);
	
	printf("\nTest Case 4: correct form \n");
	printf("Input Data: 12345678901234567\n");
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n", cardData.primaryAccountNumber);

}