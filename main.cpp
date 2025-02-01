#include "Game.h"

class notValidArguments{};
class tooManyArguments{};

void getMode(const vector<string>& args, bool& save, bool& load, bool& silent)
{
	if (args.size() > 3)
		throw tooManyArguments();
	if (std::find(args.begin(), args.end(), "-save") != args.end()) //Save mode
	{
		save = true;
		load = silent = false;
	}
	else if (args.size() > 1 && args[1] == "-load") //Load mode
	{

		if (args.size() == 3 && args[2] == "-silent")//Load silent mode
		{

			silent = true;
			load = save = false;
		}
		else //Regular load mode
		{
			load = true;
			save = silent = false;
		}
	}
	else if (args.size() > 1) //Not supported arguments
		throw notValidArguments();
	else
	load = save = silent = false;

}
int main(int argc,char* argv[])
{
	vector<string> args(argv, argv + argc); //Hold the command arguments with a vector of strings
	bool saveMode,silentMode,loadMode;

	try {
		getMode(args, saveMode, loadMode, silentMode);
	}
	catch(tooManyArguments& tma)
	{
		cout << "Too many command arguments";
		return 0;
	}
	catch (notValidArguments& nva)
	{
		cout << "Not valid command arguments";
		return 0;
	}
	
	Game().run(saveMode, loadMode, silentMode);
	return 0;
}