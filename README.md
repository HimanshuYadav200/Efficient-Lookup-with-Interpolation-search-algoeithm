# Efficient-Lookup-with-Interpolation-search-algoeithm
Project Overview

This project aims to enhance the efficiency of data lookups by combining the binary search tree features of std::map with the fast search capabilities of interpolation search. The goal is to optimize search performance for both uniformly and non-uniformly distributed datasets, leveraging the strengths of interpolation search in scenarios where data is nearly uniformly distributed.

Key Features:

Hybrid Approach: Combines the binary search tree of std::map with interpolation search for faster lookups.

Performance Measurement: Includes timing measurements for comparing the search performance of the hybrid implementation against std::map's find function.

Data Variance Testing: Evaluates the algorithm on both uniform and non-uniform datasets.

Integration: Designed to replace caching mechanisms with the improved interpolation search logic for potential use in production systems.

Objectives

Optimize lookup speeds by utilizing interpolation search where applicable.

Test and compare the hybrid implementation with std::map.

Provide a theoretical analysis of the performance.

Implement and analyze the iterator design pattern.

Develop a reusable library for interpolation search.

Prerequisites

Languages/Tools: C++, Python, STL.

Knowledge Requirements:

Data Structures: Binary Search Tree, Hash Maps, Vectors.

Search Algorithms: Interpolation Search, Binary Search.

Patterns: Iterator Design Pattern.

Implementation Details

Core Components:

Hybrid Map Structure:

Uses std::map for its self-balancing binary search tree properties.

Augments std::map's search capabilities with interpolation search.

Interpolation Search Logic:

Operates on a flat vector structure.

Assumes near-uniform distribution of data.

Timing and Performance Measurement:

Records search times for both hybrid and standard std::map searches.

Outputs results to CSV files for analysis.

Data Structure Design:

Each key in the hybrid map is associated with a vector of pairs:

struct Data {
    int id;
    std::string description;
};
std::map<int, std::vector<std::pair<int, Data>>> hybrid_map;

Code Structure:

Initialization: Prepares datasets (both uniform and non-uniform).

Search Functions:

Hybrid search combining interpolation and binary search.

Standard search using std::map::find.

Performance Testing: Compares hybrid and standard approaches.

Visualization: Plots search time comparisons.

Results

Uniform data: Significant speedup observed using interpolation search.

Non-uniform data: Performance is comparable to std::map.

CSV and graph outputs for in-depth analysis.
