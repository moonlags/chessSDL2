#include "legalMoves.h"

bool legalMoves::isLegalMove(int orig, int dest,Piece board[64])
{
	int localTeam = board[orig].Team;
	char type = board[orig].type;
	if(localTeam==board[dest].Team)
	{
		return false;
	}
	switch(type)
	{
	case 'p':
		if((localTeam==1&&(board[dest].Team==-1&&(dest==orig-8||(orig>=48&&orig<=55&&dest==orig-16&&board[orig-8].Team==-1)) ||
			(board[dest].Team==0&&(dest==orig-9||dest==orig-7)))) ||
			(localTeam==0)&&(board[dest].Team==-1&&(dest==orig+8||(orig>=8&&orig<=15&&dest==orig+16&&board[orig+8].Team==-1)) ||
			(board[dest].Team==1&&(dest==orig+9||dest==orig+7))))
		{
			if((orig%8==0&&(dest==orig+7||dest==orig-9))||(orig-7)%8==0&&(dest==orig-7||dest==orig+9)){
				return false;
			}
			return true;
		}
		break;
	case 'k':
		if(dest==orig+8||dest==orig-8||!(orig%8==0||orig==0)&&(dest==orig+7||dest==orig-9||dest==orig-1)||
			!((orig-7) % 8 == 0 || orig == 7) && (dest == orig + 1 || dest == orig - 7 || dest == orig + 9))
		{
			return true;
		}
		break;
	case 'r':
		for(int i=1;i<=7;i++){
			if(board[orig+8*i].type!=' '&&dest!=orig+8*i){
				break;
			}else if(dest==orig+8*i){
				return true;
			}
		}
		for(int i=1;i<=7;i++){
			if(board[orig-8*i].type!=' '&&dest!=orig-8*i){
				break;
			}else if(dest==orig-8*i){
				return true;
			}
		}
		for(int i=0;i<=7;i++){
			if(dest==orig-i){
				return true;
			}else if((orig-i)%8==0||(board[orig-i].type!=' '&&i!=0)){
				break;
			}
		}
		for(int i=0;i<=7;i++){
			if(dest==orig+i){
				return true;
			}else if((orig+i-7)%8==0||(board[orig+i].type!=' '&&i!=0)){
				break;
			}
		}
		break;
	case 'b':
		for(int i=0;i<=7;i++){
			if(dest==orig-9*i){
				return true;
			}else if((orig-9*i)%8==0||(board[orig-9*i].type!=' '&&i!=0)){
				break;
			}
		}
		for(int i=0;i<=7;i++){
			if(dest==orig+7*i){
				return true;
			}else if((orig+7*i)%8==0||(board[orig+7*i].type!=' '&&i!=0)){
				break;
			}
		}
		for(int i=0;i<=7;i++){
			if(dest==orig-7*i){
				return true;
			}else if((orig-7*i-7)%8==0||(board[orig-7*i].type!=' '&&i!=0)){
				break;
			}
		}
		for(int i=0;i<=7;i++){
			if(dest==orig+9*i){
				return true;
			}else if((orig+9*i-7)%8==0||(board[orig+9*i].type!=' '&&i!=0)){
				break;
			}
		}
		break;
	case 'q':
		board[orig].type='r';
		if(isLegalMove(orig,dest,board)){
			board[orig].type='q';
			return true;
		}
		board[orig].type='b';
		if(isLegalMove(orig,dest,board)){
			board[orig].type='q';
			return true;
		}
		board[orig].type='q';
		break;
	case 'n':
		if (((!((orig)%8==0||orig==0))&&(dest==orig-17||dest==orig+15))||
                ((!((orig-1)%8==0||orig==1||orig%8==0||orig==0))&&(dest==orig-10||dest==orig+6))||
                ((!((orig-7)%8==0||orig==7))&&(dest==orig+17||dest==orig-15))||
                ((!((orig-6)%8==0||orig==6||(orig-7)%8==0||orig==7))&&(dest==orig+10||dest==orig-6))){
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}
