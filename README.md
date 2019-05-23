# Texas-Holdem
A poker deck contains 52 cards - each card has a suit which is one of clubs, diamonds, hearts, or spades (denoted C, D, H, and S in the input data). Each card also has a value which is one of 2, 3, 4, 5, 6, 7, 8, 9, 10, jack, queen, king, ace (denoted 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A). For scoring purposes, the suits are unordered while the values are ordered as given above, with 2 being the lowest and ace the highest value. A poker hand consists of 5 cards dealt from the deck. Poker hands are ranked by the following partial order from lowest to highest.

一副扑克有52张牌，每张牌由一个花色和一个数字构成。
花色为以下四者之一：方片 D  黑桃 S  红桃 H  梅花 C
数字为以下13者之一，且大小顺序如下：2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A花色是大小无序的，但数字有序，2最小，A最大。

一手牌有5张。根据花色和数字的不同，其大小按照以下规则决定。
A poker hand consists of 5 cards dealt from the deck. Poker hands are ranked by the following partial order from lowest to highest.

同花顺Flush>铁支Bomb>葫芦Full house>同花Suited>顺子Straight>三条Set>两对Two Pairs>对子Pair>散牌Offsuit

散牌：不符合其他任何规则的五张牌。 比较最大一张牌的大小，如果相同，比较第二大的牌的牌点数，如果五张牌的牌点数都相同，则为平局。
Offsuit: Five cards that do not conform to any other rules. Compare the size of the largest card, if the same, compare the number of cards of the second largest card, if the number of cards of the five cards are the same, it is a draw.

对子：有两张同样大小的牌片。 比较两张大小一样的牌的牌点数，如果相同，依次比较剩余的三张牌大小。若大小都相同，则为平局。
Pair: There are two cards of the same size. Compare the number of cards of two cards of the same size. If they are the same, compare the remaining three cards in turn. If the size is the same, it is a draw.

两对：有两个对子牌。 比较大对子的大小，若相同，比较小对子的大小，若还相同，比较单张牌的大小，若还相同，则为平局。
Two Pairs:There are two pairs of subcards. Compare the size of large pairs, if the same, smaller pairs, if the same, compare the size of a single card, if the same, it is a draw.

三条：有三张同样大小的牌片。 比较三张大小一样的牌的牌点数大小。
Set: There are three cards of the same size. Compare the number of points of three cards of the same size.

顺子：五张相连的牌。 比较最大的牌点数。若大小都相同，则为平局。
Straight:Five connected cards. Compare the largest number of cards. If the size is the same, it is a draw.

同花：五张牌的花色相同。 按照散排规则比较大小。
Suited:The five cards have the same pattern. Compare sizes according to scattering rules.

葫芦：三条+对子。 比较三张大小一样的牌的牌点数。
Full house: A Set and a Pair. Compare the number of points of three cards of the same size.

铁支：有四张同样大小的牌片。 比较四张大小一样的牌的牌点数。
Bomb:There are four cards of the same size. Compare the number of points of four cards of the same size.

同花顺：同一种花色的顺子。 比较最大的牌的牌的大小。若大小都相同，则为平局。
Flush:Straight of the same pattern. Compare the size of the largest card. If the size is the same, it is a draw.

你的工作是为两手牌判断大小。Your job is to judge the size of two hand cards.

For example:
input: Black: 2H 3D 5S 9C KD White: 2C 3H 4S 8C AH
output: White wins - high card: Ace

input: Black: 2H 4S 4C 2D 4H White: 2S 8S AS QS 3S
output: Black wins - full house

input: Black: 2H 3D 5S 9C KD White: 2C 3H 4S 8C KH
output: Black wins - high card: 9

input: Black: 2H 3D 5S 9C KD White: 2D 3H 5C 9S KH
output: Tie
