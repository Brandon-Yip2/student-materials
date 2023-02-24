#include "PathSearch.h"
#include <vector>
#include "../PriorityQueue.h"
#include <unordered_map>
#include <queue>
#include <math.h>

namespace ufl_cap4053
{
	namespace searches
	{

		float distance(Tile* start, Tile* end) {
			
			float distance = 0;
			
			float X2 = end->getXCoordinate();
			float X1 = start->getXCoordinate();
			float Y2 = end->getYCoordinate();
			float Y1 = start->getYCoordinate();

			distance = sqrt(pow(X2 - X1, 2) + pow(Y2 - Y1, 2) * 1.0);
			return distance;
		}

		// EX: DLLEXPORT required for public methods - see platform.h
		DLLEXPORT PathSearch::PathSearch() : Q(foo) {
			
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
								float d = 2 * this->map->getTileRadius();
								float cost = d * going->getWeight();
								auto pair = std::make_pair(going, cost);
								tileNeighbors[curr].push_back(pair);
								neighborNum++;
							}
						}
						//Bottom Right
						if (curr->getRow() < rows-1) {
							if ((rawData->getTile(curr->getRow() + 1, curr->getColumn()))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn()));
								curr->addLineTo(going, 3);
								float d = 2 * this->map->getTileRadius();
								float cost = d * going->getWeight();
								auto pair = std::make_pair(going, cost);
								tileNeighbors[curr].push_back(pair);
								neighborNum++;

							}
							
						}
						//Bottom Left
						if (curr->getRow() < rows - 1 && curr->getColumn() > 0) {
							if ((rawData->getTile(curr->getRow() + 1, curr->getColumn() - 1))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn() - 1));
								curr->addLineTo(going, 3);
								float d = 2 * this->map->getTileRadius();
								float cost = d * going->getWeight();
								auto pair = std::make_pair(going, cost);
								tileNeighbors[curr].push_back(pair);
								neighborNum++;
							}
						}
						//Left
						if (curr->getColumn() > 0) {
							if ((rawData->getTile(curr->getRow(), curr->getColumn() - 1))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow(), curr->getColumn() - 1));
								curr->addLineTo(going, 3);
								float d = 2 * this->map->getTileRadius();
								float cost = d * going->getWeight();
								auto pair = std::make_pair(going, cost);
								tileNeighbors[curr].push_back(pair);
								neighborNum++;
							}	
						}
						//Top Left
						if (curr->getRow() > 0 && curr->getColumn() > 0) {
							if ((rawData->getTile(curr->getRow() - 1, curr->getColumn() - 1))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn() - 1));
								curr->addLineTo(going, 3);
								float d = 2 * this->map->getTileRadius();
								float cost = d * going->getWeight();
								auto pair = std::make_pair(going, cost);
								tileNeighbors[curr].push_back(pair);
								neighborNum++;
							}
							
						}
						//Top Right
						if (curr->getRow() > 0 ) {
							if ((rawData->getTile(curr->getRow() - 1, curr->getColumn()))->getWeight() != 0) {
								Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn()));
								curr->addLineTo(going, 3);
								float d = 2 * this->map->getTileRadius();
								float cost = d * going->getWeight();
								auto pair = std::make_pair(going, cost);
								tileNeighbors[curr].push_back(pair);
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
									float d = 2 * this->map->getTileRadius();
									float cost = d * going->getWeight();
									auto pair = std::make_pair(going, cost);
									tileNeighbors[curr].push_back(pair);
									neighborNum++;
								}

							}
							//Bottom Right
							if (curr->getRow() < rows - 1 && curr->getColumn() < cols - 1) {
								if ((rawData->getTile(curr->getRow() + 1, curr->getColumn() + 1))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn() + 1));
									curr->addLineTo(going, 3);
									float d = 2 * this->map->getTileRadius();
									float cost = d * going->getWeight();
									auto pair = std::make_pair(going, cost);
									tileNeighbors[curr].push_back(pair);
									neighborNum++;
								}


								
							}
							//Bottom Left
							if (curr->getRow() < rows - 1) {
								if ((rawData->getTile(curr->getRow() + 1, curr->getColumn()))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() + 1, curr->getColumn()));
									curr->addLineTo(going, 3);
									float d = 2 * this->map->getTileRadius();
									float cost = d * going->getWeight();
									auto pair = std::make_pair(going, cost);
									tileNeighbors[curr].push_back(pair);
									neighborNum++;
								}
								
							}
							//Left
							if (curr->getColumn() > 0) {
								if ((rawData->getTile(curr->getRow(), curr->getColumn() - 1))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow(), curr->getColumn() - 1));
									curr->addLineTo(going, 3);
									float d = 2 * this->map->getTileRadius();
									float cost = d * going->getWeight();
									auto pair = std::make_pair(going, cost);
									tileNeighbors[curr].push_back(pair);
									neighborNum++;
								}
								
							}
							//Top Left
							if (curr->getRow() > 0) {
								if ((rawData->getTile(curr->getRow() - 1, curr->getColumn()))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn()));
									curr->addLineTo(going, 3);
									float d = 2 * this->map->getTileRadius();
									float cost = d * going->getWeight();
									auto pair = std::make_pair(going, cost);
									tileNeighbors[curr].push_back(pair);
									neighborNum++;
								}
								
							}
							//Top Right
							if (curr->getRow() > 0 && curr->getColumn() < cols - 1) {
								if ((rawData->getTile(curr->getRow() - 1, curr->getColumn() + 1))->getWeight() != 0) {
									Tile* going = (rawData->getTile(curr->getRow() - 1, curr->getColumn() + 1));
									curr->addLineTo(going, 3);
									float d = 2 * this->map->getTileRadius();
									float cost = d * going->getWeight();
									auto pair = std::make_pair(going, cost);
									tileNeighbors[curr].push_back(pair);
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

			

			this->start = map->getTile(startRow, startCol);
			this->end = map->getTile(goalRow, goalCol);

			PlannerNode* firstPlanner = new PlannerNode(start);
			firstPlanner->prev = nullptr;
			
			this->Q.push(firstPlanner);

			this->visited[start] = Q.front();
			this->visited[start]->heuristicCost = distance(start, end);
			Q.front()->givenCost = 0;

			Q.front()->finalcost = Q.front()->givenCost + Q.front()->heuristicCost;


		};

		//Called to allow the path planner to execute for the specified timeslice(in milliseconds).Within this method
		//the search should be performed until the time expires or the solution is found.If timeslice is zero(0), this
		//method should only do a single iteration of the algorithm.Otherwise the update should only iterate for the
		//indicated number of milliseconds.This method is always preceded by at least one call to initialize().
		DLLEXPORT void PathSearch::update(long timeslice) {
			bool once = false;
			if (timeslice == 0) {
				once = true;
			}
			//one iteration
			if (once) {
				
				//If the q isn't empty, do ONE iteration of the algorithm
				if (!Q.empty()) {
					PlannerNode* current = Q.front();
					Q.pop();
					current->selfTile->setFill(0xFFFFC0CB);
					

					//The current Tile is the end tile, End algorithm
					if (current->selfTile == this->end) {
						solved = true;

						while (current->prev != nullptr) {
						

							current->selfTile->addLineTo(current->prev->selfTile, 0xFFFF0000);
							Result.push_back(current->selfTile);

							current = current->prev;

							
						
						}



						return;
					}

					//Not the solution, add its children to the Q
					for (int i = 0; i < tileNeighbors[current->selfTile].size(); i++) {
						//Readability, store the Tile* of the successorTile
						Tile* successorTile = tileNeighbors[current->selfTile].at(i).first;

						//tileNeighbors[current->selfTile].at(i) Is the successor pair, first is the Tile*, second is the cost to go there
						float tempGivenCost = current->givenCost + tileNeighbors[current->selfTile].at(i).second;

						

						//if not null, its has been searched before
						if (visited[tileNeighbors[current->selfTile].at(i).first] != NULL) {

							//Update the successorNode if the current path was cheaper than previous paths
							if (tempGivenCost < visited[successorTile]->givenCost) {
								
								PlannerNode* successorNode = visited[successorTile];
								Q.remove(successorNode);
								successorNode->givenCost = tempGivenCost;
								successorNode->prev = current;
								Q.push(successorNode);

							}


						}
						else {
							//The children node is created using a Tile* in the constructor. The Tile* is found through the current neighbors vector at position i
							PlannerNode* successorNode = new PlannerNode(successorTile);
							successorNode->givenCost = tempGivenCost;
							//Store a pointer to the current node inside of the successor node. This is used to trace back the path
							successorNode->prev = current;

							//Mark the successor as visited as well, bind its Tile* to the PlannerNode
							successorNode->heuristicCost = distance(successorTile, this->end);
							successorNode->finalcost = successorNode->givenCost + successorNode->heuristicCost * 1;

							visited[successorTile] = successorNode;
							successorTile->setFill(0xFF92C9CB);

							this->Q.push(successorNode);
						
						
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
