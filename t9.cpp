/*
    Autor: Robert Latoszewski
    Date: 03.05.2019

    Description: 
        T9 dictionary
*/

#include <iostream>

using namespace std;

struct Node // digit trie
{
    struct Node *key[8] = {}; // array of 8 Node ptrs
    struct Word_trie *word_trie = nullptr;
};

struct Word_trie
{
    struct Word_trie *letter[26] = {}; // array of 26 Word_trie ptrs
    struct Word_trie *parent = nullptr;
    bool if_word = false;
};

//*****************************************************************************
//****** fuction declaration ******//

void char_to_digit(char word[], char digits[]);
void insert(struct Node *root, char digit_arr[], char word[]);
void insert_word(char word[], struct Word_trie *root);

//*****************************************************************************
//****** main program ********// 

int main()
{
    int words;
    struct Node *root = nullptr;
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
            insert(root, digit_arr, arr);
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

void insert(struct Node *root, char digit_arr[], char word[])
{
    int i = 0;
    if (!root) root = new struct Node;
    struct Node *curr = root;
    while (digit_arr[i] != '\0' && i < 100)
    {
        if (curr->key[(digit_arr[i] - 0) - 2] == nullptr)
        {
            curr->key[(digit_arr[i] - 0) - 2] = new struct Node;
        }
        curr = curr->key[(digit_arr[i] - 0) - 2];
        i++;
    }
    // digits loaded into trie
    // add word into word trie
    // creating word trie "inside" digit trie node
    curr->word_trie = new struct Word_trie;
    insert_word(word, curr->word_trie);
}

void insert_word(char word[], struct Word_trie *root)
{
    int i = 0;
    struct Word_trie *curr = root;
    while (word[i] != '\0' && i < 100)
    {
        if (curr->letter[word[i] - 'a'] == nullptr)
        {
            curr->letter[word[i] - 'a'] = new struct Word_trie;
            curr->letter[word[i] - 'a']->parent = curr;
        }
        curr = curr->letter[word[i] - 'a'];
        i++;
    }
    curr->if_word = true;
}