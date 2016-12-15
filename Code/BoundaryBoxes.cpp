// Nov, 17 2015
// BoundaryBoxes.cpp
// Jacob London Avery Rapson
// This Class handles 95% of the boundary logic.


#include "BoundaryBoxes.h"



class BoundaryBoxes{
public:
    
    // default constructor, initializes move
    BoundaryBoxes(){
        move = true;
    }
    
    // checks position and dirrection of movement and determines if movement is acceptable
    bool check(float x, float z, float dx, float dz, int dir, int room){
        move = true;
        if (room == 1) {
            
            if (dir == 0 && !checkOuterBoundsRoom1Forwards(x, z, dx, dz))
                move = false;
            else if(dir == 1 && !checkOuterBoundsRoom1Backwords(x, z, dx, dz))
                move = false;
            
        }
        
        if(room == 2){
            if (dir == 0 && !checkOuterBoundsRoom2Forwards(x, z, dx, dz))
                move = false;
            else if(dir == 1 && !checkOuterBoundsRoom2Backwords(x, z, dx, dz))
                move = false;
        }
        return move;
    }
private:
    // stores whether movement is acceptable
    bool move;
    
    // checks forward movement boundaries of first room
    bool checkOuterBoundsRoom1Forwards(float x, float z, float dx, float dz){
        
        if (x>28) {
            if (dx > .0001) {
                return false;
            }
        }
        else if (z > 28) {
            if (dz > .0001) {
                return false;
            }
        }
        
        else if (x < -28) {
            if (dx < -.0001) {
                return false;
            }
        }
        
        else if (z < -28) {
            if (dz < -.0001) {
                return false;
            }
        }
        else return true;
        return true;
        
    }
    
    
    // checks backwards movement boundaries of first room
    
    bool checkOuterBoundsRoom1Backwords(float x, float z, float dx, float dz){
        
        if (x>28) {
            if (dx < -.0001) {
                return false;
            }
        }
        else if (z > 28) {
            if (dz < -.0001) {
                return false;
            }
        }
        
        else if (x < -28) {
            if (dx > .0001) {
                return false;
            }
        }
        
        else if (z < -28) {
            if (dz > .0001) {
                return false;
            }
        }
        else return true;
        return true;
    }
    
    
    // checks forward movement boundaries of second room
    
    bool checkOuterBoundsRoom2Forwards(float x, float z, float dx, float dz){
        
        if (x>28) {
            if (dx > .0001) {
                return false;
            }
        }
        else if (z > -42) {
            if (dz > .0001) {
                return false;
            }
        }
        
        else if (x < -28) {
            if (dx < -.0001) {
                return false;
            }
        }
        
        else if (z < -68) {
            if (dz < -.0001) {
                return false;
            }
        }
        else return true;
        return true;
        
    }
    
    
    // checks backward movement boundaries of second room
    
    bool checkOuterBoundsRoom2Backwords(float x, float z, float dx, float dz){
        
        if (x>28) {
            if (dx < -.0001) {
                return false;
            }
        }
        else if (z > -42) {
            if (dz < -.0001) {
                return false;
            }
        }
        
        else if (x < -28) {
            if (dx > .0001) {
                return false;
            }
        }
        
        else if (z < -68) {
            if (dz > .0001) {
                return false;
            }
        }
        else return true;
        return true;
    }
    
    
};