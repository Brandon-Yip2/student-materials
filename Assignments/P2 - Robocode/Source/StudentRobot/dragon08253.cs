using Robocode;
using Robocode.Util;
using System;
using System.Data.SqlTypes;
using System.Linq;
using System.Runtime.CompilerServices;

namespace CAP4053.Student
{
    public class dragon08253 : TeamRobot
    {
        //variables
        bool teamGame = false;
        State bodyState;
        

        void initializeState() {
            this.bodyState = new State(this);
        }

         public class State {

            //Robot reference
            public dragon08253 bot;

            //Default state of the bot
            public string state = "Approach";

            //Variables relating to the bots state
            public int movingdirection = 1;

            public State(dragon08253 myBot) {
                this.bot = myBot;
            }

            public State next(State current, bool locked, double distance) {
                if (bot.Energy < 20)
                {
                    this.state = "Survive";
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
                SetAllColors(System.Drawing.Color.Pink);

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

            if (IsTeammate(e.Name)) {
                return;
            }

            this.bodyState = bodyState.next(bodyState, true, e.Distance);
    
            //Standard lock on a robot
            SetTurnRadarRight(2.0 * Utils.NormalRelativeAngleDegrees(Heading + e.Bearing - RadarHeading));
            SetTurnGunRight(Utils.NormalRelativeAngleDegrees(Heading + e.Bearing - GunHeading));

            //Approach the robot State
            if (bodyState.state == "Approach") {
                Console.WriteLine("Approaching");

                SetTurnRight(e.Bearing);
                SetAhead(100);
                standardShoot(e);
            }

            //Standard Attack Formation (Dodges)
            if (bodyState.state == "Attack") {
                Console.WriteLine("Attacking");

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

                //Move in an arc of 150 distance. This arc should be the *wiggle* to dodge the enemies bullets.
                SetTurnRight(e.Bearing + 90);
                SetAhead(150 * bodyState.movingdirection);

                standardShoot(e);
            }
            
            //Attack formation if we have low energy
            if (bodyState.state == "Survive") {
                Console.WriteLine("Surviving");
                int ticksToAlternate = 80;

                if (e.Distance < 500)
                {
                    ticksToAlternate = 20;
                }
                if (e.Distance < 300)
                {
                    ticksToAlternate = 10;
                }

                Console.WriteLine("Alternating:" + ticksToAlternate);

                if (Time % ticksToAlternate == 0)
                {
                    bodyState.movingdirection *= -1;
                }

                //Move in an arc of 150 distance. This arc should be the *wiggle* to dodge the enemies bullets.
                SetTurnRight(e.Bearing + 90);
                SetAhead(250 * bodyState.movingdirection);

                cheapShoot(e);
            
            }
           

           

            //End of Scanned robot even
        }


        public override void OnHitWall(HitWallEvent evnt)
        {
            bodyState.movingdirection *= -1;
            base.OnHitWall(evnt);
        }

        public void standardShoot(ScannedRobotEvent e) {


            //Standard form of shooting (Expensive but rewarding)
            double distance = e.Distance;
            if (distance > 400)
            {
                Fire(0.3);
            }
            else if (distance > 300 && distance <= 400)
            {

                Fire(2);
            }
            else if (distance < 300)
            {
                Fire(4);
            }


        }

        public void cheapShoot(ScannedRobotEvent e)
        {


            //Standard form of shooting (Expensive but rewarding)
            double distance = e.Distance;
            if (distance > 400)
            {
                Fire(0.1);
            }
            else if (distance > 300 && distance <= 400)
            {

                Fire(1);
            }
            else if (distance < 300)
            {
                Fire(3);
            }


        }


    }
}

