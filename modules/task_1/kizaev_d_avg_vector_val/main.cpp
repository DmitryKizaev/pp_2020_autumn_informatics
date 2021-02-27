// Copyright 2020 Kizaev Dmitry

#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./avg_vector_val.h"

TEST(average_value_vector_MPI, Can_Detect_Wrong_Size) {
    std::vector <int> vector;
    const int vector_size = -100;

    ASSERT_ANY_THROW(vector = getRandVector(vector_size));
}

TEST(average_value_vector_MPI, seqWorks) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector <int> vec {10, 10, 10, -10, 100};

    EXPECT_EQ(24, averageVectorValueSeq(vec));
}

TEST(average_value_vector_MPI, parrallelEqualsSeq10000) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector <int> vec;

    const int vectorSize = 10000;

    vec = getRandVector(vectorSize);
    
    int res = averageVectorValueParallel(vec);
    if (rank == 0)
        EXPECT_EQ(res, averageVectorValueSeq(vec));
}

TEST(average_value_vector_MPI, Even_Size_Vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector <int> vec;

    const int vectorSize = 1212;

    vec = getRandVector(vectorSize);

    int res = averageVectorValueParallel(vec);
    if (rank == 0)
        EXPECT_EQ(res, averageVectorValueSeq(vec));
}

TEST(average_value_vector_MPI, Odd_Size_Vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector <int> vec;

    const int vectorSize = 12213;

    vec = getRandVector(vectorSize);

    int res = averageVectorValueParallel(vec);
    if (rank == 0)
        EXPECT_EQ(res, averageVectorValueSeq(vec));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}