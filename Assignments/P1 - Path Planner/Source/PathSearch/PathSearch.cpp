#include "PathSearch.h"
#include <vector>
namespace ufl_cap4053
{
	namespace searches
	{


		// EX: DLLEXPORT required for public methods - see platform.h
		DLLEXPORT PathSearch::PathSearch() {
		
		} 

		//The destructor should perform any final cleanup required before deletion of the object.
		DLLEXPORT PathSearch::~PathSearch() {
		
		}

		//Called after the tile map is loaded.This is usually where the search graph is generated.NOTE: This method
		//must take no longer than twice the benchmark example for any given map.
		DLLEXPORT void PathSearch::load(TileMap* _tileMap) {
			
			TileMap* rawData = _tileMap;
			int cols = rawData->getColumnCount();
			int rows = rawData->getRowCount();


			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					Tile* curr = rawData->getTile(i, j);


				}
			}
			

		}

		//Called before any update of the path planner; should prepare for search to be performed between the tiles at
		//the coordinates indicated.This method is always preceded by at least one call to load().
		DLLEXPORT void PathSearch::initialize(int startRow, int startCol, int goalRow, int goalCol) {

		};

		//Called to allow the path planner to execute for the specified timeslice(in milliseconds).Within this method
		//the search should be performed until the time expires or the solution is found.If timeslice is zero(0), this
		//method should only do a single iteration of the algorithm.Otherwise the update should only iterate for the
		//indicated number of milliseconds.This method is always preceded by at least one call to initialize().
		DLLEXPORT void PathSearch::update(long timeslice) {

		};

		//Called when the current search data is no longer needed.It should clean up any memory allocated for this
		//search.Note that this is not the same as the destructor, as the search object may be reset to perform another
		//search on the same map.May be called before initialize() and /or update() in some cases.
		DLLEXPORT void PathSearch::shutdown() {

		};

		//Called when tile map is unloadedand should clean up any memory allocated for the tile map.This is not the
		//same as the destructor, as the search object may be reinitialized with a new map.May be called before load().
		DLLEXPORT void PathSearch::unload() {

		};

		//Returns true if the update function has finished because it found a solution, and false otherwise.Once a
		//search has completed, this method should continue to return true until initialize() is called.
		DLLEXPORT bool PathSearch::isDone() const {
			return true;
		};

		//Return a vector containing the solution path as an ordered series of Tile pointers from finish to start.Once
		//a search has been completed, this method continue to return the path until initialize() is called.
		DLLEXPORT std::vector<Tile const*> const PathSearch::getSolution() const {
			std::vector<Tile const*> toReturn;
			return toReturn;
		};

		DLLEXPORT bool areAdjacent(const Tile* lhs, const Tile* rhs) {
			return true;
		};











		// CLASS DEFINITION GOES HERE
	}
}  // close namespace ufl_cap4053::searches
