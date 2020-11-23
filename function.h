#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int lat_curve(int tas, int bank, int arc, int hpre, int latpre, int lonpre)
{
    int latpre2 = latpre/10;
    int lonpre2 = lonpre/10;
    int pi = 3.14;
    int rearth = 6371000;
    int h_center;
    int br;

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
    
    int r = abs(pow(tas,2));

    int latc = asin((sin(latpre2)*cos(r/rearth)) + cos(latpre2)*sin(r/rearth)*cos(h_center));
    int lat = asin((sin(latc)*cos(r/rearth)) + (cos(latc)*sin(r/rearth)*cos(br)));
    return lat;
    
}

int lon_curve(int tas, int bank, int arc, int hpre, int latpre, int lonpre)
{
    int latpre2 = latpre/10;
    int lonpre2 = lonpre/10;
    int pi = 3.14;
    int rearth = 6371000;
    int h_center;
    int br;

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
    
    int r = abs(pow(tas,2));

    int latc = asin((sin(latpre2)*cos(r/rearth)) + cos(latpre2)*sin(r/rearth)*cos(h_center));
    int lat = asin((sin(latc)*cos(r/rearth)) + (cos(latc)*sin(r/rearth)*cos(br)));
    int lonc = lonpre2 + atan2((sin(h_center)*sin(r/rearth)*cos(latpre2)),(cos(r/rearth)+sin(latpre2)*sin(latc)));
    int lon = (lonc + atan2((sin(h_center)*sin(r/rearth)*cos(latc)),cos(r/rearth)+sin(latc)*sin(lat*(pi/180))));

}
