//
// Created by oscar on 6/18/2024.
//
#include <string>
#include <vector>

#define WORD_SIZE 5

#ifndef WORDLE_FINDER_COLLECTION_OF_NODES_H
#define WORDLE_FINDER_COLLECTION_OF_NODES_H

struct WordNode
{
    //maks sure that word is always upper case
    std::string word;
    size_t score;

    bool operator>=(const WordNode& other) const
    {
        return score >= other.score;
    }

    bool operator<(const WordNode& other) const
    {
        return score < other.score;
    }
};

struct LetterNode
{
    char letter;
    //word with the largest score will be towards the front of the array lowest will be in the back
    std::vector<WordNode*> positions[WORD_SIZE];
};

#endif //WORDLE_FINDER_COLLECTION_OF_NODES_H
