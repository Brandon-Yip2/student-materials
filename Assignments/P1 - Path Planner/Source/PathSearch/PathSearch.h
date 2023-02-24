#include "../platform.h" // This file will make exporting DLL symbols simpler for students.
#include "../Framework/TileSystem/TileMap.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include "../PriorityQueue.h"


namespace ufl_cap4053
{
	namespace searches
	{
		class PathSearch
		{
			struct PlannerNode {
				Tile* selfTile;
				PlannerNode* prev;

				float heuristicCost;
				float givenCost;

				float finalcost;


				PlannerNode(Tile* curr) {
					this->selfTile = curr;
				}

			};

			private:

				std::vector<Tile*> Result;

				static bool foo(PlannerNode* const &lhs, PlannerNode* const &rhs) {
					
					return lhs->finalcost > rhs->finalcost;


				}

				bool solved = false;

				//This contains the raw TileMap 
				TileMap* map;

				//Contains each Tile* and their neighbor Tile*
				
				std::unordered_map<Tile*, std::vector<std::pair<Tile*, float>>> tileNeighbors;


				//Uses in the search. Binds a Tile* to a PlannerNode (Planner nodes have the Tile* itself and its parent)
				std::unordered_map<Tile*, PlannerNode*> PlannerNodes;

				//FOR Breadth First Search (not used later)
				//Stores the current Queue for the search
				//std::queue<PlannerNode*> q;

				ufl_cap4053::PriorityQueue<PlannerNode*> Q;
				

				//Stores the visited Tile* in a map
				std::unordered_map<Tile*, PlannerNode*> visited;


				//Start and ending Tiles for the current search
				Tile* start = nullptr;
				Tile* end = nullptr;






		// CLASS DECLARATION GOES HERE
			public:

				DLLEXPORT PathSearch(); // EX: DLLEXPORT required for public methods - see platform.h

				//The destructor should perform any final cleanup required before deletion of the object.
				DLLEXPORT ~PathSearch();

				//Called after the tile map is loaded.This is usually where the search graph is generated.NOTE: This method
				//must take no longer than twice the benchmark example for any given map.
				DLLEXPORT void load(TileMap* _tileMap);
					
				//Called before any update of the path planner; should prepare for search to be performed between the tiles at
				//the coordinates indicated.This method is always preceded by at least one call to load().
				DLLEXPORT void initialize(int startRow, int startCol, int goalRow, int goalCol);

				//Called to allow the path planner to execute for the specified timeslice(in milliseconds).Within this method
				//the search should be performed until the time expires or the solution is found.If timeslice is zero(0), this
				//method should only do a single iteration of the algorithm.Otherwise the update should only iterate for the
				//indicated number of milliseconds.This method is always preceded by at least one call to initialize().
				DLLEXPORT void update(long timeslice);

				//Called when the current search data is no longer needed.It should clean up any memory allocated for this
				//search.Note that this is not the same as the destructor, as the search object may be reset to perform another
				//search on the same map.May be called before initialize() and /or update() in some cases.
				DLLEXPORT void shutdown();
	
				//Called when tile map is unloadedand should clean up any memory allocated for the tile map.This is not the
				//same as the destructor, as the search object may be reinitialized with a new map.May be called before load().
				DLLEXPORT void unload();

				//Returns true if the update function has finished because it found a solution, and false otherwise.Once a
				//search has completed, this method should continue to return true until initialize() is called.
				DLLEXPORT bool isDone() const;

				//Return a vector containing the solution path as an ordered series of Tile pointers from finish to start.Once
				//a search has been completed, this method continue to return the path until initialize() is called.
				DLLEXPORT std::vector<Tile const*> const getSolution() const;


		

				
		};
	}
}  // close namespace ufl_cap4053::searches
