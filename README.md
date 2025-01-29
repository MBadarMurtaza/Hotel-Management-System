# Galaxy Hotel Management System

The Galaxy Hotel Management System is a C++ application designed to manage hotel room bookings, track booking history, and display room statuses. Below is a detailed explanation of all functionalities and options available in the system.

## Functionalities

### 1. Add Booking Request

- **Description**: Allows the user to add a new booking request.
- **Input**: Customer name, room type (Single, Double, Suite), and number of nights.
- **Process**: The request can be marked as high priority, which will allocate a room immediately if available. Otherwise, the request is added to the booking queue.

```cpp
void Galaxy_hotel::addBookingRequest() {
    string name, type;
    int nights;
    cout << "Enter the customer name: ";
    cin >> name;
    cout << "Enter the room type (Single(S), Double(D), Suite(SU)): ";
    cin >> type;
    // ...existing code...
    cout << "How many nights do you want to stay: ";
    cin >> nights;
    bq.requestEnqueue(name, type, nights, root, bh);
    // ...existing code...
}
```

### 2. Process All Booking Requests

- **Description**: Processes all pending booking requests in the queue.
- **Output**: Allocates rooms to customers based on availability and updates the booking history.

```cpp
void Galaxy_hotel::processBookingRequest() {
    int count = 0;
    while (!bq.isEmpty()) {
        bookingRequest *firstRequest = bq.dequeueRequest(root);
        floor_room *room = findAvailableRoom(firstRequest->roomType);
        if (room) {
            count++;
            room->status = "Occupied";
            cout << "Room " << room->room_id << " allocated to " << firstRequest->customerName << " for " << firstRequest->nights << " nights." << endl;
            bh.push(firstRequest->customerName, firstRequest->roomType, room->room_id, firstRequest->nights);
        } else {
            cout << "No available rooms of type " << firstRequest->roomType << "." << endl;
        }
        delete firstRequest;
    }
    // ...existing code...
}
```

### 3. View Booking History

- **Description**: Displays the history of all bookings made.
- **Output**: Lists customer names, room types, room IDs, and the number of nights stayed.

```cpp
void bookingHistoryStack::display() {
    bookingNode *current = top;
    if (current == nullptr) {
        cout << "There is no booking history to show!" << endl;
        return;
    } else {
        cout << "Booking History:" << endl;
        while (current != nullptr) {
            cout << "Name: " << current->customerName << endl;
            cout << "Room Type: " << current->roomType << endl;
            cout << "Room Id: " << current->roomId << endl;
            cout << "Total Day Stay: " << current->nights << endl;
            current = current->next;
        }
    }
}
```

### 4. Cancel Most Recent Booking from History

- **Description**: Cancels the most recent booking from the booking history.
- **Output**: Updates the room status to "Ready" and removes the booking from the history.

```cpp
void Galaxy_hotel::updateRoomStatus() {
    string id = bh.pop();
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                tempRoom->status = "Ready";
                return;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### 5. Display All Hotel Room Status

- **Description**: Displays the status of all rooms in the hotel.
- **Output**: Lists room IDs, types, and statuses for each floor.

```cpp
void Galaxy_hotel::displayAllRoomStatus() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Floor " << tempFloor->floor << ":" << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            cout << "  Room ID: " << tempRoom->room_id
                 << ", Type: " << tempRoom->room_type
                 << ", Status: " << tempRoom->status << endl;
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### 6. Available Rooms

- **Description**: Displays all available (ready) rooms in the hotel.
- **Output**: Lists room IDs and types for each floor.

