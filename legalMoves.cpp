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
		}else if((dest==orig-2&&dest==58&&board[56].type=='r'&&isLegalMove(56,orig-1,board))){
            board[59]={board[56].Team,'r'};
            board[56]={-1,' '};
            return true;
        }else if((dest==orig+2&&dest==62&&board[63].type=='r'&&isLegalMove(63,orig+1,board))){
            board[61]={board[63].Team,'r'};
            board[63]={-1,' '};
            return true;
        }else if((dest==orig+2&&dest==6&&board[7].type=='r'&&isLegalMove(7,orig+1,board))){
            board[5]={board[7].Team,'r'};
            board[7]={-1,' '};
            return true;
        }else if((dest==orig-2&&dest==2&&board[0].type=='r'&&isLegalMove(0,orig-1,board))){
            board[3]={board[0].Team,'r'};
            board[0]={-1,' '};
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
