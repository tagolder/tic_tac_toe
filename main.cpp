#include <iostream>

const unsigned int cols = 3;
const unsigned int rows = 3;

int state[cols][rows] = 
	{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
	};

bool is_win(int state_win[3][3], int pl)
{
	int diag = 0, rdiag = 0, row = 0, col = 0;
	for(int i = 0; i < 3; i++)
	{
		if(state_win[i][i] == pl)diag++;
		if(state_win[i][2 - i] == pl)rdiag++; 	
		if((diag == 3) || (rdiag == 3))return true;
	}
	for(int i = 0; i < 3; i++)
	{
		row = 0, col = 0;
		for(int j = 0; j < 3; j++)
		{
			if(state_win[i][j] == pl) row++;
  			if(state_win[j][i] == pl) col++;
  			if((row == 3) || (col == 3))return true;
		}
	}
	return false;
}

bool is_draw(int state_draw[3][3])
{
	if(is_win(state_draw, 1) || is_win(state_draw, 2))return false;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(state_draw[i][j] == 0)return false;
		}
	}
	return true;	
}
	   

int minimax(int state_minmax[3][3], int depth, bool is_minmax)
{
	if(is_win(state_minmax, 2)) return 2;
	if(is_win(state_minmax, 1)) return 0;
	if(is_draw(state_minmax)) return 1;
	
	int score_best = 0;
	
	if(is_minmax)
	{

		score_best = -10000;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(state_minmax[i][j] == 0)
				{
					state_minmax[i][j] = 2;
					int score = minimax(state_minmax, 0, false);
					state_minmax[i][j] = 0;
					if(score > score_best) score_best = score;
				}
			}
		}
	}
	else
	{
		score_best = 10000;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(state_minmax[i][j] == 0)
				{
					state_minmax[i][j] = 1;
					int score = minimax(state_minmax, 0, true);
					state_minmax[i][j] = 0;
					if(score < score_best) score_best = score;
				}
			}
		}
	}
	return score_best;
} 


bool AutoPosition()
{		

	if(is_draw(state))
	{
		std::cout << "Ничья" << std::endl;
		return true;
	}
	
	int x, y;
	int state_best[3][3];
	int state_test[3][3];

    	for (int i = 0; i < 3; i++) 
    	{
        	for (int j = 0; j < 3; j++) 
        	{
        		state_test[i][j] = state[i][j];
        	}
    	}
	int score_best = -10000; 
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(state[i][j] == 0)
			{
				state_test[i][j] = 2;
				int score = minimax(state_test, 0, false);
				if(score > score_best)
				{
					x = i;
					y = j;
					score_best = score;
					for (int i = 0; i < 3; i++) 
    					{
        					for (int j = 0; j < 3; j++) 
        					{
        						
        						state_best[i][j] = state_test[i][j];
        						
        					}
    					}
				}
				state_test[i][j] = 0;
			}
		}
	}
	
	for (int i = 0; i < 3; i++) 
    	{
        	for (int j = 0; j < 3; j++) 
        	{
        		state[i][j] = state_best[i][j];
        	}
    	}
    	std::cout << "Ход компьютера : " << (char)(x + 65) << y + 1 << std::endl;
    	if(is_win(state, 2))
    	{
    		std::cout << "Компьютер победил" << std::endl;
    		return true;
    	}
    	return false;
}

void show_pos()
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			std::cout << state[i][j];
		}
		std::cout << std::endl;
	}
}

bool checkPosition(std::string pos)
{
	if((int)pos[0] >= 65 && (int)pos[0] <= 67 &&
	   (int)pos[1] >= 49 && (int)pos[1] <= 51 && pos.length() < 3)return true;
	return false;	
}

void setPlayerPosition(std::string pos)
{
	state[(int)pos[0] - 65][(int)pos[1] - 49] = 1;
}


int main()
{	
	int seq;
	
	std::cout << "Кто ходит первым ? 1 - игрок, 2 - компьютер" << std::endl;
	
	std::cin >> seq;
	
	if(seq == 2) AutoPosition();
	
	do
	{
		//std::cout << "Состояние доски : " << std::endl;
		//show_pos();
		std::string position;
		std::cout << "Введите клетку от A1 до С3" << std::endl;
		std::cout << "Клетка >> ";
		std::cin >> position;
		if(!checkPosition(position))
		{
			std::cout << "Клетка занята или не существует" << std:: endl;
			continue;
		}
		else setPlayerPosition(position);
		AutoPosition();
	}while(!is_win(state, 2) && !is_draw(state));	
	return 0;
}
