#ifndef SUPPLEMENT_H
#define SUPPLEMENT_H

#include "EvacRunner.h"


class iRoad{

    public:
    Road r;
    iRoad(){;}

    explicit iRoad(Road R): r(R){;}
    
    bool operator<(const iRoad& ir){
        return (r.peoplePerHour < ir.r.peoplePerHour);
    }
    bool operator>(const iRoad& ir){
        return (r.peoplePerHour > ir.r.peoplePerHour);
    }
    bool operator==(const iRoad& ir){
        return (r.peoplePerHour == ir.r.peoplePerHour);
    }
};

#endif