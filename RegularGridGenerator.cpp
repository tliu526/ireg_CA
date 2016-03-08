/**
Implementation of the RegularGridGenerator.

(c) 2016 Tony Liu.
*/

#include "RegularGridGenerator.h"

#include <cmath>

using namespace std;

const float RegularGridGenerator::OFFSET = 0.5; 

RegularGridGenerator::RegularGridGenerator(int mi_x, int ma_x, int mi_y, int ma_y, bool b, int degen) {
    min_x = mi_x;
    max_x = ma_x;
    max_y = ma_y;
    min_y = mi_y;
    is_toroidal = b;
    degeneracy = degen;

    init_grid();
    init_maps();
    generate_graph();

    if(degeneracy>0){
        map_faces();
        degenerate_grid();
        generate_graph();
    }

    grid_type = "Regular"; 
}

void RegularGridGenerator::init_grid() {

    //initialize gen_pts, verts, edges, grid_array
    for(int i = min_x; i <= max_x; i++){
        //initialize top-down, left-right
        for(int j = max_y; j >= min_y; j--){
            if(i < max_x && j > min_y) {
                float x = i+OFFSET;
                float y = j-OFFSET;
                Point gen_pt(x, y);
                gen_pts.push_back(gen_pt);

                if (i < max_x-1) gen_edges.push_back(Edge(gen_pt, Point(x+1,y)));
                else if (is_toroidal) gen_edges.push_back(Edge(gen_pt, Point(min_x + OFFSET,y)));

                if (j > min_y+1) gen_edges.push_back(Edge(gen_pt, Point(x,y-1)));
                else if (is_toroidal) gen_edges.push_back(Edge(gen_pt, Point(x,max_y-OFFSET)));
            }

            Point v(Point(i, j));
            verts.push_back(v);
            if(i < max_x) edges.push_back(Edge(v, Point(i+1, j)));
            if(j > min_y) edges.push_back(Edge(v, Point(i, j-1)));
        }
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
    graph = Graph<string,Cell>();

    typename map<Point, string>::iterator map_it;
    for(map_it = rev_gen_pt_map.begin(); map_it != rev_gen_pt_map.end(); map_it++) {
        graph.add_vertex(map_it->second, Cell(map_it->first, map_it->second));
    }

    for(size_t i = 0; i < gen_edges.size(); i++){
       string p1 = rev_gen_pt_map[gen_edges[i].p];
       string p2 = rev_gen_pt_map[gen_edges[i].q];

       graph.add_edge(p1,p2);
    }

   graph.print_adj_list();
}


int RegularGridGenerator::degenerate_grid(){
    if(degeneracy == 0) return 0;

    vector<string> keys;

    for(map<string, string>::iterator map_it = gen_pt_face_map.begin(); map_it != gen_pt_face_map.end(); map_it++){
        keys.push_back(map_it->first);
    }

    default_random_engine gen;
    gen.seed(degeneracy);

    shuffle(keys.begin(), keys.end(), gen);
    int num_faces_to_remove = int((float(degeneracy)/float(100))*keys.size());
    //cout << "Number of faces to remove: " << num_faces_to_remove << endl;

    for(int i = 0; i < num_faces_to_remove; i++){
        string rm_key = keys[i];

        vector<Edge>::iterator iter = gen_edges.begin();
        Poly face = face_map[gen_pt_face_map[rm_key]];

        cout << pt_map[rm_key] << endl;

        while(iter != gen_edges.end()){

            if(iter->contains(pt_map[rm_key])){
                //cout << "Erasing" << endl;
                gen_edges.erase(iter);                
            }
            else{
                iter++;
            }
        }

        gen_pts.erase(remove(gen_pts.begin(), gen_pts.end(), pt_map[rm_key]), gen_pts.end());
        gen_pt_face_map.erase(rm_key);
        rev_gen_pt_map.erase(pt_map[rm_key]);
    }

    return num_faces_to_remove;
}
/**
int main(int argc, char**argv){
    if (argc < 2){
        cout << "Provide degen amt" << endl;
        return -1;
    }
    int degen = atoi(argv[1]);

    RegularGridGenerator gen(0,64,0,64, true, degen);

    gen.grid_to_file("degen_reg_"+to_string(degen));
    gen.grid_to_dot("degen_reg_"+to_string(degen));

    return 0;
}


*/