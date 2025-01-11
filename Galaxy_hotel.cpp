#include<iostream>
using namespace std;
class floor_room{
public:
    int floor;
    string room_id;
    string room_type;
    string status;
    floor_room* left;
    floor_room* right;
    floor_room(int flr, string id="", string type="Floor", string stat="Ready")
    {
        floor=flr;
        room_id=id;
        room_type=type;
        status=stat;
        left=NULL;
        right=NULL;
    }
};
