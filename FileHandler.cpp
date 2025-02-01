#include "FileHandler.h"
#include <fstream>


bool FileHandler::starts_with(const std::string& str, const std::string& prefix)
{
	return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}
bool FileHandler::ends_with(const std::string& str, const std::string& suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
int FileHandler::containValidNumber(const std::string& str)
{
	int sum = 0;
	if (str[6] < '0' || str[6]>'9' || str[7] < '0' || str[7] > '9')
		return 0;

	sum += (str[6] - '0')*10 + (str[7] - '0');
		return sum;
}
int FileHandler::checkFileNameValidity(const string& name)
{

	if (name.size() == FILELEN && starts_with(name, "dkong_") && ends_with(name, ".screen"))
	{
		return containValidNumber(name);
	}
	return 0;
}
bool FileHandler::loadAllFiles(map<int, Level>& alllevels)
{
	bool res=false;

	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		int curLevel;
		if ((curLevel = checkFileNameValidity(entry.path().filename().string())) != 0)
		{
			Level tempLevel;
			if (readFileContent(entry.path().filename().string(), tempLevel))
			{
				alllevels[curLevel] = tempLevel; // Insert into the map only if successful
				res = true;
			}
		}
	}

	return res;
}


int FileHandler::getFloorFile(int numline)
{
	int res;
	res = (GameConfig::HEIGHT+1 - numline) / GameConfig::FLOORDIFF;
	if (res == 1||res==0)
		return GameConfig::FLOOR1 - 1;
    if (res == 2)
		return GameConfig::FLOOR2 - 1;
	if (res == 3)
		return GameConfig::FLOOR3 - 1;
	if (res == 4)
		return GameConfig::FLOOR4 - 1;
	if (res == 5)
		return GameConfig::FLOOR5 - 1;
	if (res == 6)
		return GameConfig::FLOOR6 - 1;
	if (res == 7)
		return GameConfig::FLOOR7 - 1;
	if (res == 8)
		return GameConfig::FLOOR8 - 1;
	
}



