//
//  main.c
//  PokerHands
//
//  Created by Stephan Warren on 1/7/15.
//  Copyright (c) 2015 Stephan Warren. All rights reserved.
//
/*
 https://www.codeeval.com/open_challenges/86/
 
 POKER HANDS
 CHALLENGE DESCRIPTION:
 
 In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:
 
 High Card: Highest value card.
 One Pair: Two cards of the same value.
 Two Pairs: Two different pairs.
 Three of a Kind: Three cards of the same value.
 Straight: All cards are consecutive values.
 Flush: All cards of the same suit.
 Full House: Three of a kind and a pair.
 Four of a Kind: Four cards of the same value.
 Straight Flush: All cards are consecutive values of same suit.
 Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
 The cards are valued in the order:
 2, 3, 4, 5, 6, 7, 8, 9, Ten, Jack, Queen, King, Ace.
 If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of fives. But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are compared; if the highest cards tie then the next highest cards are compared, and so on.
 
 INPUT SAMPLE:
 
 Your program should accept as its first argument a path to a filename. Each line in this file contains 2 hands (left and right). Cards and hands are separated by space. E.g.
 
 6D 7H AH 7S QC 6H 2D TD JD AS
 JH 5D 7H TC JS JD JC TS 5S 7S
 2H 8C AD TH 6H QD KD 9H 6S 6C
 JS JH 4H 2C 9H QH KC 9D 4D 3S
 TC 7H KH 4H JC 7D 9S 3H QS 7S
 OUTPUT SAMPLE:
 
 Print out the name of the winning hand or "none" in case the hands are equal. E.g.
 
 left
 none
 right
 left
 right

 
14(1) Royal Flush: Ten, Jack, Queen, King, Ace, in same suit. (straight + flush + Ace)
 
13(1) Straight Flush: All cards are consecutive values of same suit. (straight + flush)
 
10(1) Four of a Kind: Four cards of the same value.
 
4+5 = 9(2) Full House: Three of a kind and a pair.
 
7(5) Flush: All cards of the same suit.
* requires high card and subsequent cards check

6(1) Straight: All cards are consecutive values.
* highest first card
 
 
 
5(3) Three of a Kind: Three cards of the same value.

 
4(3) Two Pairs: Two different pairs.
* requires second pair check on

2 (4) One Pair: Two cards of the same value.
* requires 2nd and 3rd card check
 
1 (4) Ace
0 (5) High Card: Highest value card.
 
 
 0  1  2  3  4  5  6  7  8    9     10     11    12
 2, 3, 4, 5, 6, 7, 8, 9, Ten, Jack, Queen, King, Ace.

*/

#include <stdio.h>


typedef struct {
    char rank;
    char suit;
} card_t;

card_t card[2][5];
char rank[2][13];
char suit[2][4];
char points[2];
char * rcon = "23456789TJQKA";
char * scon = "CDHS";



int main(int argc, const char * argv[]) {

    FILE *file = fopen(argv[1], "r");
//    printf("Start\n");
    char line[32];
    while(fgets(line, 32, file)) {
        {
            char p = 0;
            char c = 0;
            char i = 0;
            while(i < 30) {
                card[p][c].rank = line[i];
                card[p][c].suit = line[i+1];
                i += 3;
                c++;
                if(c == 5) {
                    p = 1;
                    c = 0;
                }
            }
        }
//        for(char p = 0; p < 2; p++) {
//            for(char c = 0; c < 5; c++) {
//                printf("(%d,%d) = %c%c\n", p, c, card[p][c].rank, card[p][c].suit);
//            }
//        }
//        printf("%c%c %c%c %c%c %c%c %c%c - %c%c %c%c %c%c %c%c %c%c\n",
//               card[0][0].rank, card[0][0].suit,
//               card[0][1].rank, card[0][1].suit,
//               card[0][2].rank, card[0][2].suit,
//               card[0][3].rank, card[0][3].suit,
//               card[0][4].rank, card[0][4].suit,
//               card[1][0].rank, card[1][0].suit,
//               card[1][1].rank, card[1][1].suit,
//               card[1][2].rank, card[1][2].suit,
//               card[1][3].rank, card[1][3].suit,
//               card[1][4].rank, card[1][4].suit);
        
        for(char p = 0; p < 2; p++) {
            for(char i = 0; i < 13; i++) {
                rank[p][i] = 0;
            }
            for(char i = 0; i < 4; i++) {
                suit[p][i] = 0;
            }
        }
        for(char p = 0; p < 2; p++) {
            for(char c = 0; c < 5; c++) {
//                printf("%d %d - %c%c\n", p, c, card[p][c].rank, card[p][c].suit);
                // find numbers
                if(('2' <= card[p][c].rank) && (card[p][c].rank <= '9'))
                    rank[p][card[p][c].rank-'2']++;
                else if(card[p][c].rank == 'T') rank[p][8]++;
                else if(card[p][c].rank == 'J') rank[p][9]++;
                else if(card[p][c].rank == 'Q') rank[p][10]++;
                else if(card[p][c].rank == 'K') rank[p][11]++;
                else if(card[p][c].rank == 'A') rank[p][12]++;
                // find suits
                if(card[p][c].suit == 'C') suit[p][0]++;
                else if(card[p][c].suit == 'D') suit[p][1]++;
                else if(card[p][c].suit == 'H') suit[p][2]++;
                else if(card[p][c].suit == 'S') suit[p][3]++;
                
//                for(char i = 0; i < 4; i++) {
//                    printf("Suit[%d, %c] = %d, %d\n", i, scon[i], suit[0][i], suit[1][i]);
//                }
//                printf("\n");
            }
        }
//        for(char i = 0; i < 13; i++) {
//            printf("Rank[%d, %c] = %d, %d\n", i, rcon[i], rank[0][i], rank[1][i]);
//        }
//        for(char i = 0; i < 4; i++) {
//            printf("Suit[%d, %c] = %d, %d\n", i, scon[i], suit[0][i], suit[1][i]);
//        }

        for(char p = 0; p < 2; p++) {
            points[p] = 0;
            char straight = 0;
            for(char r = 0; r < 13; r++) {
                if(rank[p][r] == 0) straight = 0;
                else if(rank[p][r] == 1) {
                    straight++;
                    if(straight == 5) points[p] += 10;
                }
                else if(rank[p][r] == 2) points[p]+= 3;
                else if(rank[p][r] == 3) points[p]+= 9;
                else if(rank[p][r] == 4) points[p]+= 13;
            }
            for(char s = 0; s < 4; s++) {
                if(suit[p][s] == 5) points[p] += 11;
            }
        }
//        printf("Points (L) = %d, (R) = %d\n", points[0], points[1]);
        if(points[0] == points[1]) {
            char r = 12;
            while((points[0] == points[1]) && (r >= 0)) {
//                printf("Ranks: %d vs %d\n", rank[0][r], rank[1][r]);
                if(rank[0][r] > rank[1][r]) points[0]++;
                else if(rank[0][r] < rank[1][r]) points[1]++;
                r--;
            }
        }
//        printf("Points (L) = %d, (R) = %d\n", points[0], points[1]);
        printf("%s\n", points[0] > points[1] ? "left" : (points[1]> points[0] ? "right" : "none"));
    }
    
    return 0;
}






