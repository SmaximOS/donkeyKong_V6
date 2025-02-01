#include "Game.h"


void Game::startMenu(bool clearscreen)
{
	if(clearscreen)
	system("cls");

	std::cout << "======================== Donkey Kong ============================== \n";
	std::cout << "\n(1)Start a new game\n";
	std::cout << "(8)instructions and game controls\n";
	std::cout << "(9)Leave game\n";
	std::cout << "=================================================================== \n";
	std::cout << "Please select an option";
}

void Game:: showInstructions()
{
	system("cls");
	std::cout << "============================ Instructions ==========================\n";
	std::cout << "\nIn this game,, you play as Mario.\n";
	std::cout << "Mario is given 3 chances (lives) to reach Pauline, which will be displayed in the upper-right corner of the screen\n";
	std::cout << "Mario loses a life and the game restarts if he faces a barrel, falls to the abyss, falls for 3 or more floors, or find himself near a barrels explosion (2 Characters difference).\n";
	std::cout << "====================================================================\n";
	std::cout << "press any key to see the game controls...";
	_getch();
	system("cls");
	std::cout << "============================ game controls ==========================\n";
	std::cout << "Use the following keys to play the game:\n";
	std::cout << "A / D - Move Left / Right\n";
	std::cout << "W - Jump\n";
	std::cout << "S - Stay\n";
	std::cout << "X - Tumble Down a Ladder\n";
	std::cout << "Space - Pause the Game\n";
	std::cout << "====================================================================\n";
	std::cout << "Press any key to return to the main menu";
	_getch();
}

std::map<int, Level>::iterator Game:: lvlSelect(map<int,Level>& levels)
{
	char userInput[2];
	int currChoice;

	system("cls");
	std::cout << "========================= Level selection ==========================\n";
	std::cout << "Select the level you wish to play on: \n";

	for (auto iter = levels.begin();iter != levels.end();iter++) //Print all the level numbers loaded
		cout << setw(2) << setfill('0') << iter->first << endl;

	std::cout << "====================================================================\n";

	userInput[0] = _getch();
	cout << userInput[0];
	userInput[1] = _getch();
	cout << userInput[1]<<endl;
	currChoice = (userInput[0]-'0') * 10 + (userInput[1]-'0');
	auto it = levels.find(currChoice);

	while (it == levels.end())
	{
		cout << "Wrong choice, Try again" << endl;
		userInput[0] = _getch();
		cout << userInput[0];
		userInput[1] = _getch();
		cout << userInput[1]<<endl;
		currChoice = (userInput[0] - '0') * 10 + (userInput[1] - '0');
		it = levels.find(currChoice);
	}
	return it;
}

void Game:: drawBorders()
{

	// Top and bottom borders
	for (int x = GameConfig::MIN_X; x < GameConfig::MIN_X + GameConfig::WIDTH; ++x)
	{
		gotoxy(x, GameConfig::MIN_Y);
		cout << 'Q'; // Top border
		gotoxy(x, GameConfig::MIN_Y + GameConfig::HEIGHT);
		cout << 'Q'; // Bottom border
	}

	// Left and right borders
	for (int y = GameConfig::MIN_Y; y < GameConfig::MIN_Y + GameConfig::HEIGHT; ++y) {
		gotoxy(GameConfig::MIN_X, y);
		cout << 'Q'; // Left border
		gotoxy(GameConfig::MIN_X + GameConfig::WIDTH, y);
		cout << 'Q'; // Right border
	}
	gotoxy(GameConfig::MIN_X + GameConfig::WIDTH, GameConfig::MIN_Y + GameConfig::HEIGHT);
	cout << 'Q';
}
int Game :: getFloor(int ycoor)
{
	if (ycoor >= GameConfig::FLOOR1)
		return -1;
	return (((GameConfig::FLOOR1 - 1) - ycoor) / GameConfig::FLOORDIFF);
}

void Game::printFloorTrace(const MovableObject* obj,char board[][GameConfig::WIDTH - 2])
{
	int distancefromfloor;
	int floor = getFloor(obj->getPos().getY());

	if (floor != -1)
		distancefromfloor = objectDistanceFloor(*obj, floor);
	else
		distancefromfloor = 0;
	bool hammer=false;
	if (const Player* player = dynamic_cast<const Player*>(obj))
		hammer = (player->getHammer() != GameConfig::ARROWKEYS::STAY) && (distancefromfloor == GameConfig::FLOORDIFF - 2) && (player->getDir() == GameConfig::STAY || player->getDir() == GameConfig::UP || player->getDir() == GameConfig::DOWN);
	
	if (floor==-1||(distancefromfloor == GameConfig::FLOORDIFF - 1)||hammer)
	{
		char element;
		 element = board[floor + 1][obj->getPos().getX() - (GameConfig::MIN_X + 1)];
		if(!hammer)
		    gotoxy(obj->getPos().getX(), obj->getPos().getY());
		else
			gotoxy(obj->getPos().getX(), obj->getPos().getY()-1);
		if (element != 0)
		{
			switch (element)
			{
			case 1:
				std::cout << '=';
				break;
			case 2:
				std::cout << '>';
				break;
			case 3:
				std::cout << '<';
				break;
			}
		}
	}
	else if (distancefromfloor == 0)
	{
		char element;
		element = board[floor][obj->getPos().getX() - (GameConfig::MIN_X + 1)];
		gotoxy(obj->getPos().getX(), obj->getPos().getY()+1);
		if (element != 0)
		{
			switch (element)
			{
			case 0:
				break;
			case 1:
				std::cout << '=';
				break;
			case 2:
				std::cout << '>';
				break;
			case 3:
				std::cout << '<';
				break;
           
			}
		}
	}


}

void Game:: printLives(int lives,const Point& legend)
{
	gotoxy(legend.getX(),legend.getY());
	std::cout << "Lives:" << lives;
}
int Game:: showTime(const Point& legend, bool reset = false)
{
	static int secs;
	if (reset)
	{
		int secscopy = secs;
		secs = 0;
		return secscopy;
	}
		
	else
	{
	int minutes = secs / 60;
	int seconds = secs % 60;

	// Display time in "MM:SS" format (Given by ChatGpt)
	gotoxy(legend.getX(), legend.getY()+1);
	std::cout << "Time: ";
	gotoxy(legend.getX() + 5, legend.getY() + 1);
	std::cout << setw(2) << setfill('0') << minutes << ":"
		<< setw(2) << setfill('0') << seconds
		<< endl;
	updateScore(-1);
	return secs++;
    }
}

void Game::updateScore(int points)
{
	if(score > 0)
	score += points;  // Increment score by the specified points
}

void Game::printScore(const Point& legend)
{
	gotoxy(legend.getX(), legend.getY() + 2);  
	std::cout << "Score: " << score << std::endl;
}

