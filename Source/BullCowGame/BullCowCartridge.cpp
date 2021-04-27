// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "FileHelper.h"
#include "Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    // can't enter code above Super:: calls
    Super::BeginPlay();
    InitGame();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    //PrintLine(TEXT("The number of Words is: %i"), Words.Num());
    //PrintLine(TEXT("The 14th index of Words is: %s"), *Words[14])
    ValidWords = GetValidWords(Words);
}

void UBullCowCartridge::InitGame() {
    HiddenWord = TEXT("Carlo");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(FString::Printf(TEXT("The hidden word was: %s"), *HiddenWord)); // Debug purposes
    PrintLine(FString::Printf(TEXT("The hidden word length is %i."), HiddenWord.Len()));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) {
        ClearScreen();
        InitGame();
    }
    else {
        PrintLine(Input);
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {
    if (Guess == HiddenWord) {
        PrintLine(TEXT("You win"));
        EndGame();
        return;
    }
    /*
    if (!isIsogram()) {
    PrintLine("There are no repeating letters allowed.");
    return;
    }
    */
    // check right number of characters exists
    if (Guess.Len() != HiddenWord.Len()) { // user error, don't depreciate Lives
        PrintLine(FString::Printf(TEXT("The hidden word is %i characters long. \nTry again."), HiddenWord.Len()));
        return;
    }
    // Guess Incorrect
    --Lives;
    PrintLine(FString::Printf(TEXT("You lost a life. \nYou have %i lives remaining."), Lives));
    if (Lives <= 0) {
        PrintLine(FString::Printf(TEXT("The hidden word was: %s"), *HiddenWord));
        EndGame();
        return;
    }
    // Show number of bulls and cows
    PrintLine(TEXT("Guess again, you have %i lives remaining."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const {
    for (int32 Index = 0; Index < Word.Len(); ++Index) {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); ++Comparison) {
            if (Word[Index] == Word[Comparison]) {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const {
    TArray<FString> Valid;
    for (int32 Index = 0; Index < 3000; ++Index) {
        if (WordList[Index].Len() >= 4 && WordList[Index].Len() <= 7 && IsIsogram(WordList[Index])) {
            Valid.Emplace(WordList[Index]);
        }
    }
    return Valid;
}