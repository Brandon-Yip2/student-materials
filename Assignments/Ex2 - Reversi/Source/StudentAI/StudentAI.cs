using GameAI.GamePlaying.Core;
using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;

namespace GameAI.GamePlaying
{
    public class StudentAI : Behavior
    {



        public StudentAI() { }


        public int invertColor(int _color) {
            if (_color == -1) return 1;
            else if (_color == 1) return -1;
            else return 9999999;
        }
        public int GetNextPlayer(int _color, Board _board) {
            //The _board parameter already has our played move on it.

            //If the next player has a valid move on the board, it is their turn next
            if (_board.HasAnyValidMove(invertColor(_color))) {
                return invertColor(_color);
            }
            //If the next player has no valid moves, it is still our turn
            else return _color;

        }

        public bool betterMove(int _color, ComputerMove currentMove, ComputerMove bestMove) {
            //Return 1 if there is a better move, 0 if there isn't


            // 1 is white, we want the move with higher value
            if (_color == 1)
            {
                if (currentMove.rank > bestMove.rank)
                {
                    return true;
                }
            }   
            //0 is black, we want the move with the lower rank
            else if (_color == -1) {
                if (currentMove.rank < bestMove.rank) {
                    return true;
                }
            }

            return false;

        
        }

        // TODO: Methods go here
        public ComputerMove Run(int _color, Board _board, int _lookAheadDepth)
        {


            ComputerMove bestMove = null;

            Board newBoard = new Board();


            //Create a list to store the moves
            var allMoves = new List<ComputerMove>();

            //Generate the moves for the player
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {

                    if (_board.IsValidMove(_color, i, j)) {
                        ComputerMove newMove = new ComputerMove(i, j);
                        allMoves.Add(newMove);
                    }
                }

            }


            //For each Move that the player has
            foreach (ComputerMove move in allMoves) {


                //Make the board the same as the previous state
                newBoard.Copy(_board);
                //Apply the new move
                newBoard.MakeMove(_color, move.row, move.column);

                if (newBoard.IsTerminalState() || _lookAheadDepth == 0)
                {
                    move.rank = Evaluate(newBoard);
                }
                else {
                    move.rank = Run(GetNextPlayer(_color, newBoard), newBoard, _lookAheadDepth - 1).rank;
                }


                //Best Move shouldn't always be larger. Black and White want either negatives or positives. Change tomorrow
                //Also change evalutateTest and make your own.
                if (bestMove == null || betterMove(_color, move, bestMove)) {
                    bestMove = move;
                }

            
            }


            return bestMove;



        }


        public bool cornerTile(int i, int j)
        {
            if ((i == 0 & j == 0) || (i == 0 & j == 7) || (i == 7 & j == 0) || (i == 7 & j == 7)) {
                return true;
            }
            return false;

        }

        public bool edgeTile(int i, int j) {
            if (cornerTile(i, j) == false) {

                if (i == 0 || j == 0 || i == 7 || j == 7) {
                    return true;
                }
            }
            return false;
            
        }

        public int Evaluate(Board board) {
            int totalEvaluation = 0;

            //For each tile, calculate its value and add it to the total sum
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {

                    int curr = board.GetTile(i, j);

                    if (cornerTile(i, j))
                    {
                        curr *= 100;
                    }
                    else if (edgeTile(i, j)) {
                        curr *= 10;
                    }
                    totalEvaluation += curr;
                }
            }

            return totalEvaluation;

        }


    }
}
