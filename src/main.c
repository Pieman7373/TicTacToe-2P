/*
 *--------------------------------------
 * Program Name:Tic tac toe
 * Author: Pieman7373
 * License:
 * Description:
 *--------------------------------------
*/

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>

#define FONT_HEIGHT 8

#include "gfx/tictacgfx.h"
/* Put your function prototypes here */
void keywait();
void resetvars();
void winscreen();
/* Put all your globals here */

/* Fill in the body of the main function here */
	
	int xx = 10;
	int  xy = 20;
	int  ox = 40;
	int  oy = 40;
	int  cursorx = 86;
	int previous_cursorx;
	int  cursory = 51;
	int previous_cursory;
	int cursor_step = 50;
	int player = 1;
	int element = 0;
	int test_element = 0;
	int test_result = 0;
	int clear = 0;
	int effectx;
	int effecty;
	int value;
	const char *version = "Tic Tac Toe 2P v1.0";
	int winner = 0;
	const char *xwins = "X Wins!!!!!";
	const char *owins = "O Wins!!!!!";
	const char *catsgame = "It's a tie!!!";
	
	//initalize board array (i think)
	uint8_t board [9] = {0,0,0,0,0,0,0,0,0};
	int coord [9] = {27571,43571,59571,27621,43621,59621,27671,43671,59671};
	
	static jmp_buf buf;
	
