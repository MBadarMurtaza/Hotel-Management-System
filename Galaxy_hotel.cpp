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
class bookingHistoryStack
{
public:
    class bookingNode
    {
    public:
        bookingNode *next;
        string customerName;
        string roomType;
        string roomId;
        int nights;
        bookingNode(const string name, string type, string id, int no_night)
        {
            customerName = name;
            roomType = type;
            roomId = id;
            nights = no_night;
            next = nullptr;
        }
    };
    bookingNode *top = nullptr;
    bookingHistoryStack()
    {
        top = nullptr;
    }
    void push(const string name, const string type, const string id, int no_night)
    {
        bookingNode *newBooking = new bookingNode(name, type, id, no_night);
        newBooking->next = top;
        top = newBooking;
    }
    string pop()
    {
        if (top == nullptr)
        {
            cout << "There is no booking history in the stack!" << endl;
            return "0";
        }
        else
        {
            bookingNode *temp = top;
            string roomId = temp->roomId;
            top = top->next;
            delete temp;
            cout << "Booking for room " << roomId << " has been canceled, and the room is now available.\n";
            return roomId;
        }
    }
    void display()
    {
        bookingNode *current = top;
        if (current == nullptr)
        {
            cout << "Their is no booking history to show!" << endl;
            return;
        }
        else
        {
            cout << "Booking History:" << endl;
            while (current != nullptr)
            {
                cout << "Name: " << current->customerName << endl;
                cout << "Room Type: " << current->roomType << endl;
                cout << "Room Id: " << current->roomId << endl;
                cout << "Total Day Stay: " << current->nights << endl;
                current = current->next;
            }
        }
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
    void requestEnqueue(const string name, string type, int nights, floor_room *root, bookingHistoryStack &bh)
    {
        cout << "Is this request is a high priority? (Y/N): ";
        char ch;
        cin >> ch;
        if (ch == 'Y' || ch == 'y')
        {
            allocateRoom(name, type, nights, root, bh);
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
    void allocateRoom(const string name, const string type, int nights, floor_room *root, bookingHistoryStack &bh)
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
                    cout << "Room " << tempRoom->room_id << " allocated to " << name << " for " << nights << " nights." << endl;
                    bh.push(name, type, tempRoom->room_id, nights);
                    return;
                }
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
        cout << "No available rooms of type " << type << "." << endl;
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
    bookingHistoryStack bh;
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
        bq.requestEnqueue(name, type, nights, root, bh);
        if (bookingRequestCount == 10)
        {
            cout << endl
                 << "10 booking requests reached! Automatically processing all requests." << endl;
            processBookingRequest();
            bookingRequestCount = 0;
        }
    }
    void processBookingRequest()
    {
        int count = 0;
        while (!bq.isEmpty())
        {
            bookingRequest *firstRequest = bq.dequeueRequest(root);
            floor_room *room = findAvailableRoom(firstRequest->roomType);
            if (room)
            {
                count++;
                room->status = "Occupied";
                cout << "Room " << room->room_id << " allocated to " << firstRequest->customerName << " for " << firstRequest->nights << " nights." << endl;
                bh.push(firstRequest->customerName, firstRequest->roomType, room->room_id, firstRequest->nights);
            }
            else
            {
                cout << "No available rooms of type " << firstRequest->roomType << "." << endl;
            }
            delete firstRequest;
        }
        if (count == 0)
        {
            cout << endl
                 << "Their is no any pending request for processing." << endl;
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
    void bookingHistoryDisplay()
    {
        bh.display();
    }
    void displayAllRoomStatus()
    {
        floor_room *tempFloor = root;
        while (tempFloor)
        {
            cout << "Floor " << tempFloor->floor << ":" << endl;
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
    void availableRooms()
    {
        floor_room *tempFloor = root;
        while (tempFloor)
        {
            cout << "Available Rooms at Floor" << tempFloor->floor << ": " << endl;
            floor_room *tempRoom = tempFloor->left;
            while (tempRoom)
            {
                if (tempRoom->status == "Ready")
                {
                    cout << "  Room ID: " << tempRoom->room_id
                         << ", Type: " << tempRoom->room_type
                         << ", Status: " << tempRoom->status << endl;
                }
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
    }
    void roomStatusById()
    {
        string id;
        cout << "Enter the id of room: ";
        cin >> id;
        floor_room *tempFloor = root;
        int count = 0;
        while (tempFloor)
        {
            floor_room *tempRoom = tempFloor->left;
            while (tempRoom)
            {
                if (tempRoom->room_id == id)
                {
                    count++;
                    cout << "  Room ID: " << tempRoom->room_id
                         << ", Type: " << tempRoom->room_type
                         << ", Status: " << tempRoom->status << endl;
                }
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
        if (count == 0)
        {
            cout << "Their is no any room with this (" << id << ") id." << endl;
        }
    }
    void occupiedRoom()
    {
        int count = 0;
        floor_room *tempFloor = root;
        while (tempFloor)
        {
            floor_room *tempRoom = tempFloor->left;
            while (tempRoom)
            {
                if (tempRoom->status == "Occupied")
                {
                    count++;
                    cout << "  Room ID: " << tempRoom->room_id
                         << ", Type: " << tempRoom->room_type
                         << ", Status: " << tempRoom->status << endl;
                }
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
        if (count > 0)
        {
            cout << "Total Room Occupied are :" << count << endl;
        }
        else
        {
            cout << "Their is no any room which is occupied!" << endl;
        }
    }
    void updateRoomStatus()
    {
        string id = bh.pop();
        floor_room *tempFloor = root;
        while (tempFloor)
        {
            floor_room *tempRoom = tempFloor->left;
            while (tempRoom)
            {
                if (tempRoom->room_id == id)
                {
                    tempRoom->status = "Ready";
                    return;
                }
                tempRoom = tempRoom->right;
            }
            tempFloor = tempFloor->right;
        }
    }
};
void menue()
{
    cout << endl
         << "=========== Galaxy Hotel Management System ===========" << endl;
    cout << "||                                                   ||" <<endl;    
    cout << "||      1. Add Booking Request                       ||" << endl;
    cout << "||      2. Process All Booking Requests              ||" << endl;
    cout << "||      3. View Booking History                      ||" << endl;
    cout << "||      4. Cancel most recent Booking from Histor    ||" << endl;
    cout << "||      5. Display All Hotel Room Status             ||" << endl;
    cout << "||      6. Available Rooms                           ||" << endl;
    cout << "||      7. Room Status by Room ID                    ||" << endl;
    cout << "||      8. Occupied Rooms                            ||" << endl;
    cout << "||      0. Exit                                      ||" << endl;
    cout << "||                                                   ||" <<endl;
    cout << "======================================================" << endl;
    cout << "Enter your choice: ";
}
int main()
{
    int no_floor, no_room;
    Galaxy_hotel gh;
    cout << "Enter the number of floors you want to add: ";
    cin >> no_floor;
    cout << "Enter the number of rooms you want to add: ";
    cin >> no_room;
    gh.add_floor_room(no_floor, no_room);
    int choice;
    do
    {
        menue();
        cin >> choice;
        switch (choice)
        {
        case 1:
            gh.addBookingRequest();
            break;
        case 2:
            gh.processBookingRequest();
            break;
        case 3:
            gh.bookingHistoryDisplay();
            break;
        case 4:
            gh.updateRoomStatus();
            break;
        case 5:
            gh.displayAllRoomStatus();
            break;
        case 6:
            gh.availableRooms();
            break;
        case 7:
            gh.roomStatusById();
            break;
        case 8:
            gh.occupiedRoom();
            break;
        case 0:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}
