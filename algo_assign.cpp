#include <bits/stdc++.h>
using namespace std;

/* =========================
   COURSE STRUCTURE
========================= */
struct Course {
    int id;
    string name;
    int students;
};

/* =========================
   SORTING (by number of students)
========================= */
bool compareCourses(Course a, Course b) {
    return a.students > b.students; // larger classes first
}

/* =========================
   GRAPH COLORING (Time Slots)
========================= */
vector<int> graphColoring(vector<vector<int>>& graph, int V) {
    vector<int> result(V, -1);

    // Assign first color to first course
    result[0] = 0;

    vector<bool> available(V, false);

    for (int u = 1; u < V; u++) {

        // Mark colors of adjacent nodes as unavailable
        for (int i = 0; i < V; i++) {
            if (graph[u][i] && result[i] != -1)
                available[result[i]] = true;
        }

        // Find first available color
        int color;
        for (color = 0; color < V; color++) {
            if (!available[color])
                break;
        }

        result[u] = color;

        // Reset availability
        fill(available.begin(), available.end(), false);
    }

    return result;
}

/* =========================
   GREEDY ROOM ALLOCATION
========================= */
void assignRooms(vector<Course>& courses, vector<int>& timeslot, int rooms) {
    map<int, vector<int>> schedule;

    for (int i = 0; i < courses.size(); i++) {
        int slot = timeslot[i];

        if (schedule[slot].size() < rooms) {
            schedule[slot].push_back(i);
        } else {
            cout << "Course " << courses[i].name << " could not be assigned (no room)\n";
        }
    }

    cout << "\nFinal Timetable:\n";

    for (auto& s : schedule) {
        cout << "Time Slot " << s.first << ":\n";
        for (int idx : s.second) {
            cout << "  Course: " << courses[idx].name << "\n";
        }
    }
}

/* =========================
   MAIN FUNCTION
========================= */
int main() {

    /* =========================
       INPUT COURSES
    ========================= */
    vector<Course> courses = {
        {0, "Math", 60},
        {1, "Physics", 50},
        {2, "Chemistry", 40},
        {3, "Biology", 30},
        {4, "Computer Science", 70}
    };

    int V = courses.size();

    /* =========================
       SORT COURSES
    ========================= */
    sort(courses.begin(), courses.end(), compareCourses);

    cout << "Courses sorted by student strength:\n";
    for (auto &c : courses) {
        cout << c.name << " (" << c.students << " students)\n";
    }

    /* =========================
       CONFLICT GRAPH
       (1 means conflict)
    ========================= */
    vector<vector<int>> graph = {
        {0,1,1,0,0},
        {1,0,1,1,0},
        {1,1,0,1,1},
        {0,1,1,0,1},
        {0,0,1,1,0}
    };

    /* =========================
       GRAPH COLORING
    ========================= */
    vector<int> timeslot = graphColoring(graph, V);

    cout << "\nAssigned Time Slots:\n";
    for (int i = 0; i < V; i++) {
        cout << courses[i].name << " -> Slot " << timeslot[i] << endl;
    }

    /* =========================
       GREEDY ROOM ASSIGNMENT
    ========================= */
    int rooms = 2;
    assignRooms(courses, timeslot, rooms);

    return 0;
}