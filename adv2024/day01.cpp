// Advent of Code 2024
// Copyright 2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <tuple>
#include <vector>
#include <gtest/gtest.h>

namespace
{
    std::tuple<std::vector<int>, std::vector<int>> read_lists(const std::string& filename)
    {
        auto left  = std::vector<int>{};
        auto right = std::vector<int>{};

        auto input = std::ifstream(std::filesystem::path(PROJECT_DIR) / filename);

        while (input.good())
        {
            int l, r;
            input >> l;
            input >> r;

            left.push_back(l);
            right.push_back(r);
        }

        return {left, right};
    }


    unsigned int solution1(const std::string& file)
    {
        auto [left, right] = read_lists(file);

        std::ranges::sort(left);
        std::ranges::sort(right);


        unsigned int distance = 0;
        for (auto i = 0u; i < left.size(); i++)
        {
            distance += std::abs(left[i] - right[i]);
        }

        return distance;
    }

    unsigned int solution2(const std::string& file)
    {
        auto [left, right] = read_lists(file);

        auto similarity = std::map<int, int>{};

        unsigned int score = 0;
        for (auto i = 0u; i < left.size(); i++)
        {
            auto j = similarity.find(left[i]);
            if (j != end(similarity))
            {
                score += j->second;
            }
            else
            {
                auto s = std::ranges::count(right, left[i]) * left[i];
                similarity[left[i]] = s;
                score += s;
            }
        }

        return score;
    }
}


TEST(day01, example1)
{
    EXPECT_EQ(solution1("day01_example1.txt"), 11);
}

TEST(day01, input1)
{
    EXPECT_EQ(solution1("day01_input1.txt"), 2113135);
}

TEST(day01, example2)
{
    EXPECT_EQ(solution2("day01_example1.txt"), 31);
}

TEST(day01, input2)
{
    EXPECT_EQ(solution2("day01_input1.txt"), 19097157);
}