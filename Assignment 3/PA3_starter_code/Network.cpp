#include "Network.h"
#include <ctime>
#include <cstdio>
#include <iostream>

Network::Network() {

}

void Network::process_commands(vector<Client> &clients, vector<string> &commands, int message_limit, const string &sender_port, const string &receiver_port) {
    // TODO: Execute the commands given as a vector of strings while utilizing the remaining arguments.
    /* Don't use any static variables, assume this method will be called over and over during testing.
     Don't forget to update the necessary member variables after processing each command. For example,
     after the MESSAGE command, the outgoing queue of the sender must have the expected frames ready to send. */
     /* Commands:
     MESSAGE : Initiates communication between the clients.
     SHOW_FRAME_INFO : Displays the status of a message frame.
     SHOW_Q_INFO : Displays the status of a client’s incoming or outgoing queue.
     SEND : Initiates a single transmission step within the entire network.
     RECEIVE : Initiates a single reception step within the entire network.
     PRINT_LOG : Prints the log of a given client.
     checking if the line has a command
     */

    int hops = 0;
    int x = 0;
    std::vector<int> frame_numbers;

    for (const auto &command : commands) {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (x == 0) {
            x++;
            continue;
        }

        if (cmd == "MESSAGE") {

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Command: " << command << std::endl;

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            string sender_ID, receiver_ID, message_data;
            iss >> sender_ID >> receiver_ID >> ws;
            
            // getting the message data
            getline(iss, message_data);

            message_data = message_data.substr(1, message_data.length() - 2);

            // splitting the message data into chunks
            vector<string> message_chunks;
            for (size_t i = 0; i < message_data.length(); i += message_limit) {
                message_chunks.push_back(message_data.substr(i, message_limit));
            }

            Client* senderClient = nullptr;
            Client* receiverClient = nullptr;

            for (auto &client : clients) {
                if (client.client_id == sender_ID) {
                    senderClient = &client;
                }
                else if (client.client_id == receiver_ID) {
                    receiverClient = &client;
                }
            }

            std::cout << "Message to be sent: \"" << message_data << "\"\n" << std::endl;

            // creating the frames which are stacks of packets
            for (size_t i = 0; i < message_chunks.size(); i++) {
                stack<Packet*> frame;

                string message_chunk = message_chunks[i];

                PhysicalLayerPacket* physicalLayerPacket = new PhysicalLayerPacket(3, senderClient->client_mac, receiverClient->client_mac);
                NetworkLayerPacket* networkLayerPacket = new NetworkLayerPacket(2, senderClient->client_ip, receiverClient->client_ip);
                TransportLayerPacket* transportLayerPacket = new TransportLayerPacket(1, sender_port, receiver_port);
                ApplicationLayerPacket* applicationLayerPacket = new ApplicationLayerPacket(0, sender_ID, receiver_ID, message_chunk);

                // pushing all the layers to the frame
                frame.push(applicationLayerPacket);
                frame.push(transportLayerPacket);
                frame.push(networkLayerPacket);
                frame.push(physicalLayerPacket);

                std::cout << "Frame #" << i + 1 << std::endl;
                physicalLayerPacket->print();
                networkLayerPacket->print();
                transportLayerPacket->print();
                applicationLayerPacket->print();
                std::cout << "Message chunk carried: \"" << message_chunk << "\"" << std::endl;
                std::cout << "Number of hops so far: " << hops << std::endl;
                for (int i = 0; i < 8; i++) {
                    std::cout << "-";
                }
                std::cout << std::endl;

                // pushing the frame to the sender's outgoing queue
                senderClient->outgoing_queue.push(frame);
                frame_numbers.push_back(i + 1);
            }

            // creating the log entry
            // timestamp must be in this format: 2023-11-22 20:30:03
            time_t now = time(0);
            tm *ltm = localtime(&now);

            char buffer[100];
            strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", ltm);
            std::string timestamp(buffer);

            // creating the log entry
            Log logEntry(timestamp, message_data, message_chunks.size(), hops, sender_ID, receiver_ID, true, ActivityType::MESSAGE_SENT);

            // pushing the log entry to the sender's log entries
            senderClient->log_entries.push_back(logEntry);
            
        }
        else if (cmd == "SHOW_FRAME_INFO") {

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Command: " << command << std::endl;

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;      

            // format is SHOW_FRAME_INFO<space>client_ID<space>queue_selection<space>frame_number
            string client_id, queue_selection;
            int frame_number;
            iss >> client_id >> queue_selection >> frame_number;
            // getting the client
            Client* client = nullptr;
            for (auto &c : clients) {
                if (c.client_id == client_id) {
                    client = &c;
                }
            }
            // getting the queue
            queue<stack<Packet*>>* queue = nullptr;
            std::string q;
            if (queue_selection == "out") {
                queue = &client->outgoing_queue;
                q = "outgoing queue";
            }
            else if (queue_selection == "in") {
                queue = &client->incoming_queue;
                q = "incoming queue";
            }
            if (frame_number < queue->size()) {
                std::queue<std::stack<Packet*>> tempQueue(*queue); // Copy the original queue
                std::stack<Packet*> frame;
                for (int i = 0; i < frame_number; i++) {
                    if (!tempQueue.empty()) {
                        if (i == frame_number - 1) {
                            frame = tempQueue.front();
                        }
                        tempQueue.pop();
                    }
                }

                // getting the packets
                PhysicalLayerPacket* physicalLayerPacket = (PhysicalLayerPacket*) frame.top();
                frame.pop();
                NetworkLayerPacket* networkLayerPacket = (NetworkLayerPacket*) frame.top();
                frame.pop();
                TransportLayerPacket* transportLayerPacket = (TransportLayerPacket*) frame.top();
                frame.pop();
                ApplicationLayerPacket* applicationLayerPacket = (ApplicationLayerPacket*) frame.top();
                frame.pop();

                // printing the packet information
                std::cout << "Current Frame #" << frame_number << " on the " << q << " of client " << client->client_id << std::endl;
                std::cout << "Carried Message: \"" << applicationLayerPacket->message_data << "\"" << std::endl;
                std::cout << "Layer 0 info: ";
                applicationLayerPacket->print();
                std::cout << "Layer 1 info: ";
                transportLayerPacket->print();
                std::cout << "Layer 2 info: ";
                networkLayerPacket->print();
                std::cout << "Layer 3 info: ";
                physicalLayerPacket->print();
                std::cout << "Number of hops so far: " << hops << std::endl;
            }
            else {
                std::cout << "No such frame." << std::endl;
            }
        } 
        else if (cmd == "SHOW_Q_INFO") {
            
            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Command: " << command << std::endl;

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;            

            // Displays the status of a client’s incoming or outgoing queue.
            // SHOW_Q_INFO C out 
            // SHOW_Q_INFO C in
            string client_id, queue_type;
            iss >> client_id >> queue_type;
            
            if (queue_type == "out") {
                for (auto &client : clients) {
                    if (client.client_id == client_id) {
                        std::cout << "Client " << client_id << " Outgoing Queue Status" << std::endl;
                        std::cout << "Current total number of frames: " << client.outgoing_queue.size() << std::endl;
                    }
                }
            }
            else if (queue_type == "in") {
                for (auto &client : clients) {
                    if (client.client_id == client_id) {
                        std::cout << "Client " << client_id << " Incoming Queue Status" << std::endl;
                        std::cout << "Current total number of frames: " << client.incoming_queue.size() << std::endl;
                    }
                }
            }
        } 
        else if (cmd == "SEND") {
            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Command: " << command << std::endl;

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            // for all clients, sending all frames in the outgoing queue to the client in the routing table
            // for example: client C has a frame in its outgoing queue to client E. client C's routing table says that client E is connected to client E via client B. so client C sends the frame to client B.
            // frame will be added to the incoming queue of client B
            // client B will be found via MAC address

            for (auto &client : clients) {
                while (client.outgoing_queue.size() > 0) {
                    // getting the frame
                    std::queue<std::stack<Packet*>> tempQueue(client.outgoing_queue); // Copy the original queue
                    std::stack<Packet*> frame = tempQueue.front();
                    tempQueue.pop();

                    // getting the packets
                    PhysicalLayerPacket* physicalLayerPacket = (PhysicalLayerPacket*) frame.top();
                    frame.pop();
                    NetworkLayerPacket* networkLayerPacket = (NetworkLayerPacket*) frame.top();
                    frame.pop();
                    TransportLayerPacket* transportLayerPacket = (TransportLayerPacket*) frame.top();
                    frame.pop();
                    ApplicationLayerPacket* applicationLayerPacket = (ApplicationLayerPacket*) frame.top();
                    frame.pop();

                    std::string receiverID = client.routing_table[applicationLayerPacket->receiver_ID];

                    std::unordered_map<std::string, std::string> routes = client.routing_table;

                    if (routes.find(receiverID) != routes.end()) {
                        // receiverID exists in the routing table
                        client.outgoing_queue.pop();
                        if (routes[receiverID] == receiverID) {
                            // The ID in the routing table corresponds to the receiverID
                            // This is the intended receiver
                        } else {
                            // The ID in the routing table does not correspond to the receiverID
                            // This is not the intended receiver
                        }
                    } else {
                        // receiverID does not exist in the routing table
                        // The message will be dropped
                        // create the log entry
                        // timestamp must be in this format: 2023-11-22 20:30:03
                        time_t now = time(0);
                        tm *ltm = localtime(&now);

                        char buffer[100];
                        strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", ltm);
                        std::string timestamp(buffer);

                        // creating the log entry
                        Log logEntry(timestamp, applicationLayerPacket->message_data, applicationLayerPacket->message_data.length(), hops, applicationLayerPacket->sender_ID, applicationLayerPacket->receiver_ID, false, ActivityType::MESSAGE_DROPPED);

                        // pushing the log entry to the sender's log entries
                        client.log_entries.push_back(logEntry);

                        // popping the frame from the outgoing queue
                        client.outgoing_queue.pop();
                        continue;
                    }
                    
                }
                hops++;
            }
        } 
        else if (cmd == "RECEIVE") {
            
            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Command: " << command << std::endl;

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            // for all clients, checking if there are any frames in the incoming queue
            // if there are, pop the frame and add it to the outgoing queue of the client in the routing table
            // if the frame is intended for the client, the message will be assembled and will have a different log and output
            // if the frame is not intended for the client, the message will be forwarded and will have a different log and output. and if the intended client is not in the routing table or doesnt have a correspondence the message will be dropped and will have a different log and output.

            for (auto &client : clients) {
                while (client.incoming_queue.size() > 0) {
                    // getting the frame
                    std::queue<std::stack<Packet*>> tempQueue(client.incoming_queue); // Copy the original queue
                    std::stack<Packet*> frame = tempQueue.front();
                    tempQueue.pop();

                    // getting the packets
                    PhysicalLayerPacket* physicalLayerPacket = (PhysicalLayerPacket*) frame.top();
                    frame.pop();
                    NetworkLayerPacket* networkLayerPacket = (NetworkLayerPacket*) frame.top();
                    frame.pop();
                    TransportLayerPacket* transportLayerPacket = (TransportLayerPacket*) frame.top();
                    frame.pop();
                    ApplicationLayerPacket* applicationLayerPacket = (ApplicationLayerPacket*) frame.top();
                    frame.pop();

                    std::string receiverID = client.routing_table[applicationLayerPacket->receiver_ID];

                    std::unordered_map<std::string, std::string> routes = client.routing_table;

                    if (routes.find(receiverID) != routes.end()) {
                        // receiverID exists in the routing table
                        client.incoming_queue.pop();
                        if (routes[receiverID] == receiverID) {
                            // The ID in the routing table corresponds to the receiverID
                            // This is the intended receiver
                            // create the log entry
                            // timestamp must be in this format: 2023-11-22 20:30:03
                            time_t now = time(0);
                            tm *ltm = localtime(&now);

                            char buffer[100];
                            strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", ltm);
                            std::string timestamp(buffer);

                            // creating the log entry
                            Log logEntry(timestamp, applicationLayerPacket->message_data, applicationLayerPacket->message_data.length(), hops, applicationLayerPacket->sender_ID, applicationLayerPacket->receiver_ID, true, ActivityType::MESSAGE_RECEIVED);

                            // pushing the log entry to the sender's log entries
                            client.log_entries.push_back(logEntry);

                            // popping the frame from the incoming queue
                            client.incoming_queue.pop();
                        } else {
                            // The ID in the routing table does not correspond to the receiverID
                            // This is not the intended receiver
                            // create the log entry
                            // timestamp must be in this format: 2023-11-22 20:30:03
                            time_t now = time(0);
                            tm *ltm = localtime(&now);

                            char buffer[100];
                            strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", ltm);
                            std::string timestamp(buffer);

                            // creating the log entry
                            Log logEntry(timestamp, applicationLayerPacket->message_data, applicationLayerPacket->message_data.length(), hops, applicationLayerPacket->sender_ID, applicationLayerPacket->receiver_ID, true, ActivityType::MESSAGE_FORWARDED);

                            // pushing the log entry to the sender's log entries
                            client.log_entries.push_back(logEntry);

                            // popping the frame from the incoming queue
                            client.incoming_queue.pop();

                            // pushing the frame to the outgoing queue of the client in the routing table
                            for (auto &c : clients) {
                                if (c.client_id == routes[receiverID]) {
                                    c.outgoing_queue.push(frame);
                                }
                            }

                        }
                    } else {
                        // receiverID does not exist in the routing table
                        // The message will be dropped
                        // create the log entry
                        // timestamp must be in this format: 2023-11-22 20:30:03
                        time_t now = time(0);
                        tm *ltm = localtime(&now);

                        char buffer[100];
                        strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", ltm);
                        std::string timestamp(buffer);

                        // creating the log entry
                        Log logEntry(timestamp, applicationLayerPacket->message_data, applicationLayerPacket->message_data.length(), hops, applicationLayerPacket->sender_ID, applicationLayerPacket->receiver_ID, false, ActivityType::MESSAGE_DROPPED);

                        // pushing the log entry to the sender's log entries
                        client.log_entries.push_back(logEntry);

                        // popping the frame from the incoming queue
                        client.incoming_queue.pop();
                    }
                }
            }
        } 
        else if (cmd == "PRINT_LOG") {
            
            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Command: " << command << std::endl;

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            string client_id;
            iss >> client_id;

            // checking if the client's log is empty
            bool empty = true;
            for (auto &client : clients) {
                if (client.client_id == client_id) {
                    if (client.log_entries.size() > 0) {
                        empty = false;
                    }
                }
            }

            if (!empty) {
                std::cout << "Client " << client_id << " Logs:" << std::endl;

                for (auto &client : clients) {
                    if (client.client_id == client_id) {
                        for (int i = 0; i < client.log_entries.size(); i++) {
                            for (int j = 0; j < 14; j++) {
                                std::cout << "-";
                            }
                            std::cout << std::endl;
                            std::cout << "Log Entry #" << i + 1 << std::endl;
                            std::string activity;
                            switch(client.log_entries[i].activity_type) {
                                case ActivityType::MESSAGE_RECEIVED:
                                    activity = "Message Received";
                                    break;
                                case ActivityType::MESSAGE_FORWARDED:
                                    activity = "Message Forwarded";
                                    break;
                                case ActivityType::MESSAGE_SENT:
                                    activity = "Message Sent";
                                    break;
                                case ActivityType::MESSAGE_DROPPED:
                                    activity = "Message Dropped";
                                    break;
                            }
                            std::cout << "Activity: " << activity << std::endl;
                            std::cout << "Timestamp: " << client.log_entries[i].timestamp << std::endl;
                            std::cout << "Number of frames: " << client.log_entries[i].number_of_frames << std::endl;
                            std::cout << "Number of hops: " << client.log_entries[i].number_of_hops << std::endl;
                            std::cout << "Sender ID: " << client.log_entries[i].sender_id << std::endl;
                            std::cout << "Receiver ID: " << client.log_entries[i].receiver_id << std::endl;
                            std::cout << "Success: " << (client.log_entries[i].success_status ? "Yes" : "No") << std::endl;
                            if (activity == "Message Sent" || activity == "Message Received") {
                                std::cout << "Message: \"" << client.log_entries[i].message_content << "\"" << std::endl;
                            }
                        }
                    }
                }
            }
        } 
        else {
            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Command: " << command << std::endl;

            for (int i = 0; i < command.length() + 9; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout << "Invalid command." << std::endl;     
        }
    }
}

vector<Client> Network::read_clients(const string &filename) {
    vector<Client> clients;
    // TODO: Read clients from the given input file and return a vector of Client instances.
    // read the file line by line
    // for each line, create a client instance and add it to the vector
    // return the vector

    ifstream file(filename);
    string line;

    // first line is the number of clients
    getline(file, line);
    int number_of_clients = stoi(line);

    for (int i = 0; i < number_of_clients; i++) {
        getline(file, line);
        stringstream ss(line);
        string client_id, client_ip_address, client_mac_address;
        ss >> client_id >> client_ip_address >> client_mac_address;
        Client client(client_id, client_ip_address, client_mac_address);
        clients.push_back(client);
    }

    return clients;
}

void Network::read_routing_tables(vector<Client> &clients, const string &filename) {
    // TODO: Read the routing tables from the given input file and populate the clients' routing_table member variable.
    // read the file line by line
    // for each line, create a routing table entry and add it to the client's routing table
    // line format: Destination_Client_ID<space>Nearest_neighbor_Client_ID_on_the_path
    ifstream file(filename);
    string line;
    int index = 0;

    while (getline(file, line)) {
        if (line != "-") {
            stringstream ss(line);
            string destination_client_id, nearest_neighbor_client_id_on_the_path;
            ss >> destination_client_id >> nearest_neighbor_client_id_on_the_path;
            clients[index].routing_table[destination_client_id] = nearest_neighbor_client_id_on_the_path;
        }
        else {
            index++;
        }
    }
}

// Returns a list of token lists for each command
vector<string> Network::read_commands(const string &filename) {
    vector<string> commands;
    // TODO: Read commands from the given input file and return them as a vector of strings.
    // read the file line by line

    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        commands.push_back(line);
    }

    return commands;
}

Network::~Network() {
    // TODO: Free any dynamically allocated memory if necessary.
}
