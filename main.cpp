#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

//class Dealer
//{
//
//};
//
//class Player
//{
//
//};
//
//class Deck
//{
//
//};
//
//class Card
//{
//
//};
enum Result 
{
    CONTINUE = 0,
    PLAYER_WIN = 1,
    DEALER_WIN = 2,
    DRAW = 3
};
int judge = 0;

void InitRand()
{
    srand((unsigned int)time(NULL));
}

void Random(int card[4][13], int deck[21][2], int& handNum)
{
    int suit = 0;
    int number = 0;
    do
    {
        suit = rand() % 4;
        number = rand() % 13;
    } while (card[suit][number] == -1);

    card[suit][number] = -1;

    deck[handNum][0] = suit + 1;
    deck[handNum][1] = number + 1;
    handNum += 1;
}


Result Judge(int playerDeck[21][2], int dealerDeck[21][2], int playerHandSize, int dealerHandSize)
{
    int playerScore = DeckSum(playerDeck, playerHandSize);
    int dealerScore = DeckSum(dealerDeck, dealerHandSize);

    if (playerScore > 21)
        return DEALER_WIN;
    else if (dealerScore > 21)
        return PLAYER_WIN;
    else if (judge == 2)
    {
        if (playerScore > dealerScore)
            return PLAYER_WIN;
        else if (playerScore < dealerScore)
            return DEALER_WIN;
        else
            return DRAW;
    }

    return CONTINUE;
}

void DealerTurn(int card[4][13], int dealerDeck[21][2], int& dealerHandNum)
{
    if (DeckSum(dealerDeck, dealerHandNum) < 17)
    {
        Random(card, dealerDeck, dealerHandNum);
    }
}


int DeckSum(int deck[21][2], int handSize)
{
    int sum = 0;
    int countA = 0;
    for (int i = 0; i < handSize; i++)
    {
        if (deck[i][1] >= 10)
        {
            sum += 10;
        }
        else if (deck[i][1] == 1)
        {
            countA++;
        }
        else
        {
            sum += deck[i][1];
        }
    }

    for (int j = countA; j >= 0; --j)
    {
        if (sum <= 10 && j <= 1)
        {
            sum += 11;
        }
        else
        {
            sum += 1;
        }
    }

    return sum;
}

void Suit(int suitNum)
{
    if (suitNum == 0)cout << "�n�[�g";
    if (suitNum == 1)cout << "�_�C��";
    if (suitNum == 2)cout << "�X�y�[�h";
    if (suitNum == 3)cout << "�N���u";
}

int main()
{
    int card[4][13];
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            card[i][j] = j + 1;
        }
    }

    int playerDeck[21][2];
    int playerHandNum = 0;
    int dealerDeck[21][2];
    int dealerHandNum = 0;
    int endJudge = 0;
    int judge = 0;

    InitRand();

    cout << "�u���b�N�W���b�N" << endl
        << "�J�n: 1   �I�� : 0" << endl;
    cin >> endJudge;
    if (endJudge == 0) return 0;

    Random(card, playerDeck, playerHandNum);
    Random(card, playerDeck, playerHandNum);
    Random(card, dealerDeck, dealerHandNum);

    do
    {
        system("CLS");

        cout << "���݂̃f�B�[���[�̎�D" << endl;
        for (int i = 0; i < dealerHandNum; i++)
        {
            cout << i + 1 << "���ڂ�" << " ";
            Suit(dealerDeck[i][0]);
            cout << "  ��  "<< dealerDeck[i][1] << endl;
        }
        cout << "���v��" << DeckSum(dealerDeck, dealerHandNum) << "�ł��B" << endl;

        cout << "���݂̃v���C���[�̎�D" << endl;
        for (int i = 0; i < playerHandNum; i++)
        {
            cout << i + 1 << "���ڂ�" << " ";
            Suit(playerDeck[i][0]);
            cout << "  ��  " << playerDeck[i][1] << endl;
        }
        cout << "���v��" << DeckSum(playerDeck, playerHandNum) << "�ł��B" << endl;

        cout << "�q�b�g���܂����H�@�@�X�^���h���܂����H" << endl
            << "�q�b�g: 1    �X�^���h: 2" << endl;

        do
        {
            cin >> judge;
        } while (judge != 1 && judge != 2);

        if (judge == 1)
        {
            Random(card, playerDeck, playerHandNum);
            DealerTurn(card, dealerDeck, dealerHandNum);
        }
        else
        {
            while (DeckSum(dealerDeck, dealerHandNum) < 17)
            {
                Random(card, dealerDeck, dealerHandNum);
            }
        }

        Result result = Judge(playerDeck, dealerDeck, playerHandNum, dealerHandNum);

        if (result != CONTINUE)
        {
            system("CLS");
            cout << "�Q�[������" << endl;
            cout << "�f�B�[���[�̎�D" << endl;
            for (int i = 0; i < dealerHandNum; i++)
            {
                cout << i + 1 << "���ڂ�" << " ";
                Suit(dealerDeck[i][0]);
                cout << "  ��  " << dealerDeck[i][1] << endl;
            }
            cout << "���v��" << DeckSum(dealerDeck, dealerHandNum) << "�ł��B" << endl;

            cout << "�v���C���[�̎�D" << endl;
            for (int i = 0; i < playerHandNum; i++)
            {
                cout << i + 1 << "���ڂ�" << " ";
                Suit(playerDeck[i][0]);
                cout << "  ��  " << playerDeck[i][1] << endl;
            }
            cout << "���v��" << DeckSum(playerDeck, playerHandNum) << "�ł��B" << endl;

            if (result == PLAYER_WIN)
                cout << "�v���C���[�̏����ł��I" << endl;
            else if (result == DEALER_WIN)
                cout << "�f�B�[���[�̏����ł��I" << endl;
            else if (result == DRAW)
                cout << "���������ł��I" << endl;

            break;
        }
    } while (true);
}