void main(void) {	
	
	kb_key_t key;
	
	setjmp(buf);
	

	gfx_SetPalette(tictacgfx_pal, sizeof_tictacgfx_pal, 0);
	gfx_Begin();
	gfx_SetTextScale(2,2);
	gfx_FillScreen(0xFF);
	gfx_SetColor(0x00);
	gfx_SetTransparentColor(0xFF);
	gfx_SetTextFGColor(0x00);
	gfx_SetTextBGColor(0xFF);
	gfx_PrintStringXY(version,2,2);
	gfx_SetTextScale(1,1);
	gfx_PrintStringXY("< ^ v > = Move",2,20);
	gfx_PrintStringXY("[2nd] = Place Piece",2,30);
	gfx_PrintStringXY("[Clear] = Quit",2,40);
	gfx_PrintStringXY("By: Pieman7373 2018",2,232);
	
	/*Draw board*/
		gfx_Line(135,50,135,200);
		gfx_Line(85,100,235,100);
		gfx_Line(85,150,235,150);
		gfx_Line(185,50,185,200);
	
	
	
		
	do {
		
		/*print winner for debug
		gfx_FillRectangle(2,10,20,20);
		gfx_SetTextXY(2,20);
		gfx_PrintInt(winner,1);
		*/
		
		/*print cursor coords for debug
		gfx_SetTextXY(2,20);
		gfx_PrintInt(cursorx,3);
		gfx_SetTextXY(2,30);
		gfx_PrintInt(cursory,3);
		gfx_SetTextXY(2,40);
		gfx_PrintInt(player,1);
		*/	
		
		
			gfx_SetColor(0xFF);
			
		
		if (player == 1) {
			gfx_TransparentSprite(redcursor, cursorx, cursory);
		}
		
		if (player == 2) {
			gfx_TransparentSprite(bluecursor, cursorx, cursory);
		}
		kb_Scan();
		
		if (previous_cursorx != cursorx)  {
			gfx_Rectangle( previous_cursorx, previous_cursory, 49, 49);
		}
		if (previous_cursory != cursory) {
			gfx_Rectangle( previous_cursorx, previous_cursory, 49, 49);
		}
		
			previous_cursorx = cursorx;
			previous_cursory = cursory;
		
		/* for debug, 1 and 2 changes things
		if (kb_Data[3] & kb_1) {
			player = 1;
		}
		if (kb_Data[4] & kb_2) {
			player = 2;
		}
		*/
		
			key = kb_Data[7];
			if (key & kb_Down) {
					cursory = (cursory + cursor_step);
					keywait();
			}
			else if (key & kb_Up) {
					cursory = (cursory - cursor_step);
					keywait();
			}
			else if (key & kb_Left) {
					cursorx = (cursorx - cursor_step);
					keywait();
			}
			else if (key & kb_Right) {
					cursorx = (cursorx + cursor_step);
					keywait();
			}
			
			/*bounds checking*/
			if (cursorx<86) {
				cursorx = 186;
			}
			if (cursorx>186) {
				cursorx = 86;
			}
			if (cursory<51) {
				cursory = 151;
			}
			if (cursory>151) {
				cursory = 51;
			}
			
			
					/*gets value used to search coord array*/
						value = ((cursorx*320)+cursory);
					/*gets element of board array from value*/
						for (element=0; value!=coord[element]; element++);
						
			/*Array debug stuff
					gfx_SetTextXY(2,20);
					gfx_PrintInt(element,1);
					gfx_SetTextXY(2,30);
					gfx_PrintInt(board[element],1);
			*/
				
			
			/*if 2nd, update x or o coords and draw x or o*/
			if (kb_Data[1] & kb_2nd) {
					if (player == 1) {
						xx = cursorx;
						xy = cursory;
					}
					if (player == 2) {
						ox = cursorx;
						oy = cursory;
					}
						
				if (gfx_GetPixel((cursorx+10),(cursory+10)) == 255) {
					if (player == 1) {
						gfx_TransparentSprite(fancyredx, xx, xy);
						board[element] = 1;
						player = 2;
					}
					else if (player == 2) {
						gfx_TransparentSprite(fancyblueo, ox, oy);
						board[element] = 2;
						player = 1;
					}	
				}
				keywait();
				
				//gfx_PrintStringXY(board,2,20);
				
				/*maybe do this before testing for wins
				
				for (test_element = 0; test_element = 9; test_element++) {
					if ((board[test_element] == 1) || (board[test_element] == 2)){
						test_result++;
					}
				}
				
				//Testy debug
				gfx_FillRectangle(2,20,50,50);
				gfx_SetTextXY(2,20);
				gfx_PrintInt(test_result,1);
				*/
			
			//do win checking-ness
			
			if ((board[0]+board[1]+board[2]+board[3]+board[4]+board[5]+board[6]+board[7]+board[8])>= 13) {
			winner = 3;
			}
			
			if (board[0] != 0) { //first column
				if (board[3] == board[0]) {
					if (board[6] == board[3]) {
						if (board[6] == 1) {
							winner = 1;
						}
						else if (board[6] == 2) {
							winner = 2;
						}
					}
				}
			}
			
			if (board[1] != 0) { //second column
				if (board[4] == board[1]) {
					if (board[7] == board[4]) {
						if (board[7] == 1) {
							winner = 1;
						}
						else if (board[7] == 2) {
							winner = 2;
						}
					}
				}
			}
			
			if (board[2] != 0) { //third column
				if (board[5] == board[2]) {
					if (board[8] == board[5]) {
						if (board[8] == 1) {
							winner = 1;
						}
						else if (board[8] == 2) {
							winner = 2;
						}
					}
				}
			}
			
			if (board[0] != 0) { //first row
				if (board[1] == board[0]) {
					if (board[1] == board[2]) {
						if (board[2] == 1) {
							winner = 1;
						}
						if (board[2] == 2) {
							winner = 2;
						}
					}
				}
			}
			
			if (board[3] != 0) { //second row
				if (board[4] == board[3]) {
					if (board[5] == board[4]) {
						if (board[5] == 1) {
							winner = 1;
						}
						if (board[5] == 2) {
							winner = 2;
						}
					}
				}
			}
			
			if (board[6] != 0) { //third row
				if (board[7] == board[6]) {
					if (board[8] == board[7]) {
						if (board[8] == 1) {
							winner = 1;
						}
						if (board[8] == 2) {
							winner = 2;
						}
					}
				}
			}
			
			if (board[0] != 0) { //top left->bottom right diagonal
				if (board[4] == board[0]) {
					if (board[8] == board[4]) {
						if (board[8] == 1) {
							winner = 1;
						}
						if (board[8] == 2) {
							winner = 2;
						}
					}
				}
			}
			
			if (board[2] != 0) { //top right->bottom left diagonal
				if (board[4] == board[2]) {
					if (board[6] == board[4]) {
						if (board[6] == 1) {
							winner = 1;
						}
						if (board[6] == 2) {
							winner = 2;
						}
					}
				}
			}
			
		}
		
		if (winner != 0) {
				winscreen();
					if (clear == 1) {
						break;
					}
				resetvars();
				longjmp(buf,1);
			}
		
		
		
	} while (!(kb_Data[6] & kb_Clear));
	
	gfx_End();
}



