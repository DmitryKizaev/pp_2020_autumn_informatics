// Copyright 2020 Kizaev Dmitry

#include <mpi.h>
#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include "../../../modules/task_1/kizaev_d_avg_vector_val/avg_vector_val.h"

std::vector<int> getRandVector(int size) {
    std::mt19937 val;
    std::vector<int> vector(size);
    if (size < 1) {
        throw "size < 1!";
    }
    for (int i = 0; i < size; i++) {
        vector[i] = val() % 1000;
    }

    return vector;
}

int averageVectorValueSeq(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0) / vec.size();
}

int averageVectorValueParallel(const std::vector<int>& vec) {

    int size, rank;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vectorSize = vec.size();

    if (vectorSize < size) {
        return averageVectorValueSeq(vec);
    }

    int deltaElements = vectorSize / size;
    int restElements = vectorSize % size;

    std::vector<int>localVec(deltaElements); 

    if (rank == 0) {
        localVec.resize(deltaElements + restElements);
        localVec = std::vector<int>(vec.begin(), vec.begin() + deltaElements + restElements);

        for (int proc = 1; proc < size; proc++) {
            MPI_Send(&vec[0] + proc * deltaElements + restElements, deltaElements, MPI_INT, proc, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(&localVec[0], deltaElements, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    int localSum = std::accumulate(localVec.begin(), localVec.end(), 0);

    int globalSum = 0;

    MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return globalSum / vectorSize;
}