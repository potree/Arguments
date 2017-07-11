
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using std::unordered_map;
using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;

class Argument {
public:
	string id = "";
	string description = "";

	Argument(string id, string description) {
		this->id = id;
		this->description = description;
	}

	string fullname() {
		auto i = id.find_first_of(",");

		if (i == string::npos && id.size() > 1) {
			return id;
		} else if (i == string::npos && id.size() <= 1) {
			return "";
		}

		string t1 = id.substr(0, i);
		string t2 = id.substr(i + 1);

		if (t1.size() > 1) {
			return t1;
		} else if (t2.size() > 1) {
			return t2;
		} else {
			cerr << "Error trying to retrieve full name from id: " << id;
			exit(0);
		}
	}

	string shortname() {
		if (id.size() <= 1) {
			return id;
		}

		auto i = id.find_first_of(",");

		if (i == string::npos) {
			return "";
		}

		string t1 = id.substr(0, i);
		string t2 = id.substr(i + 1);

		if (t1.size() == 1) {
			return t1;
		} else if (t2.size() == 1) {
			return t2;
		} else {
			cerr << "Error trying to retrieve shortname from id: " << id;
			exit(0);
		}
	}
};

class Arguments {

private:
	bool startsWith(const string &str, const string &prefix) {
		if (str.size() < prefix.size()) {
			return false;
		}

		return str.substr(0, prefix.size()).compare(prefix) == 0;
	}

public:

	int argc = 0;
	char **argv = nullptr;

	bool ignoreFirst = true;

	vector<string> tokens;
	vector<Argument> argdefs;
	unordered_map<string, vector<string>> map;

	Arguments(int argc, char **argv, bool ignoreFirst = true) {
		this->argc = argc;
		this->argv = argv;
		this->ignoreFirst = ignoreFirst;

		for (int i = ignoreFirst ? 1 : 0; i < argc; i++) {
			string token = string(argv[i]);
			tokens.push_back(token);
		}

		string currentKey = "";
		map.insert({ currentKey, {} });
		for (string token : tokens) {
			if(startsWith(token, "---")) {
				cerr << "Invalid argument: " << token << endl;
				exit(1);
			} else if (startsWith(token, "--")) {
				currentKey = token.substr(2);
				map.insert({ currentKey,{} });
			} else if (startsWith(token, "-")) {
				currentKey = token.substr(1);
				map.insert({ currentKey,{} });
			} else {
				map[currentKey].push_back(token);
			}
		}
	}

	void addArgument(string id, string description) {
		Argument arg(id, description);

		argdefs.push_back(arg);
	}

	Argument *getArgument(string name) {
		for (Argument &arg : argdefs) {
			if (name == "") {
				if (arg.id == "") {
					return &arg;
				}
			} else if (arg.shortname() == name || arg.fullname() == name) {
				return &arg;
			}
		}
		
		return nullptr;
	}

	vector<string> keys() {
		vector<string> keys;
		for (auto entry : map) {
			keys.push_back(entry.first);
		}

		return keys;
	}

	string usage() {
		return "TODO";
	}

	bool has(string name) {
		Argument *arg = getArgument(name);

		if (arg == nullptr) {
			return false;
		}

		if (!arg->shortname().empty() && map.find(arg->shortname()) != map.end()) {
			return true;
		}

		if (!arg->fullname().empty() && map.find(arg->fullname()) != map.end()) {
			return true;
		}

		return false;
	}

	vector<string> get(string name) {
		Argument *arg = getArgument(name);

		if (arg == nullptr) {
			return {};
		} else if (arg->id == "") {
			if (map.find("") != map.end()) {
				return map[""];
			} else {
				return {};
			}
		} else {
			vector<string> result;

			if (!arg->shortname().empty() && map.find(arg->shortname()) != map.end()) {
				auto tokens = map[arg->shortname()];
				result.insert(result.end(), tokens.begin(), tokens.end());
			}

			if (!arg->fullname().empty() && map.find(arg->fullname()) != map.end()) {
				auto tokens = map[arg->fullname()];
				result.insert(result.end(), tokens.begin(), tokens.end());
			}

			return result;
		}

		return {};
	}

	template<typename T>
	T get(string name) {
		if (has(name)) {
			return T(get(name)[0]);
		} else {
			return T();
		}
	}

	template<>
	vector<string> get<vector<string>>(string name) {
		return get(name);
	}

	template<>
	string get<string>(string name) {
		if (has(name)) {
			return get(name)[0];
		} else {
			return "";
		}
	}

	template<>
	double get<double>(string name) {
		if (!get(name).empty()) {
			return std::stod(get(name)[0]);
		} else {
			return 0.0;
		}
	}

	template<>
	int get<int>(string name) {
		if (has(name)) {
			return std::stoi(get(name)[0]);
		} else {
			return 0;
		}
	}
};

