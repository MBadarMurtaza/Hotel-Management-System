#include <iostream>
#include <string>
using namespace std;
class floor_room
{
public:
    int floor;
    string room_id;
    string room_type;
    string status;
    floor_room *left;
    floor_room *right;
    floor_room(int flr, string id = "", string type = "Floor", string stat = "Ready")
    {
        floor = flr;
        room_id = id;
        room_type = type;
        status = stat;
        left = NULL;
        right = NULL;
    }
};
class bookingRequest
{
public:
    string customerName;
    string roomType;
    int nights;
    bookingRequest *next;
    bookingRequest(const string name, string type, int no_night)
    {
        customerName = name;
        roomType = type;
        nights = no_night;
        next = NULL;
    }
};
class Galaxy_hotel
{
public:
    floor_room *root;
    Galaxy_hotel()
    {
        root = nullptr;
    }
    void add_floor_room(int num_floor, int num_room)
    {
        floor_room *lastFloor = nullptr;
        for (int floor = 1; floor <= num_floor; floor++)
        {
            floor_room *floor_node = new floor_room(floor);
            if (!root)
            {
                root = floor_node;
            }
            else
            {
                lastFloor->right = floor_node;
            }
            lastFloor = floor_node;
            floor_room *lastRoom = nullptr;
            for (int room = 1; room <= num_room; room++)
            {
                string id = to_string(floor) + "-" + to_string(room);
                string type;
                if (room % 3 == 0)
                {
                    type = "Suite";
                }
                else if (room % 2 == 0)
                {
                    type = "Double";
                }
                else
                {
                    type = "Single";
                }
                floor_room *room_node = new floor_room(floor, id, type, "Ready");
                if (!lastRoom)
                {
                    floor_node->left = room_node;
                }
                else
                {
                    lastRoom->right = room_node;
                }
                lastRoom = room_node;
            }
        }
    }
    void addBookingRequest()
    {
    }
    void display()
    {
        floor_room *tempFloor = root;
        while (tempFloor)
        {
            cout << "Floor " << tempFloor->floor << ":\n";
            floor_room *tempRoom = tempFloor->left;
            while (tempRoom)
            {
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
    }
};
int main()
{
    int no_floor, no_room;
    Galaxy_hotel gh;
    cout << "Enter the number of floors you want to add: ";
    cin >> no_floor;
    cout << "Enter the number of rooms you want to add: ";
    cin >> no_room;
    gh.add_floor_room(no_floor, no_room);
}