char Game:: getSlope(Point currpos, char board[][GameConfig::WIDTH - 2])
{
	int row = getFloor(currpos.getY());
	int col = currpos.getX() - (GameConfig::MIN_X + 1);
	int right, left;
	right = left = col;
	bool stopSearch = false;
	while (stopSearch == false && (board[row][right] <= 1 && board[row][left] <= 1))
	{
		stopSearch = true;
		if (right < GameConfig::WIDTH - 3 && board[row][right] != 0)
		{
			stopSearch = false;
			right++;
		}
		if (left > 0 && board[row][left] != 0)
		{
			stopSearch = false;
			left--;
		}

	}

	if (stopSearch)
		return 1;
	else if (board[row][right] > 1)
		return board[row][right];
	else
		return board[row][left];

}
bool Game:: LeaveLadder(const Point& currPos,const Ladder& lad, GameConfig::ARROWKEYS dir, char board[][GameConfig::WIDTH - 2])// Checks if there is an option to leave the ladder int the middle
{
	int ypos = currPos.getY();
	int xpos = currPos.getX();
	for (int middlefloor = lad.getPos().getY() - GameConfig::FLOORDIFF; middlefloor > lad.getPos().getY() - lad.getSteps(); middlefloor -= GameConfig::FLOORDIFF)
	{
		if (ypos == middlefloor)
		{
			int indexFloor = getFloor(ypos);
			if (dir == GameConfig::LEFT && board[indexFloor][xpos - (GameConfig::MIN_X + 1) - 1] != 0)
				return true;
			else if (dir == GameConfig::RIGHT && board[indexFloor][xpos - (GameConfig::MIN_X + 1) + 1] != 0)
				return true;
			return false;
		}

	}
	return false;
}

bool Game:: nearLadder(ClimbingGhost* clgh,const Ladder lad[],const int& size)
{
	bool res=false;
	for (int i = 0; i < size; i++)
	{
		//Check upwards
		if (!clgh->getClimb()[0]) //Ladder upwards not found
		{
			for (int currfloor = lad[i].getPos().getY(); currfloor > lad[i].getPos().getY() - lad[i].getSteps(); currfloor -= GameConfig::FLOORDIFF)
			{

				if (clgh->getPos().getY() == currfloor && (clgh->getPos().getX() == lad[i].getPos().getX()))
				{
					clgh->getIndexofcurrladder()[0] = i;
					clgh->getClimb()[0] = currfloor - (lad[i].getPos().getY() - lad[i].getSteps());
					clgh->getLadderSteps()[0] = lad[i].getSteps();
					res = true;
				}

			}
		}

		//Check downwards
		if (!clgh->getClimb()[1]) //Ladder downwards not found
		{
			for (int currfloor = lad[i].getPos().getY() - lad[i].getSteps(); currfloor < lad[i].getPos().getY(); currfloor += GameConfig::FLOORDIFF)
			{

				if (clgh->getPos().getY() == currfloor && (clgh->getPos().getX() == lad[i].getPos().getX()))
				{
					clgh->getIndexofcurrladder()[1] = i;
					clgh->getClimb()[1] = (lad[i].getPos().getY())-currfloor;
					clgh->getLadderSteps()[1] = lad[i].getSteps();
					res = true;
				}


			}
		}
	}
	return res;
}

