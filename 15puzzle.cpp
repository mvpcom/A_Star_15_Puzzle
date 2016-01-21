////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STL A* Search implementation
// ReDesign by Mojtaba Valipour for 15-Puzzle- 2014
// This uses Justin Heyes-Jones A* code to solve the 8-puzzle
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <new>
#include <ctype.h>

using namespace std;

// Configuration
#define NUM_TIMES_TO_RUN_SEARCH 1
#define DISPLAY_SOLUTION_FORWARDS 1
#define DISPLAY_SOLUTION_BACKWARDS 0
#define DISPLAY_SOLUTION_INFO 1
#define DEBUG_LISTS 0
// AStar search class
#include "stlastar.h" // See header for copyright and usage information
// Global data
#define BOARD_WIDTH   (4)
#define BOARD_HEIGHT  (4)
#define GM_TILE     (-1)
#define GM_SPACE	 (0)
#define GM_OFF_BOARD (1)
// Definitions

class PuzzleState
{
public:
	// defs
	typedef enum
	{
		TL_SPACE,
		TL_1,
		TL_2,
		TL_3,
		TL_4,
		TL_5,
		TL_6,
		TL_7,
		TL_8,
		TL_9,
		TL_A,
		TL_B,
		TL_C,
		TL_D,
		TL_E,
		TL_F
	} TILE;
	// data
	static TILE g_goal[ BOARD_WIDTH*BOARD_HEIGHT];
	static TILE g_start[ BOARD_WIDTH*BOARD_HEIGHT];
	// the tile data for the 8-puzzle
	TILE tiles[ BOARD_WIDTH*BOARD_HEIGHT ];
	// member functions
	PuzzleState() {  
						memcpy( tiles, g_goal, sizeof( TILE ) * BOARD_WIDTH * BOARD_HEIGHT );			
					}

	PuzzleState( TILE *param_tiles ) 
					{
						memcpy( tiles, param_tiles, sizeof( TILE ) * BOARD_WIDTH * BOARD_HEIGHT );			
					}

	float GoalDistanceEstimate( PuzzleState &nodeGoal );
	bool IsGoal( PuzzleState &nodeGoal );
	bool GetSuccessors( AStarSearch<PuzzleState> *astarsearch, PuzzleState *parent_node );
	float GetCost( PuzzleState &successor );
	bool IsSameState( PuzzleState &rhs );
	
	void PrintNodeInfo(); 

//private:
//	// User stuff - Just add what you need to help you write the above functions...
//
	void GetSpacePosition( PuzzleState *pn, int *rx, int *ry );
	bool LegalMove( TILE *StartTiles, TILE *TargetTiles, int spx, int spy, int tx, int ty );
	int GetMap( int x, int y, TILE *tiles );
};

// Goal state
PuzzleState::TILE PuzzleState::g_goal[] = 
{
	TL_1,
	TL_2,
	TL_3,
	TL_4,
	TL_5,
	TL_6,
	TL_7,
	TL_8,
	TL_9,
	TL_A,
	TL_B,
	TL_C,
	TL_D,
	TL_E,
	TL_F,
	TL_SPACE,
};

// Start states
PuzzleState::TILE PuzzleState::g_start[] = 
{
	TL_SPACE,
	TL_6,
	TL_2,
	TL_4,
	TL_1,
	TL_A,
	TL_3,
	TL_8,
	TL_5,
	TL_E,
	TL_7,
	TL_C,
	TL_9,
	TL_D,
	TL_B,
	TL_F,
};

bool PuzzleState::IsSameState( PuzzleState &rhs )
{
	for( int i=0; i<(BOARD_HEIGHT*BOARD_WIDTH); i++ )
	{
		if( tiles[i] != rhs.tiles[i] )
		{
			return false;
		}
	}
	return true;
}

