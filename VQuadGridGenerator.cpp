/*
Implementation of VQuadGridGenerator.

(c) 2016 Tony Liu.
*/

#include "VQuadGridGenerator.h"

using namespace std;

VQuadGridGenerator::VQuadGridGenerator(string file, int degen_pct, int s){
    degen_percent = degen_pct;
    seed = s;
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

    degenerate_grid();
    generate_graph();
}

void VQuadGridGenerator::init_vgrid() {
    vector<Poly> new_faces;
    vector<Edge> new_edges;
    vector<Point> new_gen_pts;
    vector<Point> new_verts;

    //find valid face pairs
    typename map<string, vector<string>>::iterator map_it;
    for(map_it = edge_gen_pt_map.begin(); map_it != edge_gen_pt_map.end(); map_it++){
        string e_label = map_it->first;
        vector<string> *gp_labels = &(map_it->second);

        //create new face
        if(gp_labels->size() == 2){
            Point new_gp = midpoint(edge_map[e_label]);
            if(pt_in_grid(new_gp)){
                Poly face = build_quad(e_label, (*gp_labels)[0], (*gp_labels)[1]);

                new_gen_pts.push_back(new_gp);
                new_faces.push_back(face);

                //add new verts and edges to respective GridGenerator vectors
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
    gen_pt_face_map.clear();

    init_maps();
    map_faces();
}

int VQuadGridGenerator::degenerate_grid(){
    if(degen_percent == 0) return 0;

    vector<string> keys;

    for(map<string, string>::iterator map_it = gen_pt_face_map.begin(); map_it != gen_pt_face_map.end(); map_it++){
        keys.push_back(map_it->first);
    }

    default_random_engine gen;
    gen.seed(seed);

    shuffle(keys.begin(), keys.end(), gen);
    int num_faces_to_remove = int((float(degen_percent)/float(100))*keys.size());

    for(int i = 0; i < num_faces_to_remove; i++){
        string rm_key = keys[i];

        gen_pt_face_map.erase(rm_key);
        gen_pts.erase(remove(gen_pts.begin(), gen_pts.end(), pt_map[rm_key]), gen_pts.end());
        rev_gen_pt_map.erase(pt_map[rm_key]);
    }

    return num_faces_to_remove;
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

void VQuadGridGenerator::generate_graph(){
    graph = Graph<string,Cell>();

    map<string, string>::iterator gp_it;
    map<string, string>::iterator chk_it;

    for(gp_it = gen_pt_face_map.begin(); gp_it != gen_pt_face_map.end(); gp_it++){
        int num_neighbors = 0;
        string gp_label = gp_it->first;
        string face_label = gp_it->second;

        graph.add_vertex(gp_label, Cell(pt_map[gp_label], gp_label));
        list<string>* neighbors = graph.get_neighbors(gp_label);

        for(chk_it = gen_pt_face_map.begin(); chk_it != gen_pt_face_map.end(); chk_it++){
            string nbr_label = chk_it->first;
            string nbr_face_label = chk_it->second;

            //checksd if two faces share an edge 
            if (gp_label != nbr_label && face_map[face_label].shares_edge(face_map[nbr_face_label])) {
                //&& (find(neighbors->begin(), neighbors->end(), gp_label_test) == neighbors->end())){
                graph.add_edge(gp_label, nbr_label);
                num_neighbors++;
            }
        }
        //if no neighbors, add self edge
        //TODO FIXXXX
        if(num_neighbors == 0){
            graph.add_edge(gp_label,gp_label);
        }
    }

    graph.print_adj_list();

}
/*
int main(int argc, char** argv){
    if (argc < 3){
        cout << "Provide in file, degen amt" << endl;
        return -1;
    }
    string in = argv[1];
    int degen = atoi(argv[2]);

    VQuadGridGenerator gen(in,degen,degen);
    gen.grid_to_file("test_degen_stoma_"+to_string(degen));
    gen.grid_to_dot("test_degen_stoma_" +to_string(degen));
    return 0;
}
*/