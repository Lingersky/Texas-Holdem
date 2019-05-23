
#include<iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;

constexpr unsigned char Error = 0xff;


/**********************************************************************************

The special set values can help to get the type more quickly.

**********************************************************************************/

constexpr char ONE = 1;
constexpr char TWO = 5;
constexpr char THREE = 10;
constexpr char CONSEQ = 8;
constexpr char SAMECL = 14;
constexpr char FOUR = 15;
constexpr char OFFSUIT = 5 * ONE;
constexpr char PAIR = TWO + 3 * ONE;
constexpr char TWOPAIR = TWO * 2 + ONE;
constexpr char SET = THREE + 2 * ONE;
constexpr char STRAIGHT = CONSEQ + 5 * ONE;
constexpr char SUITED = SAMECL;
constexpr char FULLHOUSE = THREE + TWO;
constexpr char BOMB = FOUR + ONE;
constexpr char FLUSH = SAMECL + CONSEQ;

struct cardType {
	char name[15];
	int value;
}card[] = { {"Offsuit",OFFSUIT} ,{"Pair",PAIR},{"Two Pairs",TWOPAIR},{"Set",SET},{"Straight",STRAIGHT},
					 {"Suited",SUITED},{"Full House",FULLHOUSE},{"Bomb",BOMB},{"Flush",FLUSH} };

const char ascNum[13] = { '2','3','4','5','6','7','8','9','T','J','Q','K','A' };//card num charatcer (forward order)
const char ascSuit[4] = { 'C','D','H','S' };//pattern character

struct compareList {
	char type = 0;//memorize the type, it will be compared at first
	char list[5] = { 0 };//memorize the card values, until the type is the same, it will not be compared
};

struct sortList {
	char pairCount = 0;
	char pairNum[2] = { 0 };//memorize the pairs' values
	char uniqueNum = 0;//memorize the set or bomb value
	char offNum[5] = { 0 };//memorize the singles' values
};

unsigned char asc_search(char num, char* list)
{
	for (char i = 0; i < strlen(list); ++i)
		if (num == list[i])
			return i;
	return Error;
}

char straight_check(char* straight)//check the straight
{
	for (char i = 0; i < 4; ++i)
		if (*(straight + i) - *(straight + i + 1) != 1)
			return false;
	return true;
}

compareList type_check(char* cardCount)//with the array of cardCount, we can easily get the card type
{
	compareList result;
	sortList sort;
	char i, count = 0, type = 0;

	for (i = 12; i >= 0 && count < 5; i--)
	{
		switch (cardCount[i]) {
		case 3://A single card
			sort.offNum[count] = i;
			++count;//only one card
			type += ONE;// the core of quickly get the type while tranversing the array
			break;
		case 2://find a pair
			sort.pairNum[sort.pairCount] = i;
			++sort.pairCount;
			count += 2;// a pair has two cards
			type += TWO;
			break;
		case 1:// find a set
			sort.uniqueNum = i;
			count += 3;
			type += THREE;
			break;
		case 0:// find a bomb
			sort.uniqueNum = i;
			count += 4;
			type += FOUR;
		}
	}
	switch (type) {//with the special value, the different type of card can be accumulated into a final type
	case OFFSUIT:
		if (straight_check(sort.offNum))//5 single cards can be a Straight
			type = STRAIGHT;
		memcpy(result.list, sort.offNum, 5);
		break;
	case PAIR:
		result.list[0] = *(sort.pairNum);//memorize the pair value, it will be firstly compared
		memcpy(result.list + 1, sort.offNum, 3);//memorize the single card
		break;
	case TWOPAIR:
		memcpy(result.list, sort.pairNum, 2);
		result.list[2] = sort.offNum[0];
		break;
	case SET:
	case FULLHOUSE:
	case BOMB:
		result.list[0] = sort.uniqueNum;//only need to compare one value
	}
	result.type = type;
	return result;
}

char card_revert(char* card, compareList* outList)
{
	char cardCount[13] = { 4,4,4,4,4,4,4,4,4,4,4,4,4 };//Corresponding to array ascNum
	char cardType = 0;
	bool suited = true;
	unsigned char num;

	for (char i = 0; i < 5; ++i)// Traversing the input string
	{
		num = asc_search(card[i * 3], (char*)ascNum);//find the palce of current character in array ascNum
		if (num == Error && asc_search(card[i * 3 + 1], (char*)ascSuit) == Error)
			return false;
		cardCount[num]--;//for example: if '4' is find once, the cardCount[2] decreases 1
		if (!i)//memorize the first pattern
		{
			cardType = card[1];
			continue;
		}
		if (suited && (cardType - card[i * 3 + 1]))//compare the current pattern with the previous pattern
			suited = false;//if patters are not the same, it couldn't be a Suited.
	}
	*outList = type_check(cardCount);
	if (suited&&outList->type <= STRAIGHT)//Suited is a higher type of card
		if (outList->type == STRAIGHT)//special for Straight
			outList->type = FLUSH;
		else
			outList->type = SUITED;
	return true;
}

void texas_holdem(void)
{
	compareList listBlack, listWhite;

	printf("Input:\r\n");
	char *string;
	char stringBlack[15] = { 0 };
	char stringWhite[15] = { 0 };
	string = (char*)malloc(sizeof(char) * 50);
	if (strlen(string) != 43)//Check if the input is correct
	{
		memset(string, 0, 50);
		cin.getline(string, 50);
	}
	memcpy(stringBlack, string + 7, 14);
	memcpy(stringWhite, string + 29, 14);
	free(string);
	card_revert(stringBlack, &listBlack);//get the type
	card_revert(stringWhite, &listWhite);
	char* winstring = (char*)malloc(15 * sizeof(char));;
	char wintype = 0;
	bool winner = true;
	char i = 0;
	if (listBlack.type != listWhite.type)
	{
		wintype = listBlack.type > listWhite.type ? listBlack.type : listWhite.type;//compare the type
		winner = listBlack.type > listWhite.type ? true : false;
		while (wintype != card[i].value)//find the type name
			++i;
		memcpy(winstring, card[i].name, 15);
	}
	else
	{
		for (i = 0; i < 5; i++)//compare the card while have the same type
			if (listBlack.list[i] != listWhite.list[i])
			{
				winner = listBlack.list[i] > listWhite.list[i] ? true : false;
				sprintf_s(winstring, 12, "high card:%c", listBlack.list[i] > listWhite.list[i] ? ascNum[listBlack.list[i]] : ascNum[listWhite.list[i]]);//matched the high card
				break;
			}
		if (i == 5)//a draw
		{
			printf("Tie\r\n");
			free(winstring);
			return;
		}
	}
	printf(winner ? "Black wins - %s\r\n" : "White wins - %s\r\n", winstring);// print the result
	free(winstring);
	return;
}

int main(void)
{
	while (1) 
		texas_holdem();
	return 1;
}
