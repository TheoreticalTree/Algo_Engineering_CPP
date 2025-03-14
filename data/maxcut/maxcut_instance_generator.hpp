
//
// Created by kathy on 27.02.25.
//

#ifndef MAXCUT_INSTANCE_GENERATOR_HPP
#define MAXCUT_INSTANCE_GENERATOR_HPP

#include <graphgenerator.hpp>
#include <io.hpp>
#include <filesystem>

inline bool tinyMaxCutInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/maxcut/tiny");
    for (int i = 1; i < 2; ++i)
    {
        path.append("data/maxcut/tiny/TinyValid").append(std::to_string(i)).append(".txt");
        edgelist = createMaxCutInstance(10, 40, 200, i);
        instancename = "TinyInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

inline bool smallMaxCutInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/maxcut/small");

    for (int i = 1; i < 2; ++i)
    {
        path.append("data/maxcut/small/SmallValid").append(std::to_string(i)).append(".txt");
        edgelist = createMaxCutInstance(100, 1000, 200, i);
        instancename = "SmallInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

inline bool mediumMaxCutInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/maxcut/medium");
    for (int i = 1; i < 2; ++i)
    {
        path.append("data/maxcut/medium/MediumValid").append(std::to_string(i)).append(".txt");
        edgelist = createMaxCutInstance(10000, 200000,200, i);
        instancename = "MediumInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

inline bool largeMaxCutInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("data/maxcut/large");
    for (int i = 1; i < 6; ++i)
    {
        path.append("data/maxcut/large/LargeValid").append(std::to_string(i)).append(".txt");
        edgelist = createMaxCutInstance(i * 20000, i * 400000, 200, i);
        instancename = "LargeInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

inline bool maxcutInstanceGenerator()
{
    tinyMaxCutInstanceGenerator();
    smallMaxCutInstanceGenerator();
    mediumMaxCutInstanceGenerator();
    largeMaxCutInstanceGenerator();
    return true;
}


#endif //MST_INSTANCE_GENERATOR_HPP