int Game::nearLadder(Player* player, Ladder lad[], int size, GameConfig::ARROWKEYS dir, int* ladderindex, int* climb) //Checks if mario is near a ladder
{
	int distance;
	if (dir == GameConfig::UP) //Dir is UP
	{
		for (int i = 0; i < size; i++)
		{
			for (int currfloor = lad[i].getPos().getY(); currfloor > lad[i].getPos().getY() - lad[i].getSteps(); currfloor -= GameConfig::FLOORDIFF)
			{

				if (player->getPos().getY() == currfloor && (abs(distance = (player->getPos().getX() - lad[i].getPos().getX())) <= 1))
				{
					if (distance == 1)
						player->setPos({ player->getPos().getX() - 1, player->getPos().getY() });
					if (distance == -1)
						player->setPos({ player->getPos().getX() + 1, player->getPos().getY() });
					*ladderindex = i;
					*climb = (currfloor - (lad[i].getPos().getY() - lad[i].getSteps()) + 1);
					return lad[i].getSteps() + 1;
				}

			}
		}
	}
	else //Down
	{

		for (int i = 0; i < size; i++)
		{
			for (int currfloor = lad[i].getPos().getY() - lad[i].getSteps(); currfloor < lad[i].getPos().getY(); currfloor += GameConfig::FLOORDIFF)
			{

				if (player->getPos().getY() == currfloor && (abs(distance = (player->getPos().getX() - lad[i].getPos().getX())) <= 1))
				{
					if (distance == 1)
						player->setPos({ player->getPos().getX() - 1, player->getPos().getY() });
					if (distance == -1)
						player->setPos({ player->getPos().getX() + 1, player->getPos().getY() });
					*ladderindex = i;
					*climb = (lad[i].getPos().getY() - currfloor) + 1;
					return lad[i].getSteps() + 1;
				}

			}
		}
	}



	return 0;
}
bool Game:: barrelsCheckHits(vector<Barrel>* barrels,const Player& playerPosition) //Checks if two barrels hit and if mario is near the hit
{
	bool currIndexdeleted;
	for (int i = 0;i < (barrels->size());i++)
	{
		currIndexdeleted = false;
		for (int j = i + 1;j < (barrels->size());j++)
		{
			if (barrels->at(j).getPos().calculateDistance(barrels->at(i).getPos()) <= 1)//Explosion
			{
				if ((playerPosition.getPos().calculateDistance(barrels->at(j).getPos()) <= 2) || playerPosition.getPos().calculateDistance(barrels->at(i).getPos()) <= 2)
					return true; //Mario is near the hit
				currIndexdeleted = true;
				barrels->erase(barrels->begin() + j);
				j--;
			}
		}
		if (currIndexdeleted)
		{
			barrels->erase(barrels->begin() + i);
			i--;
		}

	}
	return false; //Mario wasnt near a barrels hit 

}
int Game:: objectDistanceFloor(const MovableObject& bar, int floor) //The distance between the object and the floor
{
	return ((GameConfig::MIN_Y + GameConfig::HEIGHT - 1) - bar.getPos().getY() - (GameConfig::FLOORDIFF * floor) - 1);
}
bool Game:: barrelsUpdateDirs(vector<Barrel>* barrels, char board[][GameConfig::WIDTH - 2],Player* mario)
{
	for (int i=0;i<barrels->size();i++)
	{
		GameConfig::ARROWKEYS currDir = barrels->at(i).getDir();
		int floor = getFloor(barrels->at(i).getPos().getY());
		int barreldistfloor = objectDistanceFloor(barrels->at(i), floor);
		switch (currDir)
		{

		case GameConfig::ARROWKEYS::RIGHT:
		case GameConfig::ARROWKEYS::LEFT:
		{
			if (board[floor][barrels->at(i).getPos().getX() - (GameConfig::MIN_X + 1)] == 0) //Barrel falls
			{
				if (currDir == GameConfig::ARROWKEYS::RIGHT)
					barrels->at(i).setDir(GameConfig::DOWNANDRIGHT);
				else //Direction is left
					barrels->at(i).setDir(GameConfig::DOWNANDLEFT);
			}
			break;
		}

		case GameConfig::ARROWKEYS::DOWNANDRIGHT:
		case GameConfig::ARROWKEYS::DOWNANDLEFT:
		{

			if (barreldistfloor == 0 && board[floor][barrels->at(i).getPos().getX() - (GameConfig::MIN_X + 1)] != 0) //Barrel fall should stop
			{
				if (barrels->at(i).getFallSecs() >= 4 * (GameConfig::FLOORDIFF)) //Barrel fell to many floors and should explode
				{
					if (mario->getPos().calculateDistance(barrels->at(i).getPos()) <= 2) //Mario is near the explosion
						return false;

					barrels->erase(barrels->begin() + i);
					i--;
					continue;
				}
				else
				{
					barrels->at(i).setFallSecs(0); //Reset the time of falling
					int slope = getSlope(barrels->at(i).getPos(), board);
					if (slope == 1) //Plain
					{
						if (currDir == GameConfig::ARROWKEYS::DOWNANDRIGHT)
							barrels->at(i).setDir(GameConfig::ARROWKEYS::RIGHT);
						else
							barrels->at(i).setDir(GameConfig::ARROWKEYS::LEFT);
					}
					else if (slope == 2)
						barrels->at(i).setDir(GameConfig::ARROWKEYS::RIGHT);
					else
						barrels->at(i).setDir(GameConfig::ARROWKEYS::LEFT);
				}
			}
			/*else if (barreldistfloor == GameConfig::FLOORDIFF - 1 && board[floor + 1][barrels->at(i).getPos().getX() - (GameConfig::MIN_X + 1)] != 0) //Barrel hits a brick while falling
			{

				char element = board[floor + 1][barrels->at(i).getPos().getX() - (GameConfig::MIN_X + 1)];
				gotoxy(barrels->at(i).getPos().getX(), barrels->at(i).getPos().getY());
				if (element != 0)
				{
					switch (element)
					{
					case 1:
						std::cout << '=';
						break;
					case 2:
						std::cout << '>';
						break;
					case 3:
						std::cout << '<';
						break;
					}
				}
			}*/
			else if (barreldistfloor == GameConfig::FLOORDIFF - 1)
				printFloorTrace(&(barrels->at(i)), board);
			
		}
		}
	  
	}

	return true;
}
bool Game:: marioHitsBarrel(vector<Barrel>& barrels,const Player& mario)
{
	for (auto& barrel : barrels)
	{
		if (mario.getPos() == barrel.getPos())
			return true;
	}
	return false;
}
bool Game::marioHitsGhost(vector<Ghost*>& ghosts,const Player& mario)
{
	for (auto& ghost : ghosts)
	{
		if (mario.getPos() == ghost->getPos())
			return true;
	}
	return false;
}
void Game::regularMoveGhost(Ghost* gh)
{
	char num;
	if (gh->getDir() == GameConfig::ARROWKEYS::STAY) //In stay mode we will choose randomly where to go
	{
		num = rand() % 2;
		num == 0 ? gh->setDir(GameConfig::LEFT) :gh->setDir(GameConfig::RIGHT);
	}
	else
	{
		num = rand() % 20;
		if (num == 0)
			gh->getDir() == GameConfig::ARROWKEYS::RIGHT ? gh->setDir(GameConfig::LEFT) : gh->setDir(GameConfig::RIGHT);
	}
}
void Game::ghostsChangeDir(vector<Ghost*> ghosts, char board[][GameConfig::WIDTH - 2],Ladder lad[],int size)
{
	vector <Ghost*> floordiv[8];
	vector <ClimbingGhost*> onLadders;

	// Dividing the existing ghosts into subvectors by their floors separated from the climbing ones
	for (auto& ghost : ghosts)
	{
		ClimbingGhost* curr = dynamic_cast<ClimbingGhost*>(ghost);

		if (curr != nullptr) //Check if the ghost is a climbing one
		{
			if (curr->getClimb()[0] == 0 && curr->getClimb()[1]==0) //Wandering a floor
			{
				int currfloor = getFloor(curr->getPos().getY());
				floordiv[currfloor].push_back(curr);
			}
			else //Climbs a ladder
				onLadders.push_back(curr);
		}
		else //The ghost is not climbing and therefore he has a floor 
		{
			int currfloor = getFloor(ghost->getPos().getY());
			floordiv[currfloor].push_back(ghost);
		}
	}

	// Check for multiple ghosts on the same floor
	for (int i = 0; i < 8; i++) 
	{

		int currsize = floordiv[i].size();
		if (currsize == 0)
			continue;

		bool* changedDirs = new bool[currsize];

		for (int i = 0;i < currsize;i++)
			changedDirs[i] = false; // if a ghost needs to change direction twice(once right and once left he will stay in its place)

			for (int j = 0; j < currsize; j++) //Current ghost in floor i
			{
				
				for (int k = j + 1; k < currsize; k++) // Check if there are ghosts that close enough to require direction change
				{
					
					if (abs(floordiv[i].at(j)->getPos().getX() - floordiv[i].at(k)->getPos().getX()) <= 2)
					{

						if (floordiv[i].at(j)->getDir() == GameConfig::STAY) //Direction will be set by the other ghost
						{
							if(floordiv[i].at(k)->getDir() == GameConfig::LEFT)
							{
								floordiv[i].at(j)->setDir(GameConfig::RIGHT);
								floordiv[i].at(k)->setDir(GameConfig::LEFT);
							}
							else
							{
								floordiv[i].at(j)->setDir(GameConfig::LEFT);
								floordiv[i].at(k)->setDir(GameConfig::RIGHT);
							}

						}
						else if (floordiv[i].at(j)->getDir() == GameConfig::LEFT)
						{
						    changedDirs[j] == true ? floordiv[i].at(j)->setDir(GameConfig::STAY) : floordiv[i].at(j)->setDir(GameConfig::RIGHT);
							changedDirs[k] == true ? floordiv[i].at(k)->setDir(GameConfig::STAY) : floordiv[i].at(k)->setDir(GameConfig::LEFT);
						}
						else  //Current ghost goes right
						{
							changedDirs[j] == true ? floordiv[i].at(j)->setDir(GameConfig::STAY) : floordiv[i].at(j)->setDir(GameConfig::LEFT);
							changedDirs[k] == true ? floordiv[i].at(k)->setDir(GameConfig::STAY) : floordiv[i].at(k)->setDir(GameConfig::RIGHT);
						}
						changedDirs[j] = changedDirs[k] = true;
					}
				}
				
				GameConfig::ARROWKEYS newdir;
				if ((floordiv[i].at(j)->getDir() != GameConfig::STAY || changedDirs[j]==false) && (newdir=ghostReachedEdge(floordiv[i].at(j), board))!=GameConfig::STAY)
				{
					if (floordiv[i].at(j)->getDir() == GameConfig::STAY) //In stay mode due to previous iteration
						 floordiv[i].at(j)->setDir(newdir);
					else
					   changedDirs[j] == true ? floordiv[i].at(j)->setDir(GameConfig::STAY) : floordiv[i].at(j)->setDir(newdir);
					
					changedDirs[j] = true;
				}

				ClimbingGhost* curr = dynamic_cast<ClimbingGhost*>(floordiv[i].at(j));
				bool nearLad;

				if (curr != nullptr &&(nearLad=nearLadder(curr, lad, size))) //There is an option to climb or tumble ladder (0.5 chance)
				{
					char num;
					
					if (curr->getClimb()[0] && curr->getClimb()[1]) //Can go both up and down
					{
						num = rand() % 4;
						if (num < 2) //0 for up, 1 for down
						{
							curr->setArrIndex(num);
							num == 0 ? curr->setDir(GameConfig::UP) : curr->setDir(GameConfig::DOWN);
						}
						else  //not climb a ladder, therefore continue regularlly
						{
							curr->Reset();
							curr->setDir(GameConfig::STAY);
							if (!changedDirs[j])
								regularMoveGhost(curr);
						}
					}
					else //Can Go up Or down
					{
						int index;
						curr->getClimb()[0] > 0 ? index = 0 : index = 1;
						num = rand() % 2;

						if (num == 0) // Go to ladder
						{
							curr->setArrIndex(index);
							index==0 ? curr->setDir(GameConfig::UP) : curr->setDir(GameConfig::DOWN);
						}
						else  //not climb a ladder, therefore continue regularlly
						{
							curr->Reset();
							curr->setDir(GameConfig::STAY);
							if (!changedDirs[j])
								regularMoveGhost(curr);
						}
					}
					
				}
				else if (!changedDirs[j])
					regularMoveGhost(floordiv[i].at(j));

			}
			delete[] changedDirs;
	}

	//The climbing ones
	for (ClimbingGhost* cgh : onLadders)
	{
		int currIndex = cgh->getarrIndex();
		int distFromFloor = cgh->getLadderSteps()[currIndex] - cgh->getClimb()[currIndex];
		

		if (cgh->getClimb()[cgh->getarrIndex()] == 0) //finished climbing or tumblimg
		{
			cgh->Reset();
			cgh->setDir(GameConfig::STAY);
		}
		else if ((cgh->getarrIndex() == 0 && cgh->getClimb()[currIndex]==1) || (cgh->getarrIndex() == 1 && cgh->getLadderSteps()[currIndex] - cgh->getClimb()[currIndex]==1)) //ghost is climbing ir tumbling through a floor
		{
			printFloorTrace(cgh, board);
		}
		else if (distFromFloor / GameConfig::FLOORDIFF > 0 && distFromFloor % GameConfig::FLOORDIFF == 0) //reached a floor
		{
			int floor = getFloor(cgh->getPos().getY());
			if (board[floor][cgh->getPos().getX() - (GameConfig::MIN_X + 1) - 1] != 0 || board[floor][cgh->getPos().getX() - (GameConfig::MIN_X + 1) + 1] != 0) //Available to leave ladder
			{
				char num = rand() % 4; //A chance of 0.25 to leave
				if (num == 0)
				{
					cgh->setDir(GameConfig::STAY);
					cgh->Reset();
				}
			}
		}
		
	}
}

