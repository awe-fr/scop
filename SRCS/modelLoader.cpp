#include "../headers/major.hpp"

bool loadOBJ(const char* path, std::vector<vec3>& out_vertices) {
    std::vector<unsigned int> vertexIndices;
    std::vector<vec3> temp_vertices;

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }
    while (1) {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        if (strcmp(lineHeader, "v") == 0) {
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[4];
            int matches = fscanf(file, "%d %d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);
            if (matches == 3) {
                for (int i = 0; i < 3; ++i) {
                    vertexIndices.push_back(vertexIndex[i]);
                }
            } else if (matches == 4) {
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[2]);
                vertexIndices.push_back(vertexIndex[3]);
            } else {
                printf("Unsupported face format in the OBJ file.\n");
                return false;
            }
        }
    }
    fclose(file);

    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        vec3 vertex = temp_vertices[vertexIndex - 1];
        out_vertices.push_back(vertex);
    }

    return true;
}