#include<iostream>
#include<string>
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
class Galaxy_hotel{
public:
    floor_room* root;
    Galaxy_hotel()
    {
        root=nullptr;
    }
    void add_floor_room(int num_floor, int num_room)
    {
        floor_room* lastFloor=nullptr;
        for(int floor=1;floor<=num_floor;floor++)
        {
            floor_room* floor_node=new floor_room(floor);
            if (!root)
            {
                root = floor_node;
            }
            else
            {
                lastFloor->right = floor_node;
            }
            lastFloor=floor_node;
            floor_room* lastRoom=nullptr;
            for(int room=1;room<=num_room;room++)
            {
                string id=to_string(floor)+"-"+to_string(room);
                string type;
                if(room%3==0)
                {
                    type="Suite";
                }
                else if(room%2==0)
                {
                    type="Double";
                }
                else
                {
                    type="Single";
                }
                floor_room* room_node=new floor_room(floor,id,type,"Ready");
                if(!lastRoom)
                {
                     floor_node->left = room_node;
                }
                else
                {
                    lastRoom->right = room_node;
                }
                lastRoom=room_node;
            }
        }
    }
    void display()
};