// Redesign by Mojtaba Valipour
void PuzzleState::PrintNodeInfo()
{
	char str[100];
	int t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;
	switch (tiles[0]){
		case 0:
			t0=tiles[0] + '0';
			break;
		case 1:
			t0 = tiles[0] + '0';
			break;
		case 2:
			t0 = tiles[0] + '0';
			break;
		case 3:
			t0 = tiles[0] + '0';
			break;
		case 4:
			t0 = tiles[0] + '0';
			break;
		case 5:
			t0 = tiles[0] + '0';
			break;
		case 6:
			t0 = tiles[0] + '0';
			break;
		case 7:
			t0 = tiles[0] + '0';
			break;
		case 8:
			t0 = tiles[0] + '0';
			break;
		case 9:
			t0 = tiles[0] + '0';
			break;

		default:
			t0 = tiles[0] + '7';
	}
	switch (tiles[1]){
	case 0:
		t1 = tiles[1] + '0';
		break;
	case 1:
		t1 = tiles[1] + '0';
		break;
	case 2:
		t1 = tiles[1] + '0';
		break;
	case 3:
		t1 = tiles[1] + '0';
		break;
	case 4:
		t1 = tiles[1] + '0';
		break;
	case 5:
		t1 = tiles[1] + '0';
		break;
	case 6:
		t1 = tiles[1] + '0';
		break;
	case 7:
		t1 = tiles[1] + '0';
		break;
	case 8:
		t1 = tiles[1] + '0';
		break;
	case 9:
		t1 = tiles[1] + '0';
		break;
	default:
		t1 = tiles[1] + '7';
	}
	switch (tiles[2]){
	case 0:
		t2 = tiles[2] + '0';
		break;
	case 1:
		t2 = tiles[2] + '0';
		break;
	case 2:
		t2 = tiles[2] + '0';
		break;
	case 3:
		t2 = tiles[2] + '0';
		break;
	case 4:
		t2 = tiles[2] + '0';
		break;
	case 5:
		t2 = tiles[2] + '0';
		break;
	case 6:
		t2 = tiles[2] + '0';
		break;
	case 7:
		t2 = tiles[2] + '0';
		break;
	case 8:
		t2 = tiles[2] + '0';
		break;
	case 9:
		t2 = tiles[2] + '0';
		break;

	default:
		t2 = tiles[2] + '7';
	}
	switch (tiles[3]){
	case 0:
		t3 = tiles[3] + '0';
		break;
	case 1:
		t3 = tiles[3] + '0';
		break;
	case 2:
		t3 = tiles[3] + '0';
		break;
	case 3:
		t3 = tiles[3] + '0';
		break;
	case 4:
		t3 = tiles[3] + '0';
		break;
	case 5:
		t3 = tiles[3] + '0';
		break;
	case 6:
		t3 = tiles[3] + '0';
		break;
	case 7:
		t3 = tiles[3] + '0';
		break;
	case 8:
		t3 = tiles[3] + '0';
		break;
	case 9:
		t3 = tiles[3] + '0';
		break;

	default:
		t3 = tiles[3] + '7';
	}
	switch (tiles[4]){
	case 0:
		t4 = tiles[4] + '0';
		break;
	case 1:
		t4 = tiles[4] + '0';
		break;
	case 2:
		t4 = tiles[4] + '0';
		break;
	case 3:
		t4 = tiles[4] + '0';
		break;
	case 4:
		t4 = tiles[4] + '0';
		break;
	case 5:
		t4 = tiles[4] + '0';
		break;
	case 6:
		t4 = tiles[4] + '0';
		break;
	case 7:
		t4 = tiles[4] + '0';
		break;
	case 8:
		t4 = tiles[4] + '0';
		break;
	case 9:
		t4 = tiles[4] + '0';
		break;

	default:
		t4 = tiles[4] + '7';
	}
	switch (tiles[5]){
	case 0:
		t5 = tiles[5] + '0';
		break;
	case 1:
		t5 = tiles[5] + '0';
		break;
	case 2:
		t5 = tiles[5] + '0';
		break;
	case 3:
		t5 = tiles[5] + '0';
		break;
	case 4:
		t5 = tiles[5] + '0';
		break;
	case 5:
		t5 = tiles[5] + '0';
		break;
	case 6:
		t5 = tiles[5] + '0';
		break;
	case 7:
		t5 = tiles[5] + '0';
		break;
	case 8:
		t5 = tiles[5] + '0';
		break;
	case 9:
		t5 = tiles[5] + '0';
		break;

	default:
		t5 = tiles[5] + '7';
	}
	switch (tiles[6]){
	case 0:
		t6 = tiles[6] + '0';
		break;
	case 1:
		t6 = tiles[6] + '0';
		break;
	case 2:
		t6 = tiles[6] + '0';
		break;
	case 3:
		t6 = tiles[6] + '0';
		break;
	case 4:
		t6 = tiles[6] + '0';
		break;
	case 5:
		t6 = tiles[6] + '0';
		break;
	case 6:
		t6 = tiles[6] + '0';
		break;
	case 7:
		t6 = tiles[6] + '0';
		break;
	case 8:
		t6 = tiles[6] + '0';
		break;
	case 9:
		t6 = tiles[6] + '0';
		break;

	default:
		t6 = tiles[6] + '7';
	}
	switch (tiles[7]){
	case 0:
		t7 = tiles[7] + '0';
		break;
	case 1:
		t7 = tiles[7] + '0';
		break;
	case 2:
		t7 = tiles[7] + '0';
		break;
	case 3:
		t7 = tiles[7] + '0';
		break;
	case 4:
		t7 = tiles[7] + '0';
		break;
	case 5:
		t7 = tiles[7] + '0';
		break;
	case 6:
		t7 = tiles[7] + '0';
		break;
	case 7:
		t7 = tiles[7] + '0';
		break;
	case 8:
		t7 = tiles[7] + '0';
		break;
	case 9:
		t7 = tiles[7] + '0';
		break;

	default:
		t7 = tiles[7] + '7';
	}
	switch (tiles[8]){
	case 0:
		t8 = tiles[8] + '0';
		break;
	case 1:
		t8 = tiles[8] + '0';
		break;
	case 2:
		t8 = tiles[8] + '0';
		break;
	case 3:
		t8 = tiles[8] + '0';
		break;
	case 4:
		t8 = tiles[8] + '0';
		break;
	case 5:
		t8 = tiles[8] + '0';
		break;
	case 6:
		t8 = tiles[8] + '0';
		break;
	case 7:
		t8 = tiles[8] + '0';
		break;
	case 8:
		t8 = tiles[8] + '0';
		break;
	case 9:
		t8 = tiles[8] + '0';
		break;

	default:
		t8 = tiles[8] + '7';
	}
	switch (tiles[9]){
	case 0:
		t9 = tiles[9] + '0';
		break;
	case 1:
		t9 = tiles[9] + '0';
		break;
	case 2:
		t9 = tiles[9] + '0';
		break;
	case 3:
		t9 = tiles[9] + '0';
		break;
	case 4:
		t9 = tiles[9] + '0';
		break;
	case 5:
		t9 = tiles[9] + '0';
		break;
	case 6:
		t9 = tiles[9] + '0';
		break;
	case 7:
		t9 = tiles[9] + '0';
		break;
	case 8:
		t9 = tiles[9] + '0';
		break;
	case 9:
		t9 = tiles[9] + '0';
		break;

	default:
		t9 = tiles[9] + '7';
	}
	switch (tiles[10]){
	case 0:
		t10 = tiles[10] + '0';
		break;
	case 1:
		t10 = tiles[10] + '0';
		break;
	case 2:
		t10 = tiles[10] + '0';
		break;
	case 3:
		t10 = tiles[10] + '0';
		break;
	case 4:
		t10 = tiles[10] + '0';
		break;
	case 5:
		t10 = tiles[10] + '0';
		break;
	case 6:
		t10 = tiles[10] + '0';
		break;
	case 7:
		t10 = tiles[10] + '0';
		break;
	case 8:
		t10 = tiles[10] + '0';
		break;
	case 9:
		t10 = tiles[10] + '0';
		break;

	default:
		t10 = tiles[10] + '7';
	}
	switch (tiles[11]){
	case 0:
		t11 = tiles[11] + '0';
		break;
	case 1:
		t11 = tiles[11] + '0';
		break;
	case 2:
		t11 = tiles[11] + '0';
		break;
	case 3:
		t11 = tiles[11] + '0';
		break;
	case 4:
		t11 = tiles[11] + '0';
		break;
	case 5:
		t11 = tiles[11] + '0';
		break;
	case 6:
		t11 = tiles[11] + '0';
		break;
	case 7:
		t11 = tiles[11] + '0';
		break;
	case 8:
		t11 = tiles[11] + '0';
		break;
	case 9:
		t11 = tiles[11] + '0';
		break;

	default:
		t11 = tiles[11] + '7';
	}
	switch (tiles[12]){
	case 0:
		t12 = tiles[12] + '0';
		break;
	case 1:
		t12 = tiles[12] + '0';
		break;
	case 2:
		t12 = tiles[12] + '0';
		break;
	case 3:
		t12 = tiles[12] + '0';
		break;
	case 4:
		t12 = tiles[12] + '0';
		break;
	case 5:
		t12 = tiles[12] + '0';
		break;
	case 6:
		t12 = tiles[12] + '0';
		break;
	case 7:
		t12 = tiles[12] + '0';
		break;
	case 8:
		t12 = tiles[12] + '0';
		break;
	case 9:
		t12 = tiles[12] + '0';
		break;

	default:
		t12 = tiles[12] + '7';
	}
	switch (tiles[13]){
	case 0:
		t13 = tiles[13] + '0';
		break;
	case 1:
		t13 = tiles[13] + '0';
		break;
	case 2:
		t13 = tiles[13] + '0';
		break;
	case 3:
		t13 = tiles[13] + '0';
		break;
	case 4:
		t13 = tiles[13] + '0';
		break;
	case 5:
		t13 = tiles[13] + '0';
		break;
	case 6:
		t13 = tiles[13] + '0';
		break;
	case 7:
		t13 = tiles[13] + '0';
		break;
	case 8:
		t13 = tiles[13] + '0';
		break;
	case 9:
		t13 = tiles[13] + '0';
		break;

	default:
		t13 = tiles[13] + '7';
	}
	switch (tiles[14]){
	case 0:
		t14 = tiles[14] + '0';
		break;
	case 1:
		t14 = tiles[14] + '0';
		break;
	case 2:
		t14 = tiles[14] + '0';
		break;
	case 3:
		t14 = tiles[14] + '0';
		break;
	case 4:
		t14 = tiles[14] + '0';
		break;
	case 5:
		t14 = tiles[14] + '0';
		break;
	case 6:
		t14 = tiles[14] + '0';
		break;
	case 7:
		t14 = tiles[14] + '0';
		break;
	case 8:
		t14 = tiles[14] + '0';
		break;
	case 9:
		t14 = tiles[14] + '0';
		break;

	default:
		t14 = tiles[14] + '7';
	}
	switch (tiles[15]){
	case 0:
		t15 = tiles[15] + '0';
		break;
	case 1:
		t15 = tiles[15] + '0';
		break;
	case 2:
		t15 = tiles[15] + '0';
		break;
	case 3:
		t15 = tiles[15] + '0';
		break;
	case 4:
		t15 = tiles[15] + '0';
		break;
	case 5:
		t15 = tiles[15] + '0';
		break;
	case 6:
		t15 = tiles[15] + '0';
		break;
	case 7:
		t15 = tiles[15] + '0';
		break;
	case 8:
		t15 = tiles[15] + '0';
		break;
	case 9:
		t15 = tiles[15] + '0';
		break;

	default:
		t15 = tiles[15] + '7';
	}
	sprintf_s(str, "%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n%c %c %c %c\n",
		t0,
		t1,
		t2,
		t3,
		t4,
		t5,
		t6,
		t7,
		t8,
		t9,
		t10,
		t11,
		t12,
		t13,
		t14,
		t15
		);
	cout << str;
}

