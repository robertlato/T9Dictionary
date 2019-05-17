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
    bool if_word = false;
};

struct Node // digit trie
{
    struct Node *key[8] = {}; // array of 8 Node ptrs
    struct Word_trie *word_trie = nullptr;
};

char char_arr[101]; 
char digit_arr[101];

//*****************************************************************************
//****** fuction declaration ******//

void char_to_digit(char word[], char digits[]);
struct Node* insert(struct Node *root, char digit_arr[], char word[]);
void insert_word(char word[], struct Word_trie *root);
void print_trie(struct Node *root, char digit_arr[]);
void print_word_trie(struct Word_trie *root, char digit_arr[], int index);
void print_digit_trie(struct Node *root, char digit_arr[]);
void delete_digit_trie(struct Node *root);
void delete_char_trie(struct Word_trie *root);



//*****************************************************************************
//****** main program ********// 

int main()
{
    int words; // number of words
    struct Node *root = nullptr;
    int query; // number of queries
    while (cin >> words)
    {
        for (int i = 0; i < words; i++)
        {
            cin >> char_arr;
            char_to_digit(char_arr, digit_arr);
            // add digits to trie
            // save word on a last digit
            if (!root) root = insert(root, digit_arr, char_arr);
            else insert(root, digit_arr, char_arr);
        }
        cin >> query;
        for (int j = 0; j < query; j++)
        {
            cin >> digit_arr;
            // check if digits are positive, excluding 0 and 1
            int i = 0;
            while (i < 100 && digit_arr[i] != '\0')
            {
                if (digit_arr[i] - 48 < 2 || digit_arr[i] - 48 > 9) return 0;
                i++;
            }
            print_trie(root, digit_arr);
        }
    }
    if (root) delete_digit_trie(root);
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
    digits[i] = '\0'; // mark end of the word
}


// insert digits to a digit trie

struct Node* insert(struct Node *root, char digit_arr[], char word[])
{
    int i = 0;
    if (!root) root = new struct Node;
    struct Node *curr = root;
    // "load" digits into digit_trie
    while (i < 101 && digit_arr[i] != '\0')
    {
        if (curr->key[(digit_arr[i] - 50)] == nullptr)
        {
            curr->key[(digit_arr[i] - 50)] = new struct Node;
        }
        curr = curr->key[(digit_arr[i] - 50)];
        i++;
    }
    // digits loaded into trie
    // create word trie "inside" digit trie node
    if (!curr->word_trie) curr->word_trie = new struct Word_trie;
    insert_word(word, curr->word_trie); // add word into word trie
    return root;
}


// insert word to a word trie 

void insert_word(char word[], struct Word_trie *root)
{
    int i = 0;
    struct Word_trie *curr = root;
    while (i < 101 && word[i] != '\0')
    {
        if (curr->letter[word[i] - 'a'] == nullptr)
        {
            curr->letter[word[i] - 'a'] = new struct Word_trie;
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
    while (i < 101 && digit_arr[i] != '\0')
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
    // if exist - print every word of this number
    // iterate through other digits and print every word left, starting from curr
    if (if_exist)
    {
        i = 0;
        print_digit_trie(curr, digit_arr);
        cout << endl;
    }
    // else do nothing 
}

// print all words starting from *root
void print_digit_trie(struct Node *root, char digit_arr[])
{
    struct Node *curr = root;
    if (curr->word_trie) print_word_trie(curr->word_trie, digit_arr, 0);
    for (int i = 0; i < 8; i++)
    {
        if (curr->key[i] != nullptr) 
        {
            print_digit_trie(curr->key[i], digit_arr);
        }
    }
}

// print words from word_trie
void print_word_trie(struct Word_trie *root, char digit_arr[], int index)
{
    struct Word_trie *curr = root;
    for (int i = 0; i < 26; i++)
    {
        if (curr->letter[i] != nullptr)
        {
            // convert i element of array into letter
            digit_arr[index] = char(97 + i); 
            index++;
            if (curr->letter[i]->if_word == true) 
            {
                digit_arr[index] = '\0';
                int i = 0;
                while (i < 101 && digit_arr[i] != '\0')
                {
                    cout << digit_arr[i];
                    i++;
                }
                cout << " "; 
            }
            else print_word_trie(curr->letter[i], digit_arr, index);
            index--;
        }
    }
}

void delete_digit_trie(struct Node *root)
{
    struct Node *curr = root;
    for (int i = 0; i < 8; i++)
    {
        if (curr->key[i]) delete_digit_trie(curr->key[i]);
    }
    if (curr->word_trie) delete_char_trie(curr->word_trie);
    delete curr;
}

void delete_char_trie(struct Word_trie *root)
{
    struct Word_trie *curr = root;
    for (int i = 0; i < 26; i++)
    {
        if (curr->letter[i]) delete_char_trie(curr->letter[i]);
    }
    delete curr;
}