/* Put other functions here */
void keywait() { while (kb_AnyKey()); }

void resetvars() {
	xx = 10;
	xy = 20;
	ox = 40;
	oy = 40;
	cursorx = 86;
	cursory = 51;
	player = 1;
	element = 0;
	test_element = 0;
	test_result = 0;
	winner = 0;
	clear = 0;
	board[0]=0;
	board[1]=0;
	board[2]=0;
	board[3]=0;
	board[4]=0;
	board[5]=0;
	board[6]=0;
	board[7]=0;
	board[8]=0;
	return;
}

void winscreen() {
	
		//gfx_FillScreen(0x67);

		
	do {
		
		gfx_SetTextScale(1,1);
		gfx_SetTextFGColor(0x00);
		gfx_PrintStringXY("Press [Enter] to continue, and then",43,210);
		gfx_PrintStringXY("[Clear] to quit, or keep playing",53,220);
		gfx_SetTextFGColor(0x67);
		gfx_SetTextBGColor(0xFF);
		gfx_SetTextScale(4,4);
		
		kb_Scan();
		if (winner == 1) {
				effectx = randInt(0,320);
				effecty = randInt(0,240);
					if (randInt(0,1)) {
						//display firework 1
						gfx_ScaledTransparentSprite_NoClip(red_firework_1_16x16,effectx,effecty,2,2);
					} 
					else if (randInt(0,1)) {
						//display spiral sprite 1
						gfx_TransparentSprite(red_swirl,effectx,effecty);
					}
					else if (randInt(0,1)) {
						//display firework 2
						gfx_ScaledTransparentSprite_NoClip(red_firework_2_16x16,effectx, effecty,2,2);
					}
					
			gfx_PrintStringXY(xwins,45,105);
			gfx_SetTextBGColor(0xE0);
		}
		if (winner == 2) {
				effectx = randInt(0,320);
				effecty = randInt(0,240);
					if (randInt(0,1)) {
						//display firework 1
						gfx_ScaledTransparentSprite_NoClip(blue_firework_1_16x16,effectx,effecty,2,2);
					} 
					else if (randInt(0,1)) {
						//display spiral sprite 1
						gfx_TransparentSprite(blue_swirl,effectx,effecty);
					}
					else if (randInt(0,1)) {
						//display firework 2
						gfx_ScaledTransparentSprite_NoClip(blue_firework_2_16x16,effectx, effecty,2,2);
					}
					
			gfx_PrintStringXY(owins,45,105);
			gfx_SetTextBGColor(0x19);
		}
		if (winner == 3) {
			gfx_SetTextBGColor(0x74);
			//gfx_PrintStringXY(xwins,45,105);
			//gfx_PrintStringXY(owins,45,105);	
			gfx_PrintStringXY(catsgame,15,105);
		}
		
		if (kb_Data[6] & kb_Clear) {
			clear = 1;
			break;
		}
	
	} while (!(kb_Data[6] & kb_Enter));
	return;
}