// Here's the heuristic function that estimates the distance from a PuzzleState
// to the Goal. 
// ReDesign by Mojtaba Valipour

float PuzzleState::GoalDistanceEstimate( PuzzleState &nodeGoal )
{	
	int tile_x[ BOARD_WIDTH * BOARD_HEIGHT ] =
	{
		/* TL_SPACE */ 3,
		/* TL_1 */ 0,    
		/* TL_2 */ 1,    
		/* TL_3 */ 2,    
		/* TL_4 */ 3,    
		/* TL_5 */ 0,    
		/* TL_6 */ 1,    
		/* TL_7 */ 2,    
		/* TL_8 */ 3, 
		/* TL_9 */ 0,
		/* TL_A */ 1,
		/* TL_B */ 2,
		/* TL_C */ 3,
		/* TL_D */ 0,
		/* TL_E */ 1,
		/* TL_F */ 2,
	};

	int tile_y[ BOARD_WIDTH * BOARD_HEIGHT ] =
	{
		/* TL_SPACE */ 3,
		/* TL_1 */ 0,
		/* TL_2 */ 0,
		/* TL_3 */ 0,
		/* TL_4 */ 0,
		/* TL_5 */ 1,
		/* TL_6 */ 1,
		/* TL_7 */ 1,
		/* TL_8 */ 1,
		/* TL_9 */ 2,
		/* TL_A */ 2,
		/* TL_B */ 2,
		/* TL_C */ 2,
		/* TL_D */ 3,
		/* TL_E */ 3,
		/* TL_F */ 3,
	};

	//Manhattan by Mojtaba Valipour for 15 puzzle
	float distance = 0;
	float result = 0;
	int x = 0; // Position x of Current Node
	int y = 0; // Position y of Current Node
	int X = 0; // Position X of Goal
	int Y = 0; // Position Y of Goal
	for (int i = 0; i < BOARD_WIDTH*BOARD_HEIGHT; i++){
		if (tiles[i]==g_goal[i]) continue;
		x = tile_x[tiles[i]];
		y = tile_y[tiles[i]];
		X = i % BOARD_WIDTH;
		Y = i / BOARD_WIDTH;
		result += abs(x-X);
		result += abs(y-Y);
		distance += result;
	}
	return distance; //Manhattan Distance

	//4x Manhattan by Mojtaba Valipour for 15 puzzle is faster than Manhattan
	//float distance = 0;
	//float result = 0;
	//int x = 0; // Position x of Current Node
	//int y = 0; // Position y of Current Node
	//int X = 0; // Position X of Goal
	//int Y = 0; // Position Y of Goal
	//for (int i = 0; i < BOARD_WIDTH*BOARD_HEIGHT; i++){
	//	if (tiles[i] == g_goal[i]) continue;
	//	x = tile_x[tiles[i]];
	//	y = tile_y[tiles[i]];
	//	X = i % BOARD_WIDTH;
	//	Y = i / BOARD_WIDTH;
	//	result += abs(x - X);
	//	result += abs(y - Y);
	//	distance += result;
	//}
	//return 4*distance; //Manhattan Distance

}

