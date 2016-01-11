/**
Implementation of the RegularGridGenerator.

(c) 2016 Tony Liu.
*/

#include "RegularGridGenerator.h"

using namespace std;

const float RegularGridGenerator::OFFSET = 0.5; 

RegularGridGenerator::RegularGridGenerator(int mi_x, int ma_x, int mi_y, int ma_y) {
    min_x = mi_x;
    max_x = ma_x;
    max_y = ma_y;
    min_y = mi_y;

    init_grid();
    init_maps();
    generate_graph();
    grid_type = "Regular"; 
}

void RegularGridGenerator::init_grid() {

    //initialize gen_pts, verts, edges, grid_array
    for(int i = min_x; i <= max_x; i++){
        //initialize top-down, left-right
        for(int j = max_y; j >= min_y; j--){
            if(i < max_x && j > min_y) {
                Point gen_pt(i+OFFSET, j-OFFSET);
                gen_pts.push_back(gen_pt);
                cout << gen_pt << endl;
                if (i < max_x-1) gen_edges.push_back(Edge(gen_pt, Point(i+1,j)));
                if (i > min_y+1) gen_edges.push_back(Edge(gen_pt, Point(i,j-1)));
            }

            Point v(Point(i, j));
            verts.push_back(v);
            if(i < max_x) edges.push_back(Edge(v, Point(i+1, j)));
            if(j > min_y) edges.push_back(Edge(v, Point(i, j-1)));
        }
        //verts.push_back(Point(i, min_y));
    }

    //initialize faces
    for(size_t i = 0; i < gen_pts.size(); i++){
        faces.push_back(construct_square(gen_pts[i]));
    }
}

Poly RegularGridGenerator::construct_square(Point &gen_pt){

    vector<Edge> edges;
    
    Point p1(gen_pt.x-OFFSET, gen_pt.y+OFFSET);
    Point p2(gen_pt.x-OFFSET, gen_pt.y-OFFSET);
    Point p3(gen_pt.x+OFFSET, gen_pt.y+OFFSET);
    Point p4(gen_pt.x+OFFSET, gen_pt.y-OFFSET);

    edges.push_back(Edge(p1,p2));
    edges.push_back(Edge(p1,p3));
    edges.push_back(Edge(p3,p4));
    edges.push_back(Edge(p2,p4));

    return Poly(edges);
}
    
//pre: init_maps has been called
void RegularGridGenerator::generate_graph() {
    typename map<Point, string>::iterator map_it;
    for(map_it = rev_gen_pt_map.begin(); map_it != rev_gen_pt_map.end(); map_it++) {
        graph.add_vertex(map_it->second, Cell(map_it->first, map_it->second));
    }

    for(size_t i = 0; i < gen_edges.size(); i++){
       string p1 = rev_gen_pt_map[gen_edges[i].p];
       string p2 = rev_gen_pt_map[gen_edges[i].q];
       graph.add_edge(p1,p2);
    }
}

int main(){
    RegularGridGenerator gen(-5,5,-5,5);
    gen.grid_to_file("reg_test.txt");
    gen.grid_to_dot("reg_test");

    return 0;
}




