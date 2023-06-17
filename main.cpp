#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "legalMoves.h"
#include <SDL2/SDL_mixer.h>
#include <cmath>
#include <chrono>
#include <ctime>

SDL_Texture* pawn_black;
SDL_Texture* pawn_white;
SDL_Texture* knight_black;
SDL_Texture* knight_white;
SDL_Texture* bishop_black;
SDL_Texture* bishop_white;
SDL_Texture* rook_black;
SDL_Texture* rook_white;
SDL_Texture* queen_black;
SDL_Texture* queen_white;
SDL_Texture* king_black;
SDL_Texture* king_white;
SDL_Texture* board_texture;
SDL_Texture* chess_text;
SDL_Texture* enter_start;

Mix_Chunk* placesfx;


void defaultBoard(Piece board[64])
{
	std::string code = "rnbqkbnrpppppppp////pppppppprnbqkbnr";
	for (int i=0,y=0;i<code.length()&&y<64;++i)
	{
		if(code[i]=='/')
		{
			y += 8;
			continue;
		}
		board[y] = Piece{ int(i > code.length() / 2),code[i] };
		++y;
	}
}

//rgb(153, 153, 102) light
//rgb(153, 102, 51) dark

void initTextures(SDL_Renderer *renderer)
{
	pawn_black = IMG_LoadTexture(renderer, "res/pawn_black.png");
	pawn_white = IMG_LoadTexture(renderer, "res/pawn_white.png");
	knight_black = IMG_LoadTexture(renderer, "res/knight_black.png");
	knight_white = IMG_LoadTexture(renderer, "res/knight_white.png");
	bishop_black = IMG_LoadTexture(renderer, "res/bishop_black.png");
	bishop_white = IMG_LoadTexture(renderer, "res/bishop_white.png");
	rook_black = IMG_LoadTexture(renderer, "res/rook_black.png");
	rook_white = IMG_LoadTexture(renderer, "res/rook_white.png");
	queen_black = IMG_LoadTexture(renderer, "res/queen_black.png");
	queen_white = IMG_LoadTexture(renderer, "res/queen_white.png");
	king_black = IMG_LoadTexture(renderer, "res/king_black.png");
	king_white = IMG_LoadTexture(renderer, "res/king_white.png");
	board_texture = IMG_LoadTexture(renderer, "res/board.png");
	chess_text=IMG_LoadTexture(renderer,"res/chesstext.png");
	enter_start=IMG_LoadTexture(renderer,"res/enterstart.png");

	placesfx = Mix_LoadWAV("res/click3.wav");
}

void renderPiece(SDL_Renderer* renderer, int x, int y, Piece* piece) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = 75;
	dst.w = 75;

	if (piece->type=='p'&&piece->Team==0)
	{
		SDL_RenderCopy(renderer,pawn_black,nullptr,&dst);
	}else if (piece->type == 'p' && piece->Team == 1)
	{
		SDL_RenderCopy(renderer, pawn_white, nullptr, &dst);
	}
	else if (piece->type == 'n' && piece->Team == 0)
	{
		SDL_RenderCopy(renderer, knight_black, nullptr, &dst);
	}
	else if (piece->type == 'n' && piece->Team== 1)
	{
		SDL_RenderCopy(renderer, knight_white, nullptr, &dst);
	}
	else if (piece->type == 'b' && piece->Team == 0)
	{
		SDL_RenderCopy(renderer, bishop_black, nullptr, &dst);
	}
	else if (piece->type == 'b' && piece->Team == 1)
	{
		SDL_RenderCopy(renderer, bishop_white, nullptr, &dst);
	}
	else if (piece->type == 'r' && piece->Team == 0)
	{
		SDL_RenderCopy(renderer, rook_black, nullptr, &dst);
	}
	else if (piece->type == 'r' && piece->Team == 1)
	{
		SDL_RenderCopy(renderer, rook_white, nullptr, &dst);
	}
	else if (piece->type == 'q' && piece->Team == 0)
	{
		SDL_RenderCopy(renderer, queen_black, nullptr, &dst);
	}
	else if (piece->type == 'q' && piece->Team == 1)
	{
		SDL_RenderCopy(renderer, queen_white, nullptr, &dst);
	}
	else if (piece->type == 'k' && piece->Team == 0)
	{
		SDL_RenderCopy(renderer, king_black, nullptr, &dst);
	}
	else if (piece->type == 'k' && piece->Team == 1)
	{
		SDL_RenderCopy(renderer, king_white, nullptr, &dst);
	}
}


