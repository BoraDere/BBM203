#include "Leaderboard.h"
#include <fstream>

void Leaderboard::insert_new_entry(LeaderboardEntry *new_entry) {
    // Insert a new LeaderboardEntry instance into the leaderboard

    // If the leaderboard is empty or the new entry has a higher score than the head entry
    if (head_leaderboard_entry == nullptr || new_entry->score > head_leaderboard_entry->score) {
        new_entry->next_leaderboard_entry = head_leaderboard_entry;
        head_leaderboard_entry = new_entry;
    } else {
        LeaderboardEntry *current = head_leaderboard_entry;

        // Find the correct position to insert the new entry while maintaining descending order by score
        while (current->next_leaderboard_entry != nullptr && new_entry->score <= current->next_leaderboard_entry->score) {
            current = current->next_leaderboard_entry;
        }

        // Insert the new entry
        new_entry->next_leaderboard_entry = current->next_leaderboard_entry;
        current->next_leaderboard_entry = new_entry;
    }

    // Ensure the leaderboard size does not exceed the maximum allowed size
    LeaderboardEntry *prev = nullptr;
    LeaderboardEntry *current = head_leaderboard_entry;
    int count = 0;

    while (current != nullptr && count < MAX_LEADERBOARD_SIZE) {
        prev = current;
        current = current->next_leaderboard_entry;
        count++;
    }

    if (count >= MAX_LEADERBOARD_SIZE && prev != nullptr) {
        prev->next_leaderboard_entry = nullptr;
        delete current;  // Free the memory of the extra entry
    }
}

void Leaderboard::write_to_file(const string& filename) {
    // Write the latest leaderboard status to the given file

    ofstream outfile(filename);

    if (outfile.is_open()) {
        LeaderboardEntry* current = head_leaderboard_entry;

        while (current != nullptr) {
            outfile << current->score << " " << current->last_played << " " << current->player_name << endl;
            current = current->next_leaderboard_entry;
        }
    
        outfile.close();
    }
}

void Leaderboard::read_from_file(const string &filename) {
    // TODO: Read the stored leaderboard status from the given file
}

void Leaderboard::print_leaderboard() {
    // TODO: Print the current leaderboard status to the standard output in the specified format
}

Leaderboard::~Leaderboard() {
    // TODO: Free dynamically allocated memory used for storing leaderboard entries
}
