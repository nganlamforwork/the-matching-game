#include "Players.h"
#include "Common.h"

Players::Players()
{

}

Players::Players(int mode, int left, int top)
{
	_size = mode;
	_left = left;
	_top = top;
}

int Players::calculateScore(duration<double> _time_played, int remainCards)
{
	_score = ((_size * _size) - remainCards) * 50 - _time_played.count() * 0.5;
	if (_score < 0) _score = 0;
	return _score;
}

std::string Players::getPlayerName()
{	
	int left = 0, top = 0;
	Common::gotoXY(left + 60, top + 12);
	cout << ">>";
	std::string name;
	getline(cin, name);
	while (name.empty())
	{
		Common::gotoXY(left + 51, top + 11);
		cout << "PLEASE ENTER A VALID NAME";
		Common::gotoXY(left + 62, top + 12);
		cout << "                                        ";
		Common::gotoXY(left + 62, top + 12);
		getline(cin, name);
	}
	_name = name;

	return _name;
}

void Players::readPlayersFile(std::vector<Players> &player)
{
	ifstream readList("PlayersList.txt");

	string s;
	int i = 0;
	Players tmp;
	readList.ignore();
	while(!readList.eof())
	{
		getline(readList, s, '/');
		tmp._name = s;
		getline(readList, s, '/');
		tmp._display_score = s;
		getline(readList, s, '\n');
		tmp._display_time = s + 's';
		player.push_back(tmp);
	}

	readList.close();
}

void Players::writePlayersFile()
{
	ofstream writeList("PlayersList.txt", ios::app);

	writeList << endl;
	writeList << _name << "/" << _score << "/" << setprecision(2) << (float)_time_played.count();

	writeList.close();
}

void Players::sortPlayers(vector<Players>& playerList)//working on ideas
{
	for (int i = 1; i < playerList.size(); i++)
	{
		if (playerList[i]._score > playerList[i - 1]._score)
		{
			int index = i - 1;
			int score = playerList[i]._score;
			Players key = playerList[i];
			while (index >= 0 && score > playerList[index]._score)
			{
				playerList[i + 1] = playerList[i];
				index--;
			}
			playerList[index + 1] = key;
		}
	}
}