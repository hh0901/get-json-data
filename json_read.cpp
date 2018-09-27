#include <iostream>
#include <fstream>
#include"json.hpp"

typedef struct ADJACENTNODEINFO {
        double distance;
        int index;
        int line_type;
        double x;
        double y;
        double k;
        double b;
        double r;
        double circle_center_x;
        double circle_center_y;
        int index_before;
        int right_direction;
        int road_number;
} AdjacentNodeInfo;

using namespace std;
using json = nlohmann::json;

json nodes_info;
json roads_info;

int main()
{
    int index =1;
    cout << "Hello World!" << endl;
    std::ifstream nodes_information("node_info.json");
    nodes_information>>nodes_info;
    std::ifstream roads_information("road_info.json");
    roads_information>>roads_info;
    int node_number = nodes_info["nodes"].size();
    for(int i = 0; i<node_number; i++){
        json node_information = nodes_info["nodes"][i];
        if(index == node_information["index"]){
            cout <<node_information["ID"]<<endl;
            int adjacent_node_number = node_information["next_nodes"].size();
            for(int j = 0; j<adjacent_node_number; j++){
                AdjacentNodeInfo adjacentNode;
                json adjacent_node_info = node_information["next_nodes"][j];
                adjacentNode.distance = adjacent_node_info["distance"];
                adjacentNode.index = adjacent_node_info["index"];
                adjacentNode.right_direction = adjacent_node_info["right_direction"];
                adjacentNode.road_number = adjacent_node_info["road_ID"];
                adjacentNode.line_type = adjacent_node_info["type"];
                adjacentNode.x = adjacent_node_info["x"];
                adjacentNode.y = adjacent_node_info["y"];
                if(adjacentNode.line_type == 1){
                    adjacentNode.k= adjacent_node_info["k"];
                    adjacentNode.b = adjacent_node_info["b"];
                } else{
                    adjacentNode.r= adjacent_node_info["r"];
                    adjacentNode.circle_center_x = adjacent_node_info["circle_center_x"];
                    adjacentNode.circle_center_y = adjacent_node_info["circle_center_y"];
                }
                cout <<adjacentNode.road_number<<endl;
                cout <<adjacent_node_info["ID"]<<endl;
            }
            return 0;
        }
    }
    return 0;
}