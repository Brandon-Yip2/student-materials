using System.Collections.Generic;
using AI.SteeringBehaviors.Core;

namespace AI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }
        public float FlockRadius { get; set; }

        #region TODO
        public virtual void Update(float deltaTime)
        {
            // Update goes here
            
            //First calculate the AverageForward and Average Position



        }
        #endregion

        private Vector3 calcAverageForward() {

            return 0;
        }


        private Vector3 CalcAlignmentAccel() {
        
        }

        private Vector3 CalcCohesionAccel() { 
        
        }

        private Vector3 CalcSeparationAccel() { 
        
        }




    }
}
