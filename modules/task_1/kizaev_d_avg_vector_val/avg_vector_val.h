// Copyright 2020 Kizaev Dmitry
#ifndef MODULES_TASK_1_KIZAEV_AVG_VECTOR_VAL_H_
#define MODULES_TASK_1_KIZAEV_AVG_VECTOR_VAL_H_

#include <vector>

std::vector<int> getRandVector(int size);
int averageVectorValueSeq(const std::vector<int>& vector);
int averageVectorValueParallel(const std::vector<int>& vector);

#endif  // MODULES_TASK_1_KIZAEV_AVG_VECTOR_VAL_H_
