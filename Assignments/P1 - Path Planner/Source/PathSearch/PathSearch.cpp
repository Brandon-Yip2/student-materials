#include "PathSearch.h"
#include <vector>
#include "../PriorityQueue.h"
#include <unordered_map>
#include <queue>

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
			
			this->map = _tileMap;
			TileMap* rawData = _tileMap;
			int cols = rawData->getColumnCount();
			int rows = rawData->getRowCount();


			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					//For each of the Tiles
					Tile* curr = rawData->getTile(i, j);
					int neighborNum = 0;

					//Even or odd row?
					bool even = false;
					if (i % 2 == 0) {
						even = true;
					}

					//Even row Tile
					if (even && curr->getWeight() != 0) {
						//Right Tile
						if (curr->getColumn() < cols-1) {
							if ((rawData->getTile(curr->getRow(), curr->getColumn() + 1)->getWeight() != 0)) {
								Tile* going = rawData->getTile(curr->getRow(), curr->getColumn() + 1);
								curr->addLineTo(going, 3);
								tileNeighbors[curr].push_back(going);
								neighborNum++;
							}
						}
						//Bottom Right
						if (curr->getRow() < rows-1) {
							if ((rawData->getTile(curr->getRow() + 1, curr->getColumn()))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn()));
								curr->addLineTo(going, 3);
								tileNeighbors[curr].push_back(going);
								neighborNum++;

							}
							
						}
						//Bottom Left
						if (curr->getRow() < rows - 1 && curr->getColumn() > 0) {
							if ((rawData->getTile(curr->getRow() + 1, curr->getColumn() - 1))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn() - 1));
								curr->addLineTo(going, 3);
								tileNeighbors[curr].push_back(going);
								neighborNum++;
							}
						}
						//Left
						if (curr->getColumn() > 0) {
							if ((rawData->getTile(curr->getRow(), curr->getColumn() - 1))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow(), curr->getColumn() - 1));
								curr->addLineTo(going, 3);
								tileNeighbors[curr].push_back(going);
								neighborNum++;
							}	
						}
						//Top Left
						if (curr->getRow() > 0 && curr->getColumn() > 0) {
							if ((rawData->getTile(curr->getRow() - 1, curr->getColumn() - 1))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn() - 1));
								curr->addLineTo(going, 3);
								tileNeighbors[curr].push_back(going);
								neighborNum++;
							}
							
						}
						//Top Right
						if (curr->getRow() > 0 ) {
							if ((rawData->getTile(curr->getRow() - 1, curr->getColumn()))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn()));
								curr->addLineTo(going, 3);
								tileNeighbors[curr].push_back(going);
								neighborNum++;
							}			
						}



						}
						//Odd row tile
						else if (even == false && curr->getWeight() != 0) {
							//Right Tile
							if (curr->getColumn() < cols - 1) {
								if ((rawData->getTile(curr->getRow(), curr->getColumn() + 1)->getWeight() != 0)) {
									Tile* going = (rawData->getTile(curr->getRow(), curr->getColumn() + 1));
									curr->addLineTo(going, 3);
									tileNeighbors[curr].push_back(going);
									neighborNum++;
								}

							}
							//Bottom Right
							if (curr->getRow() < rows - 1 && curr->getColumn() < cols - 1) {
								if ((rawData->getTile(curr->getRow() + 1, curr->getColumn() + 1))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn() + 1));
									curr->addLineTo(going, 3);
									tileNeighbors[curr].push_back(going);
									neighborNum++;
								}


								
							}
							//Bottom Left
							if (curr->getRow() < rows - 1) {
								if ((rawData->getTile(curr->getRow() + 1, curr->getColumn()))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn()));
									curr->addLineTo(going, 3);
									tileNeighbors[curr].push_back(going);
									neighborNum++;
								}
								
							}
							//Left
							if (curr->getColumn() > 0) {
								if ((rawData->getTile(curr->getRow(), curr->getColumn() - 1))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow(), curr->getColumn() - 1));
									curr->addLineTo(going, 3);
									tileNeighbors[curr].push_back(going);
									neighborNum++;
								}
								
							}
							//Top Left
							if (curr->getRow() > 0) {
								if ((rawData->getTile(curr->getRow() - 1, curr->getColumn()))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn()));
									curr->addLineTo(going, 3);
									tileNeighbors[curr].push_back(going);
									neighborNum++;
								}
								
							}
							//Top Right
							if (curr->getRow() > 0 && curr->getColumn() < cols - 1) {
								if ((rawData->getTile(curr->getRow() - 1, curr->getColumn() + 1))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn() + 1));
									curr->addLineTo(going, 3);
									tileNeighbors[curr].push_back(going);
									neighborNum++;
								}
								
							}
						}




				}
			}
			

		}

		//Called before any update of the path planner; should prepare for search to be performed between the tiles at
		//the coordinates indicated.This method is always preceded by at least one call to load().
		DLLEXPORT void PathSearch::initialize(int startRow, int startCol, int goalRow, int goalCol) {
			//Sets starting and end points, adds start point to search queue
			//ufl_cap4053::PriorityQueue<int> pQ();

			this->start = map->getTile(startRow, startCol);
			this->end = map->getTile(goalRow, goalCol);

			PlannerNode* firstPlanner = new PlannerNode(start);
			
			this->q.push(firstPlanner);

			this->visited[start] = q.front();


		};

		//Called to allow the path planner to execute for the specified timeslice(in milliseconds).Within this method
		//the search should be performed until the time expires or the solution is found.If timeslice is zero(0), this
		//method should only do a single iteration of the algorithm.Otherwise the update should only iterate for the
		//indicated number of milliseconds.This method is always preceded by at least one call to initialize().
		DLLEXPORT void PathSearch::update(long timeslice) {
			bool once;
			if (timeslice == 0) {
				once = true;
			}
			//one iteration
			if (once) {
				
				//If the q isn't empty, do ONE iteration of the algorithm
				if (!q.empty()) {
					PlannerNode* current = q.front();
					q.pop();
					current->selfTile->setFill(0xFFFFC0CB);
					

					//The current Tile is the end tile, End algorithm
					if (current->selfTile == this->end) {
						solved = true;
						return;
					}

					//Not the solution, add its children to the Q
					for (int i = 0; i < tileNeighbors[current->selfTile].size(); i++) {
						
						//First check if the child has not been searched before
						if (visited[tileNeighbors[current->selfTile].at(i)] == NULL) {
							//Readability, store the Tile* of the successorTile
							Tile* successorTile = tileNeighbors[current->selfTile].at(i);

							//The children node is created using a Tile* in the constructor. The Tile* is found through the current neighbors vector at position i
							PlannerNode* successorNode = new PlannerNode(successorTile);

							//Store a pointer to the current node inside of the successor node. This is used to trace back the path
							successorNode->prev = current;

							//Mark the successor as visited as well, bind its Tile* to the PlannerNode
							visited[successorTile] = successorNode;
							successorTile->setFill(740405);

							this->q.push(successorNode);

						}

					}
					

				
				}




			}
			//continue until time is 0
			else {
				
			}

			

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
			return solved;
		};

		//Return a vector containing the solution path as an ordered series of Tile pointers from finish to start.Once
		//a search has been completed, this method continue to return the path until initialize() is called.
		DLLEXPORT std::vector<Tile const*> const PathSearch::getSolution() const {
			std::vector<Tile const*> toReturn;
			return toReturn;
		};

		






		// CLASS DEFINITION GOES HERE
	}
}  // close namespace ufl_cap4053::searches
