
#include "arguments.hpp"
#include <vector>

using std::vector;

int main(int argc, char **argv) {

	cout << "start test" << endl;

	Arguments args(argc, argv);

	cout << "add argument definitions" << endl;

	args.addArgument("", "input");
	args.addArgument("output,o", "output directory");
	args.addArgument("scale", "Coordinate precision, e.g., 1 = meters, 0.001 = milimeters");

	cout << "retrieve some arguments" << endl;

	
	cout << "print keys" << endl;

	for (auto key : args.keys()) {
		cout << "\t" << key << endl;
	}

	cout << "print arguments" << endl;

	{
		auto input = args.get("");
		cout << "Key: \"\"" << endl;
		for (auto token : input) {
			cout << "\t" << token << endl;
		}
	}
	
	{
		auto os = args.get("o");
		cout << "Key: \"o\"" << endl;
		for (auto token : os) {
			cout << "\t" << token << endl;
		}
	}

	{
		auto outputs = args.get("output");
		cout << "Key: \"output\"" << endl;
		for (auto token : outputs) {
			cout << "\t" << token << endl;
		}
	}

	{
		auto doesnt_exist = args.get("doesnt_exist");
		cout << "Key: \"doesnt_exist\"" << endl;
		for (auto token : doesnt_exist) {
			cout << "\t" << token << endl;
		}
	}

	{
		auto scale = args.get<double>("scale");
		cout << "scale: " << scale << endl;
	}

	int a = 0;

	//auto o = args.get<string>("o");
	//auto scale = args.get<double>("scale");

}