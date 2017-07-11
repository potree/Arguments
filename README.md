


# About

Intented as a replacement of boost::program_options and developed to the extent that is needed by the PotreeConverter.

# Usage

```
int main(int argc, char **argv) {

	Arguments args(argc, argv);

	args.addArgument("", "input");
	args.addArgument("output,o", "output directory");
	args.addArgument("scale", "Coordinate precision, e.g., 1 = meters, 0.001 = milimeters");
	
	// print all occuring keys:
	for (auto key : args.keys()) {
		cout << "\t" << key << endl;
	}
	
	// get a list of values for unnamed arguments
	vector<string> input = args.get("");
	
	// get a list of values for the -o or --output argument
	vector<string> os = args.get("o");
	
	// get a list of values for the -o or --output argument.
	// -o and --output are the same argument so this will 
	// return exactly the same as args.get("o")
	vector<string> os = args.get("output");
	
	// because there is no --doesnt_exist argument, this call will return an empty list
	vector<string> doesnt_exist = args.get("doesnt_exist");
	
	// this will return the --scale <value> as a double or 0.0 if 
	// --scale is not specified or --scale is specified without value.
	double scale = args.get<double>("scale");
	
	// returns true of -o or --output are specified
	bool hasO = args.has("o");
}
	
```


Calling the test app from the windows PowerShell:
```
.\Arguments.exe `
 "abc" `
 "def" `
 --output "lala" "lele" `
 -o "what" `
 --scale 1.23
```

Will result in this output:
```
print keys

        output
        o
        scale
print arguments
Key: ""
        abc
        def
Key: "o"
        what
        lala
        lele
Key: "output"
        what
        lala
        lele
Key: "doesnt_exist"
scale: 1.23
```