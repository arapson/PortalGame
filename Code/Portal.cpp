// Nov, 17 2015
//  Portal.cpp
// Jacob London Avery Rapson
// This Class handles 95% of the portal logic. It needs to be initialized in main, and requires 10 portals to be passs in.
//

#include "Portal.h"
using namespace std;
class Portal{
    
private:
    /** Storage of all portals**/
    array<float,7> Portal1;
    array<float,7> Portal2;
    array<float,7> Portal3;
    array<float,7> Portal4;
    array<float,7> Portal5;
    array<float,7> Portal6;
    array<float,7> Portal7;
    array<float,7> Portal8;
    array<float,7> Portal9;
    array<float,7> Portal10;
    array<float,7> Portal11;
    array<float,7> Portal12;
    
    int position; //current portal marker
    
    /** Last Portal markers (to prevent falling back into the portal) */
    bool portal1;
    bool portal2;
    bool portal3;
    bool portal4;
    bool portal5;
    bool portal6;
    bool portal7;
    bool portal8;
    bool portal9;
    bool portal10;
    bool portal11;
    
    
    
public:
    
    
    /*Constructor -Creates Portal object
     *Pre: Requires 10 portals (array<float,7>)
     *Post: All portal information is saved in private globals, all variables initialized.
     */
    Portal(array<float,7> p1, array<float,7> p2, array<float,7> p3, array<float,7> p4,
           array<float,7> p5, array<float,7> p6, array<float,7> p7, array<float,7> p8, array<float,7> p9, array<float,7> p10){
        Portal1 = p1; Portal2 = p2; Portal3 = p3; Portal4 = p4; Portal5 = p5, Portal6 = p6; Portal7 = p7;
        Portal8 = p8; Portal9 = p9; Portal10= p10;
        for(int k = 0; k < 4; k++){
            std::cout<< Portal1[k]+1 << ",";
        }
        std::cout<<"\n";
        for(int k = 0; k < 4; k++){
            std::cout<< Portal2[k]+1 << ",";
        }
        portal1 =portal2 =portal3 =portal4=portal5 =portal6 =portal7 =portal8 =portal9 =portal10 =portal11= false;
        position = 0;
    }
    
    
    /*checkPortal- Determins if camera is in portal area.
     * Pre: X and Z position of camera passed in, portals are valid and in-scene
     * Post: Returns true if the camera is in a portal area, Position is changed to current portal, portal markers are set to prevent falling back into poratl*/
    bool checkPortal(float x, float z){
        bool trans =false;
        
        
        /**Each of these control structures checks a portal location*/
        
        if (z >= Portal2[1]-6 && z<= Portal2[1]+6) {
            if (x >= Portal2[0]-6 && x<= Portal2[0]+6) {
                position =2;
                if (!portal2) {
                    trans = true;
                    makeFalse();
                    portal8 = true;
                }
                
                
            }
        }
        if(z >= Portal3[1]-6 && z<= Portal3[1]+6) {
            if (x >= Portal3[0]-6 && x<= Portal3[0]+6) {
                position = 3;
                if (!portal3) {
                    trans = true;
                    makeFalse();
                    portal6 = true;
                }
            }
        }
        if (z >= Portal4[1]-6 && z<= Portal4[1]+6) {
            if (x >= Portal4[0]-6 && x<= Portal4[0]+6) {
                position = 4;
                if (!portal4) {
                    trans = true;
                    makeFalse();
                    portal4 = true;
                }
            }
        }
        
        if (z >= Portal7[1]-6 && z<= Portal7[1]+6) {
            if (x >= Portal7[0]-6 && x<= Portal7[0]+6) {
                position = 7;
                if (!portal7) {
                    trans = true;
                    makeFalse();
                    portal3 = true;
                }
            }
        }
        if (z >= Portal8[1]-6 && z<= Portal8[1]+6) {
            if (x >= Portal8[0]-6 && x<= Portal8[0]+6) {
                position = 8;
                if (!portal8) {
                    trans = true;
                    makeFalse();
                    portal2 = true;
                }
            }
        }
        if (z >= Portal6[1]-6 && z<= Portal6[1]+6) {
            if (x >= Portal6[0]-6 && x<= Portal6[0]+6) {
                position = 6;
                if (!portal6) {
                    trans = true;
                    makeFalse();
                    portal4 = true;
                }
            }
        }
        if (z >= Portal5[1]-6 && z<= Portal5[1]+6) {
            if (x >= Portal5[0]-6 && x<= Portal5[0]+6) {
                position = 5;
                if (!portal5) {
                    trans = true;
                    makeFalse();
                    portal7 = true;
                }
            }
        }
        if (z >= Portal1[1]-6 && z<= Portal1[1]+6) {
            if (x >= Portal1[0]-6 && x<= Portal1[0]+6) {
                position = 1;
                if (!portal1) {
                    trans = true;
                    makeFalse();
                    portal11= true;
                }
            }
        }
        
        if (z >= Portal9[1] -20 && z<= Portal9[1]) {
            if (x >= Portal9[0] && x<= Portal9[0]+6) {
                position = 9;
                trans = true;
                makeFalse();
                
            }
        }
        
        
        if (z >= Portal10[1] -20 && z<= Portal10[1]) {
            if (x >= Portal10[0] && x<= Portal10[0]+6) {
                position = 10;
                
                trans = true;
                makeFalse();
                
            }
        }
        
        
        return trans;
    }
    
