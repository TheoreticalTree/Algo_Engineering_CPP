//
// Created by kathy on 27.02.25.
//

#ifndef MST_INSTANCE_GENERATOR_HPP
#define MST_INSTANCE_GENERATOR_HPP

#include <graphgenerator.hpp>
#include <io.hpp>
#include <filesystem>
bool tinyMSTInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("../data/mst/tiny");
    for (int i = 1; i < 10; ++i)
    {
        path.append("../data/mst/tiny/TinyValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidMSTInstance(10, 40, 30, i);
        instancename = "TinyInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

bool smallMSTInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("../data/mst/small");

    for (int i = 1; i < 10; ++i)
    {
        path.append("../data/mst/small/SmallValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidMSTInstance(100, 1000, 3000, i);
        instancename = "SmallInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

bool mediumMSTInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("../data/mst/medium");
    for (int i = 1; i < 10; ++i)
    {
        path.append("../data/mst/medium/MediumValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidMSTInstance(10000, 200000,300000, i);
        instancename = "MediumInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}

bool largeMSTInstanceGenerator()
{
    std::string path;
    std::vector<edge> edgelist;
    std::string instancename;

    std::filesystem::create_directory("../data/mst/large");
    for (int i = 1; i < 4; ++i)
    {
        path.append("../data/mst/large/LargeValid").append(std::to_string(i)).append(".txt");
        edgelist = createValidMSTInstance(100000, 2000000, 3000000, i);
        instancename = "LargeInstance";
        instancename.append(std::to_string(i));
        writeEdgeListToDimacsFormat( path, instancename, edgelist);
        path.clear();
        edgelist.clear();
        instancename.clear();
    }
    return true;
}
bool mstInstanceGenerator()
{
    tinyMSTInstanceGenerator();
    smallMSTInstanceGenerator();
    mediumMSTInstanceGenerator();
    largeMSTInstanceGenerator();
    return true;
}


#endif //MST_INSTANCE_GENERATOR_HPP
