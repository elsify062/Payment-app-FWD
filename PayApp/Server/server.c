#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "server.h"
#include <string.h>
#include "../Card/card.h"

ST_accountsDB_t accountsDB[255] = {
	{3000.0, RUNNING,  "8989374615436851"},
	{100000.0, BLOCKED,"5807007076043875"},
	{3000.0, RUNNING,  "3379513561108795"},
	{20000.0, RUNNING, "8585454545252145"},
	{3000.0, BLOCKED,  "2514585858585847"}
};

uint8_t acc;
ST_transaction_t transactionsDB[255] = { 0 };


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	
	acc = 0;
	 while(acc <255) 
	 {
		 if (strcmp((*cardData).primaryAccountNumber, accountRefrence[acc].primaryAccountNumber) == 0) 
			 
			 return SERVER_OK;
		acc++;
		 
	}
	return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void) {

	ST_cardData_t cardData;
	
	printf("Tester Name: AHMED MAHMOUD \n");
	printf("Function Name: isValidAccount\n");

	printf("\nTest Case 1: Non-valid account\n");
	strcpy(cardData.primaryAccountNumber, "1234567890123456");
	printf("Input Data: 1234567890123456\n");
	printf("Expected Result: %d \n", ACCOUNT_NOT_FOUND);
	printf("Actual Result: %d \n", isValidAccount(&cardData, accountsDB));

	printf("\nTest Case 2: valid account\n");
	strcpy(cardData.primaryAccountNumber, "2514585858585847");
	printf("Input Data: 2514585858585847\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", isValidAccount(&cardData, accountsDB));
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {

	if ((*accountRefrence).state == RUNNING)
		return SERVER_OK;
	else
		return BLOCKED_ACCOUNT;
}

void isBlockedAccountTest(void) {
	ST_accountsDB_t accountRefrence;
	printf("\n \nTester Name:  AHMED MAHMOUD \n");
	printf("Function Name: isBlockedAccount\n");

	printf("\nTest Case 1: valid account    %s\n", accountsDB[0].primaryAccountNumber);
	printf("Input Data: 2542555554545485\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", isBlockedAccount(&accountsDB[0]));

	printf("\nTest Case 2: Non-valid account  %s\n",accountsDB[1].primaryAccountNumber);
	printf("Input Data: 5807007076043875\n");
	printf("Expected Result: %d \n", BLOCKED_ACCOUNT);
	printf("Actual Result: %d \n", isBlockedAccount(&accountsDB[1]));

	
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {

	if ((*termData).transAmount <= (*accountRefrence).balance)
		return SERVER_OK;
	else
		return LOW_BALANCE;
}

void isAmountAvailableTest(void) {

	ST_terminalData_t termData;
	termData.transAmount = 5000;
	printf("\n \nTester Name:  AHMED MAHMOUD \n");
	printf("Function Name: isAmountAvailable\n");

	printf("\nTest Case 1: low balance\n");
	printf("Input Data: 3000\n");
	printf("Expected Result: %d \n", LOW_BALANCE);
	printf("Actual Result: %d \n", isAmountAvailable(&termData, &accountsDB[0]));

	printf("\nTest Case 2: sufficient balance\n");
	printf("Input Data: 20000\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", isAmountAvailable(&termData, &accountsDB[1]));
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	
	strcpy(transactionsDB->cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName); 
	strcpy(transactionsDB->cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
	strcpy(transactionsDB->cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
	
	transactionsDB->terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
	transactionsDB->terminalData.transAmount = transData->terminalData.transAmount;
	strcpy(transactionsDB->terminalData.transactionDate, transData->terminalData.transactionDate);
	transactionsDB->transState = transData->transState;
	transactionsDB->transactionSequenceNumber = transData->transactionSequenceNumber;
	
	transData->transactionSequenceNumber = acc+1;
	return SERVER_OK;
}

void saveTransactionTest(void) 
{

	ST_transaction_t transData;

	printf("\n \nTester Name:  AHMED MAHMOUD \n");
	printf("Function Name: saveTransaction\n");
	setMaxAmount(&transData.terminalData, 20000);

	transData.transState = FRAUD_CARD;

	getCardHolderName(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);
	
	printf("\nTest Case 1: low balance\n");
	printf("Input Data:card data:\nname: Ahmed Mahmoud AbdRabbou \n pan:1234567890123456 \n EXdate:05/20 \n term data:\ntransAmount:22000\n  maxTAmount:20000 \n TransDate:31/12/2022\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);

	transData.transState = DECLINED_STOLEN_CARD;

	printf("\nTest Case 2: sufficient balance\n");
	getCardHolderName(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);
	printf("Input Data:card data:\nname: Ahmed Mahmoud AbdRabbou \n pan:5807007076043875 \n EXdate:12/24 \n term data:\ntransAmount:5000\n  maxTAmount:20000 \n TransDate:31/12/2022\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);

}

void listSavedTransactions(void) {
	
	//saveTransactionTest();

	int y;
	for (y = 0; y < acc+1; y++) {
		printf("\n#########################\n");
		printf("Transaction Sequence Number: %d\n", y + 1);
		printf("Transaction Date: %s\n", transactionsDB[y].terminalData.transactionDate);
		printf("Transaction Amount: %.2f\n", transactionsDB[y].terminalData.transAmount);
		printf("Transaction State: %d\n", transactionsDB[y].transState);
		printf("Terminal Max Amount: %.2f\n", transactionsDB[y].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", transactionsDB[y].cardHolderData.cardHolderName);
		printf("PAN: %s\n", transactionsDB[y].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", transactionsDB[y].cardHolderData.cardExpirationDate);
		printf("#########################\n");
	}
}


EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&(*transData).cardHolderData, accountsDB) == ACCOUNT_NOT_FOUND) {
		(*transData).transState = FRAUD_CARD;
		return FRAUD_CARD;
	}
	else if (isBlockedAccount(&accountsDB[acc]) == BLOCKED_ACCOUNT) {
		(*transData).transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&(*transData).terminalData, &accountsDB[acc]) == LOW_BALANCE) {
		(*transData).transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (saveTransaction(transData) == SAVING_FAILED) {
		(*transData).transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	accountsDB[acc].balance -= (*transData).terminalData.transAmount;
	printf("\nYour new balance now is: %.2f\n", accountsDB[acc].balance);

	return APPROVED;
}

void recieveTransactionDataTest(void) {

	ST_transaction_t transData;
	printf("Tester Name:  AHMED MAHMOUD  \n");
	printf("Function Name: recieveTransactionData\n");
	setMaxAmount(&transData.terminalData, 20000);



	printf("\nTest Case 1: Fraud card\n");

	transData.transState = FRAUD_CARD;

	getCardHolderName(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);

	printf("Input Data:card data:name:Ahmed Mahmoud AbdRabbou\n pan:1234567890123456\n  EXdate05/20\n term data:\n   transAmount: 2000\n maxTAmount:20000\n TransDate:31/12/2022\n");
	printf("Expected Result: %d\n", FRAUD_CARD);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

	transData.transState = DECLINED_STOLEN_CARD;

	printf("\nTest Case 2: BLOCKED ACCOUNT\n");
	getCardHolderName(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);

	printf("Input Data:card data:\nname :Ahmed Mahmoud AbdRabbou\n pan:5807007076043875\n EXdate:12/24 \n term data:\ntransAmoun:5000\n: maxTAmount: 20000\n TransDate 31/12/2022\n");
	printf("Expected Result: %d\n", DECLINED_STOLEN_CARD);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

	transData.transState = DECLINED_INSUFFECIENT_FUND;

	printf("\nTest Case 3: INSUFFECIENT FUND \n");

	getCardHolderName(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);

	printf("Input Data:card data:\nname:Ahmed Mahmoud AbdRabbou\n pan:3379513561108795\n  EXdate:11/25 \n term data:\ntransAmount:5000\n maxTAmount:20000 TransDate:31/12/2022\n\n");
	printf("Expected Result: %d\n", DECLINED_INSUFFECIENT_FUND);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

	transData.transState = APPROVED;

	printf("\nTest Case 4: Approved \n");
	getCardHolderName(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);

	printf("Input Data:card data:\nname :Ahmed Mahmoud AbdRabbou\n pan:8989374615436851\n EXdate:12/25\n term data:\ntransAmount:1000\n maxTAmount:3000\n TransDate 31/12/2022\n");
	printf("Expected Result: %d\n", APPROVED);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

}
