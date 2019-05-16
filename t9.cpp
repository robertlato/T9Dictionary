/*
    Autor: Robert Latoszewski
    Date: 03.05.2019

    Description: 
        T9 dictionary
*/

#include <iostream>

using namespace std;

struct Word_trie
{
    struct Word_trie *letter[26] = {}; // array of 26 Word_trie ptrs
    struct Word_trie *parent = nullptr;
    bool if_word = false;
};

struct Node // digit trie
{
    struct Node *key[8] = {}; // array of 8 Node ptrs
    struct Word_trie *word_trie = nullptr;
};

//*****************************************************************************
//****** fuction declaration ******//

void char_to_digit(char word[], char digits[]);
struct Node* insert(struct Node *root, char digit_arr[], char word[]);
void insert_word(char word[], struct Word_trie *root);
void print_trie(struct Node *root, char digits_arr[]);
void print_word_trie(struct Word_trie *root);
void print_digit_trie(struct Node *root);

//*****************************************************************************
//****** main program ********// 

int main()
{
    int words;
    struct Node *root = nullptr;
    int query;
    char char_arr[100]; 
    char digit_arr[100];
    //struct Node *root = nullptr;
    while (cin >> words)
    {
        for (int i = 0; i < words; i++)
        {
            cin >> char_arr;
            char_to_digit(char_arr, digit_arr);
            if (!root) root = insert(root, digit_arr, char_arr);
            else insert(root, digit_arr, char_arr);
            // add digits to trie
            // save word on a last digit
        }
        cin >> query;
        for (int j = 0; j < query; j++)
        {
            cin >> digit_arr;
            print_trie(root, digit_arr);
            // check if such combination of digits exist in digit trie
            // if not print -
            // if yes - print every word of this number and \n
            // then skip to a node pointed by this digit 
            // and iterate through digits and do the same
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


// insert digits to a digit trie

struct Node* insert(struct Node *root, char digit_arr[], char word[])
{
    int i = 0;
    if (!root) root = new struct Node;
    struct Node *curr = root;
    while (digit_arr[i] != '\0' && i < 100)
    {
        if (curr->key[(digit_arr[i] - 50)] == nullptr)
        {
            curr->key[(digit_arr[i] - 50)] = new struct Node;
        }
        curr = curr->key[(digit_arr[i] - 50)];
        i++;
    }
    // digits loaded into trie
    // add word into word trie
    // creating word trie "inside" digit trie node
    if (!curr->word_trie) curr->word_trie = new struct Word_trie;
    insert_word(word, curr->word_trie);
    return root;
}


// insert word to a word trie 

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

void print_trie(struct Node *root, char digit_arr[])
{
    // check if such combination of digits exist in digit trie
    // print "-" if not
    bool if_exist = true;
    int i = 0;
    struct Node *curr = root;
    while (digit_arr[i] != '\0' && i < 100)
    {
        if (curr->key[(digit_arr[i] - 50)] == nullptr)
        {
            cout << "-\n";
            if_exist = false;
            break;
        }
        curr = curr->key[(digit_arr[i] - 50)];
        i++;
    }
    // if yes - print every word of this number and
    // iterate through other digits and print every word left, starting from curr
    if (if_exist)
    {
        // print_word_trie(curr->word_trie);
        print_digit_trie(curr);
        cout << endl;
    }
    // else do nothing 
}

// print all words starting from *root
void print_digit_trie(struct Node *root)
{
    struct Node *curr = root;
    if (curr->word_trie) print_word_trie(curr->word_trie);
    for (int i = 0; i < 8; i++)
    {
        if (curr->key[i] != nullptr) 
        {
            //curr = curr->key[i];
            print_digit_trie(curr->key[i]);
        }
    }
}

// print words from word_trie
void print_word_trie(struct Word_trie *root)
{
    // create one array for all words
    struct Word_trie *curr = root;
    for (int i = 0; i < 26; i++)
    {
        if (curr->letter[i] != nullptr)
        {
            cout << char(97 + i); // convert i element of array into letter
            if (curr->letter[i]->if_word == true) 
            {
                cout << " "; 
            }
            else print_word_trie(curr->letter[i]);
        }
    }
}