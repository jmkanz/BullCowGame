//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Justin Kanz on 5/11/19.
//  Copyright © 2019 Justin Kanz. All rights reserved.
//
#pragma once

#include "FBullCowGame.hpp"
#include <map>

#define TMap std::map

// to make the game Unreal friendly
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32)MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 7}, {5,10}, {6,14} }; //set number of guesses dependent on word length
    return WordLengthToMaxTries[(int32)MyHiddenWord.length()];
}


void FBullCowGame::reset()
{
    const FString HIDDEN_WORD = "fuckit"; // this must be an isogram
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!bIsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram; // if the guess isn't an isogram
    }
    else if (!bIsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase; //if the guess isn't all lowercase
    }
    else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length; //if the guess length is wrong
    }
    else // otherwise
    {
        return EGuessStatus::OK; // reutrn OK
    }
    
}



// recieves a VALID guess, icrements turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    
    //loop through all letters in the hidden word
    int32 WordLength = (int32)MyHiddenWord.length(); //assuming same length as guess
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        // compare letters against the guess
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            //if they match then
            if (Guess[GChar] == MyHiddenWord[MHWChar])
            {
                //if they're in the same place
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;  //increment bulls
                }
                else
                {
                    BullCowCount.Cows++;  //increment cows
                }
            }
                //else
        }
    }
    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::bIsIsogram(FString Word) const
{
    // treat 0 and 1 letter words as isograms
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen; // setup our map
    for (auto Letter : Word) // for all letters of the word
    {
        Letter = tolower(Letter); // handles mixed case
        if (LetterSeen[Letter]) { //if the letter is in the map
            return false; // we do not have an isogram
        } else {
            LetterSeen[Letter] = true; //add the letter to the map as seen
        }
        
    }
    
    return true; // for example in cases where /0 is entered
    
    
}

bool FBullCowGame::bIsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter))// if not a lowercase letter
        {
            return false;//return false
        }
    }
    return true;
}




