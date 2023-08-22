#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include"terminal.h"
#define MAXTRANSACTIONDATE 10
#define ConvertCharToInt(x) ((x) - 48)



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	

	uint8_t transaction[20];
	printf("Enter transactionDate in format DD/MM/YYYY: ");
	fflush(stdin);
	fgets(transaction, 19, stdin);
	transaction[strcspn(transaction, "\n")] = 0;


	if (!isdigit(transaction[0]) || !isdigit(transaction[1]) ||
		!isdigit(transaction[6]) || !isdigit(transaction[7]) || !isdigit(transaction[8]) || !isdigit(transaction[9]) ||
		!isdigit(transaction[3]) || !isdigit(transaction[4]) ||
		(transaction[2]) != '/' || (transaction[5]) != '/' || transaction == NULL || strlen(transaction) != MAXTRANSACTIONDATE)

	{
		printf("Wrong date\n");
		return WRONG_DATE;
	}
	else
	{
			strcpy(((*termData).transactionDate), transaction);
			return TERMINAL_OK;
	}

}
void getTransactionDateTest(void) {

	ST_terminalData_t termData = { 0,0,"" };
	
	
	
		printf("Tester Name: Ahmed Mahmoud \n");
		printf("Function Name: getTransactionDate\n");
		printf("\nTest Case 1: NULL \n");
		printf("Input Data: \n");
		printf("Expected Result: %d \n", WRONG_DATE);
		printf("Actual Result: %d \n", getTransactionDate(&termData));
		printf("Data stored: %s \n", termData.transactionDate);

		printf("\nTest Case 2: more than 10 characters \n");
		printf("Input Data: 12/12/20222 \n");
		printf("Expected Result: %d \n", WRONG_DATE);
		printf("Actual Result: %d \n", getTransactionDate(&termData));
		printf("Data stored: %s \n", termData.transactionDate);

		printf("\nTest Case 3: less than 10 characters \n");
		printf("Input Data: 9/9/2022\n");
		printf("Expected Result: %d \n", WRONG_DATE);
		printf("Actual Result: %d \n", getTransactionDate(&termData));
		printf("Data stored: %s \n", termData.transactionDate);

		printf("\nTest Case 4: wrong format \n");
		printf("Input Data: 05-10-2022\n");
		printf("Expected Result: %d \n", WRONG_DATE);
		printf("Actual Result: %d \n", getTransactionDate(&termData));
		printf("Data stored: %s \n", termData.transactionDate);

		printf("\nTest Case 5: correct form \n");
		printf("Input Data: 05/10/2022\n");
		printf("Expected Result: %d \n", TERMINAL_OK);
		printf("Actual Result: %d \n", getTransactionDate(&termData));
		printf("Data stored: %s \n", termData.transactionDate);
	}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	//     MM/  YY
	//  DD/MM/YYYY

	///transforming the date into a numeric values  
	uint8_t CardMonth = ConvertCharToInt((*cardData).cardExpirationDate[0]) * 10 + ConvertCharToInt((*cardData).cardExpirationDate[1]);
	uint8_t CardYear = ConvertCharToInt((*cardData).cardExpirationDate[3]) * 10 + ConvertCharToInt((*cardData).cardExpirationDate[4]);

	uint8_t CurrentMonth = ConvertCharToInt((*termData).transactionDate[3]) * 10 + ConvertCharToInt((*termData).transactionDate[4]);
	uint8_t CurrentYear = ConvertCharToInt((*termData).transactionDate[8]) * 10 + ConvertCharToInt((*termData).transactionDate[9]);

	
	if (CurrentYear > CardYear)
	{
		return EXPIRED_CARD;
	}
	else if (CurrentYear == CardYear && CurrentMonth > CardMonth)
	{
		return EXPIRED_CARD;
	}

	return TERMINAL_OK;
}



