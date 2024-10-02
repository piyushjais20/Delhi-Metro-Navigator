//c++ program 
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Graph_M {
public:
    class Vertex {
    public:
        unordered_map<string, int> nbrs;
    };

    unordered_map<string, Vertex> vtces;

    Graph_M() {}

    int numVertices() { 
        return vtces.size();
    }

    bool containsVertex(const string& vname) {
        return vtces.count(vname) > 0;
    }

    void addVertex(const string& vname) {
        Vertex vtx;
        vtces[vname] = vtx;
    }

    void removeVertex(const string& vname) {
        Vertex vtx = vtces[vname];
        vector<string> keys;
        for (auto& entry : vtx.nbrs) {
            keys.push_back(entry.first);
        }

        for (const string& key : keys) {
            Vertex& nbrVtx = vtces[key];
            nbrVtx.nbrs.erase(vname);
        }

        vtces.erase(vname);
    }

    int numEdges() {
        int count = 0;
        for (auto& entry : vtces) {
            const Vertex& vtx = entry.second;
            count += vtx.nbrs.size();
        }
        return count / 2;
    }

    bool containsEdge(const string& vname1, const string& vname2) {
        const Vertex& vtx1 = vtces[vname1];
        if (vtx1.nbrs.count(vname2) > 0) {
            return true;
        }
        return false;
    }

    void addEdge(const string& vname1, const string& vname2, int value) {
        if (!containsEdge(vname1, vname2)) {
            vtces[vname1].nbrs[vname2] = value;
            vtces[vname2].nbrs[vname1] = value;
        }
    }

    void removeEdge(const string& vname1, const string& vname2) {
        if (containsEdge(vname1, vname2)) {
            vtces[vname1].nbrs.erase(vname2);
            vtces[vname2].nbrs.erase(vname1);
        }
    }

    void display_Map() {
        cout << "\t Delhi Metro Map" << endl;
        cout << "\t------------------" << endl;
        cout << "----------------------------------------------------" << endl << endl;
        for (auto& entry : vtces) {
            const string& key = entry.first;
            const Vertex& vtx = entry.second;
            cout << key << " =>" << endl;
            for (auto& nbr : vtx.nbrs) {
                cout << "\t" << nbr.first << "\t";
                if (nbr.first.length() < 16)
                    cout << "\t";
                if (nbr.first.length() < 8)
                    cout << "\t";
                cout << nbr.second << endl;
            }
            cout << endl;
        }
        cout << "\t------------------" << endl;
        cout << "---------------------------------------------------" << endl << endl;
    }

    void display_Stations() {
        cout << endl << "***********************************************************************" << endl << endl;
        int i = 1;
        for (auto& entry : vtces) {
            const string& key = entry.first;
            cout << i << ". " << key << endl;
            i++;
        }
        cout << endl << "***********************************************************************" << endl << endl;
    }

    bool hasPath(const string& vname1, const string& vname2, unordered_map<string, bool>& visited) {
        visited[vname1] = true;

        if (containsEdge(vname1, vname2))
            return true;

        for (auto& nbr : vtces[vname1].nbrs) {
            if (!visited[nbr.first] && hasPath(nbr.first, vname2, visited))
                return true;
        }

        return false;
    }

    void shortestPath(const string& vname1, const string& vname2) {
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;
        unordered_map<string, bool> visited;

        for (auto& entry : vtces) {
            const string& key = entry.first;
            dist[key] = numeric_limits<int>::max();
        }

        queue<string> q;
        q.push(vname1);
        visited[vname1] = true;
        dist[vname1] = 0;
        parent[vname1] = "";

        while (!q.empty()) {
            string vtx = q.front();
            q.pop();

            for (auto& nbr : vtces[vtx].nbrs) {
                if (!visited[nbr.first]) {
                    q.push(nbr.first);
                    visited[nbr.first] = true;
                }

                int newDist = dist[vtx] + nbr.second;
                if (newDist < dist[nbr.first]) {
                    dist[nbr.first] = newDist;
                    parent[nbr.first] = vtx;
                }
            }
        }

        vector<string> path;
        string curr = vname2;
        while (curr != "") {
            path.push_back(curr);
            curr = parent[curr];
        }

        if (path.size() == 1 && path[0] != vname1)
            cout << "No path exists between " << vname1 << " and " << vname2 << endl;
        else {
            cout << "Shortest path from " << vname1 << " to " << vname2 << ":" << endl;
            for (int i = path.size() - 1; i >= 0; i--)
                cout << path[i] << " -> ";
            cout << "Destination" << endl;
            cout << "Total Distance: " << dist[vname2] << endl;
        }
    }
};

int main() {
    Graph_M g;
    g.addVertex("New Delhi");
    g.addVertex("Chandni Chowk");
    g.addVertex("Lal Quila");
    g.addVertex("Connaught Place");
    g.addVertex("Karol Bagh");
    g.addVertex("Dwarka");
    g.addVertex("Hauz Khas");
    g.addVertex("Punjabi Bagh");
    g.addVertex("Rajouri Garden");
    g.addVertex("Rohini");
    g.addVertex("Dilshad Garden");
    g.addVertex("Gurugram");
    g.addVertex("Noida");
    g.addVertex("Vaishali");

    g.addEdge("New Delhi", "Chandni Chowk", 5);
    g.addEdge("New Delhi", "Lal Quila", 3);
    g.addEdge("New Delhi", "Connaught Place", 2);
    g.addEdge("Connaught Place", "Karol Bagh", 4);
    g.addEdge("Connaught Place", "Hauz Khas", 7);
    g.addEdge("Connaught Place", "Punjabi Bagh", 5);
    g.addEdge("Karol Bagh", "Rajouri Garden", 2);
    g.addEdge("Karol Bagh", "Rohini", 9);
    g.addEdge("Hauz Khas", "Rohini", 6);
    g.addEdge("Hauz Khas", "Dwarka", 8);
    g.addEdge("Rohini", "Dilshad Garden", 8);
    g.addEdge("Rohini", "Gurugram", 7);
    g.addEdge("Rohini", "Noida", 9);
    g.addEdge("Dwarka", "Gurugram", 3);
    g.addEdge("Dwarka", "Noida", 6);
    g.addEdge("Gurugram", "Noida", 2);
    g.addEdge("Noida", "Vaishali", 3);


    string source = "Rohini";
    string destination = "Noida";

    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;
    cout << endl;
      unordered_map<string,bool>mp;
    if (g.containsVertex(source) && g.containsVertex(destination)) {
        if (g.hasPath(source, destination, mp)) {
            g.shortestPath(source, destination);
        }
        else {
            cout << "No path exists between " << source << " and " << destination << endl;
        }
    }
    else {
        cout << "Source or destination not found!" << endl;
    }

    return 0;
}