bool Game::outOfBounds(const Point& pos)
{
	return pos.getX() < GameConfig::MIN_X + 2 || pos.getX() > GameConfig::MIN_X + GameConfig::WIDTH - 2 || pos.getY() > GameConfig::MIN_Y + GameConfig::HEIGHT - 1;
}
void Game::printBarrelTraces(vector<Barrel> barrels)
{
	for (auto& barrel : barrels)
	{
		gotoxy(barrel.getPos().getX(), barrel.getPos().getY());
		std::cout << ' ';
	}
}

GameConfig::ARROWKEYS Game:: ghostReachedEdge(Ghost* gh, char board[][GameConfig::WIDTH-2])
{

	if (gh->getPos().getX() > GameConfig::MIN_X + GameConfig::WIDTH - 2) //Reached right bound
		return GameConfig::ARROWKEYS::LEFT;
	
	else if (gh->getPos().getX() < GameConfig::MIN_X + 2) //Reached Left bound
		return GameConfig::ARROWKEYS::RIGHT;

	else
	{

		int floor = getFloor(gh->getPos().getY());

		if (gh->getDir() == GameConfig::RIGHT)
		{
			if (board[floor][(gh->getPos().getX() - (GameConfig::MIN_X) + 1)] == 0) //No right brick
				return GameConfig::ARROWKEYS::LEFT;
			
		}
		else if (gh->getDir() == GameConfig::LEFT)
		{
			if (board[floor][(gh->getPos().getX() - (GameConfig::MIN_X+1) - 1)] == 0) //No left brick
				return GameConfig::ARROWKEYS::RIGHT;
				
		}
		else //Stay
		{
			if (board[floor][(gh->getPos().getX() - (GameConfig::MIN_X+1) - 1)] == 0) //No left brick
				return GameConfig::ARROWKEYS::RIGHT;

			else if(board[floor][(gh->getPos().getX() - (GameConfig::MIN_X) + 1)] == 0) //No right brick
				return GameConfig::ARROWKEYS::LEFT;

		}

		return GameConfig::ARROWKEYS::STAY;
	}
}



void Game::printGhostsTraces(const vector<Ghost*>& ghosts)
{
	for (auto& ghost : ghosts)
	{
		ClimbingGhost* cg = dynamic_cast<ClimbingGhost*>(ghost);
		if (cg == nullptr || cg->getarrIndex() == -1||(cg->getarrIndex() != -1 && cg->getClimb()[cg->getarrIndex()]==0)) //The ghost is not climbing
		{
			gotoxy(ghost->getPos().getX(), ghost->getPos().getY());
			std::cout << ' ';
		}
	}
}