int detectSelection()
{
	int x, y;
	int rectx = 0;
	int recty = 0;
	SDL_GetMouseState(&x, &y);
	SDL_Point point = { x,y };
	for(int i=1;i<=64;++i)
	{
		SDL_Rect rect = { rectx,recty,75,75 };
		if(SDL_PointInRect(&point,&rect))
		{
			return i-1;
		}
		if (recty != int((i / 8) * 75))
		{
			rectx = 0;
			recty = (i / 8) * 75;
			continue;
		}
		rectx += 75;
	}
	return -1;
}

int main(int argc,char* argv[])
{
    bool bot_enable;
    std::string s;
    std::cout << "Enable bot?(y/n): ";
    std::cin>>s;
    if(s=="y"){
        bot_enable=true;
        std::srand(std::time(nullptr));
    }else{
        bot_enable=false;
    }

	Piece board[64];
	bool turnTeam = true;

	defaultBoard(board);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);

	Mix_Init(MIX_INIT_MP3);
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0){
		std::cout << "failed to inti mixer! "<<Mix_GetError()<<std::endl;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	initTextures(renderer);

	//SDL_SetRenderDrawColor(renderer, 153, 102, 51, 255);
	//SDL_RenderClear(renderer);
	/*
	int x = 0;
	int y = 0;
	SDL_SetRenderDrawColor(renderer, 153, 153, 102, 255);
	for (int i = 1; i <= 32; ++i)
	{
		SDL_Rect rect = { x,y,75,75 };
		SDL_RenderFillRect(renderer, &rect);
		if (y != int((i / 4) * 75))
		{
			x = 75 * int(y % 2 == 0 || y == 0);
			y = (i / 4) * 75;
			continue;
		}
		x += 150;
	}*/

	bool running = true;
	int selection = -1;
	bool inMenu=true;
	auto start=std::chrono::system_clock::now();
	while(running)
	{
		SDL_RenderClear(renderer);

		SDL_Event event;
		SDL_PollEvent(&event);

		switch(event.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button==SDL_BUTTON_LEFT&&!inMenu)
			{
				if(selection==-1)
				{
                    selection = detectSelection();
					if(board[selection].Team==-1||board[selection].Team!=turnTeam)
					{
						selection = -1;
					}
				}else if(selection>=0&&selection<=63)
				{
                    int tempselect =detectSelection();
					if(board[selection].Team!=board[tempselect].Team&&legalMoves::isLegalMove(selection,tempselect,board))
					{
						board[tempselect] = board[selection];
						board[selection] = { -1,' ' };
						turnTeam = !turnTeam;
						Mix_Volume(-1,MIX_MAX_VOLUME);
						Mix_PlayChannel(-1, placesfx, 0);
					}
					selection = -1;
				}
			}
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym==SDLK_RETURN){
				inMenu=false;
			}
		default:
			break;
		}

		SDL_RenderCopy(renderer, board_texture, nullptr, nullptr);
        int kingCount;
		if(!inMenu){
            kingCount=0;
			int x = 0;
			int y = 0;
			for (int i = 1; i <= 64; ++i)
			{
				if(selection==i-1)
				{
					SDL_SetRenderDrawColor(renderer,153,204,0,200);
					SDL_Rect rect = { x+1,y,75,75 };
					SDL_RenderFillRect(renderer, &rect);
				}
				if(((i>=1&&i<=8)||(i>=57))&&board[i-1].type=='p')
				{
					board[i - 1].type = 'q';
				}
				renderPiece(renderer, x, y, &board[i-1]);
                if(board[i-1].type=='k'){
                    ++kingCount;
                }
				if (y != int((i / 8) * 75))
				{
					x = 0;
					y = (i / 8) * 75;
					continue;
				}
				x += 75;
			}
		}else{
			auto end=std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			//std::cout << elapsed_seconds.count()<<std::endl;
			SDL_Rect rect={40,static_cast<int>(80+std::sin(elapsed_seconds.count()*5)*5),534,334};
			SDL_RenderCopy(renderer,chess_text,nullptr,&rect);
			SDL_Rect rect2={150,320,300,100};
			SDL_RenderCopy(renderer,enter_start,nullptr,&rect2);
		}

		SDL_RenderPresent(renderer);
        SDL_Delay(16);

        if(kingCount!=2&&!inMenu){
            SDL_Delay(3000);
            break;
        }

        //bot_enable && !turnTeam
        if(bot_enable && !inMenu && !turnTeam) {
            SDL_Delay(1000);
            int src,dst;
            do{
                src=std::rand()%64;
                dst=std::rand()%64;
            } while (board[src].Team==board[dst].Team||!legalMoves::isLegalMove(src,dst,board)||board[src].Team!=turnTeam);
            board[dst] = board[src];
            board[src] = { -1,' ' };
            turnTeam = !turnTeam;
            Mix_Volume(-1,MIX_MAX_VOLUME);
            Mix_PlayChannel(-1, placesfx, 0);
        }
    }
	Mix_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}