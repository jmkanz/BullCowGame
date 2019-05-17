//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Justin Kanz on 5/11/19.
//  Copyright © 2019 Justin Kanz. All rights reserved.
//
/* THe game logic (no view code or direct user interaction)
 The game is a simple guess the word game based on Mastermind
 */

#pragma once

#ifndef FBullCowGame_hpp

#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

// to make the game Unreal friendly
using int32 = int;
using FString = std::string;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
    
};


class FBullCowGame
{
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    
    bool IsGameWon() const;
    
    EGuessStatus CheckGuessValidity(FString) const;

    void reset();
    FBullCowCount SubmitValidGuess(FString);
    
//try to ignore this and focus on the interface above
private:
    //see constructor for initilization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool bIsIsogram(FString) const;
    bool bIsLowercase(FString) const;
};

#endif /* FBullCowGame_hpp */