bool FileHandler::readFileContent(const string& name, Level& tobuild)
{
	string line;
	bool foundMarioPos = false, foundPaulinePos = false, foundDonkeyKongPos = false, foundHammerPos = false, foundLegendPos = false;
	ifstream myFile(name, ios::in);
	int min_x = 0;
	Point legendPos;
	vector<Ladder> ladders;
	

	if (myFile.eof())
	{
		std::cout << "File " << name << " Is empty" << std::endl;
		return false;
	}

	while (std::getline(myFile, line)) {
		// Check if the line is not empty and not just whitespace

		if (!line.empty() && !std::all_of(line.begin(), line.end(), [](char ch) { return std::isspace(ch); })) {
			break; // Found the first non-whitespace line
		}
	}

	//Looking for the upper bound of the board

	while (line[min_x] == ' ' && min_x < line.length() - GameConfig::WIDTH)
	{
		min_x++;
	}


	if (!(min_x <= line.length() - GameConfig::WIDTH))
	{
		std::cout << "In File " << name << " board is too narrow" << std::endl;
		return false;
	}
		

	// Process top border and check it
	for (int i = 0; i < GameConfig::WIDTH; i++)
	{
		/*if (line[min_x + i] != 'Q')
		{
			// Fill missing borders with 'Q'
			line[min_x + i] = 'Q';
		}*/
		if (line[min_x + i] != 'Q')
		{
			std::cout << "In File " << name << " board frame is invalid" << std::endl;
			return false;
		}
	}

	char allladders[GameConfig::WIDTH - 2] = { 0 }; //Tracking the ladders
	vector<int> ghostXcoordinates= vector<int>(); //Tracking the ghosts

	for (int i = 0; i < GameConfig::HEIGHT-1; i++)
	{
		
		myFile.seekg(min_x, ios::cur);
		getline(myFile, line);

		if (myFile.eof())
		{
			std::cout << "In File " << name << " too less rows" << std::endl;
			return false;
		}

		// Check and fill missing borders in each row
		//if (line[0] != 'Q') line[0] = 'Q'; // Left border
		//if (line[line.size() - 1] != 'Q') line[line.size() - 1] = 'Q'; // Right border

		if (line[0] != 'Q' || (line.size() - 1) < GameConfig::WIDTH || line[GameConfig::WIDTH] != 'Q')
		{
			std::cout << "In File " << name << " board frame is invalid" << std::endl;
			return false;
		}

		int currFloor = getFloorFile(i);
		if ((GameConfig::HEIGHT - i) % GameConfig::FLOORDIFF == 1) //two characters above floor
		{

			if (i == 0) //No Ladders accepted in the top line
			{
				for (int j = 1; j < GameConfig::WIDTH-1; j++)
				{
					if (line[j] == 'L')
					{
						if (foundLegendPos == true)
						{
							std::cout << "In File " << name << " too many legend positions" << std::endl;
							return false;
						}
						tobuild.setLegendPos({ GameConfig::MIN_X + 1 + (j - 1),GameConfig::MIN_Y + 1 + i });
						foundLegendPos = true;
					}
					else if (line[j] != ' ')
					{
						std::cout << "In File " << name << " there is invalid character: "<<line[j]<<" At : "<<"Row: "<<i<<" Col: "<<j << std::endl;
						return false;
					}
				}
			}
			else
			{
				for (int j = 1; j < GameConfig::WIDTH-1; j++)
				{
					if (line[j] == 'L')
					{
						if (foundLegendPos == true)
						{
							std::cout << "In File " << name << " too many legend positions" << std::endl;
							return false;
						}
						tobuild.setLegendPos({ GameConfig::MIN_X +1+ (j - 1),GameConfig::MIN_Y+1+i });
						foundLegendPos = true;
					}
					else if (line[j] == 'H') 
						allladders[j - 1]++;

					else if (line[j] != 'H' && allladders[j - 1] > 0)
					{
						std::cout << "In File " << name << " start of a ladder " << " At : " << "Row: " << i - 1 << " Col: " << j << " Is not valid" << std::endl;
						return false; //Start of a ladder at the upper line - not valid
					}
					
					else if (line[j] != ' ')
					{
						std::cout << "In File " << name << " there is invalid character: " << line[j] << " At : " << "Row: " << i << " Col: " << j << std::endl;
						return false;
					}
					

				}
			}
		}
		else if ((GameConfig::HEIGHT - i) % GameConfig::FLOORDIFF == 0) //One character above floor
		{

			for (int j = 1; j < GameConfig::WIDTH-1; j++)
			{

				if (line[j] == '@')
				{
					if (foundMarioPos == true)
					{
						std::cout << "In File " << name << " too many mario positions" << std::endl;
						return false;
					}
					tobuild.setstartPosMario({ GameConfig::MIN_X + (j - 1),currFloor });
					foundMarioPos = true;
				}

				else if (line[j] == '&')
				{
					if (foundDonkeyKongPos == true)
					{
						std::cout << "In File " << name << " too many donkey kong positions" << std::endl;
						return false;
					}
					tobuild.setstartPosDonkeyKong({ GameConfig::MIN_X + (j - 1),currFloor });
					foundDonkeyKongPos = true;
				}

				else if (line[j] == '$')
				{
					if (foundPaulinePos == true)
					{
						std::cout << "In File " << name << " too many pauline positions" << std::endl;
						return false;
					}
					tobuild.setstartPosPauline({ GameConfig::MIN_X + (j - 1),currFloor });
					foundPaulinePos = true;
				}

				else if (line[j] == 'P')
				{
					if (foundHammerPos == true)
					{
						std::cout << "In File " << name << " too many hammer positions" << std::endl;
						return false;
					}
					tobuild.setHammer(Hammer({ GameConfig::MIN_X + (j - 1),currFloor }));
					foundHammerPos = true;
				}
				else if (line[j] == 'x' || line[j]=='X')
				{
					int ghostXcoor = GameConfig::MIN_X + (j - 1);
					ghostXcoordinates.push_back(ghostXcoor);
					if(line[j]=='x') //Regular ghost
					  tobuild.getGhosts().push_back(new Ghost(Point(ghostXcoor, currFloor)));
					else //Climbing ghost
						tobuild.getGhosts().push_back(new ClimbingGhost(Point(ghostXcoor, currFloor)));
				}
			
				else if (line[j] == 'L')
				{
					if (foundLegendPos == true)
					{
						std::cout << "In File " << name << " too many legend positions" << std::endl;
						return false;
					}
					tobuild.setLegendPos({ GameConfig::MIN_X + 1 + (j - 1),GameConfig::MIN_Y + 1 + i });
					foundLegendPos = true;
				}
				else if (line[j] == 'H' && allladders[j - 1] > 0) //End of a ladder in the current line is not accepted
					allladders[j - 1]++;

				else if (line[j] != 'H' && allladders[j - 1] > 0)
				{
					std::cout << "In File " << name << " start of a ladder " << " At : " << "Row: " << i-1 << " Col: " << j <<" Is not valid" << std::endl;
					return false; //Start of a ladder at the upper line - not valid
				}
				else if (line[j] == 'H' && allladders[j - 1] == 0)
				{
					std::cout << "In File " << name << " end of a ladder " << " At : " << "Row: " << i << " Col: " << j << " Is not valid" << std::endl;
					return false;
				}
				else if (line[j] != ' ')
				{
					std::cout << "In File " << name << " there is invalid character: " << line[j] << " At : " << "Row: " << i << " Col: " << j << std::endl;
					return false;
				}
				

			}

		}
		else //The line represents the floor itself
		{

			int floorindex = ((GameConfig::HEIGHT + 1 - i) / GameConfig::FLOORDIFF) - 1;

			for (int j = 1; j < GameConfig::WIDTH-1; j++)
			{

				if (line[j] == '=' || line[j] == '<' || line[j] == '>' || line[j] == ' ')
				{
					if (line[j] == '=')
					{
						tobuild.getBoardPointer()[floorindex][j - 1] = 1;
					}
					else if (line[j] == '>')
					{
						tobuild.getBoardPointer()[floorindex][j - 1] = 2;
					}
					else if (line[j] == '<')
					{
						tobuild.getBoardPointer()[floorindex][j - 1] = 3;
					}
					else // line line[j] is ' '
					{
						if (std::find(ghostXcoordinates.begin(), ghostXcoordinates.end(), GameConfig::MIN_X + (j - 1)) != ghostXcoordinates.end())
						{

							std::cout << "In File " << name << " There " << " At : " << "Row: " << i + 1 << " Col: " << j << " There is ghost in the air" << std::endl;
							return false;
						}
						tobuild.getBoardPointer()[floorindex][j - 1] = 0;
					}
					if (allladders[j - 1] > 0) //End of a ladder from the upper floor
					{
						int steps = (allladders[j - 1] + 1) / GameConfig::FLOORDIFF;
						tobuild.addLadder(Ladder({ GameConfig::MIN_X + j ,GameConfig::MIN_Y + i, }, steps));
						allladders[j - 1] = 0;
					}
				}

				else if (line[j] == 'H') //By default if a ladder goes through a brick the brick is plain, ladders couldnt end in this line
				{
					if (allladders[j - 1] > 0)
					{
						tobuild.getBoardPointer()[floorindex][j - 1] = 1;
						allladders[j - 1]++;
					}
					else //End of the ladder in the current line is not accepted
					{
						std::cout << "In File " << name << " end of a ladder " << " At : " << "Row: " << i << " Col: " << j << " Is not valid" << std::endl;
						return false;
					}

				}
				else
				{
					std::cout << "In File " << name << " there is invalid character: " << line[j] << " At : " << "Row: " << i << " Col: " << j << std::endl;
					return false;
				}
			}

			ghostXcoordinates.clear();
		}


	}

	//Check Bottom Border

	if (myFile.eof())
	{
		std::cout << "In File " << name << " No bottom border" << std::endl;
		return false;
	}
	getline(myFile, line);

	for (int i = 0;i < GameConfig::WIDTH;i++)
	{
		for (int i = 0; i < GameConfig::WIDTH; i++)
		{
			if (line[min_x + i] != 'Q') line[min_x + i] = 'Q'; // Ensure bottom border is 'Q'
		}
	}
	while (std::getline(myFile, line)) {
		// Check if the line is not empty and not just whitespace
		if (!line.empty() && !std::all_of(line.begin(), line.end(), [](char ch) { return std::isspace(ch); })) {
			break;
		}
	}
	if (!myFile.eof())
	{
		std::cout << "In File " << name << " extra characters at the bottom" << std::endl;
		return false; 
	}

	if (foundDonkeyKongPos && foundLegendPos && foundPaulinePos && foundMarioPos) //Picture is valid
	{
		//Creating a random pace for Donkey kong to throw barrels
		int arrsize = rand() % 4 + 3;
		tobuild.getLevelSettings().dirs = new GameConfig::ARROWKEYS[arrsize];
		tobuild.getLevelSettings().intervalsBetweenBarrels = new int[arrsize];
		tobuild.getLevelSettings().size = arrsize;

		GameConfig::ARROWKEYS currdir = GameConfig::ARROWKEYS::LEFT;
		for (int i = 0;i < arrsize;i++)
		{
			int currInterval = rand() % 21 + 10;
			tobuild.getLevelSettings().dirs[i] = currdir;
			tobuild.getLevelSettings().intervalsBetweenBarrels[i] = currInterval;
			currdir == GameConfig::ARROWKEYS::LEFT ? currdir = GameConfig::ARROWKEYS::RIGHT : currdir = GameConfig::ARROWKEYS::LEFT;
		}

		//Check if there is an hammer in the game
		if (!foundHammerPos)
			tobuild.setHammer(Hammer()); //A not visible hammer


		return true;
	}
	else
	{
		std::cout << "In File " << name << " one or more of the characters not found" << std::endl;
		return false;
	}
		
}
void FileHandler::deleteDocFiles()
{
	for (const auto& entry : fs::directory_iterator(fs::current_path()))
	{
		int curLevel;
		string currFilename = entry.path().filename().string();
		if (ends_with(currFilename,".steps")||ends_with(currFilename,".result"))	
			fs::remove(currFilename);
	}
}

