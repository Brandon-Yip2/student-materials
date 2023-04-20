using Robocode;
using Robocode.Util;
using System;
using System.Data.SqlTypes;
using System.Runtime.CompilerServices;

namespace CAP4053.Student
{
    public class SampleStudentBot : TeamRobot
    {
        //variables
        bool teamGame = false;
        State bodyState;
        

        void initializeState() {
            this.bodyState = new State(this);
        }

         public class State {

            //Robot reference
            public SampleStudentBot bot;

            //Default state of the bot
            public string state = "Approach";

            //Variables relating to the bots state
            public int movingdirection = 1;

            public State(SampleStudentBot myBot) {
                this.bot = myBot;
            }

            public State next(State current, bool locked, double distance) {
                if (bot.Energy < 20)
                {
                    this.state = "Run";
                }
                else if (locked == true && distance > 600)
                {
                    this.state = "Approach";
                }
                else {
                    this.state = "Attack";
                }

          
                return this;
                
            
            }
        
        }
        public override void Run()
        {
            if (Time == 0) {
                initializeState();
            }

            if (Others > 1) {
                teamGame = true;
            }
          
            while (true) {

                TurnRadarRight(360);

                
            }

        }

        public override void OnScannedRobot(ScannedRobotEvent e)
        {

            this.bodyState = bodyState.next(bodyState, true, e.Distance);
    
            //Standard lock on a robot
            SetTurnRadarRight(2.0 * Utils.NormalRelativeAngleDegrees(Heading + e.Bearing - RadarHeading));
            SetTurnGunRight(Utils.NormalRelativeAngleDegrees(Heading + e.Bearing - GunHeading));

            //Approach the robot State
            if (!teamGame && bodyState.state == "Approach") {
                SetTurnRight(e.Bearing);
                SetAhead(100);
                //Optimize this later so we aren't running in a straight line
               
                //else
                //{
                    //Robot is close, start maintain
                  //  bodyState = "KeepDistance";
                //}

            }

            if (!teamGame && bodyState.state == "Attack") {
                //Get an alternating time based on the distance of the enemy robot
                //This changes based on the distance to the enemy robot. If they are closer, we need to dodge faster.
                int ticksToAlternate = 100;

                if (e.Distance < 500) {
                    ticksToAlternate = 30;
                }
                if (e.Distance < 300)
                {
                    ticksToAlternate = 15;
                }

                Console.WriteLine("Alternating:" + ticksToAlternate);

                if (Time % ticksToAlternate == 0) {
                    bodyState.movingdirection *= -1;
                }

                Console.WriteLine("Moving: " + bodyState.movingdirection);


               // if (e.Distance < 100)
             //   {
                    //back the robot up to maintain the distance
                 //   SetTurnRight(e.Bearing + 180);
                   // SetAhead(100);

//                }
  //              else {
                    //Move in an arc of 150 distance. This arc should be the *wiggle* to dodge the enemies bullets.
                    SetTurnRight(e.Bearing + 90);
                    SetAhead(150 * bodyState.movingdirection);
    //            }

            }

           


            double distance = e.Distance;
            if (distance > 400)
            { 
                Fire(0.3);
            }
            else if (distance > 300 && distance <= 400)
            {
                
                Fire(2);
            }
            else if (distance < 300) {
                Fire(4);
            }

            //End of Scanned robot even
        }


        public override void OnHitWall(HitWallEvent evnt)
        {
            bodyState.movingdirection *= -1;
            base.OnHitWall(evnt);
        }

    }
}

