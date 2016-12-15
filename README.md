# PortalGame
Created a small portal game from scratch, inspired by the Portal game series, using c++ and openGL libraries in xCode. This project was created from scratch and not a game engine in order to demonstrate my working knowledge in the fundamentals of game design.

Video Link: https://youtu.be/6JMTf3lB__M




 Objective of Program:
 
 - Requirements for 3D world:
 + Construct a boundary for your world within the projection's clipping planes.
 + The observer should not be allowed to move outside of the world's boundaries.
 + The world should contain at least three different obstacles that the observer can navigate around. The obstacles can be any 3D object of your choice.
 + The obstacles must be placed within the boundaries of the world and at different positions in the world.
 + At least one obstacle is specified with a bounding box that constrains the navigator from moving through the obstacle.
 The boundaries of the box will need to be checked each time the viewpoint position is modified.
 + Smooth, filled and colored 3D polygons must be used. Surface normals for each polygon must be defined or predefined by the object definition (glut/glu objects).
 + A least one positional light must be used (ambient-diffuse/specular) that moves with the navigator. Other lights may be used for special effects within the world.
 + Texuring
 
 
 - Requirements for Navigation:
 + You must use the gluLookAt command to move the navigator through your world.
 + You should provide a key control to return the navigator to a default position and line of sight.
 
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 Controls:
 
 + To quit the program: Hit q or "esc"
 + To move forward: up arrow key
 + To move backwards: down arrow key
 + To turn right: right arrow key
 + To turn left: left arrow key
 + To reset to starting position: spacebar
 
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 Bugs:
 
 + After returning from the 2nd room to the 1st, there is an awkward jump upon initial movement and rotation
 + Spaces between portal blocks sometimes also teleport you when they are not suppose to. (only collision with teleport blocks is ment to teleport you)
 + Do not back into portals, you will get stuck (we did not implement backwards logic for entering portals)
