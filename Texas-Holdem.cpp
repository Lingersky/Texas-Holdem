
#include<iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;

constexpr unsigned char Error = 0xff;

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

const char ascNum[13] = { '2','3','4','5','6','7','8','9','T','J','Q','K','A' };
const char ascSuit[4] = { 'C','D','H','S' };

struct compareList {
	char type = 0;
	char list[5] = { 0 };
};

struct sortList {
	char pairCount = 0;
	char pairNum[2] = { 0 };
	char uniqueNum = 0;
	char offNum[5] = { 0 };
};

unsigned char asc_search(char num, char* list)
{
	for (char i = 0; i < strlen(list); ++i)
		if (num == list[i])
			return i;
	return Error;
}

char straight_check(char* straight)
{
	for (char i = 0; i < 4; ++i)
		if (*(straight + i) - *(straight + i + 1) != 1)
			return false;
	return true;
}

compareList type_check(char* cardCount)
{
	compareList result;
	sortList sort;
	char i, count = 0, type = 0;

	for (i = 12; i >= 0 && count < 5; i--)
	{
		switch (cardCount[i]) {
		case 3:
			sort.offNum[count] = i;
			++count;
			type += ONE;
			break;
		case 2:
			sort.pairNum[sort.pairCount] = i;
			++sort.pairCount;
			count += 2;
			type += TWO;
			break;
		case 1:
			sort.uniqueNum = i;
			count += 3;
			type += THREE;
			break;
		case 0:
			sort.uniqueNum = i;
			count += 4;
			type += FOUR;
		}
	}
	switch (type) {
	case OFFSUIT:
		if (straight_check(sort.offNum))
			type = STRAIGHT;
		memcpy(result.list, sort.offNum, 5);
		break;
	case PAIR:
		result.list[0] = *(sort.pairNum);
		memcpy(result.list + 1, sort.offNum, 3);
		break;
	case TWOPAIR:
		memcpy(result.list, sort.pairNum, 2);
		result.list[2] = sort.offNum[0];
		break;
	case SET:
	case FULLHOUSE:
	case BOMB:
		result.list[0] = sort.uniqueNum;
	}
	result.type = type;
	return result;
}

char card_revert(char* card, compareList* outList)
{
	char cardCount[13] = { 4,4,4,4,4,4,4,4,4,4,4,4,4 };
	char cardType = 0;
	bool suited = true;
	unsigned char num;

	for (char i = 0; i < 5; ++i)
	{
		num = asc_search(card[i * 3], (char*)ascNum);
		if (num == Error && asc_search(card[i * 3 + 1], (char*)ascSuit) == Error)
			return false;
		cardCount[num]--;
		if (!i)
		{
			cardType = card[1];
			continue;
		}
		if (suited && (cardType - card[i * 3 + 1]))
			suited = false;
	}
	*outList = type_check(cardCount);
	if (suited&&outList->type <= STRAIGHT)
		if (outList->type == STRAIGHT)
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
	card_revert(stringBlack, &listBlack);
	card_revert(stringWhite, &listWhite);
	char* winstring = (char*)malloc(15 * sizeof(char));;
	char wintype = 0;
	bool winner = true;
	char i = 0;
	if (listBlack.type != listWhite.type)
	{
		wintype = listBlack.type > listWhite.type ? listBlack.type : listWhite.type;
		winner = listBlack.type > listWhite.type ? true : false;
		while (wintype != card[i].value)
			++i;
		memcpy(winstring, card[i].name, 15);
	}
	else
	{
		for (i = 0; i < 5; i++)
			if (listBlack.list[i] != listWhite.list[i])
			{
				winner = listBlack.list[i] > listWhite.list[i] ? true : false;
				sprintf_s(winstring, 12, "high card:%c", listBlack.list[i] > listWhite.list[i] ? ascNum[listBlack.list[i]] : ascNum[listWhite.list[i]]);
				break;
			}
		if (i == 5)
		{
			printf("Tie\r\n");
			free(winstring);
			return;
		}
	}
	printf(winner ? "Black wins - %s\r\n" : "White wins - %s\r\n", winstring);
	free(winstring);
	return;
}

int main(void)
{
	while (1) 
		texas_holdem();
	return 1;
}
