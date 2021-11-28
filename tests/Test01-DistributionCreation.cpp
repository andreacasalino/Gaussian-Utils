#include <Packer.h>
#include <gtest/gtest.h>

#include <GaussianUtils/GaussianDistribution.h>

TEST(DistributionCreation, 1d) {
    EXPECT_NO_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0 }),
        gauss::test::make_matrix({ {1} })));

    EXPECT_NO_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 1 }),
        gauss::test::make_matrix({ {1} })));

    EXPECT_NO_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ -1 }),
        gauss::test::make_matrix({ {1} })));

    EXPECT_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0 }),
        gauss::test::make_matrix({ {-1} })), gauss::Error);

    EXPECT_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0 }),
        gauss::test::make_matrix({ {-10} })), gauss::Error);
}

TEST(DistributionCreation, 2d) {
    EXPECT_NO_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0, 0 }),
        gauss::test::make_matrix({ {1, 0}, {0, 2} })));

    EXPECT_NO_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 1, -1 }),
        gauss::test::make_matrix({ {1, 0}, {0, 2} })));

    EXPECT_NO_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ -1, 1 }),
        gauss::test::make_matrix({ {1, 0}, {0, 2} })));

    EXPECT_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0, 0 }),
        gauss::test::make_matrix({ {-1, 0}, {0, 2} })), gauss::Error);

    EXPECT_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0, 0 }),
        gauss::test::make_matrix({ {1, 0}, {0, -2} })), gauss::Error);

    EXPECT_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0, 0 }),
        gauss::test::make_matrix({ {1, 1}, {0, 2} })), gauss::Error);

    EXPECT_NO_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0, 0 }),
        gauss::test::make_matrix({ {1, -0.1}, {-0.1, 2} })));

    EXPECT_THROW(gauss::GaussianDistribution(gauss::test::make_vector({ 0, 0 }),
        gauss::test::make_matrix({ {0.1, -1}, {-1, 0.1} })), gauss::Error);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