    /* Changes all the portal markers to false, allowing the preveious portals to be set again
     * Pre: none
     * Post: are made false
     */
    void makeFalse(){
        portal1 =portal2 =portal3 =portal4=portal5 =portal6 =portal7 =portal8 =portal9 =portal10 =portal11= false;
        portal7 = false;
    }
    
    
    
    
    /* Switches the position of the camera with the target posistion of the current portal
     */
    array<float, 5> switchPos(int num){
        array<float, 5> r ={0,0,0,0,0};
        
        if (num == 3){
            r[0] = Portal3[2];
            r[1] = Portal3[3];
            r[2] = Portal3[4];
            r[3] = Portal3[5];
            r[4] = Portal3[6];
        }
        else if (num == 4){
            r[0] = Portal4[2];
            r[1] = Portal4[3];
            r[2] = Portal4[4];
            r[3] = Portal4[5];
            r[4] = Portal4[6];
        }
        else if (num == 6){
            r[0] = Portal6[2];
            r[1] = Portal6[3];
            r[2] = Portal6[4];
            r[3] = Portal6[5];
            r[4] = Portal6[6];
        }
        else if (num == 2){
            r[0] = Portal2[2];
            r[1] = Portal2[3];
            r[2] = Portal2[4];
            r[3] = Portal2[5];
            r[4] = Portal2[6];
        }
        else if (num == 7){
            r[0] = Portal7[2];
            r[1] = Portal7[3];
            r[2] = Portal7[4];
            r[3] = Portal7[5];
            r[4] = Portal7[6];
        }
        else if (num == 5){
            r[0] = Portal5[2];
            r[1] = Portal5[3];
            r[2] = Portal5[4];
            r[3] = Portal5[5];
            r[4] = Portal5[6];
        }
        
        else if (num == 8){
            r[0] = Portal8[2];
            r[1] = Portal8[3];
            r[2] = Portal8[4];
            r[3] = Portal8[5];
            r[4] = Portal8[6];
        }
        
        else if (num == 1){
            r[0] = Portal1[2];
            r[1] = Portal1[3];
            r[2] = Portal1[4];
            r[3] = Portal1[5];
            r[4] = Portal1[6];
        }
        else if (num == 9){
            r[0] = Portal9[2];
            r[1] = Portal9[3];
            r[2] = Portal9[4];
            r[3] = Portal9[5];
            r[4] = Portal9[6];
        }
        else if (num == 10){
            r[0] = Portal10[2];
            r[1] = Portal10[3];
            r[2] = Portal10[4];
            r[3] = Portal10[5];
            r[4] = Portal10[6];
        }
        
        
        
        return r;
    }
    
    
    /*Returns the position data memeber. The position data memeber is the current portal.*/
    
    int getPosition(){
        return position;
    }
    
    
};


