/*
Implementation of VQuadGridGenerator.

(c) 2016 Tony Liu.
*/

#include "VQuadGridGenerator.h"

using namespace std;

VQuadGridGenerator::VQuadGridGenerator(string file){
    init_from_file(file);
    init_maps();
    map_faces(); //initializes gen_pt_face_map

    //initialize edge_gen_pt_map
    typename map<string, string>::iterator map_it;
    for(map_it = gen_pt_face_map.begin(); map_it != gen_pt_face_map.end(); map_it++){
        string gp_label = map_it->first;
        string f_label = map_it->second;

        vector<Edge> *edges = &(face_map[f_label].edges);

        for(size_t e_i = 0; e_i < edges->size(); e_i++ ){
            string e_label = rev_edge_map[(*edges)[e_i]];

            if(edge_gen_pt_map.count(e_label) == 0) {
                edge_gen_pt_map[e_label];
            }

            edge_gen_pt_map[e_label].push_back(gp_label);
        }
    }

    init_vgrid();
}

void VQuadGridGenerator::init_vgrid() {
    vector<Poly> new_faces;
    vector<Edge> new_edges;
    vector<Point> new_gen_pts;
    vector<Point> new_verts;

    //find valid
    typename map<string, vector<string>>::iterator map_it;
    for(map_it = edge_gen_pt_map.begin(); map_it != edge_gen_pt_map.end(); map_it++){
        string e_label = map_it->first;
        vector<string> *gp_labels = &(map_it->second);

        //create new face
        if(gp_labels->size() == 2){            
            Poly face = build_quad(e_label, (*gp_labels)[0], (*gp_labels)[1]);

            new_gen_pts.push_back(midpoint(edge_map[e_label]));
            new_faces.push_back(face);

            for (size_t v_i = 0; v_i < face.verts.size(); v_i++){
                Point vert = face.verts[v_i];
                if(count(new_verts.begin(), new_verts.end(), vert) == 0) {
                    new_verts.push_back(vert);
                }
            }

            for (size_t e_i = 0; e_i < face.edges.size(); e_i++){
                Edge edge = face.edges[e_i];
                if(count(new_edges.begin(), new_edges.end(), edge) == 0) {
                    new_edges.push_back(edge);
                }
            }
        }
    }

    //clear data from initialization
    faces.clear();
    face_map.clear();
    faces = new_faces;

    edges.clear();
    edges = new_edges;
    edge_map.clear();
    
    rev_edge_map.clear();
    pt_map.clear();
    rev_vert_map.clear();

    verts.clear();
    verts = new_verts;
    rev_vert_map.clear();

    gen_pts.clear();
    gen_pts = new_gen_pts;
    rev_gen_pt_map.clear();

    init_maps();
}

//pre: gp_1 and gp_2's associated faces share an edge
Poly VQuadGridGenerator::build_quad(string& e_label, string& gp_label1, string& gp_label2){
    vector<Edge> quad_edges;
    Edge e = edge_map[e_label];
    Point gp1 = pt_map[gp_label1];
    Point gp2 = pt_map[gp_label2];

    quad_edges.push_back(Edge(e.p, gp1));
    quad_edges.push_back(Edge(e.p, gp2));
    quad_edges.push_back(Edge(e.q, gp1));
    quad_edges.push_back(Edge(e.q, gp2));

    return Poly(quad_edges);
}

void VQuadGridGenerator::generate_graph(){}
/*
int main(){
    VQuadGridGenerator gen("v_test.txt");
    gen.grid_to_file("q_test");
    gen.grid_to_dot("q_test");
    return 0;
}
*/