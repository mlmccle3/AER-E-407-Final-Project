#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int lat_curve(int tas, int bank, int arc, int hpre, int latpre, int lonpre)
{
  //conversions from inputs and establishment of constants
    int pi = 3.14;
    int latpre2 = (latpre/10)*(pi/180);
    int lonpre2 = (lonpre/10)*(pi/180);
    int rearth = 6371000;
    int h_center;
    int br;
    bank = bank*(pi/180);
    arc = arc*(pi/180);

    //for negative or positivebank angles, values for initial heading toward center of circles, correction 
    //factor for later calculations, and bearing
    if (bank < 0){
        h_center = (hpre - 90)*(pi / 180);
        int b = (hpre*(pi/180))+(pi/2);
        br = b - arc;
    }
    else if (bank > 0){
        h_center = (hpre + 90)*(pi/180);
        int a = (hpre*(pi/180))-(pi/2);
        br = a + arc;
    }
    //turn radius
    int r = abs(pow(tas,2));
    
    //latitude of the center and final latitude of segment
    int latc = (asin((sin(latpre2)*cos(r/rearth)) + cos(latpre2)*sin(r/rearth)*cos(h_center)));
    int lat = (asin((sin(latc)*cos(r/rearth)) + (cos(latc)*sin(r/rearth)*cos(br))))*(10)*(180/pi);
    return lat;
    
}

int lon_curve(int tas, int bank, int arc, int hpre, int latpre, int lonpre) 

{
    int pi = 3.14;
    int latpre2 = (latpre/10)*(pi/180);
    int lonpre2 = (lonpre/10)*(pi/180);
    bank = bank*(pi/180);
    arc = arc*(pi/180);
    
    int rearth = 6371000;
    int h_center;
    int br;

    if (bank < 0){
        h_center = (hpre - 90)*(pi / 180); //radians = degrees*(pi/180)
        int b = (hpre*(pi/180))+(pi/2); //radians
        br = b - arc; //radians = radians-radians
    }
    else if (bank > 0){
        h_center = (hpre + 90)*(pi/180); //radians = degrees*(pi/180)
        int a = (hpre*(pi/180))-(pi/2); //radians = degrees*(pi/180)
        br = a + arc; //radians = radians+radians
    }
    
    int r = abs(pow(tas,2));

    //latitude and longitude of the center and final frame  of segment
    int latc = asin((sin(latpre2)*cos(r/rearth)) + cos(latpre2)*sin(r/rearth)*cos(h_center));
    int lat = asin((sin(latc)*cos(r/rearth)) + (cos(latc)*sin(r/rearth)*cos(br)));
    int lonc = lonpre2 + atan2((sin(h_center)*sin(r/rearth)*cos(latpre2)),(cos(r/rearth)+sin(latpre2)*sin(latc)));
    int lon = (lonc + atan2((sin(h_center)*sin(r/rearth)*cos(latc)),cos(r/rearth)+sin(latc)*sin(lat*(pi/180))))*10*(180/pi);

    return lon;

}

int straight_h(int cur_b_lat,int cur_b_lon,int cur_e_lat,int cur_e_lon,int latpre,int lonpre) {

  int pi = 3.14;
  cur_b_lat = (cur_b_lat/10)*(pi/180);
  cur_b_lon = (cur_b_lon*10)*(pi/180);
  cur_e_lat = (cur_e_lat*10)*(pi/180);
  cur_e_lon = (cur_e_lon*10)*(pi/180);
  

  //Calculates the heading at the end of the segment
  int heading = atan2((sin(cur_e_lon-cur_b_lon)*cos(cur_e_lat)),((cos(cur_b_lat)*sin(cur_e_lat))-(sin(cur_b_lat)*cos(cur_e_lat)*cos(cur_e_lon)*cos(cur_e_lon-cur_b_lon))))*(180/pi);
    return heading;

}

bool h_spec(int cur_b_h,int las_e_h) {

  bool h_flag;

  if(cur_b_h == las_e_h) {

    return true;

  }

  else {

    return false;

  }

}

bool lat_spec(int cur_b_lat,int las_e_lat) {

  if (cur_b_lat == las_e_lat){

    return true;

  }

  else {

    return false;

  }

}

bool lon_spec(int cur_b_lon,int las_e_lon) {

  if (cur_b_lon == las_e_lon){

    return true;

  }

  else {

    return false;

  }

}

int eh_curve(int tas, int bank, int arc, int hpre, int latpre, int lonpre){

   int pi = 3.14;
    int latpre2 = (latpre/10)*(pi/180);
    int lonpre2 = (lonpre/10)*(pi/180);
    int rearth = 6371000;
    int h_center;
    int br;
    int h;
    bank = bank*(pi/180);
    arc = arc*(pi/180);

    //for negative or positivebank angles, values for initial heading toward center of circles, correction 
    //factor for later calculations, and bearing
    if (bank < 0){
        h_center = (hpre - 90)*(pi / 180);
        int b = (hpre*(pi/180))+(pi/2);
        br = b - arc;
        h = (br*(180/pi))-90;
    }
    else if (bank > 0){
        h_center = (hpre + 90)*(pi/180);
        int a = (hpre*(pi/180))-(pi/2);
        br = a + arc;
        h = (br*(180/pi))+90;
    }
    return h;

}
