//
// Created by kathy on 25.02.25.
//

#ifndef TOPSORT_INSTANCE_GENERATOR_HPP
#define TOPSORT_INSTANCE_GENERATOR_HPP
#include <graphgenerator.hpp>
#include <io.hpp>
#include <filesystem>
inline bool tinyTopsortInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/topsort/tiny");
    for (int i = 1; i < 2; ++i)
    {
        path.append("data/topsort/tiny/TinyValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidTopSortInstance(10, 20, i);
        instancename = "TinyValidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();

        path.append("data/topsort/tiny/TinyInvalid").append(std::to_string(i)).append(".txt");
        edgelist = createInvalidTopSortInstance(10, 20, i);
        instancename = "TinyInvalidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

inline bool smallTopsortInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/topsort/small");

    for (int i = 1; i < 2; ++i)
    {
        path.append("data/topsort/small/SmallValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidTopSortInstance(100, 500, i);
        instancename = "SmallValidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();

        path.append("data/topsort/small/SmallInvalid").append(std::to_string(i)).append(".txt");
        edgelist = createInvalidTopSortInstance(100, 500, i);
        instancename = "SmallInvalidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

inline bool mediumTopsortInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/topsort/medium");
    for (int i = 1; i < 2; ++i)
    {
        path.append("data/topsort/medium/MediumValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidTopSortInstance(10000, 100000, i);
        instancename = "MediumValidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();

        path.append("data/topsort/medium/MediumInvalid").append(std::to_string(i)).append(".txt");
        edgelist = createInvalidTopSortInstance(10000, 100000, i);
        instancename = "MediumInvalidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

inline bool largeTopsortInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/topsort/large");
    for (int i = 1; i < 6; ++i)
    {
        path.append("data/topsort/large/LargeValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidTopSortInstance(i * 20000, i * 200000, i);
        instancename = "LargeValidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();

        path.append("data/topsort/large/LargeInvalid").append(std::to_string(i)).append(".txt");
        edgelist = createInvalidTopSortInstance(i * 20000, i * 200000, i);
        instancename = "LargeInvalidInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}
inline bool topsortInstanceGenerator()
{
    tinyTopsortInstanceGenerator();
    smallTopsortInstanceGenerator();
    mediumTopsortInstanceGenerator();
    largeTopsortInstanceGenerator();
    return true;
}


#endif //TOPSORT_INSTANCE_GENERATOR_HPP