bool PuzzleState::IsGoal( PuzzleState &nodeGoal )
{
	return IsSameState( nodeGoal );
}

// Helper
// Return the x and y position of the space tile
void PuzzleState::GetSpacePosition( PuzzleState *pn, int *rx, int *ry )
{
	int x,y;

	for( y=0; y<BOARD_HEIGHT; y++ )
	{
		for( x=0; x<BOARD_WIDTH; x++ )
		{
			if( pn->tiles[(y*BOARD_WIDTH)+x] == TL_SPACE )
			{
				*rx = x;
				*ry = y;

				return;
			}
		}
	}

	assert( false && "Something went wrong. There's no space on the board" );

}

int PuzzleState::GetMap( int x, int y, TILE *tiles )
{

	if( x < 0 ||
	    x >= BOARD_WIDTH ||
		 y < 0 ||
		 y >= BOARD_HEIGHT
	  )
		return GM_OFF_BOARD;	 

	if( tiles[(y*BOARD_WIDTH)+x] == TL_SPACE )
	{
		return GM_SPACE;
	}

	return GM_TILE;
}

// Given a node set of tiles and a set of tiles to move them into, do the move as if it was on a tile board
// note : returns false if the board wasn't changed, and simply returns the tiles as they were in the target
// spx and spy is the space position while tx and ty is the target move from position