void Game::printMarioTrace(const Player& mario,const int& climb)
{
	//Print ' ' after mario
	gotoxy(mario.getPos().getX(), mario.getPos().getY());
	std::cout << " ";

	//Print ' ' after the hammer if mario owns it
	if (mario.getHammer() != GameConfig::ARROWKEYS::STAY && (mario.getDir() == GameConfig::STAY || mario.getDir() == GameConfig::LEFT || mario.getDir() == GameConfig::RIGHT|| (mario.getDir() == GameConfig::UP&&climb)|| mario.getDir() == GameConfig::DOWN))
	{
		if (mario.getHammer() == GameConfig::ARROWKEYS::RIGHT)
		{
			gotoxy(mario.getPos().getX() + 1, mario.getPos().getY() - 1);
			std::cout << " ";
		}
		else if(mario.getHammer()==GameConfig::ARROWKEYS::LEFT)
		{
			gotoxy(mario.getPos().getX() - 1, mario.getPos().getY() - 1);
			std::cout << " ";
		}
		else if (mario.getHammer() == GameConfig::ARROWKEYS::UP)
		{
			gotoxy(mario.getPos().getX(), mario.getPos().getY() - 1);
			std::cout << " ";
		}
		else //Hammer operates down
		{
			gotoxy(mario.getPos().getX(), mario.getPos().getY() + 1);
			std::cout << " ";
		}

	}
}
void Game::pauseGame(const Player& mario,const vector<Barrel>& barrels, const vector<Ghost*>& ghosts,const int& climb)
{
	gotoxy(0, GameConfig::HEIGHT + GameConfig::MIN_Y + 1);
	std::cout << "Game Paused";
	char keyPressed = 0;
	mario.draw();
	for (auto& bar : barrels)
		bar.draw();
	for (auto& ghost : ghosts) //draw the ghosts
		ghost->draw();
	while (keyPressed != GameConfig::ESC)
	{
		if (_kbhit())
			keyPressed = _getch();
	}

	printMarioTrace(mario, climb);

	//print ' ' after the barrels
	printBarrelTraces(barrels);

	//print ' ' after the ghosts
	printGhostsTraces(ghosts);

	//Delete the pause game caption
	gotoxy(0, GameConfig::HEIGHT +GameConfig::MIN_Y + 1);
	std::cout << "            ";
}
void Game:: restart(Player* mario, Point marioStartPos, vector<Barrel>* barrels, int* timetonextbarrel, int* climb, int* jumpsecs, vector<Ghost*>* ghosts,const vector<Ghost*>& initposesghosts,bool printtrace)
{
	if(printtrace)
	printMarioTrace(*mario, *climb);
	//Mario initial position
	mario->setPos({ marioStartPos.getX(), marioStartPos.getY() });
	mario->setDir(GameConfig::STAY);
	mario->setHammer(GameConfig::ARROWKEYS::STAY);
	//Delete all barrels
	barrels->clear();
	//Set the ghosts starting positions
	*ghosts = initposesghosts;

	//Reset other variables
	*timetonextbarrel = *climb = *jumpsecs = 0;
}
void getFilename(int levelNumber, string& stepsname,string& resultname)
{
	std::ostringstream oss;

	oss << std::setw(2) << std::setfill('0') << levelNumber;
	std::string str = oss.str();

	stepsname.append("dkong_");
	stepsname.append(str);
	stepsname.append(".steps");

	resultname.append("dkong_");
	resultname.append(str);
	resultname.append(".result");

}


void Game::reduceLivesSaveMode(ofstream& resfile, const int& timePoint,const int& lives)
{
	if (resfile)
		resfile << "Lives: " << lives << " " << timePoint<<endl;
}




