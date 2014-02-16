#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

struct Moneta
{
	int svoris;
	int verte;
	Moneta(){}
	Moneta(int v, int s) :svoris(s), verte(v){}
};

int Sprendimas(int svoris, const vector<Moneta> &monetos, function<bool(int left, int right)> comparator);
pair<int, vector<Moneta>> Skaitymas(string failas);

int main()
{
	auto data = Skaitymas("duomenai.txt");
	int didziausia = Sprendimas(data.first, data.second, [=](int left, int right){ return left > right; });
	int maziausia = Sprendimas(data.first, data.second, [=](int left, int right){ return left < right; });
	cout << "Didziausia imanoma verte " << didziausia << endl;
	cout << "Maziausia imanoma verte " << maziausia << endl;
	system("pause");
	return 0;
}

int Sprendimas(int svoris, const vector<Moneta> &monetos, function<bool(int left, int right)> comparator)
{
	vector<int> vertes(svoris + 1, -1);
	for (auto moneta : monetos)
	{
		if (comparator(vertes[moneta.svoris], moneta.verte) || vertes[moneta.svoris] == -1)
			vertes[moneta.svoris] = moneta.verte;
	}
	for (int i = 1; i <= svoris; i++)
	{
		for (auto moneta : monetos)
		{
			if (i - moneta.svoris > 0)
			{
				if (vertes[i] == -1 || comparator(vertes[i - moneta.svoris] + moneta.verte, vertes[i]))
				{
					if (vertes[i - moneta.svoris] != -1)
					{
						vertes[i] = vertes[i - moneta.svoris] + moneta.verte;
					}
				}
			}
		}
	}
	return vertes[svoris];
}

pair<int, vector<Moneta>> Skaitymas(string failas)
{
	ifstream in(failas);
	int s, m, svoris, verte;
	in >> s >> m;
	vector<Moneta> ret;
	for (int i = 0; i < m; i++)
	{
		in >> verte >> svoris;
		ret.emplace_back(verte, svoris);
	}
	return pair<int, vector<Moneta>>(s, move(ret));
}