//
// Created by oscar on 6/18/2024.
//
#include <utility>
#include <stdexcept>

#include "collection_of_nodes.h"


#ifndef WORDLE_FINDER_WORDLE_SEARCH_H
#define WORDLE_FINDER_WORDLE_SEARCH_H

#define FIND_IN_ARRAY 65
#define FINDER_SIZE 26
#define CHAR_HIERARCHY_SIZE 27
#define CHAR_HIERARCHY const char charHier[CHAR_HIERARCHY_SIZE] \
{' ','Q','J','Z','X','V','K','W','Y','F','B','G','H','M','P','D','U','C','L','S','N','T','O','I','R','A','E'}

class Searcher
{
public:
    Searcher() : finder{new LetterNode*[FINDER_SIZE]}
    {
        for(size_t i = 0; i < FINDER_SIZE; ++i)
        {
            finder[i] = nullptr;
        }
    }

    ~Searcher()
    {
        for(int i = wordNodeVector.size() - 1; i >= 0; --i)
        {
            delete wordNodeVector[i];
        }

        for(int i = 0; i < FINDER_SIZE; ++i)
        {
            delete finder[i];
        }
        delete[] finder;
    }

    //sure that we do not have duplicate words in the database
    //make a function that finds these words
    void add(const std::string& word)
    {
        if(word.size() > WORD_SIZE) throw std::logic_error("cannot add words greater than 5");

        std::string wordUpp{toUpper(word)};
        int currentCharacter{};
        std::vector<WordNode*>::iterator positionOfWordScore;
        wordNodeVector.push_back(new WordNode{wordUpp, calcScore(wordUpp)});
        WordNode* tmpNode{wordNodeVector[wordNodeVector.size() - 1]};

        for(size_t i = 0; i < word.size(); ++i)
        {
            currentCharacter = findLetter(word[i]);
            if(finder[currentCharacter] == nullptr)
            {
                //if the character does not exist then make the node that stores the character
                finder[currentCharacter] = new LetterNode{word[i]};
            }

            if(finder[currentCharacter]->positions[i].empty())
            {
                //if the vector that holds the position of the character is empty then point the pointer to the Node
                finder[currentCharacter]->positions[i].push_back(tmpNode);
            }

            else
            {
                //insert the wordNode at the given position
                //adds the position of the character to the iterator of the vector in order to use for insertion
                positionOfWordScore = finder[currentCharacter]->positions[i].begin() +
                        findPosition(currentCharacter, i, tmpNode,
                                     0,finder[currentCharacter]->positions[i].size() - 1);

                finder[currentCharacter]->positions[i].insert(positionOfWordScore, tmpNode);
            }

        }
    }

    //note: this function does not find said word
    //it will return a word that is most likely in the wordle
    std::string find(const std::string& word)
    {

    }


    [[nodiscard]] size_t getSize() const {return wordNodeVector.size();}

private:
    //A is 0, B is 2 C is 3 etc
    LetterNode** finder;
    std::vector<WordNode*> wordNodeVector;
    bool* availableLetter;


    //assuming that vector is sorted
    //finds and ret
    size_t findPosition(const int& currentCharacter,const size_t& characterPosition, const WordNode* node, const size_t& beginning,const size_t& end)
    {
        size_t position{beginning + (end - beginning)/ 2};
        size_t returnVar{};

        if(beginning == end)
        {
            if(node->score >= finder[currentCharacter]->positions[characterPosition][end]->score)
                return end;

            return end + 1;
        }


        if(finder[currentCharacter]->positions[characterPosition][position]->score >= node->score &&
        finder[currentCharacter]->positions[characterPosition][position + 1]->score <= node->score )
            return position + 1;


        if(finder[currentCharacter]->positions[characterPosition][position]->score <= node->score &&
       finder[currentCharacter]->positions[characterPosition][position + 1]->score <= node->score )
            return findPosition(currentCharacter, characterPosition, node, beginning, position);

        if(finder[currentCharacter]->positions[characterPosition][position]->score >= node->score &&
       finder[currentCharacter]->positions[characterPosition][position + 1]->score >= node->score )
            return findPosition(currentCharacter, characterPosition, node, position + 1, end);

    }

    [[nodiscard]] static size_t calcScore(const std::string& word)
    {
        CHAR_HIERARCHY;
        size_t rtnScore{};
        for (char character: word)
        {
            for (size_t i = 1; i < CHAR_HIERARCHY_SIZE; ++i)
            {
                if(character == charHier[i])
                {
                    rtnScore += i;
                    break;
                }
            }
        }

        return rtnScore;
    }

    static std::string toUpper(const std::string& word)
    {
        std::string rtnString{};
        char appender{};
        for(char character : word)
        {
            appender = static_cast<char>(toupper(character));
            rtnString.push_back(appender);
        }
        return rtnString;
    }

    static int findLetter(const char letter)
    {
        char newLetter{static_cast<char>(std::toupper(letter))};
        int newLetterToSize{newLetter - FIND_IN_ARRAY};

        return newLetterToSize;
    }

};


#endif //WORDLE_FINDER_WORDLE_SEARCH_H