void Game::run(bool saveMode, bool loadMode, bool silentMode)
{
	bool gameRunning = false, exit = false;
	bool gameValid;
	int menuOption = 0;

	map<int, Level> alllevels;
	gameValid = FileHandler::loadAllFiles(alllevels);
	auto currMapIndex = alllevels.end();

	std::vector<Step> recordedSteps;  // To store the steps from the file.
	size_t recordedIndex = 0;         // To track our position in the recordedSteps vector.
	unsigned int loadedSeed = 0;



	if (!gameValid) //None of the boards were loaded
	{
		cout << "None of the boards were defined properly" << endl;
		_getch();
		return;
	}

	if (loadMode) {
		std::string stepsfilename;
		std::string resultfilename;
		getFilename(currMapIndex->first, stepsfilename, resultfilename);
		std::ifstream stepsFile(stepsfilename);
		if (!stepsFile.is_open()) {
			std::cerr << "Error: Could not open steps file: " << stepsfilename << std::endl;
			// You might want to exit or revert to normal mode.
		}
		else {
			// Read the seed from the first line.
			std::string line;
			if (std::getline(stepsFile, line)) {
				std::istringstream iss(line);
				iss >> loadedSeed;
				std::srand(loadedSeed);
			}
			while (std::getline(stepsFile, line)) {
				if (line.empty()) continue;
				std::istringstream iss(line);
				int timeStep, move;
				bool hammerUsed = false;
				std::string token;
				if (!(iss >> timeStep >> move)) {
					std::cerr << "Error parsing line: " << line << std::endl;
					continue;
				}
				// Look for an optional third token.
				if (iss >> token) {
					if (token == "P")
						hammerUsed = true;
				}
				recordedSteps.push_back({ timeStep, static_cast<GameConfig::ARROWKEYS>(move), hammerUsed });
			}
			stepsFile.close();
		}
	}

	while (!exit) {
		if (menuOption == 0) //True in the first stage only, thus we can check whether files didnt load
			startMenu(false);
		else
			startMenu();
		menuOption = _getch() - '0';
		Level currLvl;
		int lives;
		int levelsleft;
		switch (menuOption)
		{
		case 1:
			if (saveMode)
				FileHandler::deleteDocFiles(); //Delete files from previous game

			currMapIndex = lvlSelect(alllevels);
			currLvl = currMapIndex->second;
			setLevel(&(currLvl));
			gameRunning = true;
			levelsleft = std::distance(currMapIndex, alllevels.end()); //How many levels left to play (relevant to the final score)
			lives = 3;
			score = 999;
			break;
		case 8:
			// Show instructions
			showInstructions();
			break;
		case 9:
			// Exit the game
			std::cout << "\nExiting game...\n";
			gameRunning = false;
			exit = true;
			break;  // Exit the program
		default:
			// Invalid option
			std::cout << "Invalid choice, please try again.\n";
			break;
		}

		while (gameRunning) {
			system("cls");
			ShowConsoleCursor(false);

			currLevel->printBoard();
			drawBorders();
			bool finished = false;

			Player mario('@', currLevel->getstartPosMario());
			Player pauline('$', currLevel->getstartPosPauline());
			Player donkeyKong('&', currLevel->getstartPosDonkeyKong());
			Hammer hammer(currLevel->getHammer());



			donkeyKong.draw();
			pauline.draw();

			//Jump var
			int wPressed = 0;

			//Falling down var
			int descent = 0;

			char keyPressed = 0;
			bool escPressed = false;

			//Ladder vars
			int climb = 0;
			int ladderSteps = 0;
			GameConfig::ARROWKEYS laddermotionprev;
			int indexofCurrLadder = -1;

			//The random sequence generator
			unsigned int seed = setSeed();
			std::srand(seed);

			//GameSeconds
			int timePlayed = 0;
			int gameCounter = 0;

			//Barrels
			vector<Barrel> barrels;
			LevelSettings& currSettings = currLvl.getLevelSettings();
			int timetonextbarrel = 0;
			int currbarrelindex = 0;

			//Ghosts
			vector<Ghost*>activeghosts = currLevel->getGhosts(); //Create a copy of the ghosts vector to allow returning to their opening points

			//Kill indicator
			bool hammerkill = false;

			//File organizing
			ofstream steps;
			ofstream result;

			if (saveMode)
			{
				string stepsfilename;
				string resultfilename;
				getFilename(currMapIndex->first, stepsfilename, resultfilename);
				steps.open(stepsfilename, ios_base::trunc);
				result.open(resultfilename, ios_base::trunc);
				steps << seed << endl;
			}


			do {

				hammerkill = false; //reset the bool to false
				if (loadMode) {
					// If there's a recorded step corresponding to this gameCounter, use it.
					if (recordedIndex < recordedSteps.size() && recordedSteps[recordedIndex].timeStep == gameCounter) {
						keyPressed = static_cast<char>(recordedSteps[recordedIndex].move);
						// Optionally, if a hammer action was recorded, set the hammer flag.
						if (recordedSteps[recordedIndex].hammerUsed) {
							keyPressed = 'p';
						}
						recordedIndex++;
					}
				}
				if (!wPressed) //Not Jump Mode
				{

					if (_kbhit() && descent == 0) //Confirms the player is not falling down while hitting the button
					{

						keyPressed = _getch();

						switch (keyPressed)
						{
						case 'a':
						case  'A':
							if (climb == 0)
							{
								mario.setDir(GameConfig::ARROWKEYS::LEFT);
							}

							else //Climb Mode
							{
								if (mario.getDir() == GameConfig::ARROWKEYS::STAY && LeaveLadder(mario.getPos(), currLevel->getLadder(indexofCurrLadder), GameConfig::LEFT, currLevel->getBoardPointer())) //Able to leave the ladder
								{
									climb = 0;
									mario.setDir(GameConfig::ARROWKEYS::LEFT);
								}


							}
							break;

						case 'd':
						case 'D':
							if (climb == 0)
								mario.setDir(GameConfig::ARROWKEYS::RIGHT);
							else //Climb Mode
							{
								if (mario.getDir() == GameConfig::ARROWKEYS::STAY && LeaveLadder(mario.getPos(), currLevel->getLadder(indexofCurrLadder), GameConfig::RIGHT, currLevel->getBoardPointer())) //Able to leave the ladder
								{
									climb = 0;
									mario.setDir(GameConfig::ARROWKEYS::RIGHT);
								}

							}

							break;

						case 'S':
						case 's':

							mario.setDir(GameConfig::ARROWKEYS::STAY);
							break;

						case 'W':
						case 'w':
						{
							GameConfig::ARROWKEYS currstate = mario.getDir();
							if (climb) // Climb Mode
							{
								if (currstate == GameConfig::ARROWKEYS::DOWN || (currstate == GameConfig::ARROWKEYS::STAY && laddermotionprev == GameConfig::DOWN)) //Change Direction
								{

									climb = (ladderSteps - climb) + 1;

								}
								laddermotionprev = GameConfig::ARROWKEYS::UP;
								mario.setDir(GameConfig::ARROWKEYS::UP);

							}
							else //Not climb mode
							{
								if (currstate == GameConfig::STAY && (ladderSteps = nearLadder(&mario, currLevel->getLadders(), currLevel->getNumLadders(), GameConfig::UP, &indexofCurrLadder, &climb)) != 0)//Mario is near a ladder
								{
									laddermotionprev = GameConfig::ARROWKEYS::UP;
									mario.setDir(GameConfig::ARROWKEYS::UP);
								}
								else if (descent == 0) //Regular Jump, Not allowed while falling
								{

									wPressed = GameConfig::JUMPSECS;
									if (currstate == GameConfig::ARROWKEYS::LEFT)
										mario.setDir(GameConfig::ARROWKEYS::UPANDLEFT);

									else if (currstate == GameConfig::ARROWKEYS::RIGHT)
										mario.setDir(GameConfig::ARROWKEYS::UPANDRIGHT);

									else //Current state is stay or down
										mario.setDir(GameConfig::ARROWKEYS::UP, false);

								}
							}
							break;
						}

						case 'X':
						case 'x':
						{

							if (climb == 0)//Checks an opportunity to tumble a ladder
							{
								if (mario.getDir() == GameConfig::STAY && (ladderSteps = nearLadder(&mario, currLevel->getLadders(), currLevel->getNumLadders(), GameConfig::DOWN, &indexofCurrLadder, &climb)) != 0)
								{
									laddermotionprev = GameConfig::ARROWKEYS::DOWN;
									mario.setDir(GameConfig::ARROWKEYS::DOWN);
								}
							}
							else //On climb mode
							{
								if (mario.getDir() == GameConfig::ARROWKEYS::UP || (mario.getDir() == GameConfig::ARROWKEYS::STAY && laddermotionprev == GameConfig::UP))
									climb = (ladderSteps - climb) + 1;
								laddermotionprev = GameConfig::ARROWKEYS::DOWN;
								mario.setDir(GameConfig::ARROWKEYS::DOWN);
							}
							break;
						}
						case GameConfig::ESC:
							pauseGame(mario, barrels, activeghosts, climb);
							break;
						case GameConfig::SPACE:
							escPressed = true;
							break;
						case 'p':
						case 'P':
							if (mario.getHammer() != GameConfig::STAY) //Mario is able to use the hammer
							{
								GameConfig::ARROWKEYS dirhammer = mario.getHammer();
								if (dirhammer == GameConfig::ARROWKEYS::RIGHT)
								{
									for (int i = 0; i < barrels.size(); i++)
									{
										if (barrels.at(i).getPos().getX() > mario.getPos().getX() && mario.getPos().calculateDistance(barrels.at(i).getPos()) <= 2)
										{
											barrels.erase(barrels.begin() + i);
											updateScore(150);
											i--;
											hammerkill = true;
										}
									}
									for (int i = 0; i < activeghosts.size(); i++)
									{
										if (activeghosts.at(i)->getPos().getX() > mario.getPos().getX() && mario.getPos().calculateDistance(activeghosts.at(i)->getPos()) <= 2)
										{
											activeghosts.erase(activeghosts.begin() + i);
											updateScore(200);
											i--;
											hammerkill = true;
										}
									}
								}
								else if (dirhammer == GameConfig::ARROWKEYS::LEFT) //Hammer operates towards left
								{

									for (int i = 0; i < barrels.size(); i++)
									{
										if (barrels.at(i).getPos().getX() < mario.getPos().getX() && mario.getPos().calculateDistance(barrels.at(i).getPos()) <= 2)
										{
											barrels.erase(barrels.begin() + i);
											i--;
											hammerkill = true;
										}
									}
									for (int i = 0; i < activeghosts.size(); i++)
									{
										if (activeghosts.at(i)->getPos().getX() < mario.getPos().getX() && mario.getPos().calculateDistance(activeghosts.at(i)->getPos()) <= 2)
										{
											activeghosts.erase(activeghosts.begin() + i);
											i--;
											hammerkill = true;
										}
									}
								}
								else if (dirhammer == GameConfig::ARROWKEYS::UP) //Hammer operates Up, works only on climbing ghosts
								{
									for (int i = 0; i < activeghosts.size(); i++)
									{
										if (activeghosts.at(i)->getPos().getX() == mario.getPos().getX() && mario.getPos().getY() - activeghosts.at(i)->getPos().getY() <= 2 && mario.getPos().getY() - activeghosts.at(i)->getPos().getY() >= 0)
										{
											activeghosts.erase(activeghosts.begin() + i);
											i--;
											hammerkill = true;
										}
									}
								}
								else //Hammer operates down
								{
									for (int i = 0; i < activeghosts.size(); i++)
									{
										if (activeghosts.at(i)->getPos().getX() == mario.getPos().getX() && activeghosts.at(i)->getPos().getY() - mario.getPos().getY() <= 2 && activeghosts.at(i)->getPos().getY() - mario.getPos().getY() >= 0)
										{
											activeghosts.erase(activeghosts.begin() + i);
											i--;
											hammerkill = true;
										}
									}
								}

								break;
							}
						default:
							break;
						}

					}
					if (climb > 0) //Climb Mode
					{
						if ((climb == 1 && laddermotionprev == GameConfig::UP) || ((climb == (ladderSteps - 1)) && laddermotionprev == GameConfig::DOWN) || ((climb == (ladderSteps - 2)) && laddermotionprev == GameConfig::DOWN && mario.getHammer() != GameConfig::STAY)) //in the same level of the floor
						{
							printFloorTrace(&mario, currLvl.getBoardPointer());
						}
						if (climb == 2 && laddermotionprev == GameConfig::DOWN)
						{
							if (mario.getHammer() != GameConfig::STAY)
								mario.setHammer(GameConfig::ARROWKEYS::UP);
						}

						if (mario.getDir() != GameConfig::ARROWKEYS::STAY)
							climb--;
						if (climb == 0) //Finished climbing
							mario.setDir(GameConfig::ARROWKEYS::STAY);
					}
					else if (descent > 0) //Falling Down
					{
						if (descent % GameConfig::FLOORDIFF == 0) // checks if the fall shoud stop
						{
							int currFloor = getFloor(mario.getPos().getY());
							int col = mario.getPos().getX() - (GameConfig::MIN_X + 1);
							if (col >= GameConfig::WIDTH - 2)
								col = GameConfig::WIDTH - 2 - 1;
							if (currLevel->getBoardValue(currFloor, col) != 0)
							{
								if (descent >= GameConfig::FLOORDIFF * 3) //Mario fell 3 floors or more
								{
									lives--;
									restart(&mario, currLevel->getstartPosMario(), &barrels, &timetonextbarrel, &climb, &wPressed, &activeghosts, currLevel->getGhosts(), true);
								}

								switch (mario.getDir())
								{
								case GameConfig::DOWN:
									mario.setDir(GameConfig::STAY);
									break;
								case GameConfig::DOWNANDRIGHT:
									mario.setDir(GameConfig::RIGHT);
									break;
								case GameConfig::DOWNANDLEFT:
									mario.setDir(GameConfig::LEFT);
									break;

								default:
									break;
								}
								descent = 0;
							}
						}
						else if (descent % GameConfig::FLOORDIFF == 1 && mario.getDir() != GameConfig::DOWN) //IN Case mario faces a brick while falling diagonally
						{
							printFloorTrace(&mario, currLvl.getBoardPointer());
						}
						if (descent != 0)
							descent++;
					}
					else if (wPressed == 0)//Check if mario reached an edge on regular mode,Relevant for non-jumping  mode
					{
						int currFloor = getFloor(mario.getPos().getY());
						if (currLevel->getBoardValue(currFloor, mario.getPos().getX() - (GameConfig::MIN_X + 1)) == 0)
						{
							if (mario.getDir() == GameConfig::RIGHT)
							{
								mario.setDir(GameConfig::DOWNANDRIGHT);
								descent++;
							}
							else
							{
								mario.setDir(GameConfig::DOWNANDLEFT);
								descent++;
							}
						}
					}
				}
				else //Jump
				{
					if (wPressed - 1 == GameConfig::JUMPSECS / 2)
					{

						GameConfig::ARROWKEYS currstate = mario.getDir();

						if (currstate == GameConfig::UPANDLEFT)
							mario.setDir(GameConfig::ARROWKEYS::DOWNANDLEFT);
						else if (currstate == GameConfig::UPANDRIGHT)
						{
							mario.setDir(GameConfig::ARROWKEYS::DOWNANDRIGHT);
						}

						else // Current State is Up
							mario.setDir(GameConfig::ARROWKEYS::DOWN, false);
					}
					wPressed--;
					if (wPressed == 0)
					{
						int currFloor = getFloor(mario.getPos().getY());
						GameConfig::ARROWKEYS currstate = mario.getDir();
						if (currstate == GameConfig::ARROWKEYS::DOWNANDLEFT)
						{
							if (currLevel->getBoardValue(currFloor, mario.getPos().getX() - (GameConfig::MIN_X + 1)) != 0)
								mario.setDir(GameConfig::ARROWKEYS::LEFT);
							else
								descent++;
						}

						else if (currstate == GameConfig::DOWNANDRIGHT)
						{
							if (currLevel->getBoardValue(currFloor, mario.getPos().getX() - (GameConfig::MIN_X + 1)) != 0)
								mario.setDir(GameConfig::ARROWKEYS::RIGHT);
							else
								descent++;
						}

						else // Current State is Down
							mario.setDir(GameConfig::ARROWKEYS::STAY);
					}

				}

				if (mario.getPos().getX() < GameConfig::MIN_X + 2)//Reached Left Bound
				{
					if (wPressed > 0)// Jump Mode
					{
						if ((mario.getDir() != GameConfig::ARROWKEYS::UP) && (mario.getDir() != GameConfig::ARROWKEYS::DOWN)) // Diagonal Jump Mode
						{
							if (wPressed - 1 >= GameConfig::JUMPSECS / 2)
								wPressed = GameConfig::JUMPSECS - wPressed;
							if (wPressed != 0)
								mario.setDir(GameConfig::ARROWKEYS::DOWN);
							else
								mario.setDir(GameConfig::ARROWKEYS::STAY);
						}

					}
					else if (mario.getDir() == GameConfig::DOWNANDLEFT)
						mario.setDir(GameConfig::DOWN);
					else if (keyPressed == 'd' || keyPressed == 'D')
						mario.setDir(GameConfig::RIGHT);
					else if (descent == 0)
						mario.setDir(GameConfig::ARROWKEYS::STAY);

					if (mario.getHammer() == GameConfig::ARROWKEYS::LEFT)
					{
						mario.setHammer(GameConfig::ARROWKEYS::RIGHT);
						gotoxy(mario.getPos().getX() - 1, mario.getPos().getY() - 1);
						std::cout << 'Q';
					}

				}
				if (mario.getPos().getX() > GameConfig::MIN_X + GameConfig::WIDTH - 2)// Reached Right Bound
				{
					if (wPressed > 0)// Jump Mode
					{
						if ((mario.getDir() != GameConfig::ARROWKEYS::UP) && (mario.getDir() != GameConfig::ARROWKEYS::DOWN))// Diagonal Jump Mode
						{
							if (wPressed - 1 >= GameConfig::JUMPSECS / 2)
								wPressed = GameConfig::JUMPSECS - wPressed;
							if (wPressed != 0)
								mario.setDir(GameConfig::ARROWKEYS::DOWN);
							else if (descent == 0)
								mario.setDir(GameConfig::ARROWKEYS::STAY);
						}
					}
					else if (mario.getDir() == GameConfig::DOWNANDRIGHT)
						mario.setDir(GameConfig::DOWN);
					else if (keyPressed == 'a' || keyPressed == 'A')
						mario.setDir(GameConfig::LEFT);
					else if (descent == 0)
						mario.setDir(GameConfig::ARROWKEYS::STAY);

					if (mario.getHammer() == GameConfig::ARROWKEYS::RIGHT)
					{
						mario.setHammer(GameConfig::ARROWKEYS::LEFT);
						gotoxy(mario.getPos().getX() + 1, mario.getPos().getY() - 1);
						std::cout << 'Q';
					}

				}
				if (mario.getPos().getY() >= GameConfig::MIN_Y + GameConfig::HEIGHT - 1) //Mario Fell Down
				{
					printFloorTrace(&mario, currLvl.getBoardPointer());
					lives--;
					if (saveMode)
						reduceLivesSaveMode(result, gameCounter, lives);
					restart(&mario, currLevel->getstartPosMario(), &barrels, &timetonextbarrel, &climb, &wPressed, &activeghosts, currLevel->getGhosts(), false);
				}

				//Barrels and Ghosts

				if (timetonextbarrel == currSettings.intervalsBetweenBarrels[currbarrelindex]) //Time to add next barrel
				{
					barrels.push_back(Barrel(donkeyKong.getPos(), currSettings.dirs[currbarrelindex]));
					currbarrelindex++;
					if (currbarrelindex == currSettings.size)
						currbarrelindex = 0;
					timetonextbarrel = 0;
				}
				else
					timetonextbarrel++;

				if (!barrelsUpdateDirs(&barrels, currLevel->getBoardPointer(), &mario))//Set the exact direction for each barrel and if barrel exploded near mario - restart the game
				{
					printFloorTrace(&mario, currLvl.getBoardPointer());
					lives--;
					if (saveMode)
						reduceLivesSaveMode(result, gameCounter, lives);
					restart(&mario, currLevel->getstartPosMario(), &barrels, &timetonextbarrel, &climb, &wPressed, &activeghosts, currLevel->getGhosts(), true);
				}

				ghostsChangeDir(activeghosts, currLevel->getBoardPointer(), currLevel->getLadders(), currLevel->getNumLadders());


				for (auto& barel : barrels) //Move the barrels
					barel.move();
				for (auto& ghost : activeghosts) //Move the ghosts
					ghost->move();


				if (marioHitsBarrel(barrels, mario) || marioHitsGhost(activeghosts, mario))
				{
					printFloorTrace(&mario, currLvl.getBoardPointer());
					//mario hit a barrel / ghost
					lives--;
					if (saveMode)
						reduceLivesSaveMode(result, gameCounter, lives);
					restart(&mario, currLevel->getstartPosMario(), &barrels, &timetonextbarrel, &climb, &wPressed, &activeghosts, currLevel->getGhosts(), true);
				}

				if (barrelsCheckHits(&barrels, mario)) //delete barrels that share same position (explosion)
				{
					printFloorTrace(&mario, currLvl.getBoardPointer());
					//Mario is near an explosion
					lives--;
					if (saveMode)
						reduceLivesSaveMode(result, gameCounter, lives);
					restart(&mario, currLevel->getstartPosMario(), &barrels, &timetonextbarrel, &climb, &wPressed, &activeghosts, currLevel->getGhosts(), true);
				}


				for (int i = 0; i < barrels.size(); i++) //erasing all the barrels that are out of bounds
				{
					if (outOfBounds(barrels[i].getPos()))
					{
						barrels.erase(barrels.begin() + i);
						i--;
					}

				}

				mario.move();

				if (marioHitsBarrel(barrels, mario) || marioHitsGhost(activeghosts, mario))
				{
					printFloorTrace(&mario, currLvl.getBoardPointer());
					//mario hit a barrel / ghost
					lives--;
					if (saveMode)
						reduceLivesSaveMode(result, gameCounter, lives);
					restart(&mario, currLevel->getstartPosMario(), &barrels, &timetonextbarrel, &climb, &wPressed, &activeghosts, currLevel->getGhosts(), true);
				}
				if (mario.getPos() == hammer.getPos() && hammer.getIsVisible()) //mario gets the hammer
				{
					hammer.setIsVisible(false);
					mario.setHammer(mario.getDir());
				}

				currLevel->printLadders();
				printLives(lives, currLevel->getLegendPos());

				if (climb > 0)
					mario.draw(true);
				else
					mario.draw();
				pauline.draw();

				for (auto& barel : barrels) //Draw the barrels
					barel.draw();
				for (auto& ghost : activeghosts) //draw the ghosts
					ghost->draw();

				hammer.draw();

				Sleep(INTERVAL);

				//Game clock is running
				timePlayed += INTERVAL;
				gameCounter++;

				if (timePlayed >= SECOND)
				{
					timePlayed -= SECOND;
					showTime(currLevel->getLegendPos());
				}

				printScore(currLevel->getLegendPos());  // Print score
				printMarioTrace(mario, climb);

				//Print ' ' after the barrels and ghosts
				printBarrelTraces(barrels);
				printGhostsTraces(activeghosts);

				if (saveMode)
				{
					steps << gameCounter << " ";
					steps << mario.getDir();
					if (hammerkill) //'p' should be pressed if there is a kill
						steps << " P";
					steps << endl;
				}

				if (mario.getPos() == pauline.getPos())
				{
					finished = true;
					updateScore(400);
					break;
				}
			} while (lives > 0 && escPressed == false);

			if (saveMode) //Anyway close the steps file when level finished
				steps.close();


			if (escPressed == false)
			{
				if (finished)
				{
					if (saveMode)
					{
						result << "Lives: " << lives << " Score: " << score << " Finished: " << gameCounter;
						result.close();
					}
					gotoxy(0, GameConfig::HEIGHT + GameConfig::MIN_Y + 1);
					std::cout << "Level Won,";

					//Level up
					currMapIndex++;
					if (currMapIndex != alllevels.end())
					{

						currLvl = currMapIndex->second;
						std::cout << "Press any key to continue";
						_getch();
						setLevel(&(currLvl));
					}

					else //All levels finished
					{
						system("cls");
						int gamesecs = showTime(currLevel->getLegendPos(), true);

						//Show the time for the whole game
						int minutes = gamesecs / 60;
						int seconds = gamesecs % 60;
						gotoxy(0, GameConfig::MIN_Y);
						std::cout << "Time: ";
						std::cout << setw(2) << setfill('0') << minutes << ":"
							<< setw(2) << setfill('0') << seconds
							<< endl;
						//Show the score based on the game time and levels that played
						std::cout << "Score: " << score << std::endl;
						gameRunning = false;
						std::cout << "Press any key to continue";
						_getch();


					}

				}
				else
				{
					if (saveMode)
					{
						result << " Score: F";
						result.close();
					}
					gotoxy(0, GameConfig::HEIGHT + GameConfig::MIN_Y + 1);
					std::cout << "Failure,";
					showTime(currLevel->getLegendPos(), true);
					gameRunning = false;
					std::cout << "Press any key to continue";
					_getch();
				}


			}
			else //ESC pressed
			{
				if (saveMode)
				{
					result << " Score: ESC";
					result.close();
				}
				gameRunning = false;
				showTime(currLevel->getLegendPos(), true);
			}


			gameCounter = 0;

		}
	}
}

