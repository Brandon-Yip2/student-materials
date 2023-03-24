using GameAI.GamePlaying.Core;
using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;

namespace GameAI.GamePlaying
{
    public class StudentAI : Behavior
    {



        public StudentAI() { }


        public int invertColor(int _color) {
            if (_color == 0) return 1;
            else if (_color == 1) return 0;
            else return -1;
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
                    move.rank = ExampleAI.MinimaxExample.EvaluateTest(newBoard);
                }
                else {
                    move.rank = Run(GetNextPlayer(_color, newBoard), newBoard, _lookAheadDepth - 1).rank;
                }


                //Best Move shouldn't always be larger. Black and White want either negatives or positives. Change tomorrow
                //Also change evalutateTest and make your own.
                if (bestMove == null || move.rank > bestMove.rank) {
                    bestMove = move;
                }

            
            }


            return bestMove;



        }

        public int Evaluate(Board board) {

            return 0;
        }


    }
}
