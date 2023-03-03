using System.Collections.Generic;
using System.Reflection;
using AI.SteeringBehaviors.Core;
using System;

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
            calcAverageForward();
            calcAveragePosition();

            //For each boid, update the separation, alignment, and cohesion
            foreach (MovingObject m in Boids) {

                Vector3 accel = CalcAlignmentAccel(m);
                accel += CalcCohesionAccel(m);
                accel += CalcSeparationAccel(m);
                float accelMultiplier = m.MaxSpeed;
                accel *= accelMultiplier * deltaTime;
                m.Velocity += accel;


                
                //Calculate Velocities maginitude
                float velocityMag = (float) Math.Sqrt(m.Velocity.X * m.Velocity.X + m.Velocity.Y * m.Velocity.Y + m.Velocity.Z * m.Velocity.Z);

                if (velocityMag > m.MaxSpeed) {

                    m.Velocity.Normalize();
                    m.Velocity *= m.MaxSpeed;
                }
                m.Update(deltaTime);

            }
            



        }
        #endregion

        private void calcAverageForward() {

            float avgX = 0, avgY = 0, avgZ = 0;

            foreach (MovingObject b in Boids)
            {
                avgX += b.Velocity.X;
                avgY += b.Velocity.Y;
                avgZ += b.Velocity.Z;
            }
            avgX /= Boids.Count;
            avgY /= Boids.Count;
            avgZ /= Boids.Count;

            Vector3 direction = new Vector3(avgX, avgY, avgZ);

            AverageForward = direction;


        }

        private void calcAveragePosition()
        {

            float avgX=0, avgY=0, avgZ=0;

            foreach (MovingObject b in Boids) {
                avgX += b.Position.X;
                avgY += b.Position.Y; 
                avgZ += b.Position.Z; 
            }
            avgX /= Boids.Count;
            avgY /= Boids.Count;
            avgZ /= Boids.Count;

            Vector3 position = new Vector3(avgX, avgY, avgZ);

            AveragePosition = position;

        }


        private Vector3 CalcAlignmentAccel(MovingObject boid) {
            Vector3 v = AverageForward / boid.MaxSpeed;
            float magnitude = (float)Math.Sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
            if (magnitude > 1) {
                v.Normalize();
            }
            return v;
        }

        private Vector3 CalcCohesionAccel(MovingObject boid) {
            Vector3 sum = new Vector3(0, 0, 0);

            foreach (MovingObject otherB in Boids) {
                Vector3 vector = boid.Position - otherB.Position;
                float distance = (float)Math.Sqrt(vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z);
                float safeDistance = boid.SafeRadius + otherB.SafeRadius;

                if (distance < safeDistance) {
                    vector.Normalize();
                    vector *= (safeDistance - distance) / safeDistance;
                    sum += vector;
                }
            }

            if (sum.Length > 1.0f) {
                sum.Normalize();
            }

            return sum * SeparationStrength;
        }

        private Vector3 CalcSeparationAccel(MovingObject boid) {

            Vector3 v = AveragePosition - boid.Position;
            float distance = (float)Math.Sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
            v.Normalize();

            if (distance < FlockRadius) { 
                v *= distance / FlockRadius;
            }

            return v * CohesionStrength;


        }




    }
}
