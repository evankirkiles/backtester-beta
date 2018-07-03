//
// Created by Evan Kirkiles on 7/3/18.
//

#include <gtest/gtest.h>
#include "DataHandling/DataRetriever.hpp"

// Data Retriever test fixture
class DataRetrieverFixture : public ::testing::Test {
protected:
    virtual void TearDown() {}
    virtual void SetUp() {}

public:
    // Instance of Data Retriever
    std::unique_ptr<DataRetriever> dr;

    // Initializes test variables to be used
    DataRetrieverFixture() : Test(), dr(new DataRetriever()) {};

    // Destructor
    virtual ~DataRetrieverFixture() {}
};

// Tests