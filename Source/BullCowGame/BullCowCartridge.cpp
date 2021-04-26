// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    // can't enter code above Super:: calls
    Super::BeginPlay();
    InitGame();
}

void UBullCowCartridge::InitGame() {
    HiddenWord = TEXT("Carlo");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(FString::Printf(TEXT("The hidden word was: %s"), *HiddenWord)); // Debug purposes
    PrintLine(FString::Printf(TEXT("The hidden word length is %i."), HiddenWord.Len()));
    PrintLine(TEXT("Please press enter to continue..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) {
        ClearScreen();
        InitGame();
    }
    PrintLine(Input);
    if (Input == HiddenWord) {
        PrintLine(TEXT("You win"));
        EndGame();
    }
    else { // guess failed
        if (Input.Len() != HiddenWord.Len()) { // user error, don't depreciate Lives
            PrintLine(FString::Printf(TEXT("The hidden word is %i characters long. \nTry again."), HiddenWord.Len()));
        }
        else { // guessed a word with the correct number of letters
            --Lives;
            PrintLine(FString::Printf(TEXT("You lost a life. \nYou have %i lives remaining."), Lives));
            if (Lives <= 0) {
                PrintLine(FString::Printf(TEXT("The hidden word was: %s"), *HiddenWord));
                EndGame();
            }
        }
    }
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}