bool PuzzleState::LegalMove( TILE *StartTiles, TILE *TargetTiles, int spx, int spy, int tx, int ty )
{

	int t;
	
	if( GetMap( spx, spy, StartTiles ) == GM_SPACE )
	{
		if( GetMap( tx, ty, StartTiles ) == GM_TILE )
		{

			// copy tiles
			for( t=0; t<(BOARD_HEIGHT*BOARD_WIDTH); t++ )
			{
				TargetTiles[t] = StartTiles[t];
			}


			TargetTiles[ (ty*BOARD_WIDTH)+tx ] = StartTiles[ (spy*BOARD_WIDTH)+spx ];
			TargetTiles[ (spy*BOARD_WIDTH)+spx ] = StartTiles[ (ty*BOARD_WIDTH)+tx ];

			return true;
		}
	}


	return false;

}

// This generates the successors to the given PuzzleState. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool PuzzleState::GetSuccessors( AStarSearch<PuzzleState> *astarsearch, PuzzleState *parent_node )
{
	PuzzleState NewNode;

	int sp_x,sp_y;

	GetSpacePosition( this, &sp_x, &sp_y );

	bool ret;

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x, sp_y-1 ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );

		if( !ret ) return false;
	}

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x, sp_y+1 ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );
		
		if( !ret ) return false;
	}

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x-1, sp_y ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );

		if( !ret ) return false;
	}

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x+1, sp_y ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );
	
		if( !ret ) return false;
	}

	return true; 
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float PuzzleState::GetCost( PuzzleState &successor )
{
	return 1.0f; // I love it when life is simple

}


