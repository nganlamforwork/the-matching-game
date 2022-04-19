#include "Players.h"
#include "Common.h"

Players::Players()
{

}

Players::Players(int level, int mode)
{
	_level = level;
	_mode = mode;
}

int Players::calculateScore(duration<double> _time_played, int remainCards)
{
	_score = ((_level * _level) - remainCards) * 50 - _time_played.count() * 0.5;
	if (_score < 0) _score = 0;
	return _score;
}

std::string Players::getPlayerName()
{	
	int left = 0, top = 0;
	Common::gotoXY(left + 60, top + 12);
	cout << ">> ";
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

void Players::readPlayersFile(std::vector<Players> &player, std::string file)
{
	ifstream readList(file);

	string s;
	int i = 0;
	Players tmp;
	readList.ignore();
	while(!readList.eof())
	{
		getline(readList, s, '/');
		tmp._name = s;
		getline(readList, s, '/');
		tmp._score = stoi(s);
		getline(readList, s, '/');
		tmp._level = stoi(s);
		getline(readList, s, '/');
		tmp._mode = stoi(s);
		getline(readList, s, '\n');
		tmp._display_time = s;
		player.push_back(tmp);
	}

	readList.close();
}

void Players::writePlayersFile()
{
	vector<Players> playerList;
	Players::readPlayersFile(playerList, "PlayersList.txt");
	
	Players tmp;
	tmp._score = _score;
	tmp._name = _name;
	tmp._time_played = _time_played;
	tmp._level = _level;
	tmp._mode = _mode;
	playerList.push_back(tmp);
	
	for (int i = playerList.size() - 1; i > 0; i--){
		if (playerList[i]._score > playerList[i - 1]._score) swap(playerList[i], playerList[i - 1]);
		else break;
	}

	ofstream writeList("PlayersList.txt");

	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]._display_time.empty()){
			writeList << endl;
			writeList << playerList[i]._name << "/" << playerList[i]._score << "/";
			writeList << playerList[i]._level << "/" << playerList[i]._mode << "/";
			writeList << fixed << setprecision(2) << (float)playerList[i]._time_played.count();
			continue;
		}
		writeList << endl;
		writeList << playerList[i]._name << "/" << playerList[i]._score << "/";
		writeList << playerList[i]._level << "/" << playerList[i]._mode << "/";
		writeList << fixed << setprecision(2) << playerList[i]._display_time;
	}

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