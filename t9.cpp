/*
    Autor: Robert Latoszewski
    Date: 03.05.2019

    Description: 
        T9 dictionary
*/

#include <iostream>

using namespace std;

struct Node
{
    struct Node *character[8]; // array of 26 Node ptrs
    bool if_word;
};

//*****************************************************************************
//****** fuction declaration ******//

void char_to_digit(char word[], char digits[]);

//*****************************************************************************
//****** main program ********// 

int main()
{
    int words;
    int query;
    char arr[100]; 
    char digit_arr[100];
    struct Node *root = nullptr;
    while (cin >> words)
    {
        for (int i = 0; i < words; i++)
        {
            cin >> arr;
            char_to_digit(arr, digit_arr);
            cout << "Drukuje digit_arr: " << digit_arr << endl;
            // add digits to trie
            // save word on a last digit
        }
        cin >> query;
        for (int j = 0; j < query; j++)
        {
            cin >> arr;
            // return all matching to query words in lexicographical order
        }
    }
    return 0;
}

//*****************************************************************************
//**** function definition ******//


void char_to_digit(char word[], char digits[])
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] - 0 > 96 && word[i] - 0 < 100) digits[i] = '2';
        else if (word[i] - 0 > 99 && word[i] - 0 < 103) digits[i] = '3';
        else if (word[i] - 0 > 102 && word[i] - 0 < 106) digits[i] = '4';
        else if (word[i] - 0 > 105 && word[i] - 0 < 109) digits[i] = '5';
        else if (word[i] - 0 > 108 && word[i] - 0 < 112) digits[i] = '6';
        else if (word[i] - 0 > 111 && word[i] - 0 < 116) digits[i] = '7';
        else if (word[i] - 0 > 115 && word[i] - 0 < 119) digits[i] = '8';
        else if (word[i] - 0 > 118 && word[i] - 0 < 123) digits[i] = '9';
        i++;
    }
}