```cpp
void Galaxy_hotel::availableRooms() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Available Rooms at Floor" << tempFloor->floor << ": " << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Ready") {
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### 7. Room Status by Room ID

- **Description**: Displays the status of a specific room based on its ID.
- **Input**: Room ID.
- **Output**: Shows the room ID, type, and status.

```cpp
void Galaxy_hotel::roomStatusById() {
    string id;
    cout << "Enter the id of room: ";
    cin >> id;
    floor_room *tempFloor = root;
    int count = 0;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count == 0) {
        cout << "There is no room with this (" << id << ") id." << endl;
    }
}
```

### 8. Occupied Rooms

- **Description**: Displays all currently occupied rooms in the hotel.
- **Output**: Lists room IDs and types for each floor, along with the total count of occupied rooms.

```cpp
void Galaxy_hotel::occupiedRoom() {
    int count = 0;
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Occupied") {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count > 0) {
        cout << "Total Room Occupied are :" << count << endl;
    } else {
        cout << "There is no room which is occupied!" << endl;
    }
}
```

### 0. Exit

- **Description**: Exits the application.

## Usage

1. **Initialize the Hotel**:
   - Enter the number of floors and rooms to initialize the hotel structure.
2. **Main Menu**:

   - The main menu provides options to add booking requests, process requests, view booking history, cancel bookings, and display room statuses.

3. **Booking Requests**:

   - Add booking requests through the menu option and specify if they are high priority.
   - Process all pending requests to allocate rooms.

4. **Room Status**:

   - Check the status of all rooms, available rooms, or specific rooms by ID.
   - View occupied rooms and their details.

5. **Booking History**:
   - View the complete booking history.
   - Cancel the most recent booking to free up a room.

## Detailed Steps

### Adding Floors and Rooms

- **Step 1**: Initialize the hotel by specifying the number of floors and rooms.
- **Step 2**: Each floor will have a specified number of rooms, and each room will be assigned a unique ID and type (Single, Double, Suite).

```cpp
void Galaxy_hotel::add_floor_room(int num_floor, int num_room) {
    floor_room *lastFloor = nullptr;
    for (int floor = 1; floor <= num_floor; floor++) {
        floor_room *floor_node = new floor_room(floor);
        if (!root) {
            root = floor_node;
        } else {
            lastFloor->right = floor_node;
        }
        lastFloor = floor_node;
        floor_room *lastRoom = nullptr;
        for (int room = 1; room <= num_room; room++) {
            string id = to_string(floor) + "-" + to_string(room);
            string type;
            if (room % 3 == 0) {
                type = "Suite";
            } else if (room % 2 == 0) {
                type = "Double";
            } else {
                type = "Single";
            }
            floor_room *room_node = new floor_room(floor, id, type, "Ready");
            if (!lastRoom) {
                floor_node->left = room_node;
            } else {
                lastRoom->right = room_node;
            }
            lastRoom = room_node;
        }
    }
}
```

### Adding a Booking Request

- **Step 1**: Select the option to add a booking request from the main menu.
- **Step 2**: Enter the customer's name, room type, and number of nights.
- **Step 3**: Indicate if the request is high priority. High priority requests will be processed immediately if a room is available.

```cpp
void bookingQueue::requestEnqueue(const string name, string type, int nights, floor_room *root, bookingHistoryStack &bh) {
    cout << "Is this request a high priority? (Y/N): ";
    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') {
        allocateRoom(name, type, nights, root, bh);
    } else {
        bookingRequest *newRequest = new bookingRequest(name, type, nights);
        if (rear == nullptr) {
            front = newRequest;
            rear = newRequest;
        } else {
            rear->next = newRequest;
            rear = newRequest;
        }
    }
    bookingRequestCount++;
}
```

### Processing Booking Requests

- **Step 1**: Select the option to process all booking requests from the main menu.
- **Step 2**: The system will allocate rooms to customers based on availability and update the booking history.

```cpp
void Galaxy_hotel::processBookingRequest() {
    int count = 0;
    while (!bq.isEmpty()) {
        bookingRequest *firstRequest = bq.dequeueRequest(root);
        floor_room *room = findAvailableRoom(firstRequest->roomType);
        if (room) {
            count++;
            room->status = "Occupied";
            cout << "Room " << room->room_id << " allocated to " << firstRequest->customerName << " for " << firstRequest->nights << " nights." << endl;
            bh.push(firstRequest->customerName, firstRequest->roomType, room->room_id, firstRequest->nights);
        } else {
            cout << "No available rooms of type " << firstRequest->roomType << "." << endl;
        }
        delete firstRequest;
    }
    if (count == 0) {
        cout << "There is no pending request for processing." << endl;
    }
}
```

### Viewing Booking History

- **Step 1**: Select the option to view booking history from the main menu.
- **Step 2**: The system will display a list of all bookings, including customer names, room types, room IDs, and the number of nights stayed.

```cpp
void bookingHistoryStack::display() {
    bookingNode *current = top;
    if (current == nullptr) {
        cout << "There is no booking history to show!" << endl;
        return;
    } else {
        cout << "Booking History:" << endl;
        while (current != nullptr) {
            cout << "Name: " << current->customerName << endl;
            cout << "Room Type: " << current->roomType << endl;
            cout << "Room Id: " << current->roomId << endl;
            cout << "Total Day Stay: " << current->nights << endl;
            current = current->next;
        }
    }
}
```

### Canceling the Most Recent Booking

- **Step 1**: Select the option to cancel the most recent booking from the main menu.
- **Step 2**: The system will update the room status to "Ready" and remove the booking from the history.

```cpp
void Galaxy_hotel::updateRoomStatus() {
    string id = bh.pop();
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                tempRoom->status = "Ready";
                return;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Displaying Room Status

- **Step 1**: Select the option to display all hotel room statuses from the main menu.
- **Step 2**: The system will list room IDs, types, and statuses for each floor.

```cpp
void Galaxy_hotel::displayAllRoomStatus() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Floor " << tempFloor->floor << ":" << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            cout << "  Room ID: " << tempRoom->room_id
                 << ", Type: " << tempRoom->room_type
                 << ", Status: " << tempRoom->status << endl;
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Viewing Available Rooms

- **Step 1**: Select the option to view available rooms from the main menu.
- **Step 2**: The system will list all rooms that are currently "Ready" for each floor.

```cpp
void Galaxy_hotel::availableRooms() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Available Rooms at Floor" << tempFloor->floor << ": " << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Ready") {
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Checking Room Status by ID

- **Step 1**: Select the option to check room status by room ID from the main menu.
- **Step 2**: Enter the room ID to view its status, type, and other details.

```cpp
void Galaxy_hotel::roomStatusById() {
    string id;
    cout << "Enter the id of room: ";
    cin >> id;
    floor_room *tempFloor = root;
    int count = 0;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count == 0) {
        cout << "There is no room with this (" << id << ") id." << endl;
    }
}
```

### Viewing Occupied Rooms

- **Step 1**: Select the option to view occupied rooms from the main menu.
- **Step 2**: The system will list all rooms that are currently "Occupied" for each floor, along with the total count of occupied rooms.

```cpp
void Galaxy_hotel::occupiedRoom() {
    int count = 0;
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Occupied") {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count > 0) {
        cout << "Total Room Occupied are :" << count << endl;
    } else {
        cout << "There is no room which is occupied!" << endl;
    }
}
```

### 0. Exit

- **Description**: Exits the application.

## Usage

1. **Initialize the Hotel**:
   - Enter the number of floors and rooms to initialize the hotel structure.
2. **Main Menu**:

   - The main menu provides options to add booking requests, process requests, view booking history, cancel bookings, and display room statuses.

3. **Booking Requests**:

   - Add booking requests through the menu option and specify if they are high priority.
   - Process all pending requests to allocate rooms.

4. **Room Status**:

   - Check the status of all rooms, available rooms, or specific rooms by ID.
   - View occupied rooms and their details.

5. **Booking History**:
   - View the complete booking history.
   - Cancel the most recent booking to free up a room.

## Detailed Steps

### Adding Floors and Rooms

- **Step 1**: Initialize the hotel by specifying the number of floors and rooms.
- **Step 2**: Each floor will have a specified number of rooms, and each room will be assigned a unique ID and type (Single, Double, Suite).

```cpp
void Galaxy_hotel::add_floor_room(int num_floor, int num_room) {
    floor_room *lastFloor = nullptr;
    for (int floor = 1; floor <= num_floor; floor++) {
        floor_room *floor_node = new floor_room(floor);
        if (!root) {
            root = floor_node;
        } else {
            lastFloor->right = floor_node;
        }
        lastFloor = floor_node;
        floor_room *lastRoom = nullptr;
        for (int room = 1; room <= num_room; room++) {
            string id = to_string(floor) + "-" + to_string(room);
            string type;
            if (room % 3 == 0) {
                type = "Suite";
            } else if (room % 2 == 0) {
                type = "Double";
            } else {
                type = "Single";
            }
            floor_room *room_node = new floor_room(floor, id, type, "Ready");
            if (!lastRoom) {
                floor_node->left = room_node;
            } else {
                lastRoom->right = room_node;
            }
            lastRoom = room_node;
        }
    }
}
```

### Adding a Booking Request

- **Step 1**: Select the option to add a booking request from the main menu.
- **Step 2**: Enter the customer's name, room type, and number of nights.
- **Step 3**: Indicate if the request is high priority. High priority requests will be processed immediately if a room is available.

```cpp
void bookingQueue::requestEnqueue(const string name, string type, int nights, floor_room *root, bookingHistoryStack &bh) {
    cout << "Is this request a high priority? (Y/N): ";
    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') {
        allocateRoom(name, type, nights, root, bh);
    } else {
        bookingRequest *newRequest = new bookingRequest(name, type, nights);
        if (rear == nullptr) {
            front = newRequest;
            rear = newRequest;
        } else {
            rear->next = newRequest;
            rear = newRequest;
        }
    }
    bookingRequestCount++;
}
```

### Processing Booking Requests

- **Step 1**: Select the option to process all booking requests from the main menu.
- **Step 2**: The system will allocate rooms to customers based on availability and update the booking history.

```cpp
void Galaxy_hotel::processBookingRequest() {
    int count = 0;
    while (!bq.isEmpty()) {
        bookingRequest *firstRequest = bq.dequeueRequest(root);
        floor_room *room = findAvailableRoom(firstRequest->roomType);
        if (room) {
            count++;
            room->status = "Occupied";
            cout << "Room " << room->room_id << " allocated to " << firstRequest->customerName << " for " << firstRequest->nights << " nights." << endl;
            bh.push(firstRequest->customerName, firstRequest->roomType, room->room_id, firstRequest->nights);
        } else {
            cout << "No available rooms of type " << firstRequest->roomType << "." << endl;
        }
        delete firstRequest;
    }
    if (count == 0) {
        cout << "There is no pending request for processing." << endl;
    }
}
```

### Viewing Booking History

- **Step 1**: Select the option to view booking history from the main menu.
- **Step 2**: The system will display a list of all bookings, including customer names, room types, room IDs, and the number of nights stayed.

```cpp
void bookingHistoryStack::display() {
    bookingNode *current = top;
    if (current == nullptr) {
        cout << "There is no booking history to show!" << endl;
        return;
    } else {
        cout << "Booking History:" << endl;
        while (current != nullptr) {
            cout << "Name: " << current->customerName << endl;
            cout << "Room Type: " << current->roomType << endl;
            cout << "Room Id: " << current->roomId << endl;
            cout << "Total Day Stay: " << current->nights << endl;
            current = current->next;
        }
    }
}
```

### Canceling the Most Recent Booking

- **Step 1**: Select the option to cancel the most recent booking from the main menu.
- **Step 2**: The system will update the room status to "Ready" and remove the booking from the history.

```cpp
void Galaxy_hotel::updateRoomStatus() {
    string id = bh.pop();
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                tempRoom->status = "Ready";
                return;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Displaying Room Status

- **Step 1**: Select the option to display all hotel room statuses from the main menu.
- **Step 2**: The system will list room IDs, types, and statuses for each floor.

```cpp
void Galaxy_hotel::displayAllRoomStatus() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Floor " << tempFloor->floor << ":" << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            cout << "  Room ID: " << tempRoom->room_id
                 << ", Type: " << tempRoom->room_type
                 << ", Status: " << tempRoom->status << endl;
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Viewing Available Rooms

- **Step 1**: Select the option to view available rooms from the main menu.
- **Step 2**: The system will list all rooms that are currently "Ready" for each floor.

```cpp
void Galaxy_hotel::availableRooms() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Available Rooms at Floor" << tempFloor->floor << ": " << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Ready") {
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Checking Room Status by ID

- **Step 1**: Select the option to check room status by room ID from the main menu.
- **Step 2**: Enter the room ID to view its status, type, and other details.

```cpp
void Galaxy_hotel::roomStatusById() {
    string id;
    cout << "Enter the id of room: ";
    cin >> id;
    floor_room *tempFloor = root;
    int count = 0;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count == 0) {
        cout << "There is no room with this (" << id << ") id." << endl;
    }
}
```

### Viewing Occupied Rooms

- **Step 1**: Select the option to view occupied rooms from the main menu.
- **Step 2**: The system will list all rooms that are currently "Occupied" for each floor, along with the total count of occupied rooms.

```cpp
void Galaxy_hotel::occupiedRoom() {
    int count = 0;
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Occupied") {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count > 0) {
        cout << "Total Room Occupied are :" << count << endl;
    } else {
        cout << "There is no room which is occupied!" << endl;
    }
}
```

### 0. Exit

- **Description**: Exits the application.

## Usage

1. **Initialize the Hotel**:
   - Enter the number of floors and rooms to initialize the hotel structure.
2. **Main Menu**:

   - The main menu provides options to add booking requests, process requests, view booking history, cancel bookings, and display room statuses.

3. **Booking Requests**:

   - Add booking requests through the menu option and specify if they are high priority.
   - Process all pending requests to allocate rooms.

4. **Room Status**:

   - Check the status of all rooms, available rooms, or specific rooms by ID.
   - View occupied rooms and their details.

5. **Booking History**:
   - View the complete booking history.
   - Cancel the most recent booking to free up a room.

## Detailed Steps

### Adding Floors and Rooms

- **Step 1**: Initialize the hotel by specifying the number of floors and rooms.
- **Step 2**: Each floor will have a specified number of rooms, and each room will be assigned a unique ID and type (Single, Double, Suite).

```cpp
void Galaxy_hotel::add_floor_room(int num_floor, int num_room) {
    floor_room *lastFloor = nullptr;
    for (int floor = 1; floor <= num_floor; floor++) {
        floor_room *floor_node = new floor_room(floor);
        if (!root) {
            root = floor_node;
        } else {
            lastFloor->right = floor_node;
        }
        lastFloor = floor_node;
        floor_room *lastRoom = nullptr;
        for (int room = 1; room <= num_room; room++) {
            string id = to_string(floor) + "-" + to_string(room);
            string type;
            if (room % 3 == 0) {
                type = "Suite";
            } else if (room % 2 == 0) {
                type = "Double";
            } else {
                type = "Single";
            }
            floor_room *room_node = new floor_room(floor, id, type, "Ready");
            if (!lastRoom) {
                floor_node->left = room_node;
            } else {
                lastRoom->right = room_node;
            }
            lastRoom = room_node;
        }
    }
}
```

### Adding a Booking Request

- **Step 1**: Select the option to add a booking request from the main menu.
- **Step 2**: Enter the customer's name, room type, and number of nights.
- **Step 3**: Indicate if the request is high priority. High priority requests will be processed immediately if a room is available.

```cpp
void bookingQueue::requestEnqueue(const string name, string type, int nights, floor_room *root, bookingHistoryStack &bh) {
    cout << "Is this request a high priority? (Y/N): ";
    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') {
        allocateRoom(name, type, nights, root, bh);
    } else {
        bookingRequest *newRequest = new bookingRequest(name, type, nights);
        if (rear == nullptr) {
            front = newRequest;
            rear = newRequest;
        } else {
            rear->next = newRequest;
            rear = newRequest;
        }
    }
    bookingRequestCount++;
}
```

### Processing Booking Requests

- **Step 1**: Select the option to process all booking requests from the main menu.
- **Step 2**: The system will allocate rooms to customers based on availability and update the booking history.

```cpp
void Galaxy_hotel::processBookingRequest() {
    int count = 0;
    while (!bq.isEmpty()) {
        bookingRequest *firstRequest = bq.dequeueRequest(root);
        floor_room *room = findAvailableRoom(firstRequest->roomType);
        if (room) {
            count++;
            room->status = "Occupied";
            cout << "Room " << room->room_id << " allocated to " << firstRequest->customerName << " for " << firstRequest->nights << " nights." << endl;
            bh.push(firstRequest->customerName, firstRequest->roomType, room->room_id, firstRequest->nights);
        } else {
            cout << "No available rooms of type " << firstRequest->roomType << "." << endl;
        }
        delete firstRequest;
    }
    if (count == 0) {
        cout << "There is no pending request for processing." << endl;
    }
}
```

### Viewing Booking History

- **Step 1**: Select the option to view booking history from the main menu.
- **Step 2**: The system will display a list of all bookings, including customer names, room types, room IDs, and the number of nights stayed.

```cpp
void bookingHistoryStack::display() {
    bookingNode *current = top;
    if (current == nullptr) {
        cout << "There is no booking history to show!" << endl;
        return;
    } else {
        cout << "Booking History:" << endl;
        while (current != nullptr) {
            cout << "Name: " << current->customerName << endl;
            cout << "Room Type: " << current->roomType << endl;
            cout << "Room Id: " << current->roomId << endl;
            cout << "Total Day Stay: " << current->nights << endl;
            current = current->next;
        }
    }
}
```

### Canceling the Most Recent Booking

- **Step 1**: Select the option to cancel the most recent booking from the main menu.
- **Step 2**: The system will update the room status to "Ready" and remove the booking from the history.

```cpp
void Galaxy_hotel::updateRoomStatus() {
    string id = bh.pop();
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                tempRoom->status = "Ready";
                return;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Displaying Room Status

- **Step 1**: Select the option to display all hotel room statuses from the main menu.
- **Step 2**: The system will list room IDs, types, and statuses for each floor.

```cpp
void Galaxy_hotel::displayAllRoomStatus() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Floor " << tempFloor->floor << ":" << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            cout << "  Room ID: " << tempRoom->room_id
                 << ", Type: " << tempRoom->room_type
                 << ", Status: " << tempRoom->status << endl;
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Viewing Available Rooms

- **Step 1**: Select the option to view available rooms from the main menu.
- **Step 2**: The system will list all rooms that are currently "Ready" for each floor.

```cpp
void Galaxy_hotel::availableRooms() {
    floor_room *tempFloor = root;
    while (tempFloor) {
        cout << "Available Rooms at Floor" << tempFloor->floor << ": " << endl;
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Ready") {
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
}
```

### Checking Room Status by ID

- **Step 1**: Select the option to check room status by room ID from the main menu.
- **Step 2**: Enter the room ID to view its status, type, and other details.

```cpp
void Galaxy_hotel::roomStatusById() {
    string id;
    cout << "Enter the id of room: ";
    cin >> id;
    floor_room *tempFloor = root;
    int count = 0;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->room_id == id) {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count == 0) {
        cout << "There is no room with this (" << id << ") id." << endl;
    }
}
```

### Viewing Occupied Rooms

- **Step 1**: Select the option to view occupied rooms from the main menu.
- **Step 2**: The system will list all rooms that are currently "Occupied" for each floor, along with the total count of occupied rooms.

```cpp
void Galaxy_hotel::occupiedRoom() {
    int count = 0;
    floor_room *tempFloor = root;
    while (tempFloor) {
        floor_room *tempRoom = tempFloor->left;
        while (tempRoom) {
            if (tempRoom->status == "Occupied") {
                count++;
                cout << "  Room ID: " << tempRoom->room_id
                     << ", Type: " << tempRoom->room_type
                     << ", Status: " << tempRoom->status << endl;
            }
            tempRoom = tempRoom->right;
        }
        tempFloor = tempFloor->right;
    }
    if (count > 0) {
        cout << "Total Room Occupied are :" << count << endl;
    } else {
        cout << "There is no room which is occupied!" << endl;
    }
}
```