void isCardExpiredTest(void) {

ST_terminalData_t termData;
ST_cardData_t CARDEXP1 = { "","", "10/21" };
ST_cardData_t CARDEXP2 = { "","", "01/23" };
ST_cardData_t CARDEXP3 = { "","", "02/23" };
ST_cardData_t CARDEXP4 = { "","", "09/23" };

printf("\n\nTester Name: Ahmed Mahmoud \n");
printf("Function Name: isCardExpired\n");

printf("Enter transaction date\n");
getTransactionDate(&termData);

printf("\nTest Case 1: expired card exp_year < trans_year \n");
printf("Input Data: 10/21 \n");
printf("Expected Result: %d \n", EXPIRED_CARD);
printf("Actual Result: %d \n", isCardExpired(&CARDEXP1, &termData));

printf("\nTest Case 2: expired card exp_year == trans_year  && exp_month < trans_month\n");
printf("Input Data: 01/23 \n");
printf("Expected Result: %d \n", EXPIRED_CARD);
printf("Actual Result: %d \n", isCardExpired(&CARDEXP2,&termData));

printf("\nTest Case 3: non-expired card exp_year == trans_year  && exp_month == trans_month\n");
printf("Input Data: 02/23 \n");
printf("Expected Result: %d \n", TERMINAL_OK);
printf("Actual Result: %d \n", isCardExpired(&CARDEXP3, &termData));

printf("\nTest Case 4: non-expired card exp_year > trans_year \n");
printf("Input Data: 09/23 \n");
printf("Expected Result: %d \n", TERMINAL_OK);
printf("Actual Result: %d \n", isCardExpired(&CARDEXP4, &termData));
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

	float buff;
	printf("please enter amount transaction: ");

	scanf_s("%f", &buff);
	getche();
	if (buff > 0)
	{
		(*termData).transAmount = buff;

		return TERMINAL_OK;
	}

	printf("Wrong amount\n");
	return INVALID_AMOUNT;
}

void getTransactionAmountTest(void){

	ST_terminalData_t termData;
printf("\n\nTester Name: Ahmed Mahmoud \n");
printf("Function Name: getTransactionAmountTest\n");

printf("\nTest Case 1: if amount equle zero  \n");
printf("Input Data: 0 \n");
printf("Expected Result: %d \n", INVALID_AMOUNT);
printf("Actual Result: %d \n", getTransactionAmount( &termData));

printf("\nTest Case 2: less than zero \n");
printf("Input Data: -35000 \n");
printf("Expected Result: %d \n", INVALID_AMOUNT);
printf("Actual Result: %d \n", getTransactionAmount(&termData));

printf("\nTest Case 3: correct form\n");
printf("Input Data: 3250 \n");
printf("Expected Result: %d \n", TERMINAL_OK);
printf("Actual Result: %d \n", getTransactionAmount( &termData));


}



EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount > 0)
	{
		(*termData).maxTransAmount = maxAmount;

		return TERMINAL_OK;
	}


	return INVALID_MAX_AMOUNT;
}
void setMaxAmountTest(void)
{
	ST_terminalData_t termData;
	printf("\n\nTester Name: Ahmed Mahmoud \n");
	printf("Function Name: setMaxAmount\n");

	printf("\nTest Case 1: if amount equle zero  \n");
	printf("Input Data: 0 \n");
	printf("Expected Result: %d \n", INVALID_MAX_AMOUNT);
	printf("Actual Result: %d \n", setMaxAmount(&termData, 0));

	printf("\nTest Case 2: less than zero \n");
	printf("Input Data: -35000 \n");
	printf("Expected Result: %d \n", INVALID_MAX_AMOUNT);
	printf("Actual Result: %d \n", setMaxAmount(&termData, -6550));

	printf("\nTest Case 3: correct form\n");
	printf("Input Data: 3250 \n");
	printf("Expected Result: %d \n", TERMINAL_OK);
	printf("Actual Result: %d \n", setMaxAmount(&termData,300));
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if ((*termData).transAmount <= (*termData).maxTransAmount)
	{
		return TERMINAL_OK;
	}

	return EXCEED_MAX_AMOUNT;
}

void isBelowMaxAmountTest(void)
{
	ST_terminalData_t termData;

	printf("\n\nTester Name: Ahmed Mahmoud \n");
	printf("Function Name: isBelowMaxAmount\n");

	setMaxAmount(&termData, 5000);

	printf("\nTest Case 1: if amount equal max amount \n");
	printf("Input Data: 5000 \n");
	(void)getTransactionAmount(&termData);
	printf("Expected Result: %d \n", TERMINAL_OK);
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));

	printf("\nTest Case 2: more than 5000 \n");
	printf("Input Data: 7000 \n");
		(void)getTransactionAmount(&termData);
	printf("Expected Result: %d \n", EXCEED_MAX_AMOUNT);
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));

	printf("\nTest Case 3: correct form :between 1 to 5000\n");
	printf("Input Data: 2000 \n");
	(void)getTransactionAmount(&termData);
	printf("Expected Result: %d \n", TERMINAL_OK);
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));

}