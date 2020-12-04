#include <iostream>
#include <vector>
#include <string>

using namespace std;

string trash;

string toLowercase(string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

class Team {
	public:
		string name;
		int points;
		int gamesplayed;
		int wins;
		int ties;
		int losses;
		int goalsscored;
		int goalsagainst;

		Team(string& name) {
			this->name = name;
			points = 0;
			gamesplayed = 0;
			wins = 0;
			ties = 0;
			losses = 0;
			goalsscored = 0;
			goalsagainst = 0;
		}
};

struct TeamComparator {
	bool operator()(Team* A, Team* B) {
		if (A->points != B->points) {
			return A->points > B->points;
		} else if (A->wins != B->wins) {
			return A->wins > B->wins;
		} else if (A->goalsscored - A->goalsagainst != B->goalsscored - B->goalsagainst) {
			return (A->goalsscored - A->goalsagainst) > (B->goalsscored - B->goalsagainst);
		} else if (A->goalsscored != B->goalsscored) {
			return A->goalsscored > B->goalsscored;
		} else if (A->gamesplayed != B->gamesplayed) {
			return A->gamesplayed < B->gamesplayed;
		} else {
			return toLowercase(A->name) < toLowercase(B->name);
		}
	}
} TeamComparator;


class Tournament {
	public:
		string name;
		vector<Team*> teams;

		Tournament(string name) {
			this->name = name;
		}
};

void readInput(Tournament* tournament) {
	int teamsCount;
	cin >> teamsCount;
	getline(cin, trash);
	string teamName;
	for (int i = 0; i < teamsCount; i++) {
		getline(cin, teamName);
		tournament->teams.push_back(new Team(teamName));
	}

	int gameCount;
	cin >> gameCount;
	getline(cin, trash);

	string firstTeamName;
	string secondTeamName;
	int firstTeamScore;
	int secondTeamScore;

	for (int i = 0; i<gameCount; i++) {
		getline(cin, firstTeamName, '#');
		cin >> firstTeamScore;
		getline(cin, trash, '@');
		cin >> secondTeamScore;
		getline(cin, trash, '#');
		getline(cin, secondTeamName);

		for (int j=0; j < tournament->teams.size(); j++) {
			Team* team = tournament->teams[j];

			if (team->name == firstTeamName) {
				team->gamesplayed++;
				team->goalsscored += firstTeamScore;
				team->goalsagainst += secondTeamScore;
				if (firstTeamScore > secondTeamScore) {
					team->wins++;
					team->points += 3;
				} else if (firstTeamScore == secondTeamScore) {
					team->ties++;
					team->points++;
				} else {
					team->losses++;
				}
			} else if (team->name == secondTeamName) {
				team->gamesplayed++;
				team->goalsscored += secondTeamScore;
				team->goalsagainst += firstTeamScore;
				if (secondTeamScore > firstTeamScore) {
					team->wins++;
					team->points += 3;
				} else if (firstTeamScore == secondTeamScore) {
					team->ties++;
					team->points++;
				} else {
					team->losses++;
				}
			}
		}
	}
}

void writeOutput(Tournament* tournament) {
	sort(tournament->teams.begin(), tournament->teams.end(), TeamComparator);
	cout << tournament->name << endl;

	for(int i = 0; i < tournament->teams.size(); i++) {
		Team* team = tournament->teams[i];
		cout << i+1 << ") " \
		<< team->name << " " \
		<< team->points << "p, " \
		<< team->gamesplayed \
		<< "g (" << team->wins << "-" << team->ties << "-" << team->losses << "), " \
		<< team->goalsscored - team->goalsagainst \
		<< "gd (" << team->goalsscored << "-" << team->goalsagainst << ")" \
		<< endl;
	}
}

int main(int argc, const char *argv[]) {
	int tournamentCount;
	string tournamentName;
	cin >> tournamentCount;
	getline(cin, trash);

	for(int i = 0; i < tournamentCount; i++) {
		getline(cin, tournamentName);
		Tournament* tournament = new Tournament(tournamentName);
		readInput(tournament);
		writeOutput(tournament);
		if (i != tournamentCount - 1) {
			cout << endl;
		}
	}
	return 0;
}