// Main
// Changed by Mojtaba Valipour
int main( int argc, char *argv[] )
{
	cout << "STL A* 15-puzzle solver implementation\nReDesign & Programming by Mojtaba Valipour\nThe Main Implementation is for 8-Puzzle by Justin Heyes-Jones\n";
	if( argc > 1 )
	{
		int i = 0;
		int c;
		while( (c = argv[1][i]) )
		{
			if( isdigit( c ) )
			{
				int num = (c - '0');
				PuzzleState::g_start[i] = static_cast<PuzzleState::TILE>(num);			
			}	
			i++;
		}
	}

	// Create an instance of the search class...

	AStarSearch<PuzzleState> astarsearch;

	int NumTimesToSearch = NUM_TIMES_TO_RUN_SEARCH;

	while( NumTimesToSearch-- )
	{
		// Create a start state
		PuzzleState nodeStart( PuzzleState::g_start );
		// Define the goal state
		PuzzleState nodeEnd( PuzzleState::g_goal );
		// Set Start and goal states
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );
		unsigned int SearchState;
		unsigned int SearchSteps = 0;
		do
		{
			SearchState = astarsearch.SearchStep();
			SearchSteps++;
		}
		while( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_SUCCEEDED )
		{
#if DISPLAY_SOLUTION_FORWARDS
			cout << "Search found goal state\n";
#endif
			PuzzleState *node = astarsearch.GetSolutionStart();

#if DISPLAY_SOLUTION_FORWARDS
			cout << "Displaying solution\n";
#endif
			int steps = 0;

#if DISPLAY_SOLUTION_FORWARDS
			node->PrintNodeInfo();
			cout << endl;
#endif
			for( ;; )
			{
				node = astarsearch.GetSolutionNext();

				if( !node )
				{
					break;
				}

#if DISPLAY_SOLUTION_FORWARDS
				node->PrintNodeInfo();
				cout << endl;
#endif
				steps ++;
			
			};

#if DISPLAY_SOLUTION_FORWARDS
			// todo move step count into main algorithm
			cout << "Solution steps " << steps << endl;
#endif

////////////

			node = astarsearch.GetSolutionEnd();

#if DISPLAY_SOLUTION_BACKWARDS
			cout << "Displaying reverse solution\n";
#endif
			steps = 0;

			node->PrintNodeInfo();
			cout << endl;
			for( ;; )
			{
				node = astarsearch.GetSolutionPrev();

				if( !node )
				{
					break;
				}
#if DISPLAY_SOLUTION_BACKWARDS
				node->PrintNodeInfo();
                cout << endl;
#endif
				steps ++;
			
			};

#if DISPLAY_SOLUTION_BACKWARDS
			cout << "Solution steps " << steps << endl;
#endif

//////////////

			// Once you're done with the solution you can free the nodes up
			astarsearch.FreeSolutionNodes();
		
		}
		else if( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_FAILED ) 
		{
#if DISPLAY_SOLUTION_INFO
			cout << "Search terminated. Did not find goal state\n";
#endif		
		}
		else if( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_OUT_OF_MEMORY ) 
		{
#if DISPLAY_SOLUTION_INFO
			cout << "Search terminated. Out of memory\n";
#endif		
		}

		

		// Display the number of loops the search went through
#if DISPLAY_SOLUTION_INFO
		cout << "SearchSteps : " << astarsearch.GetStepCount() << endl;
#endif
	}
	system("PAUSE");
	return 0;
}


