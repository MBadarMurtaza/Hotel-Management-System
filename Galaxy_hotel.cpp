#include <iostream>
#include <string>
using namespace std;
int bookingRequestCount = 0;
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
class bookingQueue
{
public:
    bookingRequest *front;
    bookingRequest *rear;
    bookingQueue()
    {
        front = nullptr;
        rear = nullptr;
    }
    void requestEnqueue(const string name, string type, int nights, floor_room *root)
    {
        cout << "Is this request is a high priority? (Y/N): ";
        char ch;
        cin >> ch;
        if (ch == 'Y' || ch == 'y')
        {
            allocateRoom(name, type, nights, root);
        }
        else
        {
            bookingRequest *newRequest = new bookingRequest(name, type, nights);
            if (rear == nullptr)
            {
                front = newRequest;
                rear = newRequest;
            }
            else
            {
                rear->next = newRequest;
                rear = newRequest;
            }
        }
        bookingRequestCount++;
    }
    void allocateRoom(const string name, string type, int nights, floor_room *root)
    {
        floor_room *tempFloor = root;
        while (tempFloor)
        {
            floor_room *tempRoom = tempFloor->left;
            while (tempRoom)
            {
                if (tempRoom->room_type == type && tempRoom->status == "Ready")
                {
                    tempRoom->status = "Occupied";
                    cout << "Room " << tempRoom->room_id << " allocated to " << name << " for " << nights << " nights.\n";
                    return;
                }
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
        cout << "No available rooms of type " << type << ".\n";
    }
    bookingRequest *dequeueRequest(floor_room *root)
    {
        if (front == nullptr)
        {
            cout << endl
                 << "Their is not any request in the queue for processing!" << endl;
            return nullptr;
        }

        bookingRequest *temp = front;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        return temp;
    }
    bool isEmpty()
    {
        if (front == nullptr)
        {
            return true;
        }
        return false;
    }
};
class Galaxy_hotel
{
public:
    floor_room *root;
    bookingQueue bq;
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
        string name, type;
        int nights;
        cout << "Enter the customer name: ";
        cin >> name;
        cout << "Enter the room type (Single(S), Double(D), Suite(SU)): ";
        cin >> type;
        do
        {
            if (type == "S")
            {
                type = "Single";
                break;
            }
            else if (type == "D")
            {
                type = "Double";
                break;
            }
            else if (type == "SU")
            {
                type = "Suite";
                break;
            }
            else
            {
                cout << "Invalid room type. Please select (Single(S), Double(D), Suite(SU)): ";
                cin >> type;
            }
        } while (true);
        cout << "How many nights do you want to stay: ";
        cin >> nights;
        bq.requestEnqueue(name, type, nights, root);
        if (bookingRequestCount == 10)
        {
            cout << "\n10 booking requests reached! Automatically processing all requests.\n";
            processBookingRequest(root);
            bookingRequestCount = 0;
        }
    }
    void processBookingRequest(floor_room *root)
    {
        while (!bq.isEmpty())
        {
            bookingRequest *firstRequest = bq.dequeueRequest(root);
            floor_room *room = findAvailableRoom(firstRequest->roomType);
            if (room)
            {
                room->status = "Occupied";
                cout << "Room " << room->room_id << " allocated to " << firstRequest->customerName << " for " << firstRequest->nights << " nights.\n";
            }
            else
            {
                cout << "No available rooms of type " << firstRequest->roomType << ".\n";
            }
            delete firstRequest;
        }
    }
    floor_room *findAvailableRoom(string type)
    {
        floor_room *tempFloor = root;
        while (tempFloor)
        {
            floor_room *tempRoom = tempFloor->left;
            while (tempRoom)
            {
                if (tempRoom->room_type == type && tempRoom->status == "Ready")
                {
                    return tempRoom;
                }
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
        return nullptr;
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
