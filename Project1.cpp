#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice {Stone = 1 , Paper = 2 , Scissors = 3};
enum enWinner {Player  = 1 , Computer = 2 , Draw = 3};

struct stRoundInfo {
    unsigned short int Rounds = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults {
    short GameRounds = 0;
    short PlayerWinTimes;
    short ComputerWinTimes;
    short DrawTimes;
    enWinner GameWinner;

    string WinnerName = "";
};

int RandomNumber(int From , int To) {
    
    int Random = rand() % (To - From + 1) + From;
    return Random;
}


string WinnerName(enWinner Winner) {
    string ArrWinnerName[3] = {"Player" , "Computer" , "No Winner"};
    return ArrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice GameChoice) {
    string ArrGameChoice[3] = {"Stone" , "Paper" , "Scissors"};
    return ArrGameChoice[GameChoice - 1];
}

enWinner WhoWinTheGame(short PlayerWonTimes , short ComputerWonTimes) {

    if(PlayerWonTimes > ComputerWonTimes) 
        return enWinner :: Player;
    else if (PlayerWonTimes < ComputerWonTimes) 
        return enWinner :: Computer;
    else
        return enWinner :: Draw;
}

stGameResults FillGameResults(int GameRounds , short PlayerWonTimes , short ComputerWonTimes , short DrawTimes) {

    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = PlayerWonTimes;
    GameResults.ComputerWinTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWinTheGame(PlayerWonTimes , ComputerWonTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}



enGameChoice ReadPlayerChoice() {
    short Choice;
    do {
        cout << "\nYour Choice : [1] Stone , [2] Paper , [3] Scissors ? : ";
        cin >> Choice;

    }while (Choice > 3 || Choice < 1);

    return (enGameChoice) Choice;
}

enGameChoice GetComputerChoice() {
    return (enGameChoice) RandomNumber(1 , 3);
}


enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
    
    if(RoundInfo.ComputerChoice == RoundInfo.PlayerChoice) {
        return enWinner :: Draw;
    }

    switch(RoundInfo.PlayerChoice) {
        case enGameChoice :: Stone :
            if(RoundInfo.ComputerChoice == enGameChoice :: Paper) 
                return enWinner :: Computer;
            break;
        case enGameChoice :: Paper:
            if(RoundInfo.ComputerChoice == enGameChoice :: Scissors)
                return enWinner :: Computer;
            break;
        case enGameChoice :: Scissors:
            if(RoundInfo.ComputerChoice == enGameChoice :: Stone) 
                return enWinner :: Computer;
            break;
    }

    return enWinner :: Player;
}


void SetWinnerScreenColor(enWinner Winner) {
    
    switch(Winner) {
        case enWinner :: Player:
            system("color 2F");
            break;
        case enWinner :: Computer:
            system("color 4F");
            cout << "\a";
            break;
        default :
            system("color 6F");
            break;
    }
}




void PrintRoundResults(stRoundInfo RoundInfo) {

    cout << "\n_____________Round [" << RoundInfo.Rounds << "]____________\n\n";
    cout << "Player Choice : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner : [ " << RoundInfo.WinnerName <<" ]"<< endl; 
    cout << "________________________\n" << endl;

    //SetWinnerScreenColor(RoundInfo.Winner);



}


string Tabs(short NumOfTabs) {
    string Tab = "";
    for(int i = 0 ; i < NumOfTabs ; i++ ) {
        Tab += "\t";
    }
    return Tab;
}




void ShowGameOverScreen() {

    cout << Tabs(2) << 
    "________________________________________________________________\n\n";
    cout << Tabs(2) << "                       +++ G a m e O v e r +++\n\n"; 
    cout << Tabs(2) << "________________________________________________________________\n\n";

}



stGameResults PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0 , ComputerWinTimes = 0 , DrawTimes = 0;

    for (int GameRound = 1 ; GameRound <= HowManyRounds ; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins : \n";
        RoundInfo.Rounds = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);


        if(RoundInfo.Winner == enWinner :: Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner :: Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds , PlayerWinTimes , ComputerWinTimes , DrawTimes);
}




void ShowFinalGameResults(stGameResults GameResults) {

    cout << Tabs(2) << "________________________ [Game Results] ________________________\n\n";
    cout << Tabs(2) << "Game Rounds            : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Won Times       : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer Won Times     : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "DrawTimes              : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner           : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "________________________________________________________________\n\n";

    //SetWinnerScreenColor(GameResults.GameWinner);


}



short ReadHowManyRounds() {
    short GameRounds;

    do
    {
        cout << "How Many Rounds 1 To 10 ? ";
        cin >> GameRounds;
    } while (GameRounds > 10 || GameRounds < 1 );
    
    return GameRounds;
}


void ResetScreen() {
    system("cls");
    system("Color 6F");
}




void StartGame() {
    char PlayAgain;

    do {
        //ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << "\n\nDo You Want To Play Again ? " ;
        cin>> PlayAgain;


    } while(PlayAgain == 'Y' || PlayAgain == 'y');

    cout << "\n\nDo You Want To Play Again ? " ;
    cin>> PlayAgain;

}













int main() {
    srand((unsigned int ) time (NULL));

    StartGame();

    return 0;
}