#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "app.h"

ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;


void appStart(void)
{

	while (getCardHolderName(&cardData));

	while (getCardExpiryDate(&cardData));

	while (getCardPAN(&cardData));

	while (getTransactionDate(&termData));

	if (isCardExpired(&cardData, &termData) == TERMINAL_OK) {

		while (getTransactionAmount(&termData));

		setMaxAmount(&termData, 20000);

		if (isBelowMaxAmount(&termData) == TERMINAL_OK) {

			transData.cardHolderData = cardData;
			transData.terminalData = termData;

			switch (recieveTransactionData(&transData)) {
			case 0:
				listSavedTransactions();
				break;
			case 1:
				printf("Declined Insufficient Funds\n");
				break;
			case 2:
				printf("Declined Stolen Card\n");
				break;
			case 3:
				printf("Declined Invalid Account\n");
				break;
			case 4:
				printf("INTERNAL SERVER ERROR\n");
				break;
			}

		}
		else {
			printf("Declined amount limit \n");

		}
	}
	else {
		printf("Declined Expired Card\n");
	}

}