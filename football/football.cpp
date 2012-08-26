// Scott Wiedemann
// 10/06/2010
// football.cpp
// CSCI562-A Applied Algorithms and Data Structures

#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


string trash;

class team
{
	public:
		string name;
		int points;
		int gamesplayed;
		int wins;
		int ties;
		int losses;
		int goalsscored;
		int goalsagainst;

		team()
		{ }

		team(string Name)
		{
			name=Name;
			points=0;
			gamesplayed=0;
			wins=0;
			ties=0;
			losses=0;
			goalsscored=0;
			goalsagainst=0;
		}
};



string StringToUpper(string strToConvert)
{
	for(unsigned int i=0;i<strToConvert.length();i++)
	{
		strToConvert[i] = tolower(strToConvert[i]);
	}
	return strToConvert;
}



struct teamcmp
{
	bool operator()(team A,team B)
	{
		if(A.points!=B.points)
		{
			return A.points>B.points;
		}
		else if(A.wins!=B.wins)
		{
			return A.wins>B.wins;
		}
		else if(A.goalsscored-A.goalsagainst!=B.goalsscored-B.goalsagainst)
		{
			return (A.goalsscored-A.goalsagainst)>(B.goalsscored-B.goalsagainst);
		}
		else if(A.goalsscored!=B.goalsscored)
		{
			return A.goalsscored>B.goalsscored;
		}
		else if(A.gamesplayed!=B.gamesplayed)
		{
			return A.gamesplayed<B.gamesplayed;
		}
		else
		{
			return StringToUpper(A.name)<StringToUpper(B.name);
		}
	}
} teamcmp;


class tournament
{
	public:
		string name;
		vector<team> teams;

		tournament()
		{ }

		tournament(string Name)
		{
			name=Name;
		}
};

void readInput(tournament &Tour)
{
	// read in teams
	int Nteams;
	string TeamName;
	cin >> Nteams;
	getline(cin, trash);
	//cout << Nteams << endl;
	for(int i=0; i<Nteams; i++)
	{
		getline(cin,TeamName);
		Tour.teams.push_back(team(TeamName));
		//cout << Tour.teams[i].name << endl;
	}

	// read in games
	int NGames;
	cin >> NGames;
	getline(cin, trash);
	//cout << NGames << endl;

	string FirstTeamName;
	string SecondTeamName;
	int Firstteamscore;
	int Secondteamscore;

	for(int i=0; i<NGames; i++)
	{
		getline(cin,FirstTeamName,'#');
		cin >> Firstteamscore;
		getline(cin,trash,'@');
		cin >> Secondteamscore;
		getline(cin,trash,'#');
		getline(cin,SecondTeamName);

		//cout << FirstTeamName << " " << Firstteamscore << "," << SecondTeamName << " " << Secondteamscore << endl;

		for(int j=0; j<Tour.teams.size(); j++)
		{
			if(Tour.teams[j].name==FirstTeamName)
			{
				Tour.teams[j].gamesplayed++;
				Tour.teams[j].goalsscored+=Firstteamscore;
				Tour.teams[j].goalsagainst+=Secondteamscore;
				if(Firstteamscore>Secondteamscore)
				{
					Tour.teams[j].wins++;
					Tour.teams[j].points+=3;
				}
				else if(Firstteamscore==Secondteamscore)
				{
					Tour.teams[j].ties++;
					Tour.teams[j].points++;
				}
				else
				{
					Tour.teams[j].losses++;
				}
			}
			else if(Tour.teams[j].name==SecondTeamName)
			{
				Tour.teams[j].gamesplayed++;
				Tour.teams[j].goalsscored+=Secondteamscore;
				Tour.teams[j].goalsagainst+=Firstteamscore;
				if(Secondteamscore>Firstteamscore)
				{
					Tour.teams[j].wins++;
					Tour.teams[j].points+=3;
				}
				else if(Firstteamscore==Secondteamscore)
				{
					Tour.teams[j].ties++;
					Tour.teams[j].points++;
				}
				else
				{
					Tour.teams[j].losses++;
				}
			}
		}
	}
}


void writeOutput(tournament Tour)
{
	sort(Tour.teams.begin(), Tour.teams.end(), teamcmp);
	cout << Tour.name << endl;
	for(int i=0; i<Tour.teams.size(); i++)
	{
		cout << i+1 << ") " << Tour.teams[i].name << " " << Tour.teams[i].points << "p, " << Tour.teams[i].gamesplayed << \
		"g (" << Tour.teams[i].wins << "-" << Tour.teams[i].ties << "-" << Tour.teams[i].losses << "), " << \
		Tour.teams[i].goalsscored-Tour.teams[i].goalsagainst << "gd (" << Tour.teams[i].goalsscored << "-" << Tour.teams[i].goalsagainst << ")" << endl;
	}
}

int main()
{
	int NTours;
	string TourName;
	cin >> NTours;
	getline(cin, trash);

	for(int i=0; i<NTours; i++)
	{
		getline(cin, TourName);
		tournament cTour(TourName);
		readInput(cTour);
		
		writeOutput(cTour);
		if(i!=NTours-1)
			cout << endl;
	}
	return 0;
}
