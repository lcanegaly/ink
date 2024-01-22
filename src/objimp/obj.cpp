#include "obj.h"

objimp::Model::Model(const char* filename){

    std::size_t file_size = std::filesystem::file_size(filename);
    std::ifstream file = std::ifstream(filename, std::ios::in);
    std::cout << filename << "\n";
    std::string output;
    while (getline(file, output)){
      sort(output);
    }
    CreateMesh();
}

void objimp::Model::print(){
    for (auto& vert : points_){
      printf("vertex - %f %f %f\n", vert.x, vert.y, vert.z);
    }
    for (auto& tex : texture_coords_){
      printf("texture - %f %f\n", tex.x, tex.y);
    }
    for (auto& face : faces_){
      printf("face - %i %i %i\n", face.vertex_index[0], face.vertex_index[1], face.vertex_index[2]);
    }
}

int findVertex(objimp::Vertex v, objimp::Mesh& m){
    for (int i = 0; i < m.Vertices.size(); i++){
      auto vert = m.Vertices[i];
      if (vert == v) 
          return i;
    } 
    return -1;
}

void objimp::Model::CreateMesh(){
  Mesh m;
  for (int i = 0; i < faces_.size(); i++) {
      for (int j = 0; j < faces_[i].vertex_index.size(); j++) {
        //for each face, push the vertex and texture indices values to a Vertex struct
        Vertex v;
        auto face_index = faces_[i].vertex_index[j] - 1;
        auto face_tex = faces_[i].texture_index[j] - 1;
        auto vertex = points_[face_index]; 
        auto texture_coord = texture_coords_[face_tex]; 
        v.Position = {(float)vertex.x, (float)vertex.y, (float)vertex.z};
        v.TexCoord = {(float)texture_coord.x, (float)texture_coord.y};
        //m.Vertices.push_back(v); 
        if (findVertex(v, m) == -1){
          m.Vertices.push_back(v); 
          m.Indices.push_back(m.Vertices.size() -1); // index starting at 1
        } else {
          m.Indices.push_back(findVertex(v, m)); 
        }
      }
    }
  m.Points = points_; 
  meshes_.push_back(m);

}

bool objimp::Model::sort(std::string line){
    switch(line[0]) {
      case '#':
          //std::cout << line << " line \n";
        break;
      case 'v':
          switch(line[1]){
            case 't': 
              {
                int index = 0;
                Texture t;
                for(size_t i = 0; i < line.length();){
                  auto marker = line.find(' ', i);
                  if (marker != std::string::npos) {
                    auto end = line.find(' ', marker+1);
                    if (end == std::string::npos){
                      end = line.length(); 
                    }
                    i = end; 
                    float* value_ptr = &t.x;
                    std::string out = line.substr(marker+1, end - marker);
                    *(value_ptr + index++) = std::stod(out);
                  }
                }
                texture_coords_.push_back(t); 
              }  
              break;
            case 'n':
              // TODO vertex normals
              break;
            default:
              { 
              int index = 0;
              Point p;
              for(size_t i = 0; i < line.length();){
                auto marker = line.find(' ', i);
                if (marker != std::string::npos) {
                  auto end = line.find(' ', marker+1);
                  if (end == std::string::npos){
                    end = line.length(); 
                  }
                  i = end; 
                  float* value_ptr = &p.x;
                  std::string out = line.substr(marker+1, end - marker);
                  *(value_ptr + index++) = std::stod(out);
                }
              }
              points_.push_back(p); 
              }
               break;
          }
        break;
        case 'f':
               {
                int index = 0;
                Face f;
                for(size_t i = 0; i < line.length();){
                  auto marker = line.find(' ', i);
                  if (marker != std::string::npos) {
                    auto end = line.find(' ', marker+1);
                    if (end == std::string::npos){
                      end = line.length(); 
                    }
                    i = end; 
                    std::string out = line.substr(marker+1, end - marker);
                    auto face_marker = out.find('/', 0); // find first seperator 
                    std::string face_vert = out.substr(0, face_marker);
                    auto face_end = out.find('/',face_marker+1);// find sec seperator
                    std::string face_tex = ""; 
                    if (face_end == std::string::npos){
                      face_tex = out.substr(face_marker+1, out.length()-face_marker);
                    }else{
                      face_marker = face_end;
                      face_end = out.length();
                      face_tex = out.substr(face_marker+1, face_end - face_marker);
                    }
                    f.vertex_index.push_back(std::stoi(face_vert));
                    f.texture_index.push_back(std::stoi(face_tex));
                  } 
                }
                faces_.push_back(f);
              } 
    }
     
    return true;
    //if first char is f, process faces
    //if first char is m, process mesh
}


